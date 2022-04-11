/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_app.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 21:36:55 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	client;

static void handler(int sig, siginfo_t *info, void *ucontext)
{
	int bit_val;

	(void)ucontext;
	if (info->si_pid != client.pid)
	{
		//accept
		client.pid = info->si_pid;
	}
	if (sig == SIGUSR1)
		bit_val = 0;
	else if (sig == SIGUSR2)
		bit_val = 1;
	else
		return ;
	bit_buf_put_bit(client.buf, bit_val);
	client.fail = -1;
}

static int	updater(void)
{
	int	sig;

	if (client.fail < 0)
	{
		client.buf->sequence++;
		if (bit_buf_terminate(client.buf, '\0'))
		{
			//clear
			client.buf->limit = client.buf->sequence;
			write_safe(STDOUT_FILENO, client.buf->buf, (client.buf->limit + BIT_COUNT - 1) / BIT_COUNT);
			return (0);
		}
	}
	if (client.fail > TIMEOUT_MAX_COUNT)
	{
		//timeout
	}
	if (client.buf->sequence & 1)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	kill(client.pid, sig);
	client.fail++;
	return (1);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	putstr_safe("PID: ");
	putnbr_safe(pid);
	putstr_safe("\n");
	client.pid = 133221333;
	client.buf = bit_buf_init();
	client.fail = 0;
	signal_bind(&handler);
	signal_listen(&updater);
	return (EXIT_SUCCESS);
}
