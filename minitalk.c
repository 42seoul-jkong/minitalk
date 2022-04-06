/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/07 02:59:53 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t _strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	_puts(char *s)
{
	write(STDOUT_FILENO, s, _strlen(s));
}

int	main(int argc, char *argv[])
{
	(void)argc;
	_puts(ANSI_ESC_BOLD);
	_puts(argv[0]);
	_puts(": ");
	_puts(ANSI_ESC_FG_RED);
	_puts("fatal error: ");
	_puts(ANSI_ESC_FG_DEFAULT);
	_puts(ANSI_ESC_NORMAL);
	_puts("not implemented\n");
	_puts("minitalk fails\n");
	return (EXIT_FAILURE);
}
