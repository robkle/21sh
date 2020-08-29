/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 10:24:31 by rklein            #+#    #+#             */
/*   Updated: 2020/08/28 15:46:40 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_reprint(t_sh *sh, int line)
{
	int	i;

	while (line--)
		tputs(tgetstr("up", NULL), 1, ft_putint);
	tputs(tgetstr("cr", NULL), 1, ft_putint);
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	ft_prompt(sh, 1);
	ft_putstr_fd(sh->in->buffer, STDOUT_FILENO);
	i = sh->in->end - sh->in->index;
	while (i--)
		tputs(tgetstr("le", NULL), 1, ft_putint);
}

void		ft_add_char(t_sh *sh, int c)
{
	if (sh->in->index == sh->in->end)
		sh->in->buffer[sh->in->index] = c;
	else
	{
		ft_memmove(sh->in->buffer + sh->in->index + 1, \
		sh->in->buffer + sh->in->index, \
		ft_strlen(sh->in->buffer + sh->in->index));
		sh->in->buffer[sh->in->index] = c;
	}
	if (sh->in->index < sh->in->end && 
			((sh->in->index + sh->in->prompt_size) / sh->ws.ws_col !=  
			(sh->in->end + sh->in->prompt_size) / sh->ws.ws_col ||
			(sh->in->end + sh->in->prompt_size) % sh->ws.ws_col == 0))
	{
		ft_reprint(sh, (sh->in->index + sh->in->prompt_size) / sh->ws.ws_col);
	}
	else
		write(1, &c, 1);
	sh->in->index++;
	sh->in->end++;
}

void		ft_del_char(t_sh *sh)
{
	sh->in->end--;
	if (sh->in->index == sh->in->end)
		sh->in->buffer[sh->in->index] = 0;
	else
	{
		ft_memmove(sh->in->buffer + sh->in->index, \
		sh->in->buffer + sh->in->index + 1, \
		ft_strlen(sh->in->buffer + sh->in->index));
	}
	if (sh->in->end + sh->in->prompt_size < sh->ws.ws_col)
		tputs(tgetstr("dc", NULL), 1, ft_putint);
	else
		ft_reprint(sh, (sh->in->index + sh->in->prompt_size) / sh->ws.ws_col);
}

void		ft_backspace(t_sh *sh)
{
	sh->in->index--;
	sh->in->end--;
	if (sh->in->index == sh->in->end)
		sh->in->buffer[sh->in->index] = 0;
	else
	{
		ft_memmove(sh->in->buffer + sh->in->index, \
		sh->in->buffer + sh->in->index + 1, \
		ft_strlen(sh->in->buffer + sh->in->index));
	}
	if (sh->in->end + 1 + sh->in->prompt_size < sh->ws.ws_col)
	{	
		tputs(tgetstr("le", NULL), 1, ft_putint);
		tputs(tgetstr("dc", NULL), 1, ft_putint);
	}
	else
	{
		if (sh->in->index == sh->in->end)
			ft_reprint(sh, (sh->in->index + sh->in->prompt_size) / sh->ws.ws_col);
		else
		{
			ft_reprint(sh, (sh->in->index + 1 + sh->in->prompt_size) / sh->ws.ws_col);
			if ((sh->in->end + sh->in->prompt_size) % sh->ws.ws_col == 0)
				tputs(tgetstr("nd", NULL), 1, ft_putint); //when the end point is on the last column in insert mode, the cursor does not move right
		}
	}
}
