/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:48:17 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/24 13:19:52 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

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

# define PF_IS_NUMBER(d) (PF_IS_INTEGER(d) || PF_IS_DOUBLE(d))

# define PF_TYPE_C		15
# define PF_TYPE_S		16
# define PF_TYPE_P		17
# define PF_TYPE_N		18
# define PF_TYPE_PERCENT 19

# define PF_IS_POINTER(d) ((d) >= PF_TYPE_S && (d) <= PF_TYPE_N)

# define PF_DOUBLE_MODE_F		0
# define PF_DOUBLE_MODE_E		1
# define PF_DOUBLE_MODE_G		2
# define PF_DOUBLE_MODE_A		3

# define PF_DOUBLE_MODE(d) (((d) - PF_TYPE_F) >> 1)
# define PF_IS_DOUBLE_BIG(d) (((d) - PF_TYPE_F) & 1)

# ifndef PF_DDS_RATE
#  define PF_DDS_RATE 256
# endif

# define BUFSZ 128
# define FBUFSZ (BUFSZ * 2 + 1)

typedef unsigned long long	t_llu;
typedef long long	t_ll;

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

typedef struct	s_pf_specificator
{
	t_ushort	flags;
	t_ushort	size;
	t_uint		type;
	int			width;
	int			precision;
	t_pf_value	val;
}				t_pf_spec;

typedef struct	s_pf_notation
{
	size_t		base;
	const char	*sym;
}				t_pf_notation;

# define PF_NOTATION(base, syms) ((t_pf_notation){base, syms})
# define PF_DECNOT PF_NOTATION(10, "0123456789")

size_t			pf_llutostr(t_s *s, t_llu n, t_pf_notation not);
size_t			pf_lltostr(t_s *s, t_ll n, t_pf_notation not);
int				pf_double(t_s *s, double f, t_pf_notation not);
int				pf_double_fract(t_s *s, double f, t_pf_notation not,
	size_t precision);

int				pf_get_value(t_pf_spec *spec, va_list va);
t_llu			pf_get_llu(t_pf_spec *spec);
t_ll			pf_get_ll(t_pf_spec *spec);

t_vs			pf_sign(t_pf_spec *spec);
int				pf_prepend_zero(t_dds *dds, size_t len, t_pf_spec *spec);
int				pf_prepend_space(t_dds *dds, size_t len, t_pf_spec *spec);
int				pf_append_space(t_dds *dds, size_t len, t_pf_spec *spec);

t_pf_spec		pf_parse_spec(t_vs *vs, va_list va);

int				pf_draw_spec(t_dds *dds, t_pf_spec spec, va_list va);
int				pf_draw_integer(t_dds *dds, t_pf_spec *spec);
int				pf_draw_double(t_dds *dds, t_pf_spec *spec);

int				pf_draw_element(t_dds *dds, t_s *s, size_t len, t_pf_spec *sp);
int				pf_modf(t_s *whl, t_s *frc, t_pf_spec *sp);
int				pf_emodf(t_s *whl, t_s *frc, t_pf_spec *sp, int *exp);
size_t			pf_combine(t_s *whl, t_s *frc, t_s *post_cbnull, t_pf_spec *sp);
int				pf_e_modify_value(t_pf_spec *sp);

int				ft_printf(const char *fmt, ...);
int				ft_dprintf(int fd, const char *fmt, ...);
int				ft_snprintf(char *out, size_t n, const char *fmt, ...);
int				ft_vdprintf(int fd, const char *fmt, va_list va);
int				ft_vsnprintf(char *out, size_t n, const char *fmt, va_list va);
int				ft_vddsvsprintf(t_dds *dds, t_vs fmt, va_list va);

#endif
