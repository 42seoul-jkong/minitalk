/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:30:03 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 18:50:19 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((unsigned char *)b)[i++] = (unsigned char)c;
	return (b);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (src != dst)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	final_size = count * size;
	void			*ptr;

	ptr = malloc(final_size);
	if (ptr)
		ft_memset(ptr, 0, final_size);
	return (ptr);
}
