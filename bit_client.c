/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:16:30 by jkong             #+#    #+#             */
/*   Updated: 2022/04/12 01:15:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	*_client_find(t_client **head, pid_t pid)
{
	t_client	*latest;
	t_client	*unlink;

	latest = NULL;
	unlink = *head;
	while (unlink)
	{
		if (unlink->pid == pid)
		{
			if (latest)
				latest->next = unlink->next;
			else
				*head = unlink->next;
			unlink->next = NULL;
			break ;
		}
		latest = unlink;
		unlink = unlink->next;
	}
	return (unlink);
}

t_client	*client_operation(t_client_operation op, pid_t arg)
{
	static t_client	*list;
	t_client		*result;

	if (op == HEAD)
		return (list);
	result = _client_find(&list, arg);
	if (op == PUT && !result)
	{
		result = malloc_safe(sizeof(t_client));
		ft_memset(result, 0, sizeof(*result));
		result->buf = bit_buf_init();
		result->pid = arg;
	}
	if (op == DELETE && result)
	{
		free(result->buf);
		free(result);
	}
	else if (result)
	{
		result->next = list;
		list = result;
	}
	return (result);
}
