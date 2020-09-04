/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 12:51:07 by rklein            #+#    #+#             */
/*   Updated: 2020/09/01 16:44:08 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


static void	ft_cursor(t_sh *sh, int len)
{
	int	row;
	int	cursor;

	row = len / sh->ws.ws_col;
	tputs(tgetstr("cr", NULL), 1, ft_putint);
	while (row--)
		tputs(tgetstr("up", NULL), 1, ft_putint);
	cursor = -1;
	while (++cursor < sh->in->index + sh->in->prompt_size)
	{
		if (cursor / sh->ws.ws_col && cursor % sh->ws.ws_col == 0)
		{
		   tputs(tgetstr("cr", NULL), 1, ft_putint);
		   tputs(tgetstr("do", NULL), 1, ft_putint);
		}
		tputs(tgetstr("nd", NULL), 1, ft_putint);
	}
	if (cursor / sh->ws.ws_col && cursor % sh->ws.ws_col == 0)
	{
	   tputs(tgetstr("cr", NULL), 1, ft_putint);
	   tputs(tgetstr("do", NULL), 1, ft_putint);
	}
}

void	ft_reprint(t_sh *sh)
{
	int	len;
	int	row;

	len = sh->in->prompt_size + ft_strlen(sh->in->buffer) - 1;
	row = sh->in->line;
	tputs(tgetstr("cr", NULL), 1, ft_putint);
	while (row-- /*&& len > sh->ws.ws_col * row*/)
		tputs(tgetstr("up", NULL), 1, ft_putint);
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	ft_putstr_fd(sh->in->prompt, STDOUT_FILENO);	
	ft_putstr_fd(sh->in->buffer, STDOUT_FILENO);
	ft_cursor(sh, len);
	sh->in->line = (sh->in->index + sh->in->prompt_size) / sh->ws.ws_col;
}

