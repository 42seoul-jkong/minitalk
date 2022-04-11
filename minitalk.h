/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:59:42 by jkong             #+#    #+#             */
/*   Updated: 2022/04/11 21:11:05 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef VECTOR_SIZE
#  define VECTOR_SIZE 1024
# endif

# define ANSI_ESC_BOLD "\033[1m"
# define ANSI_ESC_NORMAL "\033[22m"
# define ANSI_ESC_FG_RED "\033[31m"
# define ANSI_ESC_FG_DEFAULT "\033[39m"

typedef unsigned long	t_bit_set;

enum	e_bit_set_constant
{
	BIT_COUNT = 8,
	BITSET_MAX = sizeof(t_bit_set) * BIT_COUNT
};

typedef struct s_bit_buf
{
	t_bit_set	*buf;
	size_t		capacity;
	size_t		sequence;
	size_t		limit;
}	t_bit_buf;

/*
 * 0.0025sec * 4cnt for 1msg/0.01sec.
 * to sufficient, use 0.002sec * 3cnt
 */
enum	e_timeout_constant
{
	TIMEOUT_IN_MICROS = 20000000, //2000,
	TIMEOUT_MAX_COUNT = 3
};

typedef struct s_client
{
	pid_t		pid;
	t_bit_buf	*buf;
	int			fail;
}	t_client;

typedef void			(*t_sighandler)(int, siginfo_t *, void *);
typedef int				(*t_appupdater)(void);

/*
 * MiniTalk functions (minitalk.c)
 */
void		pretty_error(char *s);

/*
 * Signal functions (signal.c)
 */
void		signal_bind(t_sighandler handler);
void		signal_listen(t_appupdater updater);

/*
 * Bit Buffer functions (bit_buf.c bit_buf_ext.c)
 */
t_bit_buf	*bit_buf_init(void);
void		bit_buf_destroy(t_bit_buf *p);
void		bit_buf_retain(t_bit_buf *p);
int			bit_buf_get_bit(t_bit_buf *p);
void		bit_buf_put_bit(t_bit_buf *p, int val);
size_t		bit_buf_append(t_bit_buf *p, const void *buf, size_t nbyte);
int			bit_buf_terminate(t_bit_buf *p, int null);

/*
 * Forty-Two Library functions (libft*.c)
 */
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_try_atoi(const char *str, int *out);

/*
 * Safety Memory Allocation functions (safe_mem.c)
 */
void		*malloc_safe(size_t size);
void		*calloc_safe(size_t count, size_t size);

/*
 * Safety Input/Output Streaming functions (safe_io.c)
 */
int			read_safe(int fd, void *buf, size_t len);
void		write_safe(int fd, const void *buf, size_t len);
void		putstr_safe(const char *str);
void		putnbr_safe(int n);
void		puterr_safe(const char *str);

#endif
