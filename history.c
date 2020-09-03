#include "sh.h"

//REPLACE sh->in->buffer WITH sh->in->input

static void	ft_history_init(t_sh *sh)
{
	sh->in->hs = (t_hs*)malloc(sizeof(t_hs));
	sh->in->hs->hist = ft_strdup(sh->in->input);
	sh->in->hs->prev = NULL;
	sh->in->hs->next = NULL;
	sh->in->hs_begin = sh->in->hs;
	sh->in->hs_last = sh->in->hs;
}
 
void	ft_history_add(t_sh *sh)
{
	t_hs *new;

	if (!sh->in->hs)
		ft_history_init(sh);
	else
	{
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
}

void	ft_history_scroll(t_sh *sh, int motion)
{
	int	i;

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
	i = -1;
	while (sh->in->hs->hist[++i])
		ft_add_char(sh, sh->in->hs->hist[i]);
}
