/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:36:11 by yamohamm          #+#    #+#             */
/*   Updated: 2025/02/16 19:45:18 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"

void error_message(char *msg)
{
	ft_putstr_fd(msg, 2);
}
void signal_handler(int sig)
{
    if (sig == SIGUSR1)
    {
        }
        else if (sig == SIGUSR2)
        {
            ft_putstr_fd("Message received by server.\n", 1);
            exit(EXIT_SUCCESS);
        }
}

void send_char(pid_t server_pid, char c)
{
	int bit;
	int kill_result;

	bit =7;
	while (bit >=0)
	{
		if((c >> bit) & 1 )
			kill_result = kill( server_pid, SIGUSR2);
		else
			kill_result = kill (server_pid, SIGUSR1);
		if( kill_result == -1)
		{ 
		error_message("ohno. Error:failed to send signal.\n");
		exit(EXIT_FAILURE);
		}
		usleep(500);
		bit--; 
	}
}

void send_message(pid_t server_pid, char *message)
{
    while (*message)
    {
    send_char(server_pid, *message);
    message++; 
    }
    send_char(server_pid, '\0');
}

int main (int argc, char **argv)
{
    {
        pid_t server_pid;
        char *message;
        if (argc != 3 || !argv[2][0])
        {
            error_message("Usage: ./client <server_pid> <message>\n");
            return (1);
        }

        server_pid = ft_atoi(argv[1]);
        if (server_pid <= 0)
        {
            error_message("ohno error, PID is invalid.\n");
            return (1);
        }
        message = argv[2];
        signal(SIGUSR1, signal_handler);
        signal(SIGUSR2, signal_handler);
        send_message(server_pid, message);
        while (1)
            pause();
    
        return (0);
    }
}
