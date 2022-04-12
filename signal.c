/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:42:01 by jkong             #+#    #+#             */
/*   Updated: 2022/04/12 17:33:18 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_bind(t_sighandler handler)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

void	signal_listen(t_appupdater updater)
{
	while (updater())
		usleep(TIMEOUT_IN_MICROS);
}

void	signal_connect(t_appupdater updater)
{
	while (updater())
		pause();
}
