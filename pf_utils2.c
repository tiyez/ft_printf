/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:14:13 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/24 12:16:52 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_draw_element(t_dds *dds, t_s *s, size_t len, t_pf_spec *sp)
{
	int success;

	success = pf_prepend_space(dds, len, sp);
	success = success && pf_prepend_zero(dds, len, sp);
	success = success && !ft_ddsappend(dds, (char *)s->m->ptr, len);
	success = success && pf_append_space(dds, len, sp);
	return (success);
}

int		pf_modf(t_s *whl, t_s *frc, t_pf_spec *sp)
{
	int		success;
	double	dint;

	success = pf_double_fract(frc,
		ft_modf_rounded(sp->val.f, &dint, sp->precision), PF_DECNOT,
			sp->precision);
	success = success && pf_double(whl, dint, PF_DECNOT);
	return (success);
}

int		pf_emodf(t_s *whl, t_s *frc, t_pf_spec *sp, int *exp)
{
	int		success;
	double	dint;

	if (sp->precision)
		success = pf_double_fract(frc,
			ft_modf_rounded(sp->val.f, &dint, sp->precision), PF_DECNOT,
				sp->precision);
	else
		success = pf_double_fract(frc,
			ft_modf_erounded(sp->val.f, &dint, sp->precision), PF_DECNOT,
				sp->precision);
	while (ft_fabs(dint) >= 10 && ++*exp)
		dint /= 10;
	success = success && pf_double(whl, dint, PF_DECNOT);
	return (success);
}

size_t	pf_combine(t_s *whl, t_s *frc, t_s *post_cbnull, t_pf_spec *sp)
{
	int		dot;
	size_t	len;

	if (!sp->precision && frc->m->len == 1 && frc->m->ptr[0] == '0')
		frc->m->len = 0;
	dot = !!frc->m->len;
	if (!sp->precision && sp->flags & PF_FLAG_HASH)
		dot = 1;
	ft_smove(frc, whl->m->ptr + whl->m->len + dot, FBUFSZ - whl->m->len - dot);
	if (dot)
		whl->m->ptr[whl->m->len] = '.';
	len = whl->m->len + frc->m->len + dot;
	if (post_cbnull)
	{
		ft_smove(post_cbnull, whl->m->ptr + len, FBUFSZ - len);
		len += post_cbnull->m->len;
	}
	return (len);
}

int		pf_e_modify_value(t_pf_spec *sp)
{
	double		val;
	int			exp;
	t_ieee754	ieee754;

	exp = 0;
	val = ft_fabs(sp->val.f);
	while (val && val < 1.0 && --exp)
		val *= 10;
	while (val && val >= 10.0 && ++exp)
		val /= 10;
	ieee754.f = sp->val.f;
	sp->val.f = (ieee754.u >> 63 ? -1 : 1) * val;
	return (exp);
}
