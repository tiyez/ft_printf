/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:28:30 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/23 21:49:31 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define BUFSZ 128
#define FBUFSZ (BUFSZ * 2 + 1)

static int		f_draw(t_dds *dds, t_s *whl, t_s *frc, t_pf_spec *sp)
{
	int				success;
	size_t			len;
	int		dot;

	if (!sp->precision && frc->m->len == 1 && frc->m->ptr[0] == '0')
		frc->m->len = 0;
	dot = !!frc->m->len;
	if (!sp->precision && sp->flags & PF_FLAG_HASH)
		dot = 1;
	ft_smove(frc, whl->m->ptr + whl->m->len + dot, FBUFSZ - whl->m->len - dot);
	if (dot)
		whl->m->ptr[whl->m->len] = '.';
	len = whl->m->len + frc->m->len + dot;
	success = pf_prepend_space(dds, len, sp);
	success = success && pf_prepend_zero(dds, len, sp);
	success = success && ft_ddsappend(dds, (char *)whl->m->ptr, len) == E_OK;
	success = success && pf_append_space(dds, len, sp);
	return (success);
}

static int		count_zeros_from_right(t_s *s)
{
	size_t	i;

	i = 0;
	while (i < s->m->len && s->m->ptr[s->m->len - i - 1] == '0')
		i += 1;
	return (i);
}

static int		g_draw(t_dds *dds, t_s *whl, t_s *frc, t_pf_spec *sp)
{
	int		success;
	size_t	len;
	int		dot;

	frc->m->len -= count_zeros_from_right(frc);
	dot = !!frc->m->len;
	ft_smove(frc, whl->m->ptr + whl->m->len + dot, BUFSZ * 2 - whl->m->len - dot);
	if (dot)
		whl->m->ptr[whl->m->len] = '.';
	len = whl->m->len + frc->m->len + dot;
	success = pf_prepend_space(dds, len, sp);
	success = success && pf_prepend_zero(dds, len, sp);
	success = success && !ft_ddsappend(dds, (char *)whl->m->ptr, len);
	success = success && pf_append_space(dds, len, sp);
	return (success);
}

static int		e_draw(t_dds *dds, t_s *whl, t_s *frc, t_pf_spec *sp)
{
	int		success;
	size_t	len;
	int		dot;

	frc->m->len -= count_zeros_from_right(frc);
	dot = !!frc->m->len;
	ft_smove(frc, whl->m->ptr + whl->m->len + dot, BUFSZ * 2 - whl->m->len - dot);
	if (dot)
		whl->m->ptr[whl->m->len] = '.';
	len = whl->m->len + frc->m->len + dot;
	success = pf_prepend_space(dds, len, sp);
	success = success && pf_prepend_zero(dds, len, sp);
	success = success && !ft_ddsappend(dds, (char *)whl->m->ptr, len);
	success = success && pf_append_space(dds, len, sp);
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
	// (void)dds, (void)val, (void)sp, (void)f_draw;

	ft_sinitraw(&whl, mem, BUFSZ);
	ft_sinitraw(&frc, mem + BUFSZ + 1, BUFSZ);
	if (ft_isinf(sp->val.f) || ft_isnan(sp->val.f))
		success = draw_non_number(dds, &whl, sp->val.f, sp);
	else
	{
		success = pf_double_fract(&frc, ft_modf_rounded(sp->val.f, &sp->val.f, sp->precision), PF_DECNOT, sp->precision);
		success = success && pf_double(&whl, sp->val.f, PF_DECNOT);
		if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_F)
			success = f_draw(dds, &whl, &frc, sp);
		else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_G)
			success = g_draw(dds, &whl, &frc, sp);
		else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_E)
			success = e_draw(dds, &whl, &frc, sp);
	}
	return (success);
}
