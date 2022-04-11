/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:50:50 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 21:11:42 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_bit_buf	*bit_buf_init(void)
{
	t_bit_buf	*p;

	p = malloc_safe(sizeof(*p));
	p->buf = NULL;
	p->capacity = 0;
	p->sequence = 0;
	p->limit = 0;
	return (p);
}

void	bit_buf_destroy(t_bit_buf *p)
{
	if (!p)
		return ;
	free(p->buf);
	p->buf = NULL;
	p->capacity = 0;
	p->sequence = 0;
	p->limit = 0;
	free(p);
}

void	bit_buf_retain(t_bit_buf *p)
{
	const size_t	capacity = p->capacity;
	size_t			new_capacity;
	t_bit_set		*detach;
	t_bit_set		*attach;

	if (capacity > p->sequence)
		return ;
	new_capacity = capacity + VECTOR_SIZE * BITSET_MAX;
	detach = p->buf;
	attach = calloc_safe(new_capacity / BITSET_MAX, sizeof(t_bit_set));
	ft_memcpy(attach, detach, capacity / BITSET_MAX * sizeof(t_bit_set));
	free(detach);
	p->buf = attach;
	p->capacity = new_capacity;
}

int	bit_buf_get_bit(t_bit_buf *p)
{
	const size_t	offset = p->sequence / BITSET_MAX;
	const int		bit_index = p->sequence % BITSET_MAX;

	return ((p->buf[offset] >> bit_index) & 1);
}

void	bit_buf_put_bit(t_bit_buf *p, int val)
{
	const size_t	offset = p->sequence / BITSET_MAX;
	const int		bit_index = p->sequence % BITSET_MAX;
	t_bit_set		mask;

	mask = 1UL << bit_index;
	bit_buf_retain(p);
	if (val)
		p->buf[offset] |= mask;
	else
		p->buf[offset] &= ~mask;
}
