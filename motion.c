# include "sh.h"

void	ft_arrow_motion(t_sh *sh, int motion)
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
				tputs(tgetstr("cr", NULL), 1, ft_putint);	
				tputs(tgetstr("do", NULL), 1, ft_putint);
			}
			else
				tputs(tgetstr("nd", NULL), 1, ft_putint);
		}
	}
}

void	ft_word_motion(t_sh *sh, int motion)
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

void	ft_he_motion(t_sh *sh, int motion)
{
	if (motion == HOME)
	{
		while (sh->in->index > 0)
			ft_arrow_motion(sh, LEFT);
	}
	if (motion == END)
	{
		while (sh->in->index < sh->in->end)
			ft_arrow_motion(sh, RIGHT);
	}
}

void	ft_line_motion(t_sh *sh, int motion)		
{
	if (motion == CTRL_UP)
	{
		if (sh->in->index - sh->ws.ws_col > 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putint);
			sh->in->index = sh->in->index - sh->ws.ws_col;
		}
		else
			ft_he_motion(sh, HOME);
		}
	if (motion == CTRL_DOWN)
	{
		if (sh->in->index + sh->ws.ws_col < sh->in->end)
		{
			tputs(tgetstr("do", NULL), 1, ft_putint);
			sh->in->index = sh->in->index + sh->ws.ws_col;
		}
		else
			ft_he_motion(sh, END);
	}
}
