/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 11:00:23 by rklein            #+#    #+#             */
/*   Updated: 2020/09/01 16:44:18 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_prompt(t_sh *sh, int prompt)
{
	if (prompt == 0)
		tputs(tgetstr("cl", NULL), 1, ft_putint);
	if (!sh->in->qp)
		ft_strcpy(sh->in->prompt, "21sh$ ");
	else
	{
		ft_bzero(sh->in->prompt, 7);
		ft_strcpy(sh->in->prompt, "> ");
	}
	sh->in->prompt_size = ft_strlen(sh->in->prompt);
	ft_putstr_fd(sh->in->prompt, STDOUT_FILENO);
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
	sh->in->qp = 0;
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
		ft_prompt(sh, prompt++);
		ft_readkey(sh);
		ft_reset_buffer(sh);
		if (!sh->in->qp)
		{
			//Prepare input string
			//Send to command handling function
			write(STDOUT_FILENO, "\n\r>>", 4); //TEMP for testing
			ft_putstr(sh->in->input); //TEMP for testing
			write(STDOUT_FILENO, "\n\r", 2); //TEMP for testing
			ft_history_add(sh); //after quotes are handles change so that final sh->in->input goes to history
			ft_bzero(sh->in->input, ft_strlen(sh->in->input));
		}
	}
}
