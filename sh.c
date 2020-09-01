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
	if (!sh->in->q && !sh->in->p)
		write(STDOUT_FILENO, "21sh$ ", sh->in->prompt_size =  6);
	else if (sh->in->q || sh->in->p)
		write(STDOUT_FILENO, "> ", sh->in->prompt_size = 2);
}

void	ft_sh(t_sh *sh)
{
	int	prompt;

	prompt = 0;
	while (1)
	{
		sh->in->buffer = ft_memalloc(ARG_MAX);
		sh->in->index = 0;
		sh->in->line = 0;
		ft_prompt(sh, prompt++);
		ft_readkey(sh);
	}
}
