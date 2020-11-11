/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:51:15 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/11 03:03:45 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *fmt, ...)
{
	va_list	va;
	int		result;

	va_start(va, fmt);
	result = ft_vfprintf(STDOUT_FILENO, fmt, va);
	va_end(va);
	return (result);
}

int				ft_fprintf(int fd, const char *fmt, ...)
{
	va_list	va;
	int		result;

	va_start(va, fmt);
	result = ft_vfprintf(fd, fmt, va);
	va_end(va);
	return (result);
}

int				ft_snprintf(char *out, size_t n, const char *fmt, ...)
{
	va_list	va;
	int		result;

	va_start(va, fmt);
	result = ft_vsnprintf(out, n, fmt, va);
	va_end(va);
	return (result);
}
