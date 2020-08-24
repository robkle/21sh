/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:43:46 by rklein            #+#    #+#             */
/*   Updated: 2020/08/21 12:40:34 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_line(char **str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_strsub(*str, 0, i);
		tmp = ft_strdup(&((*str)[i + 1]));
		free(*str);
		*str = tmp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

int	ft_return(int rv, char **str, char **line)
{
	if (rv < 0)
		return (-1);
	if (rv == 0 && *str == NULL)
		return (0);
	else
		return (ft_line(str, line));
}

int	get_next_line(const int fd, char **line)
{
	int			rv;
	char		buffer[BUFF_SIZE + 1];
	static char	*str[FD_MAX];
	char		*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((rv = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[rv] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(str[fd], buffer);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	return (ft_return(rv, &str[fd], line));
}
