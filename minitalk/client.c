/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbilla <ahbilla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:44:32 by ahbilla           #+#    #+#             */
/*   Updated: 2024/12/28 22:44:22 by ahbilla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	void	send_bit(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(400);
		i--;
	}
}

int	my_error(void)
{
	write(1, "Usage: ./client <Server PID> <message>\n", 39);
	return (1);
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;

	if (argc != 3)
		return (my_error());
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 0 || !is_numeric(argv[1]))
	{
		write(1, "./client <PID must be a positive number> <message>\n", 51);
		return (1);
	}
	if (kill(server_pid, 0) == -1)
	{
		write(1, "No Server is running with this PID", 34);
		return (1);
	}
	message = argv[2];
	while (*message)
	{
		send_bit(server_pid, *message);
		message++;
	}
	send_bit(server_pid, '\0');
	return (0);
}
