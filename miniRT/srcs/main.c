/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:50:38 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 10:50:39 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		exit_error_parsing_end(MALLOC_ERROR, NULL, parsing_var);
	init_data(parsing_var, data);
	init_euler_angles(data->scene->camera);
	display_info_move_cam();
	run_minirt(data);
	events_loop(data);
	clean_data(data);
	return (0);
}
