/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_doubletostr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:24:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/17 06:19:11 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#if 0
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
#endif
#include <stdio.h>
int		pf_double(t_s *s, double f, t_pf_notation not)
{
	double	power;
	size_t	start;

	f = ft_fabs(f);
	start = s->m->len;
	power = 1.0;
	// printf(":%f\n", f);
	if (f < power)
		ft_sappendc(s, not.sym[0]);
	while (f >= power && s->m->len + 1 < s->m->cap)
	{
		ft_sappendc(s, not.sym[(t_ll)(f / power) % not.base]);
		power *= not.base;
	}
	if (s->m->len - start)
		ft_sreverse(s, start, s->m->len - start);
	return (1);
}

int		pf_double_fract(t_s *s, double f, t_pf_notation not, size_t precision)
{
	double	power;
	size_t	start;

	f = ft_fabs(f);
	start = s->m->len;
	power = 1.0;
	// printf(":%f\n", f);
	if (f < power)
		ft_sappendc(s, not.sym[0]);
	while (f >= power && s->m->len + 1 < s->m->cap)
	{
		ft_sappendc(s, not.sym[(t_ll)(f / power) % not.base]);
		power *= not.base;
	}
	while (s->m->len - start < precision && s->m->len + 1 < s->m->cap)
		ft_sappendc(s, not.sym[0]);
	if (s->m->len - start)
		ft_sreverse(s, start, s->m->len - start);
	return (1);
}
