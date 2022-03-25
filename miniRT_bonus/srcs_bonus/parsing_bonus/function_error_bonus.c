/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_error_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:44 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	close_error(char *str)
{
	ft_putstr_fd("Close failed: fd ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free(str);
	return (errno);
}

int	read_error(char *str)
{
	ft_putstr_fd("Read failed: fd ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free(str);
	return (errno);
}

int	strjoin_error(void)
{
	ft_putstr_fd("Critical error: Strjoin failed\n", 2);
	return (STRJOIN_ERROR);
}

int	strdup_error(void)
{
	ft_putstr_fd("Critical error: Strdup failed\n", 2);
	return (STRDUP_ERROR);
}
