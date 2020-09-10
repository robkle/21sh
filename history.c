#include "sh.h"

void	ft_history_add(t_sh *sh)
{
	t_hs *new;

	new = (t_hs*)malloc(sizeof(t_hs));
	new->hist = ft_strdup(sh->in->input);
	//connecting new with last
	new->prev = sh->in->hs_last;
	sh->in->hs_last->next = new;
	//connecting new with old begin
	new->next = sh->in->hs_begin;
	sh->in->hs_begin->prev = new;
	//change begin to new
	sh->in->hs_begin = new;
	//reset pointer to beginning
	sh->in->hs = sh->in->hs_begin;
	sh->in->hss = 0;
}

void	ft_history_scroll(t_sh *sh, int motion)
{
	int	i;

	ft_he_motion(sh, HOME);
	ft_bzero(sh->in->buffer, ft_strlen(sh->in->buffer));
	sh->in->index = 0;
	sh->in->line = 0;
	if (sh->in->hss++)
	{
		if (motion == UP)
			sh->in->hs = sh->in->hs->next;
		if (motion == DOWN)
			sh->in->hs = sh->in->hs->prev;
	}
	if (!*(sh->in->hs->hist))
		ft_reprint(sh);
	else
	{
		ft_strcpy(sh->in->buffer, sh->in->hs->hist);
		ft_reprint(sh);
		ft_he_motion(sh, END);
	}
}
