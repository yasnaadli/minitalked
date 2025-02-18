/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:36:11 by yamohamm          #+#    #+#             */
/*   Updated: 2025/02/18 17:37:14 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"

void	error_message(char *msg)
{
	ft_putstr_fd (msg, 2);
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_putstr_fd("Signal SIGUSR1 received.\n", 1);
	}
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Message received by server.\n", 1);
		exit(EXIT_SUCCESS);
	}
}

static void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		bit++;
		usleep(100);
	}
}

static void	send_message(pid_t server_pid, char *message)
{
	while (*message)
	{
		send_char (server_pid, *message);
		message++;
	}
	send_char (server_pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr_fd ("Usage: ", 1);
		ft_putstr_fd (argv[0], 1);
		ft_putstr_fd (" <server_pid> <message>\n", 1);
		return (1);
	}
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);
	server_pid = ft_atoi(argv[1]);
	send_message (server_pid, argv[2]);
	return (0);
}
