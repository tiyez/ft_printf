/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_doubletostr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:24:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/14 00:42:40 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_ll		own_llabs(t_ll ll)
{
	return (ll < 0 ? -ll : ll);
}

int				pf_double_whole_part(t_s *s, double f, t_pf_notation not)
{
	size_t	start;

	start = s->m->len;
	if (f < 1.0)
		ft_sappendc(s, not.sym[0]);
	while (f >= 1.0)
	{
		ft_sappendc(s, not.sym[own_llabs((t_ll)f) % not.base]);
		f /= not.base;
	}
	if (s->m->len - start)
		ft_sreverse(s, start, s->m->len - start);
	return (s->m->len - start);
}

int				pf_double_frac_part(t_s *s, double f, t_pf_notation not,
	size_t precision)
{
	size_t	start;

	start = s->m->len;
	while (precision > 0)
	{
		f *= not.base;
		ft_sappendc(s, not.sym[llabs((t_ll)f) % not.base]);
		precision -= 1;
	}
	if (s->m->len - start)
		ft_sreverse(s, start, s->m->len - start);
	return (s->m->len - start);
}
