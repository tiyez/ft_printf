/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_value.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:32:15 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/11 04:41:11 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ll		pf_get_ll(t_pf_value val, t_pf_spec *spec)
{
	long long	n;

	n = 0;
	if (spec->type == PF_TYPE_D || spec->type == PF_TYPE_I)
	{
		if (spec->size == PF_SZ_L)
			n = (long long)val.ld;
		else if (spec->size == PF_SZ_LL)
			n = val.lld;
		else if (spec->size == PF_SZ_J)
			n = (long long)val.jd;
		else if (spec->size == PF_SZ_Z)
			n = (long long)val.zd;
		else
			n = (long long)val.d;
	}
	return (n);
}

t_llu		pf_get_llu(t_pf_value val, t_pf_spec *spec)
{
	unsigned long long	n;

	n = 0;
	if (spec->type >= PF_TYPE_O && spec->type <= PF_TYPE_BIGX)
	{
		if (spec->size == PF_SZ_L)
			n = (unsigned long long)val.lu;
		else if (spec->size == PF_SZ_LL)
			n = val.llu;
		else if (spec->size == PF_SZ_J)
			n = (unsigned long long)val.ju;
		else if (spec->size == PF_SZ_Z)
			n = (unsigned long long)val.zu;
		else
			n = (unsigned long long)val.u;
	}
	return (n);
}

static void	get_signed_value(t_pf_value *val, t_pf_spec *spec, va_list va)
{
	if (spec->size == PF_SZ_HH)
		val->d = (char)va_arg(va, int);
	else if (spec->size == PF_SZ_H)
		val->d = (short)va_arg(va, int);
	else if (spec->size == PF_SZ_L)
		val->ld = va_arg(va, long);
	else if (spec->size == PF_SZ_LL)
		val->lld = va_arg(va, long long);
	else if (spec->size == PF_SZ_J)
		val->jd = va_arg(va, intmax_t);
	else if (spec->size == PF_SZ_Z)
		val->zd = va_arg(va, ssize_t);
	else
		val->d = va_arg(va, int);
}

static void	get_unsigned_value(t_pf_value *val, t_pf_spec *spec, va_list va)
{
	if (spec->size == PF_SZ_HH)
		val->u = (unsigned char)va_arg(va, int);
	else if (spec->size == PF_SZ_H)
		val->u = (unsigned short)va_arg(va, int);
	else if (spec->size == PF_SZ_L)
		val->lu = va_arg(va, unsigned long);
	else if (spec->size == PF_SZ_LL)
		val->llu = va_arg(va, unsigned long long);
	else if (spec->size == PF_SZ_J)
		val->ju = va_arg(va, uintmax_t);
	else if (spec->size == PF_SZ_Z)
		val->zu = va_arg(va, size_t);
	else
		val->u = va_arg(va, unsigned int);
}

int			pf_get_value(t_pf_value *val, t_pf_spec *spec, va_list va)
{
	int success;

	success = 1;
	val->p = NULL;
	if (PF_IS_SIGNED(spec->type))
		get_signed_value(val, spec, va);
	else if (PF_IS_UNSIGNED(spec->type))
		get_unsigned_value(val, spec, va);
	else if (PF_IS_DOUBLE(spec->type))
		val->f = va_arg(va, double);
	else if (spec->type == PF_TYPE_C)
		val->d = va_arg(va, int);
	else if (PF_IS_POINTER(spec->type))
		val->p = va_arg(va, void *);
	else
		success = 0;
	return (success);
}
