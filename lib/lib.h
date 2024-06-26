/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lib.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 17:08:12 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:24:25 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft/get_next_line.h"
# include "libft/libft.h"
# include "hash/includes/hashing.h"

int					ft_vfprintf(FILE *stream, const char *format, va_list ap);
int					ft_fprintf(FILE *stream, const char *format, ...);

int					ft_vdprintf(int fd, const char *format, va_list ap);
int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_vprintf(const char *format, va_list ap);

int					ft_vasprintf(char **ret, const char *format, va_list ap);
int					ft_asprintf(char **ret, const char *format, ...);

int					ft_vsnprintf(char *str, size_t size, const char *format,
						va_list ap);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_snprintf(char *str, size_t size,
						const char *format, ...);
int					ft_vsprintf(char *str, const char *format, va_list ap);

int					get_next_line(const int fd, char **line);

void				ft_del(void *content, size_t size);
void				ft_putchar(int c);
void				ft_putstr(char const *str);
void				*ft_memset(void *arr, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_mempcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strnlen(const char *s, size_t max);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_atoi(const char *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strdup(const char *s1);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s1, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
int					ft_lstaddend(t_list **begin_list, void const *s, size_t n);
void				ft_lstadd(t_list **alst, t_list *nw);
int					ft_lstlen(t_list **alst);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstpop(t_list **lst);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_error(char *str, int n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_itoabase(int n, int base);
int					ft_atoibase(char *s, int base);
void				ft_swap(int *a, int *b);
int					ft_sqrt(int n);
void				ft_rot(char *s, int rot);
void				ft_rotr(char *s, int rot);
int					ft_pow(int base, int pow);
void				ft_strtolower(char *s);
void				ft_strtoupper(char *s);
int					ft_memplen(void *src, void *tofind, size_t len);
void				ft_lsteremove(t_list **lst, t_list *curr);
int					ft_memtrunc(void **orig, size_t start, size_t len);
int					ft_lsttoarr(t_list **lst, void **arr, size_t arrlen);
void				ft_lstedel(t_list **alst);
int					ft_memrealloc(void **ptr, size_t prev_size, size_t size);

#endif
