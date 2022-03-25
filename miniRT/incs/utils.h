/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:49:50 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 22:47:25 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <errno.h>
# include "enum.h"
# include "error.h"
# include "libft.h"

void	check_size_window(void);
void	ft_free(void *to_free);
void	safe_close(int fd);
int		ft_open(char *file, int *fd);
int		safe_read(int fd, char *buff, int buff_size, char *input);
int		safe_ft_strjoin(char **input, char *buff, int fd);
int		safe_ft_strdup(char **dest, char *to_copy, int fd);
void	display_info_move_cam(void);
void	display_cam_param(t_camera *camera);
void	print_list(t_obj *obj);
void	print_matrix(t_matrix4 matrix);

#endif
