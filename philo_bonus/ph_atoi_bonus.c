/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:52:04 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/18 17:27:19 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	ft_paraset(unsigned long *max_num, int *lim_num, int sign, \
						unsigned long *acc)
{
	int	size;

	*acc = 0;
	size = sizeof(long long) * sizeof(void *);
	*max_num = (sign) * ((unsigned long long)1 << (size - 1)) - (sign > 0);
	*lim_num = (*max_num % 10) + '0';
}

/* func(string to convert integer, address of result)
return value : TRUE or FALSE */
int	ph_atoi(const char *nptr, long long *ans)
{
	unsigned long	acc;
	unsigned long	max_num;
	int				lim_num;
	int				sign;

	sign = 1;
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign *= -1;
	if (*nptr == '\0' || sign == -1)
		return (FALSE);
	ft_paraset(&max_num, &lim_num, sign, &acc);
	while ('0' <= *nptr && *nptr <= '9')
	{
		acc = acc * 10 + *nptr - '0';
		if (acc > max_num || (acc == (max_num / 10) && *(nptr + 1) > lim_num))
			return (FALSE);
		nptr++;
	}
	if (*nptr != 0)
		return (FALSE);
	*ans = sign * acc;
	return (TRUE);
}
