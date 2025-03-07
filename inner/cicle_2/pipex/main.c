/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:48:55 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/15 11:13:18 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_separation(char **argv, char **envp, t_pipex p);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc != 5)
		print_error("error in argc: ");
	if (pipe(p.fd) == -1)
		print_error("error in pipe: ");
	p.cmd_path = find_path(envp);
	if (!p.cmd_path)
		print_error("error in split/path:");
	process_separation(argv, envp, p);
	return (0);
}

void	process_separation(char **argv, char **envp, t_pipex p)
{
	p.pid[0] = fork();
	if (p.pid[0] == -1)
		print_error("error in fork: ");
	else if (p.pid[0] == 0)
		child_process_1(argv, envp, p);
	else
	{
		p.pid[1] = fork();
		if (p.pid[1] == -1)
			print_error("error in fork: ");
		else if (p.pid[1] == 0)
			child_process_2(argv, envp, p);
		else
			parent_process(p);
	}
}
