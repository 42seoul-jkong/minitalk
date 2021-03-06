/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 18:07:49 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	pretty_error(char *s)
{
	puterr_safe(ANSI_ESC_BOLD);
	puterr_safe("minitalk");
	puterr_safe(": ");
	puterr_safe(ANSI_ESC_FG_RED);
	puterr_safe("error: ");
	puterr_safe(ANSI_ESC_FG_DEFAULT);
	puterr_safe(ANSI_ESC_NORMAL);
	puterr_safe(s);
	puterr_safe("\n");
}
