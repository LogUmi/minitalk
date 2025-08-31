/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:58:21 by lgerard           #+#    #+#             */
/*   Updated: 2025/08/31 20:40:38 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	state0(int npid, int *state)
{
	(*state) = 1;
	kill(npid, SIGUSR1);
	ft_printf("Synchronisation with client PID %d\n", npid);
	return (npid);
}

size_t	state1(int sig, int pid)
{
	static int	len = 0;
	static int	bit = 0;

	if (bit >= (int)(CHAR_BIT * sizeof(size_t)) || bit == 0)
	{
		len = 0;
		bit = 0;
		ft_printf("Receiving lengh of chain ...\n");
	}
	if (bit < (int)(CHAR_BIT * sizeof(size_t)))
	{
		if (sig == SIGUSR1)
		{
			len |= (1 << bit++);
			kill(pid, SIGUSR1);
		}
		else if (sig == SIGUSR2)
		{
			len &= ~(1 << bit++);
			kill(pid, SIGUSR1);
		}
	}
	if (bit >= (int)(CHAR_BIT * sizeof(size_t)))
		return (len + 1);
	return (0);
}

unsigned int	state3(int sig, int pid)
{
	static unsigned int	check = 0;
	static int			bit = 0;

	if (bit == CHAR_BIT * sizeof(unsigned int) || bit == 0)
	{
		check = 0;
		bit = 0;
	}
	if (bit < (int)(CHAR_BIT * sizeof(unsigned int)))
	{
		if (sig == SIGUSR1)
		{
			check |= (1 << bit++);
			kill(pid, SIGUSR1);
		}
		else if (sig == SIGUSR2)
		{
			check &= ~(1 << bit++);
			kill(pid, SIGUSR1);
		}
	}
	if ((sig == SIGUSR1 || sig == SIGUSR2) && bit == 32)
		return (check);
	return (0);
}

void	handler_0(int sig, int *pid, int *state, size_t *len)
{
	if ((*state) == 1)
	{
		(*len) = state1(sig, (*pid));
		if ((*len) != 0)
		{
			(*state) = 2;
			ft_printf("Receiving %d character(s) ...\n", (*len));
		}
	}
	else if ((*state) == 2)
	{
		(*len) = state2(sig, (*pid), (*len));
		if ((*len) == 0)
		{
			(*state) = 3;
			ft_printf("receiving checksum ...\n");
		}
	}
	else if ((*state) == 3)
	{
		if((*len) != 0)
			handler_1(sig, pid, state, len);
		else
			(*len) = state3(sig,(*pid));
	}
}
