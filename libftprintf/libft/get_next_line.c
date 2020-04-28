/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/13 13:13:44 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/28 17:25:31 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_getline(t_params *p, void **read, void **eol)
{
	size_t lenl;

	if (p->curr)
		free(((t_fd *)p->curr->content)->rest);
	if (*eol)
	{
		lenl = ft_memplen(*read, *eol, *p->len);
		*p->line = ft_strnew(lenl);
		if (!*p->line)
			return (0);
		*p->line = ft_memcpy((void *)*p->line, *read, lenl);
		ft_memtrunc(read, lenl + 1, *p->len);
		*p->len -= lenl + 1;
	}
	else if (*p->len != 0)
	{
		*p->line = ft_strnew(*p->len);
		if (!*p->line)
			return (0);
		*p->line = ft_memcpy((void *)*p->line, *read, *p->len);
		ft_memdel(read);
		*p->len = 0;
	}
	return (1);
}

int		ft_managerest(t_params *p, void **read)
{
	t_fd *info;

	if (p->curr && *p->len != 0)
		((t_fd *)p->curr->content)->rest = *read;
	else if (*p->len != 0)
	{
		info = (t_fd *)ft_memalloc(sizeof(t_fd));
		if (!info)
			return (0);
		info->fd = p->fd;
		info->len = *p->len;
		info->rest = *read;
		p->curr = ft_lstnew((t_fd *)info, sizeof(t_fd));
		if (!p->curr)
			return (0);
		free((void *)info);
		ft_lstadd(p->data, p->curr);
	}
	else
	{
		if (p->curr)
			ft_lsteremove(p->data, p->curr);
		ft_memdel(read);
	}
	return (1);
}

int		ft_read(t_params *p)
{
	void	*eol;
	char	buffer[BUFF_SZ];
	t_list	*node;
	void	*fullread;

	eol = ft_memchr(((t_list *)*p->buff)->content, '\n', *p->len);
	while (!eol && p->nbr != 0)
	{
		p->nbr = read(p->fd, &buffer, BUFF_SZ);
		if (p->nbr < 0)
			return (-1);
		eol = ft_memchr(buffer, '\n', p->nbr);
		node = ft_lstnew(buffer, p->nbr);
		ft_lstadd(p->buff, node);
		ft_bzero(buffer, BUFF_SZ);
		*p->len += p->nbr;
	}
	ft_lsttoarr(p->buff, &fullread, *p->len);
	ft_lstedel(p->buff);
	eol = ft_memchr(fullread, '\n', *p->len);
	if (!ft_getline(p, &fullread, &eol) || !ft_managerest(p, &fullread))
		return (-1);
	if (p->nbr <= 0 && !p->curr && !*p->line)
		return (0);
	return (1);
}

void	ft_initialize(t_params *p, int fd, t_list **curr, t_list **data)
{
	p->data = data;
	p->fd = fd;
	p->nbr = -1;
	*curr = *data;
	while (*curr)
	{
		if (((t_fd *)(*curr)->content)->fd == fd)
			break ;
		*curr = (*curr)->next;
	}
	p->curr = *curr;
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*data;
	t_params		p;
	t_list			*curr;
	t_list			*buff;
	size_t			len;

	if (BUFF_SZ <= 0 || !line || fd < 0)
		return (-1);
	*line = NULL;
	len = 0;
	ft_initialize(&p, fd, &curr, &data);
	if (curr)
	{
		buff = ft_lstnew(((t_fd *)curr->content)->rest,
((t_fd *)curr->content)->len);
		p.len = &((t_fd *)curr->content)->len;
	}
	else
	{
		buff = ft_lstnew(NULL, 0);
		p.len = &len;
	}
	p.buff = &buff;
	p.line = line;
	return (ft_read(&p));
}
