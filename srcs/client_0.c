/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:48:02 by lgerard           #+#    #+#             */
/*   Updated: 2025/08/31 20:40:02 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile sig_atomic_t	g_sig = 0;

void	handlerc(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGUSR1)
		g_sig = 1;
	else if (sig == SIGUSR2)
		g_sig = 2;
}

size_t	waitfinal(size_t i, int pid)
{
	ft_printf("Transmission conformity: ");
	i = send_bit(0, pid, 0);
	if (i != 0)
		return (i);
	ft_printf("Ok\nEnd of synchronisation\n");
	return (0);
}

size_t	send_bit(int bit, int pid, size_t i)
{
	g_sig = 0;
	if (bit == 1)
	{
		if (kill(pid, SIGUSR1) != 0)
			return (5);
	}
	else
	{
		if (kill(pid, SIGUSR2) != 0)
			return (5);
	}
	usleep(SYNC_TIME);
	while (g_sig == 0 && i < WAIT_LIMIT)
		i++;
	if (g_sig == 1)
	{
		g_sig = 0;
		return (0);
	}
	else
	{
		return (test_g_sig(g_sig, 1));
	}
}

size_t	initiate(int pid, char *str, size_t i, unsigned int check)
{
	size_t	len;

	len = ft_strlen(str);
	if (kill(pid, 0) != 0)
		return (7);
	if (kill(pid, SIGUSR1) != 0)
		return (5);
	pause();
	while ((g_sig == 0 && i < WAIT_LIMIT) || g_sig == 2)
		i++;
	if (g_sig != 1)
		return (test_g_sig(g_sig, 0));
	ft_printf("Syncronisation with server PID %d : Ok\n", pid);
	i = send_len(pid, len, 0, 0);
	if (i != 0)
		return (i);
	i = send_str(pid, str, len, 0);
	if (i != 0)
		return (i);
	i = send_check(pid, 0, check);
	if (i != 0)
		return (i);
	i = waitfinal(0, pid);
	if (i != 0)
		return (i);
	return (0);
}

void	deb_error(void)
{
	ft_printf("Error abort\nLe client doit avoir 2 arguments : \n");
	ft_printf("./client <PID serveur> \"chaine a envoyer au serveur\"\n");
}