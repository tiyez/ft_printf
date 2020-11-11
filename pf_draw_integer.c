/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:30:56 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/11 03:28:41 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		is_value_negative(t_pf_value val, t_pf_spec *spec)
{
	int		result;

	result = 0;
	if (PF_IS_SIGNED(spec->type))
	{
		if (spec->size == PF_SZ_L)
			result = val.ld < 0;
		else if (spec->size == PF_SZ_LL)
			result = val.lld < 0;
		else if (spec->size == PF_SZ_J)
			result = val.jd < 0;
		else if (spec->size == PF_SZ_Z)
			result = val.zd < 0;
		else
			result = val.d < 0;
	}
	return (result);
}

#define TERN(cond,expr1,expr2) (cond ? expr1 : expr2)
#define TYPE(t) (spec->type == PF_TYPE_##t)
#define FLAG(t) (spec->flags & PF_FLAG_##t)

static	int		draw(t_dds *dds, t_pf_value val, t_pf_spec *spec, t_m *m)
{
	char	prepend;
	char	sign;
	t_vs	hash;
	int		res;
	size_t	wordlen;

	hash = FLAG(HASH) ? TERN(TYPE(O), ft_vscreatestr("0"), TERN(TYPE(X),
		ft_vscreatestr("0x"), TERN(TYPE(BIGX), ft_vscreatestr("0X"),
		ft_vscreatestr("")))) : ft_vscreatestr("");
	sign = PF_IS_DECIMAL(spec->type) ? TERN(is_value_negative(val, spec), '-',
		TERN(FLAG(PLUS), '+', TERN(FLAG(SPACE), ' ', 0))) : 0;
	prepend = FLAG(ZERO) && !FLAG(PRECISION) ? '0' : ' ';
	res = prepend == '0' && sign ? (ft_ddsappendc(dds, sign) == E_OK) : 1;
	res = prepend == '0' ? (ft_ddsappendvs(dds, &hash) == E_OK) : res;
	wordlen = m->len + !!sign + hash.len + FT_USUB(spec->precision, m->len);
	res = FLAG(WIDTH) && !FLAG(MINUS) && spec->width > wordlen ?
		ft_dds_spread(dds, prepend, spec->width - wordlen) == E_OK : res;
	res = prepend == ' ' && sign ? (ft_ddsappendc(dds, sign) == E_OK) : res;
	res = prepend == ' ' ? (ft_ddsappendvs(dds, &hash) == E_OK) : res;
	res = FLAG(PRECISION) ? ft_dds_spread(dds, '0',
		FT_USUB(spec->precision, m->len)) == E_OK : res;
	res = res && ft_ddsappend(dds, (char *)m->ptr, m->len) == E_OK;
	res = FLAG(WIDTH) && FLAG(MINUS) && spec->width > wordlen ?
		ft_dds_spread(dds, ' ', spec->width - wordlen) == E_OK : res;
	return (res);
}

int				pf_draw_integer(t_dds *dds, t_pf_value val, t_pf_spec *spec)
{
	char	arr[24];
	t_s		s;
	int		success;

	arr[0] = '\0';
	ft_sinitn(&s, arr, sizeof(arr) - 1);
	success = 1;
	if (PF_IS_SIGNED(spec->type))
		pf_lltostr(&s, pf_get_ll(val, spec), 10, "0123456789");
	else if (spec->type == PF_TYPE_U)
		pf_llutostr(&s, pf_get_llu(val, spec), 10, "0123456789");
	else if (spec->type == PF_TYPE_O)
		pf_llutostr(&s, pf_get_llu(val, spec), 8, "01234567");
	else if (spec->type == PF_TYPE_X)
		pf_llutostr(&s, pf_get_llu(val, spec), 16, "0123456789abcdef");
	else if (spec->type == PF_TYPE_BIGX)
		pf_llutostr(&s, pf_get_llu(val, spec), 16, "0123456789ABCDEF");
	else
		success = 0;
	if (FLAG(PRECISION) && !spec->precision && s.m->len == 1 && arr[0] == '0')
		s.m->len -= 1;
	success = draw(dds, val, spec, s.m);
	return (success);
}
