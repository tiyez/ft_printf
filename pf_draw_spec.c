/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:52:30 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/11 17:47:23 by jsandsla         ###   ########.fr       */
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
		vs.len = FT_MIN(vs.len, spec->precision);
	if (!str && vs.len < 6)
		vs.len = 0;
	if (PF_FLAG(spec, WIDTH) && !PF_FLAG(spec, MINUS))
		success = !ft_dds_spread(dds, ' ', FT_USUB(spec->width, vs.len));
	success = success && ft_ddsappendvs(dds, &vs) == E_OK;
	if (success && PF_FLAG(spec, WIDTH) && PF_FLAG(spec, MINUS))
		success = !ft_dds_spread(dds, ' ', FT_USUB(spec->width, vs.len));
	return (success);
}

static	int		draw_pointer(t_dds *dds, t_pf_value val, t_pf_spec *spec)
{
	int		success;

	if (val.p == NULL)
	{
		success = 1;
		if (PF_FLAG(spec, WIDTH) && !PF_FLAG(spec, MINUS))
			success = !ft_dds_spread(dds, ' ', FT_USUB(spec->width, 5));
		success = success && ft_ddsappend(dds, "(nil)", 5) == E_OK;
		if (success && PF_FLAG(spec, WIDTH) && PF_FLAG(spec, MINUS))
			success = !ft_dds_spread(dds, ' ', FT_USUB(spec->width, 5));
	}
	else
	{
		val.zu = (size_t)val.p;
		spec->type = PF_TYPE_X;
		spec->size = PF_SZ_Z;
		spec->flags |= PF_FLAG_HASH;
		success = pf_draw_integer(dds, val, spec);
	}
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
			success = draw_char(dds, value.d, &spec);
		else if (spec.type == PF_TYPE_S)
			success = draw_str(dds, (char *)value.p, &spec);
		else if (spec.type == PF_TYPE_P)
			success = draw_pointer(dds, value, &spec);
		else if (spec.type == PF_TYPE_N)
			success = write_n(dds, value.p, &spec);
	}
	return (success);
}
