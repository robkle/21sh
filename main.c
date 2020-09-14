/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:29:39 by rklein            #+#    #+#             */
/*   Updated: 2020/08/21 16:37:53 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

int	main()
{	
	t_sh	*sh;

	sh = (t_sh*)malloc(sizeof(t_sh));
	sh->in = (t_in*)malloc(sizeof(t_in));
	ft_validate_term();
	tcgetattr(STDIN_FILENO, &sh->orig);
	ft_sh(sh);
	return (0);	
}
