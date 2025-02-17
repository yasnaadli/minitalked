
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:37:03 by yamohamm          #+#    #+#             */
/*   Updated: 2025/02/17 19:43:48 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"

static void sig_action(int sig, siginfo_t *info, void *context)
{ 
    static int bit = 0;
    static char death = 0;
    static pid_t client_corpse = 0;

    (void)context;
    if (!client_corpse)
        client_corpse = info->si_pid;

    death |= (sig == SIGUSR2) << bit;
    bit++;

    if (bit == 8)
    {
        if (death == '\0') 
        {
            ft_putchar_fd('\n', 1);
            kill(client_corpse, SIGUSR2);
            client_corpse = 0; 
        }  
        else 
        {
            ft_putchar_fd(death, 1);
            kill(client_corpse, SIGUSR1);
        }
        bit = 0; 
        death = 0;
    }
    usleep(100);
}   

int main(void)
{
    struct sigaction sa;

    ft_putstr_fd("Server PID: ", 1);
    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);

    sa.sa_sigaction = sig_action;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    
    while (1)
        pause();
    
    return (0);
}