/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:48:12 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/24 13:35:27 by jsandsla         ###   ########.fr       */
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

static	int	check_flags(t_pf_spec *spec, t_vs *vs, va_list va)
{
	int	error;

	while ((error = check_flag(spec, ft_vs(vs, 0))) > 0)
		ft_vsinc(vs, 1);
	if (error >= 0 && (ft_vs(vs, 0) == '*' || IS_DIGIT(ft_vs(vs, 0))))
	{
		spec->flags |= PF_FLAG_WIDTH;
		if (ft_vsincif(vs, '*', 1))
			spec->width = va_arg(va, int);
		else
			ft_vs_read_uint(vs, (t_uint *)&spec->width);
		spec->flags |= spec->width < 0 ? PF_FLAG_MINUS : 0;
		spec->width = spec->width < 0 ? -spec->width : spec->width;
	}
	if (error >= 0 && ft_vsincif(vs, '.', 1))
	{
		spec->flags |= PF_FLAG_PRECISION;
		if (ft_vsincif(vs, '*', 1))
			spec->precision = va_arg(va, int);
		else
			ft_vs_read_uint(vs, (t_uint *)&spec->precision);
		spec->flags &= spec->precision < 0 ? ~(PF_FLAG_PRECISION) : 0xFFFFFFFF;
		spec->precision = FT_ABS(spec->precision);
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

static	char	g_type_table[][2] =
{
	{'d', PF_TYPE_D}, {'i', PF_TYPE_I}, {'o', PF_TYPE_O}, {'x', PF_TYPE_X},
	{'X', PF_TYPE_BIGX}, {'f', PF_TYPE_F}, {'F', PF_TYPE_BIGF},
	{'e', PF_TYPE_E}, {'E', PF_TYPE_BIGE}, {'g', PF_TYPE_G},
	{'G', PF_TYPE_BIGG}, {'a', PF_TYPE_A}, {'A', PF_TYPE_BIGA},
	{'c', PF_TYPE_C}, {'s', PF_TYPE_S}, {'p', PF_TYPE_P},
	{'n', PF_TYPE_N}, {'%', PF_TYPE_PERCENT}
};

static	int	check_type(t_pf_spec *spec, t_vs *vs)
{
	int		success;
	size_t	array_count;
	size_t	i;

	array_count = sizeof(g_type_table) / sizeof(g_type_table[0]);
	i = 0;
	success = 0;
	while (!success && i < array_count)
	{
		if (ft_vsincif(vs, g_type_table[i][0], 1))
		{
			spec->type = g_type_table[i][1];
			success = 1;
		}
		i += 1;
	}
	return (success);
}

t_pf_spec	pf_parse_spec(t_vs *vs, va_list va)
{
	t_pf_spec	spec;
	int			success;

	spec.flags = 0;
	spec.size = 0;
	spec.type = PF_TYPE_NONE;
	spec.width = 0;
	spec.precision = 0;
	success = check_flags(&spec, vs, va);
	success = success && check_size(&spec, vs);
	success = success && check_type(&spec, vs);
	if (!(spec.flags & PF_FLAG_PRECISION) && PF_IS_DOUBLE(spec.type))
		spec.precision = 6;
	return (spec);
}
