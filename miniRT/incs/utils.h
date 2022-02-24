#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <errno.h>
# include "enum.h"
# include "error.h"
# include "libft.h"

void	ft_free(void *to_free);
void	safe_close(int fd);
int		ft_open(char *file, int *fd);
int		safe_read(int fd, char *buff, int buff_size, char *input);
int		safe_ft_strjoin(char **input, char *buff, int fd);
int		safe_ft_strdup(char **dest, char *to_copy, int fd);
void	ft_exit_parsing(int errnum, t_parsing *parsing_var);
void	free_str_tab(char **tab);
void	display_info_move_cam(void);
void	display_cam_param(t_camera *camera, t_data *data);
void	display_loading(t_data *data, t_thread *thread, int ratio, _Bool end);

#endif
