/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:42:50 by lgerard           #+#    #+#             */
/*   Updated: 2025/08/31 20:40:44 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile char	*g_str = NULL;

void	state2_0(int *bit, int i, int sig, int pid)
{
	if ((*bit) < CHAR_BIT)
	{
		if (sig == SIGUSR1)
		{
			g_str[i] |= (1 << (*bit)++);
			kill(pid, SIGUSR1);
		}
		else if (sig == SIGUSR2)
		{
			g_str[i] &= ~(1 << (*bit)++);
			kill(pid, SIGUSR1);
		}
	}
}

size_t	state2(int sig, int pid, int len)
{
	static int		bit = 0;
	static int		i = 0;

	if (g_str == NULL && bit == 0 && i == 0)
	{
		g_str = (char *)ft_calloc(sizeof(char), len);
		if (!g_str)
		{
			kill(pid, SIGUSR2);
			return (0);
		}
	}
	state2_0(&bit, i, sig, pid);
	if (bit == CHAR_BIT)
	{
		bit = 0;
		len -= 1;
		if (g_str[i] == 0 && len == 0)
		{
			i = 0;
			return (0);
		}
		i += 1;
	}
	return (len);
}

void	handler_1(int sig, int *pid, int *state, size_t *len)
{
	if (sig == SIGUSR2)
	{
		ft_printf("Data integrity: ");
		if ((unsigned int)(*len) == checksum((char *)g_str))
		{
			kill((*pid), SIGUSR1);
			ft_printf("Ok\nEnd of synchronisation\n%s\n", g_str);
		}
		else
		{
			kill((*pid), SIGUSR2);
			ft_printf("Corrupted\nEnd of synchronisation\n");
		}
		(*state) = 0;
		(*pid) = 0;
		(*len) = 0;
		free((void *)g_str);
		g_str = NULL;
		ft_printf("Waiting signal ...\n");
	}
	else
		kill((*pid), SIGUSR2);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int		pid = 0;
	static int		state = 0;
	static size_t	len = 0;

	(void)context;
	if (info->si_pid == 0 || (sig != SIGUSR1 && sig != SIGUSR2))
	{
		ft_printf("Unrequested request PID 0\n");
		return ;
	}
	if (pid == 0 && info->si_pid != 0 && sig == SIGUSR1)
		pid = state0(info->si_pid, &state);
	else if (pid != 0 && pid != info->si_pid)
	{	
		kill(info->si_pid, SIGUSR2);
		ft_printf("Denied request from client PID %d\n", info->si_pid);
	}
	else if (pid == info->si_pid)
		handler_0(sig, &pid, &state, &len);
}

void	free_if_needed(int sig, siginfo_t *info, void *context)
{
	struct sigaction	sa;

	(void)sig;
	(void)info;
	(void)context;
	if (g_str != NULL)
		free((void *)g_str);
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("End of session\n");
	exit (0);
}
