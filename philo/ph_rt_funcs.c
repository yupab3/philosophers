/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_rt_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:58:46 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/06 13:43:31 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(string to print, filedescriptor)
return : FALSE */
int	_rt_false_with_msg_nl_fd(char *null_able, int fd)
{
	int	len;

	len = 0;
	if (null_able != NULL)
	{
		while (*(null_able + len) != '\0')
			len++;
		write(fd, null_able, len + 1);
		write(fd, "\n", 1);
	}
	return (FALSE);
}

/* func(string to print, filedescriptor)
return : FAILURE */
int	_rt_failure_with_msg_nl_fd(char *null_able, int fd)
{
	int	len;

	len = 0;
	if (null_able != NULL)
	{
		while (*(null_able + len) != '\0')
			len++;
		write(fd, null_able, len + 1);
		write(fd, "\n", 1);
	}
	return (FAILURE);
}

/* func(string to print, filedescriptor)
return : (void *)NULL */
void	*_rt_null_with_msg_nl_fd(char *null_able, int fd)
{
	int	len;

	len = 0;
	if (null_able != NULL)
	{
		while (*(null_able + len) != '\0')
			len++;
		write(fd, null_able, len + 1);
		write(fd, "\n", 1);
	}
	return (NULL);
}
