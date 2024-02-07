/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyeuk <dongyeuk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:46:00 by dongyeuk          #+#    #+#             */
/*   Updated: 2024/02/07 14:12:41 by dongyeuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func(void)
return : (long long)current time(miliseconds) */
long long	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_usec / 1000);
}

/* func(time to compare)
return : (long long)result of comparison(miliseconds) */
long long	get_time_diff(long long runtime)
{
	struct timeval	start;
	long long		result;

	gettimeofday(&start, NULL);
	result = start.tv_sec * 1000 + start.tv_usec / 1000 - runtime;
	return (result);
}

/* func(miliseconds to sleep)
return : NONE(void) */
int	ph_sleep(t_ph *ph, long milisec)
{
	long long	set_time;

	set_time = get_time();
	while (get_time_diff(set_time) < milisec)
	{
		usleep(100);
		if (chk_death(ph) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

// 슬립하는 함수를 따로 만들어서 관리한다
// 시간 커지면 부정확해진다 usleep << 작은 숫자로 자주 깨어나면서 현재 시간이 얼마나 지났는지 확인하는 방식으로 구현하는 것이 정확하다
// usleep으로 현재 시간의 80%정도만 쉬고 나머지 20%는 busy wait상태를 유지하는게 오히려 정확할 수 있다.

// xsleep(start_time, time)
// {
// 	while (get_time() - start_time < time)
// 	{
// 		usleep(500);
// 	}
// }