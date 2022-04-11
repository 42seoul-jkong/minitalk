/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_app.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 21:37:07 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	client;

static void handler(int sig, siginfo_t *info, void *ucontext)
{
	int expect_sig;

	(void)ucontext;
	if (info->si_pid != client.pid)
		return ;
	if (!(client.buf->sequence & 1))
		expect_sig = SIGUSR1;
	else
		expect_sig = SIGUSR2;
	if (sig == expect_sig)
		client.buf->sequence++;
	client.fail = 0;
}

static int	updater(void)
{
	int	sig;

	if (client.fail > TIMEOUT_MAX_COUNT)
	{
		pretty_error("timed out");
		exit(EXIT_FAILURE);
	}
	if (client.buf->sequence < client.buf->limit)
	{
		if (!bit_buf_get_bit(client.buf))
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		client.fail++;
		kill(client.pid, sig);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int			res_atoi;

	if (argc != 3 || !ft_try_atoi(argv[1], &res_atoi))
	{
		pretty_error("wrong usage");
		return (EXIT_FAILURE);
	}
	client.pid = res_atoi;
	client.buf = bit_buf_init();
	client.buf->limit += bit_buf_append(client.buf, argv[2], ft_strlen(argv[2]) + 1);
	client.buf->sequence = 0;
	client.fail = 0;
	signal_bind(&handler);
	signal_listen(&updater);
	return (EXIT_SUCCESS);
}
