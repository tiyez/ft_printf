/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:28:30 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/15 09:19:16 by jsandsla         ###   ########.fr       */
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

	dot = !!frc->m->len;
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

int				pf_draw_double(t_dds *dds, t_pf_spec *sp)
{
	char	mem[FBUFSZ];
	t_s		whl;
	t_s		frc;
	int		success;
	// (void)dds, (void)val, (void)sp, (void)f_draw;

	ft_sinitraw(&whl, mem, BUFSZ);
	ft_sinitraw(&frc, mem + BUFSZ + 1, BUFSZ);
	success = pf_double_fract_part(&frc, sp, PF_DECNOT);
	success = success && pf_double_whole_part(&whl, sp, PF_DECNOT);
	if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_F)
		success = f_draw(dds, &whl, &frc, sp);
	else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_G)
		success = g_draw(dds, &whl, &frc, sp);
	#if 0
	if (ft_isnan(val.f) || ft_isinf(val.f))
		success = infnan_draw(dds, val, sp);
	else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_F)
		success = f_draw(dds, val.f, {10, "0123456789"}, sp);
	else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_E)
		success = e_draw(dds, val.f, {10, "0123456789"}, sp);
	else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_G)
		success = g_draw(dds, val.f, {10, "0123456789"}, sp);
	else if (PF_DOUBLE_MODE(sp->type) == PF_DOUBLE_MODE_A)
		success = f_draw(dds, val.f, {16, PF_IS_DOUBLE_BIG(sp->type) ?
			"0123456789ABCDEF" : "0123456789abcdef"}, sp);
	#endif
	return (success);
}
