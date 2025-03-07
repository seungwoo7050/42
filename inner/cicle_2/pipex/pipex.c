/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:50:37 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/15 10:58:00 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_1(char **argv, char **envp, t_pipex p);
void	child_process_2(char	**argv, char **envp, t_pipex p);
char	**find_path(char **envp);
char	*set_cmd(char **path, char *cmd);

void	parent_process(t_pipex p)
{
	close(p.fd[0]);
	close(p.fd[1]);
	waitpid(p.pid[0], NULL, 0);
	waitpid(p.pid[1], NULL, 0);
}

void	child_process_1(char **argv, char **envp, t_pipex p)
{
	p.infile = open(argv[1], O_RDONLY);
	if (p.infile == -1)
		print_error("error in open: ");
	close(p.fd[0]);
	dup2(p.fd[1], 1);
	close(p.fd[1]);
	dup2(p.infile, 0);
	close(p.infile);
	p.cmd_option = ft_split(argv[2], ' ');
	if (!p.cmd_option)
		print_error("error in split/cmd: ");
	p.cmd = set_cmd(p.cmd_path, p.cmd_option[0]);
	if (!p.cmd)
		print_error("error in cmd: ");
	if (execve(p.cmd, p.cmd_option, envp) == -1)
		print_error("error in execve: ");
}

void	child_process_2(char	**argv, char **envp, t_pipex p)
{
	p.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (p.outfile == -1)
		print_error("error in open: ");
	close(p.fd[1]);
	dup2(p.fd[0], 0);
	dup2(p.outfile, 1);
	close(p.outfile);
	p.cmd_option = ft_split(argv[3], ' ');
	if (!p.cmd_option)
		print_error("error in split/cmd: ");
	p.cmd = set_cmd(p.cmd_path, p.cmd_option[0]);
	if (!p.cmd)
		print_error("error in cmd: ");
	if (execve(p.cmd, p.cmd_option, envp) == -1)
		print_error("error in execve: ");
}

char	**find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	*envp += 5;
	return (ft_split(*envp, ':'));
}

char	*set_cmd(char **path, char *cmd)
{
	char	*cmd_path;
	char	*tmp;

	while (*path)
	{
		cmd_path = ft_strjoin(*path, "/");
		if (!cmd_path)
			print_error("error in strjoin: ");
		tmp = ft_strjoin(cmd_path, cmd);
		if (!tmp)
		{
			free(cmd_path);
			free(tmp);
			print_error("error in strjoin: ");
		}
		if (access(tmp, X_OK) != -1)
			return (tmp);
		free(tmp);
		path++;
	}
	return (NULL);
}
