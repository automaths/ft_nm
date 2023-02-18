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
#include <stdbool.h>

#define ERR_MALLOC "Error: failed malloc\n"

typedef struct s_argv {
    bool a;
    bool g;
    bool p;
    bool r;
    bool u;
    char **files;
} t_argv;

typedef struct s_grb
{
    void            *grb;
    struct s_grb    *next;
} t_grb;

typedef struct s_data {
    t_argv  argv;
    t_grb   *grb;
} t_data;

size_t  ft_strlen(const char *str);
void    *ft_memcpy(void *dest, const void *src, size_t len);
void    ft_putnbr_fd(int n, int fd);
int     ft_isalnum(int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_substr(char const *s, unsigned int start, size_t len);
bool    parse_argv(int argc, char **argv, t_data *zz);
char    **ft_split(char const *s, char c);
char    *ft_strdup(const char *str);
void    writing(char *str);
t_grb    *new_grb(void *content);
bool    add_grb(t_grb **grb, t_grb *new);
void    clean_grb(t_grb **grb);
bool    malloc_secure(void *ptr, t_data *zz);
int     ft_isalnum(int c);

#endif