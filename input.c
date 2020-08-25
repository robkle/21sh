/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 10:24:31 by rklein            #+#    #+#             */
/*   Updated: 2020/08/25 17:09:27 by rklein           ###   ########.fr       */
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
	}
	if (motion == RIGHT)
	{
		if (sh->in->index < sh->in->end)
		{
			sh->in->index++;
			if ((sh->in->index + sh->in->prompt_size) % sh->ws.ws_col == 0)
			{
				tputs(tgetstr("do", NULL), 1, ft_putint);
				tputs(tgetstr("cr", NULL), 1, ft_putint);	
			}
			else
				tputs(tgetstr("nd", NULL), 1, ft_putint);
		}
	}
}

static void		ft_word_motion(t_sh *sh, int motion)
{
	int	i;

	i = 0;
	while (sh->in->buffer[i] == ' ')
		i++;
	if (motion == CTRL_LEFT)
	{
		if (sh->in->index > i && sh->in->buffer[sh->in->index] != ' ' &&
				sh->in->buffer[sh->in->index - 1] == ' ')
			ft_arrow_motion(sh, LEFT);
		while (sh->in->index > i && !(sh->in->buffer[sh->in->index] != ' ' &&
				sh->in->buffer[sh->in->index - 1] == ' '))
			ft_arrow_motion(sh, LEFT);
	}
	if (motion == CTRL_RIGHT)
	{
		if (sh->in->index < sh->in->end && sh->in->buffer[sh->in->index] != ' '
				&& sh->in->buffer[sh->in->index - 1] == ' ')
			ft_arrow_motion(sh, RIGHT);
		while (sh->in->index < sh->in->end && !(sh->in->buffer[sh->in->index] != ' ' &&
				sh->in->buffer[sh->in->index - 1] == ' '))
			ft_arrow_motion(sh, RIGHT);
	}
}

void	ft_input(t_sh *sh)
{
	char	key[9];
	int		bytes;
	int		i;
	int		sum;

	while (1)
	{
		//sh->in->line = (sh->in->end + sh->in->prompt_size) / sh->ws.ws_col;
		bytes = read(STDIN_FILENO, key, 8);
		key[bytes] = '\0';
		i = -1;
		sum = 0;
		while (key[++i])
			sum += key[i];
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
		/*
		** DELETE
		*/	
		if (sum == DEL && sh->in->index < sh->in->end)
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
			tputs(tgetstr("dc", NULL), 1, ft_putint);//delete character
		}
		/*
		** LEFT and RIGHT
		*/
		if (sum == LEFT || sum == RIGHT)
			ft_arrow_motion(sh, sum);
		/*
		** CTRL_LEFT and CTRL_RIGHT
		*/
		if (sum == CTRL_LEFT || sum == CTRL_RIGHT)
			ft_word_motion(sh, sum);
		/*
		** CTRL_UP and CTRL_DOWN
		*/
		if (sum == CTRL_UP)
		{
			if (sh->in->index - sh->ws.ws_col > 0)
			{
				tputs(tgetstr("up", NULL), 1, ft_putint);
				sh->in->index = sh->in->index - sh->ws.ws_col;
			}
			else
				sum = HOME;
		}
		if (sum == CTRL_DOWN)
		{
			if (sh->in->index + sh->ws.ws_col < sh->in->end)
			{
				tputs(tgetstr("do", NULL), 1, ft_putint);
				sh->in->index = sh->in->index + sh->ws.ws_col;
			}
			else
				sum = END;
		}
		/*
		** HOME and END
		*/
		if (sum == HOME)
		{
			while (sh->in->index > 0)
				ft_arrow_motion(sh, LEFT);
		}
		if (sum == END)
		{
			while (sh->in->index < sh->in->end)
				ft_arrow_motion(sh, RIGHT);
		}
	}
}
