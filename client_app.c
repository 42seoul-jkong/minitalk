/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_app.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/12 12:19:10 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	*_get_client(void)
{
	return (client_operation(HEAD, 0));
}

static t_client	*_connect_client(pid_t pid, char *str)
{
	const size_t	len = ft_strlen(str) + 1;
	t_client		*client;

	client = client_operation(PUT, pid);
	free(client->buf);
	client->buf = bit_buf_init();
	if (str)
	{
		client->buf->limit += bit_buf_append(client->buf, str, len);
		client->buf->sequence = 0;
	}
	client->fail = 0;
	return (client);
}

static void	_handler(int sig, siginfo_t *info, void *ucontext)
{
	t_client *const	client = _get_client();
	int				expect_sig;

	(void)ucontext;
	if (info->si_pid != client->pid)
		return ;
	if (!(client->buf->sequence & 1))
		expect_sig = SIGUSR1;
	else
		expect_sig = SIGUSR2;
	if (sig == expect_sig)
		client->buf->sequence++;
	client->fail = 0;
}

static int	_updater(void)
{
	t_client *const	client = _get_client();
	int				sig;

	if (client->fail >= TIMEOUT_MAX_COUNT)
	{
		pretty_error("timed out");
		exit(EXIT_FAILURE);
	}
	if (client->buf->sequence < client->buf->limit)
	{
		if (!bit_buf_get_bit(client->buf))
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		client->fail++;
		kill(client->pid, sig);
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
	_connect_client(res_atoi, argv[2]);
	signal_bind(&_handler);
	signal_listen(&_updater);
	return (EXIT_SUCCESS);
}
