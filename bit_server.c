/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:24:46 by jkong             #+#    #+#             */
/*   Updated: 2022/04/12 13:14:48 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	*accept_client(pid_t pid)
{
	if (pid == 0)
		return (client_operation(HEAD, pid));
	return (client_operation(PUT, pid));
}

void	close_client(t_client *client, int reason)
{
	(void)client, (void)reason;
}

int	foreach_client(int (*f)(t_client *))
{
	int			removed;
	t_client	*client;
	t_client	*next;
	int			reason;

	removed = 0;
	client = client_operation(HEAD, 0);
	while (client)
	{
		next = client->next;
		reason = f(client);
		if (f(client))
		{
			close_client(client, reason);
			removed++;
		}
		client = next;
	}
	return (removed);
}
