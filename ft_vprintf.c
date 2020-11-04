/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:55:23 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/04 23:13:43 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_vfprintf(int fd, const char *fmt, va_list va)
{
	t_dd	dd;
	int		result;
	size_t	i;

	ft_ddinit(&dd);
	result = ft_vddprintf(&dd, fmt, va);
	i = 0;
	while (i < dd.len)
	{
		write(fd, dd.ptr[i].ptr, dd.ptr[i].len);
		i += 1;
	}
	ft_ddfree(&dd);
	return (result);
}

int				ft_vddprintf(t_dd *dd, const char *fmt, va_list va)
{
	int		result;
	int		sum_result;
	t_vs	vs;
	t_err	error;
	t_d		*d;

	sum_result = 0;
	result = 0;
	vs = ft_vsconst(fmt);
	while (error == E_OK && result >= 0 && vs.offset < vs.len)
	{
		error = ft_ddnewinitex(dd, 0, 1, PF_D_SIZE - 1);
		if (error == E_OK)
		{
			d = dd->ptr[dd->len - 1];
			if (error == E_OK)
				result = ft_vsnvsprintf(d->ptr, d->max_len, &vs, va);
			if (error == E_OK && result >= 0)
				d->len = result;
		}
	}
	return (sum_result);
}

int				ft_vsnprintf(char *out, size_t n, const char *fmt, va_list va)
{

}

int				ft_vsnvsprintf(char *out, size_t n, t_vs *vs, va_list va)
{

}
