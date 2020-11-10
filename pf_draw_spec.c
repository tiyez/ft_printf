/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:52:30 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/10 20:22:06 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		draw_pointer(t_dds *dds, void *ptr)
{
	char	arr[17];
	char	arrz[17];
	t_s		s;
	size_t	len;
	t_err	error;

	arr[0] = '\0';
	ft_sinitn(&s, arr, sizeof(arr) - 1);
	pf_llutostr(&s, (unsigned long long)ptr, 16, "0123456789ABCDEF");
	error = E_OK;
	len = 0;
	while (error == E_OK && len < (sizeof(void *) * 2 - s.m->len))
		arrz[len++] = '0';
	arrz[len] = '\0';
	error = ft_ddsappend(dds, arrz, len);
	if (error == E_OK)
		error = ft_ddsappends(dds, &s);
	return (error == E_OK);
}

static int		write_n(t_dds *dds, void *ptr, t_pf_spec *spec)
{
	size_t	len;
	int		success;

	success = 1;
	len = ft_dds_len(dds);
	if (spec->size == 0)
		*(int *)ptr = (int)len;
	else if (spec->size == PF_SZ_L)
		*(long int *)ptr = (long int)len;
	else if (spec->size == PF_SZ_HH)
		*(signed char *)ptr = (signed char)len;
	else if (spec->size == PF_SZ_H)
		*(short int *)ptr = (short int)len;
	else if (spec->size == PF_SZ_LL)
		*(long long int *)ptr = (long long int)len;
	else if (spec->size == PF_SZ_J)
		*(intmax_t *)ptr = (intmax_t)len;
	else if (spec->size == PF_SZ_Z)
		*(ssize_t *)ptr = (ssize_t)len;
	else
		success = 0;
	return (success);
}

int				pf_draw_spec(t_dds *dds, t_pf_spec spec, va_list va)
{
	int			success;
	t_pf_value	value;

	success = 0;
	if (spec.type == PF_TYPE_PERCENT)
		success = (ft_ddsappend(dds, "%", 1) == E_OK);
	else if ((success = pf_get_value(&value, &spec, va)))
	{
		if (PF_IS_INTEGER(spec.type))
			success = pf_draw_integer(dds, value, &spec);
		else if (PF_IS_DOUBLE(spec.type))
			success = pf_draw_double(dds, value.f, &spec);
		else if (spec.type == PF_TYPE_C)
			success = (ft_ddsappendc(dds, (char)value.d) == E_OK);
		else if (spec.type == PF_TYPE_S)
			success = (ft_ddsappendstr(dds, (char *)value.p) == E_OK);
		else if (spec.type == PF_TYPE_P)
			success = draw_pointer(dds, value.p);
		else if (spec.type == PF_TYPE_N)
			success = write_n(dds, value.p, &spec);
	}
	return (success);
}
