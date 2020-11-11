/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:48:17 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/11 03:39:53 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <libft.h>
# include <stdarg.h>
# include <inttypes.h>
# include <unistd.h>

# define PF_FLAG_MINUS		(1 << 0)
# define PF_FLAG_PLUS		(1 << 1)
# define PF_FLAG_SPACE		(1 << 2)
# define PF_FLAG_HASH		(1 << 3)
# define PF_FLAG_ZERO		(1 << 4)
# define PF_FLAG_WIDTH		(1 << 5)
# define PF_FLAG_PRECISION	(1 << 6)

# define PF_FLAG(spec,flg) ((spec)->flags & PF_FLAG_##flg)

# define PF_SZ_L	1
# define PF_SZ_HH	2
# define PF_SZ_H	3
# define PF_SZ_LL	4
# define PF_SZ_J	5
# define PF_SZ_Z	6

# define PF_TYPE_NONE	0

# define PF_TYPE_D		1
# define PF_TYPE_I		2
# define PF_TYPE_O		3
# define PF_TYPE_U		4
# define PF_TYPE_X		5
# define PF_TYPE_BIGX	6

# define PF_IS_INTEGER(d) ((d) >= PF_TYPE_D && (d) <= PF_TYPE_BIGX)
# define PF_IS_SIGNED(d) ((d) >= PF_TYPE_D && (d) <= PF_TYPE_I)
# define PF_IS_UNSIGNED(d) ((d) >= PF_TYPE_O && (d) <= PF_TYPE_BIGX)
# define PF_IS_DECIMAL(d) (PF_IS_SIGNED(d) || (d) == PF_TYPE_U)

# define PF_TYPE_F		7
# define PF_TYPE_BIGF	8
# define PF_TYPE_E		9
# define PF_TYPE_BIGE	10
# define PF_TYPE_G		11
# define PF_TYPE_BIGG	12
# define PF_TYPE_A		13
# define PF_TYPE_BIGA	14

# define PF_IS_DOUBLE(d) ((d) >= PF_TYPE_F && (d) <= PF_TYPE_BIGA)

# define PF_TYPE_C		15
# define PF_TYPE_S		16
# define PF_TYPE_P		17
# define PF_TYPE_N		18
# define PF_TYPE_PERCENT 19

# define PF_IS_POINTER(d) ((d) >= PF_TYPE_S && (d) <= PF_TYPE_N)

# define PF_DOUBLE_MODE_F		0
# define PF_DOUBLE_MODE_E		2
# define PF_DOUBLE_MODE_G		4
# define PF_DOUBLE_MODE_A		6

# ifndef PF_DDS_RATE
#  define PF_DDS_RATE 256
# endif

typedef unsigned long long	t_llu;
typedef long long	t_ll;

typedef struct	s_pf_specificator
{
	t_ushort	flags;
	t_ushort	size;
	t_uint		type;
	t_uint		width;
	t_uint		precision;
}				t_pf_spec;

typedef union	u_pf_value
{
	int					d;
	unsigned int		u;
	long				ld;
	unsigned long		lu;
	long long			lld;
	unsigned long long	llu;
	double				f;
	intmax_t			jd;
	uintmax_t			ju;
	ssize_t				zd;
	size_t				zu;
	void				*p;
}				t_pf_value;

size_t			pf_llutostr(t_s *s, t_llu n, int base, const char *sym);
size_t			pf_lltostr(t_s *s, t_ll n, int base, const char *sym);
int				pf_doubletostr(char *out, double n, int mode, const char *sym);

int				pf_get_value(t_pf_value *val, t_pf_spec *spec, va_list va);
t_llu			pf_get_llu(t_pf_value val, t_pf_spec *spec);
t_ll			pf_get_ll(t_pf_value val, t_pf_spec *spec);

t_pf_spec		pf_parse_spec(t_vs *vs, va_list va);

int				pf_draw_spec(t_dds *dds, t_pf_spec spec, va_list va);
int				pf_draw_integer(t_dds *dds, t_pf_value val, t_pf_spec *spec);
int				pf_draw_double(t_dds *dds, double val, t_pf_spec *spec);

int				ft_printf(const char *fmt, ...);
int				ft_fprintf(int fd, const char *fmt, ...);
int				ft_snprintf(char *out, size_t n, const char *fmt, ...);
int				ft_vfprintf(int fd, const char *fmt, va_list va);
int				ft_vsnprintf(char *out, size_t n, const char *fmt, va_list va);
int				ft_vddsvsprintf(t_dds *dds, t_vs fmt, va_list va);

#endif
