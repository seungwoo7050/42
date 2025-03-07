/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:34:20 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/13 10:34:20 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd[2];
	pid_t	pid[2];
	int		infile;
	int		outfile;
	char	**cmd_path;
	char	*cmd;
	char	**cmd_option;
}	t_pipex;

void	print_error(char *str);
char	**find_path(char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
int		split_iteration(char **dest, const char *s, char c, int count);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	split_free(char **dest, int j);
void	process_separation(char **argv, char **envp, t_pipex p);
void	child_process_1(char **argv, char **envp, t_pipex p);
void	child_process_2(char	**argv, char **envp, t_pipex p);
void	parent_process(t_pipex p);
char	*set_cmd(char **path, char *cmd);
char	*ft_strjoin(char const *s1, char const *s2);

#endif