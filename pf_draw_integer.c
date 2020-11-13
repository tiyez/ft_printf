/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:30:56 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/14 01:19:52 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		draw(t_dds *dds, t_pf_value val, t_pf_spec *spec, t_m *m)
{
	int		res;

	res = pf_prepend_space(dds, val, m->len, spec);
	res = res && pf_prepend_zero(dds, val, m->len, spec);
	res = res && ft_ddsappend(dds, (char *)m->ptr, m->len) == E_OK;
	res = res && pf_append_space(dds, val, m->len, spec);
	return (res);
}

int				pf_draw_integer(t_dds *dds, t_pf_value val, t_pf_spec *spec)
{
	char	arr[24];
	t_s		s;
	int		success;

	ft_sinitraw(&s, arr, sizeof(arr));
	success = 1;
	if (PF_IS_SIGNED(spec->type))
		pf_lltostr(&s, pf_get_ll(val, spec), PF_NOTATION(10, "0123456789"));
	else if (spec->type == PF_TYPE_U)
		pf_llutostr(&s, pf_get_llu(val, spec), PF_NOTATION(10, "0123456789"));
	else if (spec->type == PF_TYPE_O)
		pf_llutostr(&s, pf_get_llu(val, spec), PF_NOTATION(8, "01234567"));
	else if (spec->type == PF_TYPE_X)
		pf_llutostr(&s, pf_get_llu(val, spec), PF_NOTATION(16,
			"0123456789abcdef"));
	else if (spec->type == PF_TYPE_BIGX)
		pf_llutostr(&s, pf_get_llu(val, spec), PF_NOTATION(16,
			"0123456789ABCDEF"));
	else
		success = 0;
	if (spec->flags & PF_FLAG_PRECISION && !spec->precision &&
		s.m->len == 1 && arr[0] == '0')
		s.m->len -= 1;
	success = draw(dds, val, spec, s.m);
	return (success);
}
