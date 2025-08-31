/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:05:54 by lgerard           #+#    #+#             */
/*   Updated: 2025/08/31 20:50:03 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/includes/libft.h"
# include <signal.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdatomic.h>

# ifndef WAIT_LIMIT
#  define WAIT_LIMIT 10000000000
# endif
# ifndef SYNC_TIME
#  define SYNC_TIME 500
# endif

int				test_pid(char *str);
void			error_msg(size_t i);
int				test_g_sig(int sig, size_t i);
void			handler(int sig, siginfo_t *info, void *context);
void			handler_0(int sig, int *pid, int *state, size_t *len);
void			handler_1(int sig, int *pid, int *state, size_t *len);
void			handlerc(int sig, siginfo_t *info, void *context);
int				state0(int npid, int *state);
size_t			state1(int sig, int pid);
size_t			state2(int sig, int pid, int len);
void			state2_0(int *bit, int i, int sig, int pid);
unsigned int	state3(int sig, int pid);
void			deb_error(void);
size_t			initiate(int pid, char *str, size_t i, unsigned int check);
size_t			send_len(int pid, size_t len, int bit, size_t i);
size_t			send_str(int pid, char *str, size_t len, size_t i);
size_t			send_bit(int bit, int pid, size_t i);
size_t			send_check(int pid, int bit,  unsigned int check);
size_t			waitfinal(size_t i, int pid);
unsigned int	checksum(char *str);
void			free_if_needed(int sig, siginfo_t *info, void *context);
#endif