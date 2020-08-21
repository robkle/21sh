/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 10:24:31 by rklein            #+#    #+#             */
/*   Updated: 2020/08/21 16:37:50 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

static void		ft_arrow_motion(t_sh *sh, int motion)
{
	if (motion == LEFT)
	{
		if (sh->in->index > 0)
		{
			tputs(tgetstr("le", NULL), 1, ft_putint);
			sh->in->index--;
		}
		/*if (sh->cursor->row > 0 && sh->cursor->col == 0)
		{
			tputs(tgetstr("bw", NULL), 1, ft_putint);
			tputs(tgetstr("le", NULL), 1, ft_putint);
			sh->cursor->row--;
			sh->cursor->col = sh->ws.ws_col;
		}*/
	}
	if (motion == RIGHT)
	{
		if (sh->in->index < sh->in->end)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putint);
			sh->in->index++;
		}
		/*if (sh->cursor->col == sh->ws.ws_col)
		{
			tputs(tgetstr("do", NULL), 1, ft_putint);
			sh->cursor->row++;
			tputs(tgetstr("cr", NULL), 1, ft_putint);
			sh->cursor->col = 0;
		}
		printf("<r%d c%d> ", sh->cursor->row, sh->cursor->col);*/
	}
}

void	ft_input(t_sh *sh)
{
	char	key[5];
	int		bytes;
	int		i;
	int		sum;

	while (1)
	{
		bytes = read(STDIN_FILENO, key, 4);
		key[bytes] = '\0';
		i = -1;
		sum = 0;
		while (key[++i])
			sum = sum + key[i];
		if (key[0] == 3/*(0x1f & ('c'))*/)
			exit(1);
		/*
		** ENTER
		*/
		if (key[0] == CR)
		{
			write(1, "\n>>", 3);
			ft_putstr(sh->in->buffer);
			write(STDOUT_FILENO, "\n\r", 2);
			break;
		}
		/*
		** PRINT
		*/
		if (key[1] == '\0' && (!iscntrl(sum) || isspace(sum)))
		{
			if (sh->in->index == sh->in->end)
				sh->in->buffer[sh->in->index] = key[0];
			else
			{
				ft_memmove(sh->in->buffer + sh->in->index + 1, \
				sh->in->buffer + sh->in->index, \
				ft_strlen(sh->in->buffer + sh->in->index));
				sh->in->buffer[sh->in->index] = key[0];
			}
			write(1, &key[0], 1);
			sh->in->index++;
			sh->in->end++;
		}
		/*
		** BACKSPACE
		*/
		if (key[1] == '\0' && key[0] == BS && sh->in->index > 0)
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
			write(1, "\b", 1);
			tputs(tgetstr("dc", NULL), 1, ft_putint);//delete character
		}
		/*if (sum == DEL)
		{
			tputs(tgetstr("dc", NULL), 1, ft_putint);
			sh->cursor->col--;
		}*/
		if (sum == LEFT || sum == RIGHT)
			ft_arrow_motion(sh, sum);
	}
}
