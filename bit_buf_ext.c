/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_buf_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:50:50 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 21:27:29 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	bit_buf_append(t_bit_buf *p, const void *buf, size_t nbyte)
{
	size_t	nbit;
	size_t	i;
	int		j;

	nbit = 0;
	i = 0;
	while (i < nbyte)
	{
		j = 0;
		while (j < BIT_COUNT)
		{
			bit_buf_put_bit(p, (((const unsigned char *)buf)[i] >> j) & 1);
			p->sequence++;
			j++;
			nbit++;
		}
		i++;
	}
	return (nbit);
}

int	bit_buf_terminate(t_bit_buf *p, int null)
{
	size_t	offset;
	int		bit_index;
	int		byte;

	if (p->sequence >= BIT_COUNT && p->sequence % BIT_COUNT == 0)
	{
		offset = (p->sequence - BIT_COUNT) / BITSET_MAX;
		bit_index = (p->sequence - BIT_COUNT) % BITSET_MAX;
		byte = (p->buf[offset] >> bit_index) & 0xFF;
		return ((unsigned char)byte == (unsigned char)null);
	}
	return (0);
}
