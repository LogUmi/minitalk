/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:19:54 by lgerard           #+#    #+#             */
/*   Updated: 2025/08/31 20:40:54 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	main(void)
{
	struct sigaction	sa;
	struct sigaction	sb;
	int					i;

	i = 0;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	ft_printf ("Serveur PID: %d\n\nWaiting signal ...\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sb.sa_flags = SA_SIGINFO | SA_RESTART;
	sb.sa_sigaction = free_if_needed;
	sigemptyset(&sb.sa_mask);
	sigaction(SIGINT, &sb, NULL);
	while (i++ == 0)
		i--;
	return (0);
}
