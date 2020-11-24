/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_doubletostr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:24:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/24 11:44:11 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_double(t_s *s, double f, t_pf_notation not)
{
	double	power;
	size_t	start;

	f = ft_fabs(f);
	start = s->m->len;
	power = 1.0;
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
