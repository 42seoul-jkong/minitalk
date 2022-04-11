/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 18:48:55 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	*_required_non_null(void *ptr)
{
	if (!ptr)
		exit(EXIT_FAILURE);
	return (ptr);
}

void	*ft_calloc(size_t count, size_t size);

void	*malloc_safe(size_t size)
{
	return (_required_non_null(malloc(size)));
}

void	*calloc_safe(size_t count, size_t size)
{
	return (_required_non_null(ft_calloc(count, size)));
}
