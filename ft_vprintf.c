/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:55:23 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/09 02:31:51 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_vfprintf(int fd, const char *fmt, va_list va)
{
	t_dds	dds;
	int		result;
	size_t	i;
	t_s		s;

	ft_ddsinit(&dds, PF_DDS_RATE);
	result = ft_vddsvsprintf(&dds, ft_vscreatestr(fmt), va);
	i = 0;
	while (i < dds.dd.len)
	{
		s = ft_dds(&dds, i);
		write(fd, s.m->ptr, s.len);
		i += 1;
	}
	ft_ddsfree(&dds);
	return (result);
}

int				ft_vsnprintf(char *out, size_t n, const char *fmt, va_list va)
{
	t_dds	dds;
	int		result;
	size_t	i;
	size_t	len;
	t_s		s;

	result = 0;
	if (n > 0)
	{
		n -= 1;
		ft_ddsinit(&dds, PF_DDS_RATE);
		result = ft_vddsvsprintf(&dds, ft_vscreatestr(fmt), va);
		i = 0;
		while (n > 0 && i < dds.dd.len)
		{
			s = ft_dds(&dds, i);
			len = ft_strncpy(out, (char *)s.m->ptr, FT_MIN(n, s.len));
			out += len;
			n -= len;
			i += 1;
		}
		*out = '\0';
		ft_ddsfree(&dds);
	}
	return (result);
}

int				ft_vddsvsprintf(t_dds *dds, t_vs fmt, va_list va)
{
	size_t	start;
	int		success;

	success = 1;
	start = 0;
	while (success && ft_vs(&fmt, 0) != '\0')
	{
		if (ft_vs(&fmt, 0) == '%')
		{
			if (fmt.offset > start)
				success = !ft_ddsappend(dds, fmt.ptr + start,
					fmt.offset - start);
			if (success)
			{
				ft_vsinc(&fmt, 1);
				success = pf_draw_spec(dds, pf_parse_spec(&fmt, va), va);
				start = fmt.offset;
			}
		}
		else
			ft_vsinc(&fmt, 1);
	}
	if (fmt.offset > start)
		success = !ft_ddsappend(dds, fmt.ptr + start, fmt.offset - start);
	return (success ? (int)ft_dds_len(dds) : -1);
}
