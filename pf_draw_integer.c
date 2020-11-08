/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_draw_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:30:56 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/09 01:48:12 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		draw_pre_flags(t_dds *dds, t_pf_value val, t_pf_spec *spec)
{
	(void)dds, (void)val, (void)spec;
	return (1);
}

static	int		draw_flags(t_dds *dds, t_pf_value val, t_pf_spec *spec, t_s *s)
{
	t_err	error;

	(void)dds, (void)val, (void)spec;
	error = ft_ddsappends(dds, s);
	return (error == E_OK);
}

static	int		draw_post_flags(t_dds *dds, t_pf_value val, t_pf_spec *spec)
{
	(void)dds, (void)val, (void)spec;
	return (1);
}

int				pf_draw_integer(t_dds *dds, t_pf_value val, t_pf_spec *spec)
{
	char	arr[24];
	t_s		s;
	int		success;

	arr[0] = '\0';
	ft_sinitn(&s, arr, sizeof(arr) - 1);
	success = 1;
	if (PF_IS_SIGNED(spec->type))
		pf_lltostr(&s, pf_get_ll(val, spec), 10, "0123456789");
	else if (spec->type == PF_TYPE_U)
		pf_llutostr(&s, pf_get_llu(val, spec), 10, "0123456789");
	else if (spec->type == PF_TYPE_O)
		pf_llutostr(&s, pf_get_llu(val, spec), 8, "01234567");
	else if (spec->type == PF_TYPE_X)
		pf_llutostr(&s, pf_get_llu(val, spec), 16, "0123456789abcdef");
	else if (spec->type == PF_TYPE_BIGX)
		pf_llutostr(&s, pf_get_llu(val, spec), 16, "0123456789ABCDEF");
	else
		success = 0;
	success = success && draw_pre_flags(dds, val, spec);
	success = success && draw_flags(dds, val, spec, &s);
	success = success && draw_post_flags(dds, val, spec);
	return (success);
}
