/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:48:12 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/13 20:24:14 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	check_flag(t_pf_spec *spec, char c)
{
	int	success;

	success = 1;
	if (c == '-')
		spec->flags |= PF_FLAG_MINUS;
	else if (c == '+')
		spec->flags |= PF_FLAG_PLUS;
	else if (c == ' ')
		spec->flags |= PF_FLAG_SPACE;
	else if (c == '#')
		spec->flags |= PF_FLAG_HASH;
	else if (c == '0')
		spec->flags |= PF_FLAG_ZERO;
	else
		success = 0;
	return (success);
}

static	int	check_flags(t_pf_spec *spec, t_vs *vs, va_list va, int *w, int *p)
{
	int	error;

	while ((error = check_flag(spec, ft_vs(vs, 0))) > 0)
		ft_vsinc(vs, 1);
	if (error >= 0)
	{
		if (ft_vs(vs, 0) == '*' || IS_DIGIT(ft_vs(vs, 0)))
		{
			spec->flags |= PF_FLAG_WIDTH;
			*w = ft_vsincif(vs, '*', 1) ? va_arg(va, int) : 
				(ft_vs_read_uint(vs, &spec->width), (int)spec->width);
			spec->flags |= *w < 0 ? PF_FLAG_MINUS : 0;
			spec->width = *w < 0 ? -*w : *w;
		}
		if (ft_vsincif(vs, '.', 1))
		{
			spec->flags |= PF_FLAG_PRECISION;
			*p = ft_vsincif(vs, '*', 1) ? va_arg(va, int) :
				(ft_vs_read_uint(vs, &spec->precision), (int)spec->precision);
			if (*p < 0)
				spec->flags &= ~(PF_FLAG_PRECISION);
			spec->precision = *p < 0 ? -*p : *p;
		}
	}
	return (error < 0 ? 0 : 1);
}

static	int	check_size(t_pf_spec *spec, t_vs *vs)
{
	if (ft_vsincif(vs, 'l', 1))
	{
		if (ft_vsincif(vs, 'l', 1))
			spec->size = PF_SZ_LL;
		else
			spec->size = PF_SZ_L;
	}
	else if (ft_vsincif(vs, 'h', 1))
	{
		if (ft_vsincif(vs, 'h', 1))
			spec->size = PF_SZ_HH;
		else
			spec->size = PF_SZ_H;
	}
	else if (ft_vsincif(vs, 'j', 1))
		spec->size = PF_SZ_J;
	else if (ft_vsincif(vs, 'z', 1))
		spec->size = PF_SZ_Z;
	return (1);
}

#define CHECK(c,f) if (ft_vsincif(vs, c, 1)) spec->type = PF_TYPE_##f; else
#define COMPOSER(c) c('d',D)c('i',I)c('o',O)c('u',U)c('x',X)c('X',BIGX)c('f',F)
#define COMPOSER2(c) c('F',BIGF)c('e',E)c('E',BIGE)c('g',G)c('G',BIGG)c('a',A)
#define COMPOSER3(c) c('A',BIGA)c('c',C)c('s',S)c('p',P)c('n',N)c('%',PERCENT)
#define COMPOSER0(c) COMPOSER(c)COMPOSER2(c)COMPOSER3(c) error = 0

static	int	check_type(t_pf_spec *spec, t_vs *vs)
{
	int	error;

	error = 1;
	COMPOSER0(CHECK);
	return (error);
}

#undef CHECK
#undef COMPOSER
#undef COMPOSER2
#undef COMPOSER3
#undef COMPOSER0

t_pf_spec	pf_parse_spec(t_vs *vs, va_list va)
{
	t_pf_spec	spec;
	int			success;
	int			w;
	int			p;

	spec.flags = 0;
	spec.size = 0;
	spec.type = PF_TYPE_NONE;
	spec.width = 0;
	spec.precision = 0;
	success = check_flags(&spec, vs, va, &w, &p);
	success = success && check_size(&spec, vs);
	success = success && check_type(&spec, vs);
	if (!(spec.flags & PF_FLAG_PRECISION) && PF_IS_DOUBLE(spec.type))
		spec.precision = 6;
	return (spec);
}
