/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:52:30 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/24 12:05:35 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int		draw_str(t_dds *dds, char *str, t_pf_spec *spec)
{
	int		success;
	t_vs	vs;

	vs = ft_vscreatestr(str ? str : "(null)");
	success = 1;
	if (PF_FLAG(spec, PRECISION))
		vs.len = FT_MIN(vs.len, (size_t)spec->precision);
	success = pf_prepend_space(dds, vs.len, spec);
	success = success && pf_prepend_zero(dds, vs.len, spec);
	success = success && ft_ddsappendvs(dds, &vs) == E_OK;
	success = success && pf_append_space(dds, vs.len, spec);
	return (success);
}

static	int		draw_char(t_dds *dds, char c, t_pf_spec *spec)
{
	int		success;

	success = 1;
	if (PF_FLAG(spec, WIDTH) && !PF_FLAG(spec, MINUS))
		success = !ft_dds_spread(dds, ' ', FT_USUB(spec->width, 1));
	success = success && ft_ddsappendraw(dds, &c, 1) == E_OK;
	if (success && PF_FLAG(spec, WIDTH) && PF_FLAG(spec, MINUS))
		success = !ft_dds_spread(dds, ' ', FT_USUB(spec->width, 1));
	return (success);
}

static	int		draw_percent(t_dds *dds, t_pf_spec *spec)
{
	int		res;

	res = pf_prepend_space(dds, 1, spec);
	res = res && pf_prepend_zero(dds, 1, spec);
	res = res && ft_ddsappend(dds, "%", 1) == E_OK;
	res = res && pf_append_space(dds, 1, spec);
	return (res);
}

int				pf_draw_spec(t_dds *dds, t_pf_spec spec, va_list va)
{
	int			success;

	success = 0;
	if (spec.type == PF_TYPE_PERCENT)
		success = draw_percent(dds, &spec);
	else if ((success = pf_get_value(&spec, va)))
	{
		if (PF_IS_INTEGER(spec.type) || spec.type == PF_TYPE_P)
			success = pf_draw_integer(dds, &spec);
		else if (PF_IS_DOUBLE(spec.type))
			success = pf_draw_double(dds, &spec);
		else if (spec.type == PF_TYPE_C)
			success = draw_char(dds, spec.val.d, &spec);
		else if (spec.type == PF_TYPE_S)
			success = draw_str(dds, (char *)spec.val.p, &spec);
		else if (spec.type == PF_TYPE_N)
			success = write_n(dds, spec.val.p, &spec);
	}
	return (success);
}
