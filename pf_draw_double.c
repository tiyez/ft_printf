/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:28:30 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/24 12:17:12 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		f_draw(t_dds *dds, t_s *whl, t_s *frc, t_pf_spec *sp)
{
	int				success;
	size_t			len;

	len = pf_combine(whl, frc, NULL, sp);
	success = pf_draw_element(dds, whl, len, sp);
	return (success);
}

static int		g_draw(t_dds *dds, t_s *whl, t_s *frc, t_pf_spec *sp)
{
	int		success;
	size_t	len;
	int		dot;

	len = 0;
	while (len < frc->m->len && frc->m->ptr[frc->m->len - len - 1] == '0')
		len += 1;
	frc->m->len -= len;
	dot = !!frc->m->len;
	ft_smove(frc, whl->m->ptr + whl->m->len + dot,
		BUFSZ * 2 - whl->m->len - dot);
	if (dot)
		whl->m->ptr[whl->m->len] = '.';
	len = whl->m->len + frc->m->len + dot;
	success = pf_draw_element(dds, whl, len, sp);
	return (success);
}

static int		e_draw(t_dds *dds, t_s *whl, t_s *frc, t_pf_spec *sp)
{
	char	buf[16];
	t_s		post;
	int		success;
	int		exp;
	size_t	len;

	ft_sinitraw(&post, buf, sizeof(buf));
	exp = pf_e_modify_value(sp);
	whl->m->len = 0;
	frc->m->len = 0;
	pf_emodf(whl, frc, sp, &exp);
	ft_sappend(&post, PF_IS_DOUBLE_BIG(sp->type) ? "E" : "e");
	ft_sappend(&post, exp < 0 ? "-" : "+");
	if (FT_ABS(exp) < 10)
		ft_sappendc(&post, '0');
	ft_s_unsigned(&post, FT_ABS(exp));
	len = pf_combine(whl, frc, &post, sp);
	success = pf_draw_element(dds, whl, len, sp);
	return (success);
}

static	int		draw_non_number(t_dds *dds, t_s *s, double val, t_pf_spec *spec)
{
	int		success;
	size_t	len;

	if (ft_isinf(val))
		ft_sappend(s, PF_IS_DOUBLE_BIG(spec->type) ? "INF" : "inf");
	else if (ft_isnan(val))
		ft_sappend(s, PF_IS_DOUBLE_BIG(spec->type) ? "NAN" : "nan");
	len = s->m->len;
	success = pf_prepend_space(dds, len, spec);
	success = success && pf_prepend_zero(dds, len, spec);
	success = success && ft_ddsappend(dds, (char *)s->m->ptr, len) == E_OK;
	success = success && pf_append_space(dds, len, spec);
	return (success);
}

int				pf_draw_double(t_dds *dds, t_pf_spec *sp)
{
	char	mem[FBUFSZ];
	t_s		whl;
	t_s		frc;
	int		success;

	ft_sinitraw(&whl, mem, BUFSZ);
	ft_sinitraw(&frc, mem + BUFSZ + 1, BUFSZ);
	success = pf_modf(&whl, &frc, sp);
	if (ft_isinf(sp->val.f) || ft_isnan(sp->val.f))
		success = draw_non_number(dds, &whl, sp->val.f, sp);
	else
	{
		if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_F)
			success = f_draw(dds, &whl, &frc, sp);
		else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_G)
			success = g_draw(dds, &whl, &frc, sp);
		else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_E)
			success = e_draw(dds, &whl, &frc, sp);
	}
	return (success);
}
