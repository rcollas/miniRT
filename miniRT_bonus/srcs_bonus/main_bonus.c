/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:41:35 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 22:47:55 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	check_size_window();
	if (parsing(argv, argc, parsing_var) == FAIL)
		exit_error_parsing_end(
			MALLOC_ERROR, NULL, parsing_var, DESTROY_TEXTURE);
	init_data(parsing_var, data);
	init_euler_angles(data->scene->camera);
	display_info_move_cam();
	run_minirt(data);
	events_loop(data);
	print_list(data->obj);
	clean_data(data);
	return (0);
}
