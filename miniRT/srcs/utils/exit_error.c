/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:51:06 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 10:51:08 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_error(int errnum, char *error_msg, t_data *data)
{
	if (error_msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	clean_data(data);
	exit(errnum);
}

void	exit_error_parsing_end(int errnum,
								char *error_msg,
								t_parsing *parsing_var)
{
	if (error_msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	free_str_tab(parsing_var->input_list);
	free_list(parsing_var->objs);
	clean_mlx(parsing_var->mlx);
	exit(errnum);
}

void	exit_error_parsing(int errnum, char *error_msg, t_parsing *parsing_var)
{
	if (error_msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	clean_parsing_var(parsing_var);
	exit(errnum);
}
