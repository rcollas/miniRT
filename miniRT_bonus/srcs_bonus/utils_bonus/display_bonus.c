/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:41:47 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	display_loading(t_data *data, t_thread *thread, int ratio)
{
	char	*msg;
	char	*percent;

	if (data->path_tracing && data->multithreading && thread->id == THREADS - 1)
	{
		msg = ft_strdup(ORANGE);
		msg = ft_strjoin_and_free(
				msg, "\r   Rendering scene with path_tracing... [");
		percent = ft_itoa(100 * (thread->pixel_y % ratio) / ratio);
		msg = ft_strjoin_and_free(msg, percent);
		clean_free(&percent);
		msg = ft_strjoin_and_free(msg, "%]");
		ft_putstr_fd(msg, 1);
		clean_free(&msg);
	}
}

void	display_end_loading(t_data *data, t_thread *thread)
{
	char	*msg;

	if (data->path_tracing && data->multithreading && thread->id == THREADS - 1)
	{
		msg = ft_strdup(GREEN);
		msg = ft_strjoin_and_free(
				msg, "\r ✔ Rendering scene with path_tracing... [100%]");
		ft_putstr_fd(msg, 1);
		printf(" with %d threads in %.2fs\n\n",
			THREADS, (get_time() - data->start_time) / 1000);
		ft_putstr_fd(RESET, 1);
		clean_free(&msg);
	}
}

void	display_cam_param(t_camera *camera, t_data *data)
{
	static int	even;

	if (data->path_tracing)
		return ;
	if (even % 2 == 0)
		ft_putstr_fd(LIGHT_GREY, 1);
	else
		ft_putstr_fd(GREY, 1);
	printf("   {%-6.2f %6.2f %6.2f}\t", camera->origin->coord[X],
		camera->origin->coord[Y], camera->origin->coord[Z]);
	printf("{%-6.2f %6.2f %6.2f}\t", camera->dir->coord[X],
		camera->dir->coord[Y], camera->dir->coord[Z]);
	printf("      %.2fs\n", (get_time() - data->start_time) / 1000);
	ft_putstr_fd(RESET, 1);
	even++;
}

void	display_info_move_cam(void)
{
	ft_putstr_fd("\n\t-----------------------------------------------------\n", 1);
	ft_putstr_fd("\t\033[38;5;215m To move the camera : ", 1);
	ft_putstr_fd("\t\tTo tilt the camera : \n", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ x_axis : A D\t\t\t◦ left/right : ← →\n", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ y_axis : SPACE MAJ\t\t", 1);
	ft_putstr_fd("◦ up/down    : ↑ ↓\n\033[0m", 1);
	ft_putstr_fd("\t\033[38;5;229m ◦ z_axis : W S\n", 1);
	ft_putstr_fd(RESET, 1);
	ft_putstr_fd(
		"\t-----------------------------------------------------\n\n\n", 1);
	ft_putstr_fd("        CAMERA ORIGIN\t\t   CAMERA DIRECTION\t", 1);
	ft_putstr_fd("   RENDER TIME\n", 1);
	ft_putstr_fd("  ___________________________________________________", 1);
	ft_putstr_fd("_____________________\n\n", 1);
}
