/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.h									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: seungwok <seungwok@student.42seoul.kr>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/06/26 21:18:06 by seungwok		  #+#	#+#			 */
/*   Updated: 2023/07/07 16:29:32 by seungwok		 ###   ########seoul.kr  */
/*																			*/
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*free_arr(char **arr_line);
char	*setline(char *arr_line);
char	*makeline(char *arr_line);
char	*readline(char *arr_line, int fd);
char	*get_next_line(int fd);

#endif

// 헤더파일의 기본적인 양식

// #ifndef HEADER_H
// # define HEADER_H

// 표준 라이브러리 헤더파일

// 매크로 정의

// 사용자 struct, type 정의

// 전역 변수 선언

// 함수 선언

// #endif