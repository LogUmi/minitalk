/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:30:02 by lgerard           #+#    #+#             */
/*   Updated: 2025/08/31 20:40:13 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

size_t	send_str(int pid, char *str, size_t len, size_t i)
{
	int		bit;
	size_t	j;

	j = 0;
	ft_printf("Sending chain: ");
	while (j <= len)
	{
		bit = 0;
		while (bit < CHAR_BIT)
		{
			if (str[j] & 1 << bit)
				i = 1;
			else
				i = 0;
			i = send_bit(i, pid, 0);
			if (i != 0)
				return (i);
			bit++;
		}
		j++;
	}
	ft_printf("Ok\n");
	return (0);
}

size_t	send_check(int pid, int bit,  unsigned int check)
{
	size_t	i;

	i = 0;
	ft_printf("Sending checksum %u: ", check);
	while (bit < (int)(CHAR_BIT * sizeof(unsigned int)))
	{
		if (check & 1 << bit)
			i = 1;
		else
			i = 0;
		i = send_bit(i, pid, 0);
		if (i != 0)
			return (i);
		bit++;
	}
	ft_printf("Ok\n");
	return (0);
}

size_t	send_len(int pid, size_t len, int bit, size_t i)
{
	ft_printf("Sending lengh of chain %d + 1: ", len);
	while (bit < (int)(CHAR_BIT * sizeof(size_t)))
	{
		if (len & 1 << bit)
			i = 1;
		else
			i = 0;
		i = send_bit(i, pid, 0);
		if (i != 0)
			return (i);
		bit++;
	}
	ft_printf("Ok\n");
	return (0);
}

int	test_g_sig(int sig, size_t i)
{
	if (sig == 2 && i == 1)
		return (3);
	if (sig == 2 && i == 0)
		return (2);
	if (sig == 2 && i == 2)
		return (8);
	if (sig == 0)
		return (4);
	return (6);
}

void	error_msg(size_t i)
{
	if (i == 1)
		ft_printf("Error abort\nNo response from server\n");
	if (i == 2)
		ft_printf("Error abort\nServer is busy\n");
	if (i == 3)
		ft_printf("Error abort\nServer memory allocation issue\n");
	if (i == 4)
		ft_printf("Error abort\nSynchronisation issue (WAIT_LIMIT reach)\n");
	if (i == 5)
		ft_printf("Error abort\nBit transmission issue\n");
	if (i == 6)
		ft_printf("Error abort\nUnknown error\n");
	if (i == 7)
		ft_printf("Error abort\nServer does not exist or unreachable\n");
	if (i == 8)
		ft_printf("Error abort\nTransmited chain corrupted\n");
}
