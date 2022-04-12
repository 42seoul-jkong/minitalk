/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_app.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/12 13:14:26 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	*accept_client(pid_t pid);
int			foreach_client(int (*f)(t_client *));

static void	_handler(int sig, siginfo_t *info, void *ucontext)
{
	t_client	*client;
	int			bit_val;

	(void)ucontext;
	client = accept_client(info->si_pid);
	if (!client)
		return ;
	if (sig == SIGUSR1)
		bit_val = 0;
	else if (sig == SIGUSR2)
		bit_val = 1;
	else
		return ;
	bit_buf_put_bit(client->buf, bit_val);
	client->fail = -1;
}

static int	_update_client(t_client *client)
{
	int	sig;
	int	clear;

	clear = 0;
	if (client->fail < 0)
	{
		client->buf->sequence++;
		if (bit_buf_terminated(client->buf, '\0'))
			clear = 1;
	}
	else if (client->fail >= TIMEOUT_MAX_COUNT)
		clear = 2;
	if (client->buf->sequence & 1)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	kill(client->pid, sig);
	if (clear)
	{
		if (clear == 1)
		{
			client->buf->limit = client->buf->sequence;
			write_safe(STDOUT_FILENO, client->buf->buf, (client->buf->limit + BIT_COUNT - 1) / BIT_COUNT);
		}
		return (0);
	}
	client->fail++;
	return (1);
}

static int	_updater(void)
{
	foreach_client(&_update_client);
	return (1);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	putstr_safe("PID: ");
	putnbr_safe(pid);
	putstr_safe("\n");
	signal_bind(&_handler);
	signal_listen(&_updater);
	return (EXIT_SUCCESS);
}
