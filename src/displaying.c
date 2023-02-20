#include "ft_nm.h"

void writing(char *str)
{
    write(2, str, strlen(str));
}

void print_struct(t_data *zz)
{
    int i;

    printf("the options are: \na: %d, g: %d, p: %d, r: %d, u: %d\n", zz->argv.a, zz->argv.g, zz->argv.p, zz->argv.r, zz->argv.u);
    i = -1;
    while (zz->argv.files[++i] != NULL)
        printf("file %d: %s\n", i + 1, zz->argv.files[i]);
}

void print_section_debug(Elf64_Shdr * sections)
{
    printf("flags: %lx\n", sections->sh_flags);
    printf("size: %ld\n", sections->sh_size);
    printf("addr: %p\n", &sections->sh_addr);
    printf("offset: %ld\n", sections->sh_offset);
    printf("link: %d\n", sections->sh_link);
    printf("info: %d\n", sections->sh_info);
    printf("addralign: %ld\n", sections->sh_addralign);
    printf("entsize: %ld\n", sections->sh_entsize);
    printf("name: %d\n", sections->sh_name);
}

void print_symtab_debug(Elf64_Sym *sym)
{
    printf("%d, %d %d %d %d ", ELF64_ST_BIND(sym->st_info), ELF64_ST_TYPE(sym->st_info), sym->st_info, sym->st_shndx, sym->st_other);
    printf("st_name %d\n", sym->st_name);
    printf("st_info %d\n", sym->st_info);
    printf("st_other %d\n", sym->st_other);
    printf("st_shndx %d\n", sym->st_shndx);
    printf("st_value %ld\n", sym->st_value);
    printf("st_size %ld\n", sym->st_size);
}

void print_element(t_elem *elem)
{
    if (elem->type == 'a')
        return ;
    if (elem->st_value || elem->type == 'T')
        printf("%016lx ", elem->st_value);
    else
        printf("                 ");
    printf("%c ", elem->type);
    printf("%s\n", elem->name);
}
