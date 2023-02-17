#ifndef FT_NM_H
# define FT_NM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <elf.h>

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	ft_putnbr_fd(int n, int fd);
int     ft_isalnum(int c);

#endif