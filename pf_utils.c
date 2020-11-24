/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 01:19:38 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/24 12:08:21 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		is_value_negative(t_pf_spec *spec)
{
	int			result;
	t_ieee754	ieee754;

	result = 0;
	if (PF_IS_SIGNED(spec->type))
	{
		if (spec->size == PF_SZ_L)
			result = spec->val.ld < 0;
		else if (spec->size == PF_SZ_LL)
			result = spec->val.lld < 0;
		else if (spec->size == PF_SZ_J)
			result = spec->val.jd < 0;
		else if (spec->size == PF_SZ_Z)
			result = spec->val.zd < 0;
		else
			result = spec->val.d < 0;
	}
	else if (PF_IS_DOUBLE(spec->type))
	{
		ieee754.f = spec->val.f;
		result = ieee754.u >> 63;
	}
	return (result);
}

t_vs			pf_sign(t_pf_spec *spec)
{
	t_vs	vs;

	if (is_value_negative(spec))
		vs = ft_vscreatestr("-");
	else if (spec->type == PF_TYPE_O && (spec->flags & PF_FLAG_HASH))
		vs = ft_vscreatestr("0");
	else if ((spec->type == PF_TYPE_X && (spec->flags & PF_FLAG_HASH)) ||
		spec->type == PF_TYPE_P)
		vs = ft_vscreatestr("0x");
	else if (spec->type == PF_TYPE_BIGX && (spec->flags & PF_FLAG_HASH))
		vs = ft_vscreatestr("0X");
	else if (PF_IS_NUMBER(spec->type) && spec->flags & PF_FLAG_PLUS)
		vs = ft_vscreatestr("+");
	else if (PF_IS_NUMBER(spec->type) && spec->flags & PF_FLAG_SPACE)
		vs = ft_vscreatestr(" ");
	else
		vs = ft_vscreatestr("");
	return (vs);
}

int				pf_prepend_zero(t_dds *dds, size_t len, t_pf_spec *spec)
{
	t_vs	sign;
	int		success;

	success = 1;
	sign = pf_sign(spec);
	if (spec->flags & PF_FLAG_WIDTH && spec->flags & PF_FLAG_ZERO &&
		(!(spec->flags & PF_FLAG_PRECISION) || PF_IS_DOUBLE(spec->type)) &&
		!(spec->flags & PF_FLAG_MINUS))
	{
		len += sign.len;
		if (success && (size_t)spec->width > len)
			success = ft_dds_spread(dds, '0', spec->width - len) == E_OK;
	}
	return (success);
}

int				pf_prepend_space(t_dds *dds, size_t len, t_pf_spec *spec)
{
	t_vs	sign;
	int		success;
	ssize_t	wordlen;

	success = 1;
	sign = pf_sign(spec);
	wordlen = len + sign.len + (PF_IS_INTEGER(spec->type) ?
		FT_USUB((size_t)spec->precision, len) : 0);
	if (spec->width > wordlen && !(spec->flags & PF_FLAG_MINUS) &&
		spec->flags & PF_FLAG_WIDTH && (!(spec->flags & PF_FLAG_ZERO) ||
			(spec->flags & PF_FLAG_PRECISION && !PF_IS_DOUBLE(spec->type))))
		success = ft_dds_spread(dds, ' ', spec->width - wordlen) == E_OK;
	success = success && ft_ddsappendvs(dds, &sign) == E_OK;
	if (spec->flags & PF_FLAG_PRECISION && PF_IS_INTEGER(spec->type))
		success = success && ft_dds_spread(dds, '0',
			FT_USUB((size_t)spec->precision, len)) == E_OK;
	return (success);
}

int				pf_append_space(t_dds *dds, size_t len, t_pf_spec *spec)
{
	t_vs	sign;
	int		success;
	ssize_t	wordlen;

	success = 1;
	sign = pf_sign(spec);
	wordlen = len + sign.len + (PF_IS_INTEGER(spec->type) ?
		FT_USUB((size_t)spec->precision, len) : 0);
	if (spec->flags & PF_FLAG_WIDTH && spec->flags & PF_FLAG_MINUS &&
			spec->width > wordlen)
		success = ft_dds_spread(dds, ' ', spec->width - wordlen) == E_OK;
	return (success);
}
