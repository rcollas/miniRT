/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:47:43 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:47:45 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include <stdlib.h>
# include <errno.h>
# include "enum_bonus.h"
# include "error_bonus.h"
# include "libft_bonus.h"

void	ft_free(void *to_free);
void	safe_close(int fd);
int		ft_open(char *file, int *fd);
int		safe_read(int fd, char *buff, int buff_size, char *input);
int		safe_ft_strjoin(char **input, char *buff, int fd);
int		safe_ft_strdup(char **dest, char *to_copy, int fd);
void	display_info_move_cam(void);
void	display_cam_param(t_camera *camera, t_data *data);
void	display_loading(t_data *data, t_thread *thread, int ratio);
void	display_end_loading(t_data *data, t_thread *thread);
void	print_list(t_obj *obj);
void	print_matrix4(t_matrix4 matrix);
void	print_matrix3(t_matrix3 matrix);

#endif
