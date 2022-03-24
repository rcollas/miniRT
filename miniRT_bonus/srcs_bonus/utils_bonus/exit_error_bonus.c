/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:41:58 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:42:34 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	exit_error_parsing_end(int errnum, char *error_msg,
	t_parsing *parsing_var, _Bool need_destroy_texture)
{
	if (error_msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	free_str_tab(parsing_var->input_list);
	if (BONUS && need_destroy_texture)
	{
		destroy_texture(
			parsing_var->objs, parsing_var->obj_nb, parsing_var->mlx);
		free_list(parsing_var->objs);
	}
	else if (BONUS && !need_destroy_texture)
		free_list_error(parsing_var->objs, parsing_var->mlx);
	else
		free_list(parsing_var->objs);
	if (parsing_var->diffuse_light)
		ft_free(parsing_var->scene->diffuse_light);
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

int	exit_hook(t_data *data)
{
	clean_data(data);
	printf("\n");
	exit(EXIT_SUCCESS);
	return (0);
}
