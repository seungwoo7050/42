/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:22:01 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 20:19:57 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_stack{
	int				val;
	struct s_stack	*above;
	struct s_stack	*below;
}	t_stack;

typedef struct s_info{
	int		*arr;
	int		size;
	t_stack	*a_head;
	t_stack	*a_tail;
	t_stack	*b_head;
	t_stack	*b_tail;
}	t_info;

// parse.c
void	set_info(t_info **info);
void	cal_size(t_info **info, char **av);
void	check_sort_dup(t_info **info);
void	check_space(char **av);
void	inspect_av(char **av, t_info **info);
// utils.c: atoi, 
int		ft_atoi(const char *s);
// split.c
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	split_free(char **dest, int j);
int		split_iteration(char **dest, const char *s, char c, int count);
char	**ft_split(char const *s, char c);
// error.c
void	print_error(void);
//sawp.c
void	sa(t_info **info);
void	sb(t_info **info);
void	ss(t_info **info);
//push.c
void	pa(t_info **info);
void	pb(t_info **info);
//rotate.c
void	ra(t_info	**info);
void	rb(t_info	**info);
void	rr(t_info	**info);
//reverse.c
void	rra(t_info	**info);
void	rrb(t_info	**info);
void	rrr(t_info	**info);
//sort.c
void	search_val_a(t_info **info, int val);
void	b_to_a(t_info **info, int val);
void	a_to_b(t_info **info, int chunk, int size);
void	sort_start(t_info **info);
//cal.c
int		cal_chunk(t_info **info);
int		cal_abs_a(t_stack *cur, int val);
int		cal_abs_b(t_stack *cur, int val);
//small.c
void	small_3(t_info **info);
void	small_4(t_info **info);
void	small_5(t_info **info);
void	rotate_5(t_info **info, int cnt_ra, int cnt_rra);

#endif