/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 11:00:23 by rklein            #+#    #+#             */
/*   Updated: 2020/09/11 15:19:20 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_prompt(t_sh *sh, int prompt)
{
	if (prompt == 0)
		tputs(tgetstr("cl", NULL), 1, ft_putint);
	if (!sh->in->qph)
		ft_strcpy(sh->in->prompt, "21sh$ ");
	else
	{
		ft_bzero(sh->in->prompt, 7);
		ft_strcpy(sh->in->prompt, "> ");
	}
	sh->in->prompt_size = ft_strlen(sh->in->prompt);
	//ft_putstr_fd(sh->in->prompt, STDOUT_FILENO);
}

static void	ft_init(t_sh *sh)
{
	sh->in->prompt= ft_memalloc(7);
	sh->in->buffer = ft_memalloc(ARG_MAX);
	sh->in->index = 0;
	sh->in->line = 0;
	sh->in->input = ft_memalloc(ARG_MAX);
	sh->in->clipboard = ft_memalloc(ARG_MAX);
	sh->in->cp_range[0] = -1;
	sh->in->cp_range[1] = -1;
	sh->in->hs = NULL;
	sh->in->qph = 0;
	sh->in->hdoc = ft_memalloc(256);
	sh->in->hs = (t_hs*)malloc(sizeof(t_hs));
	sh->in->hs->hist = ft_strnew(0);;
	sh->in->hs->prev = sh->in->hs;
	sh->in->hs->next = sh->in->hs;
	sh->in->hs_begin = sh->in->hs;
	sh->in->hs_last = sh->in->hs;
}

static void	ft_reset_buffer(t_sh *sh)
{
	ft_bzero(sh->in->buffer, ARG_MAX);
	sh->in->index = 0;
	sh->in->line = 0;
	sh->in->cp_range[0] = -1;
	sh->in->cp_range[1] = -1;
}

void	ft_sh(t_sh *sh)
{
	int	prompt;

	ft_init(sh);
	prompt = 0;
	while (1)
	{
		ft_rawmode(sh); //NEW moved from main
		ft_prompt(sh, prompt++);
		ft_reprint(sh);
		ft_readkey(sh);
		ft_resetmode(sh); //NEW moved from main
		ft_reset_buffer(sh);
		if (!sh->in->qph)
		{
			//Prepare input string
			//Send to command handling function
			if (*(sh->in->input))
			{
				tputs(tgetstr("cr", NULL), 1, ft_putint);
				tputs(tgetstr("do", NULL), 1, ft_putint);
				ft_putstr(sh->in->input); //TEMP for testing
				ft_history_add(sh);
			}
			tputs(tgetstr("cr", NULL), 1, ft_putint);
			tputs(tgetstr("do", NULL), 1, ft_putint);
			ft_bzero(sh->in->input, ft_strlen(sh->in->input));
		}
		else
		{
			tputs(tgetstr("cr", NULL), 1, ft_putint);
			tputs(tgetstr("do", NULL), 1, ft_putint);
		}
	}
}
