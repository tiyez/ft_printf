/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:48:17 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/04 23:10:31 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <libft.h>

# define PF_FLAG_MINUS			(1 << 0)
# define PF_FLAG_PLUS			(1 << 1)
# define PF_FLAG_SPACE			(1 << 2)
# define PF_FLAG_HASH			(1 << 3)
# define PF_FLAG_ZERO			(1 << 4)
# define PF_FLAG_WIDTH			(1 << 5)
# define PF_FLAG_WIDTH_STAR		(1 << 6)
# define PF_FLAG_PRECISION		(1 << 7)
# define PF_FLAG_PRECISION_STAR	(1 << 8)

# define PF_SZ_L	(1 << 0)
# define PF_SZ_HH	(1 << 1)
# define PF_SZ_H	(1 << 2)
# define PF_SZ_LL	(1 << 3)
# define PF_SZ_J	(1 << 4)
# define PF_SZ_Z	(1 << 5)
# define PF_SZ_T	(1 << 6)
# define PF_SZ_BIGL	(1 << 7)

# define PF_TYPE_NONE	0
# define PF_TYPE_D		1
# define PF_TYPE_I		2
# define PF_TYPE_O		3
# define PF_TYPE_U		4
# define PF_TYPE_X		5
# define PF_TYPE_BIGX	6
# define PF_TYPE_F		7
# define PF_TYPE_BIGF	8
# define PF_TYPE_E		9
# define PF_TYPE_BIGE	10
# define PF_TYPE_G		11
# define PF_TYPE_BIGG	12
# define PF_TYPE_A		13
# define PF_TYPE_BIGA	14
# define PF_TYPE_C		15
# define PF_TYPE_S		16
# define PF_TYPE_P		17
# define PF_TYPE_N		18
# define PF_TYPE_PERCENT 19

# ifndef PF_D_SIZE
#  define PF_D_SIZE 512
# endif

typedef struct	s_pf_specificator
{
	t_ushort	flags;
	t_ushort	size;
	t_uint		type;
	t_uint		width;
	t_uint		precision;
}				t_pf_spec;

t_pf_spec		pf_parse_specificator(t_vs *vs);

int				ft_printf(const char *fmt, ...);
int				ft_fprintf(int fd, const char *fmt, ...);
int				ft_snprintf(char *out, size_t n, const char *fmt, ...);
int				ft_vfprintf(int fd, const char *fmt, va_list va);
int				ft_vddprintf(t_dd *dd, const char *fmt, va_list va);
int				ft_vsnprintf(char *out, size_t n, const char *fmt, va_list va);
int				ft_vsnvsprintf(char *out, size_t n, t_vs *vs, va_list va);

#endif
