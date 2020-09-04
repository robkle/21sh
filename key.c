#include "sh.h"

static void	ft_check_qp(t_sh *sh)
{
	int	i;

	i = -1;
	while (sh->in->buffer[++i])
	{
		if (sh->in->buffer[i] == 39) 
		{
			if (!(sh->in->qp % 4))
				sh->in->qp += 1;
			else if (sh->in->qp % 4 == 1)
				sh->in->qp -= 1;
		}
		if (sh->in->buffer[i] == 34) 
		{
			if (!(sh->in->qp % 4))
				sh->in->qp += 2;
			else if (sh->in->qp % 4 == 2)
				sh->in->qp = sh->in->qp - 2;
		}
		if (sh->in->buffer[i] == 124 && !sh->in->qp)
			sh->in->qp += 4;
		if (sh->in->buffer[i] != 124 && sh->in->buffer[i] != ' ' && sh->in->qp == 4)	
			sh->in->qp -= 4;
	}
}

void	ft_readkey(t_sh *sh)
{
	char	key[9];
	int		bytes;
	int		i;
	int		sum;

	while (1)
	{
		bytes = read(STDIN_FILENO, key, 8);
		key[bytes] = '\0';
		i = -1;
		sum = 0;
		while (key[++i])
			sum += key[i];
		if (sum == 3/*(0x1f & ('c'))*/)
			exit(1);
		/*
		** ENTER
		*/
		if (sum == CR)
		{
			write(STDOUT_FILENO, "\n\r", 2); //TEMP for testing
			ft_check_qp(sh);
			ft_strcat(sh->in->input, sh->in->buffer);
			break;
		}
		//reset copy range if not a motion
		if (ft_isprint(sum))
			ft_add_char(sh, sum);
		if (sum == BS && sh->in->index > 0)
			ft_backspace(sh);
		if (sum == DEL)
			ft_del_char(sh);
		if (sum == LEFT || sum == RIGHT)
			ft_arrow_motion(sh, sum);
		if (sum == CTRL_LEFT || sum == CTRL_RIGHT)
			ft_word_motion(sh, sum);
		if (sum == CTRL_UP || sum == CTRL_DOWN)
			ft_line_motion(sh, sum);
		if (sum == HOME || sum == END)
			ft_he_motion(sh, sum);
		if (sum == UP || sum == DOWN)
			ft_history_scroll(sh, sum);
		if (sum == COPY)
			ft_copy(sh);
		if (sum == PASTE)
			ft_paste(sh);
	}
}
