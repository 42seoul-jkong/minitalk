/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_app.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/12 17:48:56 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	*accept_client(pid_t pid);
int			foreach_client(t_client_error (*f)(t_client *));

static int	_try_update_signal(t_client *client)
{
	int	sig;
	int	bit_val;

	sig = client->sig;
	client->sig = 0;
	if (sig == SIGUSR1)
		bit_val = 0;
	else if (sig == SIGUSR2)
		bit_val = 1;
	else
		return (0);
	bit_buf_put_bit(client->buf, bit_val);
	return (1);
}

static t_client_error	_update_client(t_client *client)
{
	int				sig;
	t_client_error	error;

	error = CE_AGAIN;
	if (_try_update_signal(client))
	{
		client->fail = 0;
		client->buf->sequence++;
		if (bit_buf_terminated(client->buf, '\0'))
			error = CE_OK;
		sig = SIGUSR2;
	}
	else
	{
		client->fail++;
		if (client->fail >= TIMEOUT_MAX_COUNT)
			error = CE_TIMEOUT;
		sig = SIGUSR1;
	}
	if (kill(client->pid, sig) == -1)
		error = CE_NOSUCHPROC;
	return (error);
}

static void	_handler(int sig, siginfo_t *info, void *ucontext)
{
	t_client	*client;

	(void)ucontext;
	client = accept_client(info->si_pid);
	if (!client)
		return ;
	client->sig = sig;
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
