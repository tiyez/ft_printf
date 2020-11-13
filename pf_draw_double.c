/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:28:30 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/14 00:37:35 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define TERN(cond, expr1, expr2) ((cond) ? (expr1) : (expr2))
#define FLAG(flg) (spec->flags & PF_FLAG_##flg)

static int		f_draw(t_dds *dds, t_pf_value val, t_pf_notation not,
	t_pf_spec *spec)
{
	char	mem[24 + 1 + 24];
	t_s		whole;
	t_s		fract;
	int		success;
	(void)dds;

	ft_sinitraw(&whole, mem, 24);
	ft_sinitraw(&fract, mem + 25, 24);
	success = pf_double_frac_part(&fract, val.f, not, spec->precision);
	success = success && pf_double_whole_part(&whole, val.f, not);
	if (success)
	{
		ft_smove(&fract, mem + whole.m->len + 1, sizeof(mem) - whole.m->len - 1);
		mem[whole.m->len] = '.';
	}
	return (success);
}

int				pf_draw_double(t_dds *dds, t_pf_value val, t_pf_spec *spec)
{
	int		success;
	(void)dds, (void)val, (void)spec, (void)f_draw;

	success = 0;
	#if 0
	if (ft_isnan(val.f) || ft_isinf(val.f))
		success = infnan_draw(dds, val, spec);
	else if (PF_DOUBLE_MODE(spec->type) == PF_DOUBLE_MODE_F)
		success = f_draw(dds, val.f, {10, "0123456789"}, spec);
	else if (PF_DOUBLE_MODE(spec->type) == PF_DOUBLE_MODE_E)
		success = e_draw(dds, val.f, {10, "0123456789"}, spec);
	else if (PF_DOUBLE_MODE(spec->type) == PF_DOUBLE_MODE_G)
		success = g_draw(dds, val.f, {10, "0123456789"}, spec);
	else if (PF_DOUBLE_MODE(spec->type) == PF_DOUBLE_MODE_A)
		success = f_draw(dds, val.f, {16, PF_IS_DOUBLE_BIG(spec->type) ?
			"0123456789ABCDEF" : "0123456789abcdef"}, spec);
	#endif
	return (success);
}
