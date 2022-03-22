/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:46:33 by rcollas           #+#    #+#             */
/*   Updated: 2022/03/22 10:29:39 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static	int	ft_is_space(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == ' ')
		return (1);
	return (0);
}

static long	result_atoi(const char *nptr, unsigned long long int nb, int sign)
{
	if (*nptr != '\0')
		return (-2147483649);
	if (nb > 2147483647 && sign == 1)
		return (-2147483649);
	else if (nb > 2147483648 && sign == -1)
		return (-2147483649);
	return (nb * sign);
}

long	ft_atoi(const char *nptr)
{
	int						sign;
	unsigned long long int	nb;

	nb = 0;
	sign = 1;
	while (ft_is_space(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		nb = nb * 10 + *nptr - 48;
		nptr++;
	}
	return (result_atoi(nptr, nb, sign));
}
