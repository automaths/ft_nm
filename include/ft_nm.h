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
#include <inttypes.h>

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

typedef struct s_elem
{
    char            *name;
    char            type;
    Elf64_Addr      st_value;
    bool            sorted;
    struct s_elem   *next;
} t_elem;

typedef struct s_elem32
{
    char            *name;
    char            type;
    Elf32_Addr      st_value;
    bool            sorted;
    struct s_elem32   *next;
} t_elem32;

typedef struct s_data {
    t_argv          argv;
    t_grb           *grb;
    char            *strtab;
    int             arch;

    Elf64_Ehdr      *header;
    Elf64_Shdr      *sections;
    Elf64_Shdr      *strtab_section;
    Elf64_Sym       *sym;
    t_elem          *elem;
    t_elem          *sorted;

    Elf32_Ehdr      *header32;
    Elf32_Shdr      *sections32;
    Elf32_Shdr      *strtab_section32;
    Elf32_Sym       *sym32;
    t_elem32        *elem32;
    t_elem32        *sorted32;
} t_data;

size_t              ft_strlen(const char *str);
void                *ft_memcpy(void *dest, const void *src, size_t len);
void                ft_putnbr_fd(int n, int fd);
int                 ft_isalnum(int c);
int                 ft_strncmp(const char *s1, const char *s2, size_t n);
char                *ft_substr(char const *s, unsigned int start, size_t len);
bool                parse_argv(int argc, char **argv, t_data *zz);
char                **ft_split(char const *s, char c);
char                *ft_strdup(const char *str);
void                writing(char *str);
t_grb               *new_grb(void *content);
bool                add_grb(t_grb **grb, t_grb *new);
void                clean_grb(t_grb **grb);
bool                malloc_secure(void *ptr, t_data **zz);
int                 ft_isalnum(int c);
void                writing(char *str);
void                print_struct(t_data *zz);
char	            symtab_section_type(Elf64_Sym sym, Elf64_Shdr *shdr);
t_elem              *new_elem(char *name, char type, Elf64_Addr st_value, t_data *zz);
bool                add_elem(t_elem **elem, t_elem *new);
void                print_section_debug(Elf64_Shdr * sections);
void                print_symtab_debug(Elf64_Sym *sym);
void                print_element(t_elem *elem);
char*               init_file(char *files, struct stat *file_stats);
void                init_pointers_64bits(char *ptr, t_data *zz);
bool                parsing_elf64(char *ptr, t_data *zz);
int                 ft_isalpha(int c);
int                 ft_lstsize(t_elem *elem);
bool                sorting_elements(t_data *zz);
int                 ft_tolower(int c);

char	symtab_section_type32(Elf32_Sym sym, Elf32_Shdr *shdr);
t_elem32 *new_elem32(char *name, char type, Elf32_Addr st_value, t_data *zz);
bool    add_elem32(t_elem32 **elem, t_elem32 *new);
int	ft_lstsize32(t_elem32 *elem);
char	*ft_substr_st_name(char const *s);
bool parsing_elf32(char *ptr, t_data *zz);
bool sorting_elements32(t_data *zz);
void print_element32(t_elem32 *elem);

#endif