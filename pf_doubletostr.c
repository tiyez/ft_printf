/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_doubletostr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:24:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/15 09:23:46 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const double	g_double_powers[] = {
	1.0,
	10.0,
	100.0,
	1000.0,
	10000.0,
	100000.0,
	1000000.0,
	10000000.0,
	100000000.0,
	1000000000.0,
	10000000000.0,
	100000000000.0,
	1000000000000.0,
	10000000000000.0,
	100000000000000.0,
	1000000000000000.0,
	10000000000000000.0,
};

static	double	round_double(double d, int precision)
{
	double	db;
	double	fr;

	db = d * g_double_powers[precision];
	fr = (db - (t_ll)db);
	db = fr >= 0.5 ? db - fr + 1 : db - fr;
	db /= g_double_powers[precision];
	return (db);
}

int				pf_double_whole_part(t_s *s, t_pf_spec *sp, t_pf_notation not)
{
	size_t	start;
	double	f;
	size_t	i;
	size_t	precision;

	start = s->m->len;
	precision = sp->precision > 16 ? 16 : sp->precision;
	f = sp->val.f;
	if (f < 0.0)
		f = -f;
	f = round_double(f, precision);
	if (f < 1.0)
		ft_sappendc(s, not.sym[0]);
	i = 0;
	while (i < 16 && f / g_double_powers[i] >= 1.0)
	{
		ft_sappendc(s, not.sym[(t_ll)(f / g_double_powers[i]) % not.base]);
		i += 1;
	}
	if (s->m->len - start)
		ft_sreverse(s, start, s->m->len - start);
	return (s->m->len - start);
}

int				pf_double_fract_part(t_s *s, t_pf_spec *sp, t_pf_notation not)
{
	size_t	precision;
	double	f;
	size_t	i;

	precision = sp->precision > 16 ? 16 : sp->precision;
	f = sp->val.f;
	if (f < 0.0)
		f = -f;
	f = round_double(f, precision);
	i = 0;
	while (i < precision)
	{
		ft_sappendc(s, not.sym[(t_ll)(f * g_double_powers[i + 1])
			% not.base]);
		i += 1;
	}
	return (1);
}
