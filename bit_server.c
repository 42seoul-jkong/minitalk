/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:24:46 by jkong             #+#    #+#             */
/*   Updated: 2022/04/12 17:52:22 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	*accept_client(pid_t pid)
{
	if (pid == 0)
		return (client_operation(HEAD, pid));
	return (client_operation(PUT, pid));
}

void	close_client(t_client *client, t_client_error reason)
{
	if (reason == CE_OK)
	{
		client->buf->limit = client->buf->sequence;
		putnbr_safe(client->pid);
		putstr_safe(": \"");
		putstr_safe((char *)client->buf->buf);
		putstr_safe("\"\n");
	}
	else
	{
		putnbr_safe(client->pid);
		putstr_safe(": ErrorReason=");
		putnbr_safe(reason);
		putstr_safe(";\n");
	}
	client_operation(DELETE, client->pid);
}

int	foreach_client(t_client_error (*f)(t_client *))
{
	int				removed;
	t_client		*client;
	t_client		*next;
	t_client_error	reason;

	removed = 0;
	client = client_operation(HEAD, 0);
	while (client)
	{
		next = client->next;
		reason = f(client);
		if (reason != CE_AGAIN)
		{
			close_client(client, reason);
			removed++;
		}
		client = next;
	}
	return (removed);
}
