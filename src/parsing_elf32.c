#include "ft_nm.h"

// char	*ft_substr_st_name(char const *s)
// {
// 	char	*dest;
// 	size_t	i;

// 	if (s == NULL)
// 		return (NULL);
// 	dest = NULL;
// 	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 	if (dest == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (s[++i])
// 		dest[i] = s[i];
// 	dest[i] = '\0';
// 	return (dest);
// }

void init_pointers_32bits(char *ptr, t_data *zz)
{
    Elf32_Shdr *table_index;
    char *table_titles;

    zz->header32 = (Elf32_Ehdr*)ptr;
    zz->sections32 = (Elf32_Shdr*)((char *)ptr + zz->header32->e_shoff);
    table_index = (Elf32_Shdr*)(&zz->sections32[zz->header32->e_shstrndx]);
    table_titles = (char*)(ptr + table_index->sh_offset);
    for (int i = 0; i < zz->header32->e_shnum; i++)
    if (!ft_strncmp((char *)(table_titles + zz->sections32[i].sh_name), ".strtab", 8)) {
        zz->strtab_section32 = &zz->sections32[i];
    }
    zz->strtab = (char *)(ptr + zz->strtab_section32->sh_offset);
}

bool parsing_elf32(char *ptr, t_data *zz)
{
    init_pointers_32bits(ptr, zz);
    // printf("coucou\n");
    for (int i = 0; i < zz->header32->e_shnum; i++)
    if (zz->sections32[i].sh_type == SHT_SYMTAB)
    {
        zz->sym32 = (Elf32_Sym*)(ptr + zz->sections32[i].sh_offset);
        char *buf;
        for (unsigned long int j = 0; j < zz->sections32[i].sh_size / sizeof(Elf32_Sym); ++j)
        {
            if (zz->sym32[j].st_name)
            {
                buf = ft_substr_st_name(zz->strtab + zz->sym32[j].st_name);
                if (!malloc_secure((void*)buf, &zz))
                    return (false);
                if (!add_elem32(&zz->elem32, new_elem32(buf, symtab_section_type32(zz->sym32[j], zz->sections32), zz->sym32[j].st_value, zz)))
                    return (writing(ERR_MALLOC), false);
            }
            // if (ft_strncmp("__frame_dummy_init_array", buf, 15) == 0)
            //     print_symtab_debug32(&zz->sym32[j]);
        }
    }
    // if (zz.sections32[i].sh_type == SHT_HASH)
    // if (zz.sections32[i].sh_type == SHT_DYNSYM)
    return true;
}
