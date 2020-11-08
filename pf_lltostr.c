/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_lltostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:42:51 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/09 03:08:33 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			pf_llutostr(t_s *s, unsigned long long n, int base,
	const char *sym)
{
	size_t	start;

	start = s->len;
	if (!n)
		ft_sappendc(s, sym[0]);
	while (n > 0)
	{
		ft_sappendc(s, sym[n % base]);
		n /= base;
	}
	if (s->len - start)
		ft_sreverse(s, start, s->len - start);
	return (s->len - start);
}

size_t			absolute(long long n)
{
	return (n < 0 ? -n : n);
}

size_t			pf_lltostr(t_s *s, long long n, int base, const char *sym)
{
	size_t	start;

	start = s->len;
	if (!n)
		ft_sappendc(s, sym[0]);
	while (n != 0)
	{
		ft_sappendc(s, sym[absolute(n % base)]);
		n /= base;
	}
	if (s->len - start)
		ft_sreverse(s, start, s->len - start);
	return (s->len - start);
}
