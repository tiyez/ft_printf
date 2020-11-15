/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_value.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:32:15 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/15 07:46:13 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ll		pf_get_ll(t_pf_spec *spec)
{
	long long	n;

	n = 0;
	if (spec->type == PF_TYPE_D || spec->type == PF_TYPE_I)
	{
		if (spec->size == PF_SZ_L)
			n = (long long)spec->val.ld;
		else if (spec->size == PF_SZ_LL)
			n = spec->val.lld;
		else if (spec->size == PF_SZ_J)
			n = (long long)spec->val.jd;
		else if (spec->size == PF_SZ_Z)
			n = (long long)spec->val.zd;
		else
			n = (long long)spec->val.d;
	}
	return (n);
}

t_llu		pf_get_llu(t_pf_spec *spec)
{
	unsigned long long	n;

	n = 0;
	if (spec->type >= PF_TYPE_O && spec->type <= PF_TYPE_BIGX)
	{
		if (spec->size == PF_SZ_L)
			n = (unsigned long long)spec->val.lu;
		else if (spec->size == PF_SZ_LL)
			n = spec->val.llu;
		else if (spec->size == PF_SZ_J)
			n = (unsigned long long)spec->val.ju;
		else if (spec->size == PF_SZ_Z)
			n = (unsigned long long)spec->val.zu;
		else
			n = (unsigned long long)spec->val.u;
	}
	return (n);
}

static void	get_signed_value(t_pf_spec *spec, va_list va)
{
	if (spec->size == PF_SZ_HH)
		spec->val.d = (char)va_arg(va, int);
	else if (spec->size == PF_SZ_H)
		spec->val.d = (short)va_arg(va, int);
	else if (spec->size == PF_SZ_L)
		spec->val.ld = va_arg(va, long);
	else if (spec->size == PF_SZ_LL)
		spec->val.lld = va_arg(va, long long);
	else if (spec->size == PF_SZ_J)
		spec->val.jd = va_arg(va, intmax_t);
	else if (spec->size == PF_SZ_Z)
		spec->val.zd = va_arg(va, ssize_t);
	else
		spec->val.d = va_arg(va, int);
}

static void	get_unsigned_value(t_pf_spec *spec, va_list va)
{
	if (spec->size == PF_SZ_HH)
		spec->val.u = (unsigned char)va_arg(va, int);
	else if (spec->size == PF_SZ_H)
		spec->val.u = (unsigned short)va_arg(va, int);
	else if (spec->size == PF_SZ_L)
		spec->val.lu = va_arg(va, unsigned long);
	else if (spec->size == PF_SZ_LL)
		spec->val.llu = va_arg(va, unsigned long long);
	else if (spec->size == PF_SZ_J)
		spec->val.ju = va_arg(va, uintmax_t);
	else if (spec->size == PF_SZ_Z)
		spec->val.zu = va_arg(va, size_t);
	else
		spec->val.u = va_arg(va, unsigned int);
}

int			pf_get_value(t_pf_spec *spec, va_list va)
{
	int success;

	success = 1;
	spec->val.p = NULL;
	if (PF_IS_SIGNED(spec->type))
		get_signed_value(spec, va);
	else if (PF_IS_UNSIGNED(spec->type))
		get_unsigned_value(spec, va);
	else if (PF_IS_DOUBLE(spec->type))
		spec->val.f = va_arg(va, double);
	else if (spec->type == PF_TYPE_C)
		spec->val.d = va_arg(va, int);
	else if (PF_IS_POINTER(spec->type))
		spec->val.p = va_arg(va, void *);
	else
		success = 0;
	return (success);
}
