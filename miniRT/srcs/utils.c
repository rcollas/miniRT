# include "utils.h"

void	ft_free(void *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

/*
void	free_sphere(t_sphere *list)
{
	t_sphere	*tmp;

	while (list && list->next)
	{
		tmp = list->next;
		ft_free(list);
		list = tmp;
	}
}

void	free_plan(t_plan *list)
{
	t_plan	*tmp;

	while (list && list->next)
	{
		tmp = list->next;
		ft_free(list);
		list = tmp;
	}
}

void	free_cylinder(t_cylinder *list)
{
	t_cylinder *tmp;

	while (list && list->next)
	{
		tmp = list->next;
		ft_free(list);
		list = tmp;
	}
}

void	free_objs(t_obj *objs)
{
	if (objs)
	{
		free_sphere(objs->sphere);
		free_plan(objs->plan);
		free_cylinder(objs->cylinder);
	}
}
 */

void	free_str_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		ft_free(tab[i]);
	ft_free(tab);
}

void	ft_exit_parsing(int errnum, t_parsing *parsing_var)
{
	//free_objs(parsing_var->objs);
	free_str_tab(parsing_var->input_list);
	free_str_tab(parsing_var->obj_info);
	exit(errnum);
}

int	ft_open(char *file, int *fd)
{
	if ((*fd = open(file, O_DIRECTORY)) >= 0)
		return (parsing_error(IS_DIR_ERROR, file));
	if ((*fd = open(file, O_RDONLY | O_NOFOLLOW)) < 0)
		return (parsing_error(FILE_ERROR, file));
	return (SUCCESS);
}

void	safe_close(int fd)
{
	if (fd >= 0)
	{
		if (close(fd) == -1)
		{
			error(CLOSE_ERROR, ft_itoa(fd));
			exit(CLOSE_ERROR);
		}
	}
}

int	safe_read(int fd, char *buff, int buff_size, char *input)
{
	int	ret;

	ret = read(fd, buff, buff_size);
	if (ret < 0)
	{
		error(READ_ERROR, ft_itoa(fd));
		ft_free(input);
		safe_close(fd);
		exit(errno);
	}
	return (ret);
}

int	safe_ft_strjoin(char **input, char *buff, int fd)
{
	char *tmp;

	tmp = *input;
	*input = ft_strjoin(*input, buff);
	if (!*input)
	{
		error(STRJOIN_ERROR, NULL);
		safe_close(fd);
		exit(STRJOIN_ERROR);
	}
	ft_free(tmp);
	return (SUCCESS);
}

int	safe_ft_strdup(char **dest, char *to_copy, int fd)
{
	*dest = ft_strdup(to_copy);
	if (!dest)
	{
		error(STRDUP_ERROR, NULL);
		safe_close(fd);
		exit(STRDUP_ERROR);
	}
	return (SUCCESS);
}
