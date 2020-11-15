/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:30:56 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/15 07:40:22 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		draw(t_dds *dds, t_pf_spec *spec, t_m *m)
{
	int		res;

	res = pf_prepend_space(dds, m->len, spec);
	res = res && pf_prepend_zero(dds, m->len, spec);
	res = res && ft_ddsappend(dds, (char *)m->ptr, m->len) == E_OK;
	res = res && pf_append_space(dds, m->len, spec);
	return (res);
}

static int		special_cases(t_pf_spec *spec, t_s *s) {
	if (spec->flags & PF_FLAG_PRECISION && !spec->precision &&
		s->m->len == 1 && spec->val.p == NULL)
		s->m->len -= 1;
	if (spec->flags & PF_FLAG_HASH && !PF_IS_DECIMAL(spec->type) &&
		spec->val.p == NULL)
		spec->flags &= ~PF_FLAG_HASH;
	return (1);
}

int				pf_draw_integer(t_dds *dds, t_pf_spec *spec)
{
	char	arr[24];
	t_s		s;
	int		success;

	ft_sinitraw(&s, arr, sizeof(arr));
	success = 1;
	if (PF_IS_SIGNED(spec->type))
		pf_lltostr(&s, pf_get_ll(spec), PF_NOTATION(10, "0123456789"));
	else if (spec->type == PF_TYPE_U)
		pf_llutostr(&s, pf_get_llu(spec), PF_NOTATION(10, "0123456789"));
	else if (spec->type == PF_TYPE_O)
		pf_llutostr(&s, pf_get_llu(spec), PF_NOTATION(8, "01234567"));
	else if (spec->type == PF_TYPE_X)
		pf_llutostr(&s, pf_get_llu(spec), PF_NOTATION(16,
			"0123456789abcdef"));
	else if (spec->type == PF_TYPE_BIGX)
		pf_llutostr(&s, pf_get_llu(spec), PF_NOTATION(16,
			"0123456789ABCDEF"));
	else
		success = 0;
	special_cases(spec, &s);
	success = draw(dds, spec, s.m);
	return (success);
}
