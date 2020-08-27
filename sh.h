/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:35:43 by rklein            #+#    #+#             */
/*   Updated: 2020/08/26 16:11:08 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <unistd.h>
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <ctype.h>
# include <sys/ioctl.h>
# include <limits.h>
# include "libft/libft.h"

# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>

# define UP 183
# define DOWN 184
# define LEFT 186
# define RIGHT 185

# define CTRL_UP 344 
# define CTRL_DOWN 345
# define CTRL_LEFT 347
# define CTRL_RIGHT 346

# define HOME 190
# define END 188

# define DEL 295
# define BS 127
# define CR 13

typedef struct	s_in
{
	char		*buffer;
	int			index;
	int			end;
	short int	line;
	char		*input;
	_Bool		q;
	_Bool		p;
	short int	prompt_size;
}				t_in;


typedef struct	s_sh
{
	struct termios	orig;
	struct termios	raw;
	struct winsize	ws;
	t_in			*in;

}				t_sh;

void	ft_validate_term(void);
void	ft_rawmode(t_sh *sh);
void	ft_sh(t_sh *sh);
void	ft_prompt(t_sh *sh, int prompt);
void	ft_readkey(t_sh *sh);
void	ft_resetmode(t_sh *sh);
int	ft_putint(int c);
/*
** line edit: input
*/
void	ft_add_char(t_sh *sh, int c);
void	ft_del_char(t_sh *sh);
void	ft_backspace(t_sh *sh);
void	ft_reprint(t_sh *sh, int line);
/*
** line edit: motion
*/
void	ft_arrow_motion(t_sh *sh, int motion);
void	ft_word_motion(t_sh *sh, int motion);
void	ft_he_motion(t_sh *sh, int motion);
void	ft_line_motion(t_sh *sh, int motion);		



#endif
