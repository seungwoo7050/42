/**
 * @file mylibc.h
 * @brief mylibc 라이브러리 헤더 파일
 * 
 * 이 헤더 파일은 mylibc 프로젝트에서 사용되는 함수들과 구조체를 선언합니다.
 */

#ifndef LIBmy_H
#define LIBmy_H

# include <unistd.h>
# include <stdlib.h>

/**
 * @brief 연결 리스트 노드 구조체
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;


/* Libc functions */
int		my_atoi(const char *str);
void	my_bzero(void *s, size_t n);
void	*my_calloc(size_t count, size_t size);
int		my_isalpha(int c);
int		my_isdigit(int c);
int		my_isalnum(int c);
int		my_isascii(int c);
int		my_isprint(int c);
int		my_tolower(int c);
int		my_toupper(int c);
size_t	my_strlen(const char *s);
void	*my_memset(void *b, int c, size_t len);
void	*my_memcpy(void *dst, const void *src, size_t n);
void	*my_memmove(void *dst, const void *src, size_t len);
size_t	my_strlcpy(char *dst, const char *src, size_t size);
size_t	my_strlcat(char *dst, const char *src, size_t size);
char	*my_strchr(const char *s, int c);
char	*my_strrchr(const char *s, int c);
int		my_strncmp(const char *s1, const char *s2, size_t n);
void	*my_memchr(const void *b, int c, size_t n);
int		my_memcmp(const void *b1, const void *b2, size_t n);
char	*my_strnstr(const char *haystack, const char *needle, size_t len);
char	*my_strdup(const char *s);
char	*my_substr(char const *s, unsigned int start, size_t len);
char	*my_strjoin(char const *s1, char const *s2);
char	*my_strtrim(char const *s, char const *set);
char	**my_split(char const *s, char c);
char	*my_itoa(int n);
char	*my_strmapi(char const *s, char (*f)(unsigned int, char));
void	my_striteri(char *s, void (*f)(unsigned int, char *));
void	my_putchar_fd(char c, int fd);
void	my_putstr_fd(char *s, int fd);
void	my_putendl_fd(char *s, int fd);
void	my_putnbr_fd(int n, int fd);

/* Linked List functions */
t_list	*my_lstnew(void *content);
void	my_lstadd_front(t_list **alst, t_list *new);
int		my_lstsize(t_list *lst);
t_list	*my_lstlast(t_list *lst);
void	my_lstadd_back(t_list **alst, t_list *new);
void	my_lstdelone(t_list *lst, void (*del)(void *));
void	my_lstclear(t_list **alst, void (*del)(void *));
void	my_lstiter(t_list *lst, void (*f)(void *));
t_list	*my_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));



#endif
