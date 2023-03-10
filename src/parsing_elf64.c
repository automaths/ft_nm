#include "ft_nm.h"

char	*ft_substr_st_name(char const *s)
{
	char	*dest;
	size_t	i;

	if (s == NULL)
		return (NULL);
	dest = NULL;
	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}

void init_pointers_64bits(char *ptr, t_data *zz)
{
    Elf64_Shdr *table_index;
    char *table_titles;

    zz->header = (Elf64_Ehdr*)ptr;
    zz->sections = (Elf64_Shdr*)((char *)ptr + zz->header->e_shoff);
    table_index = (Elf64_Shdr*)(&zz->sections[zz->header->e_shstrndx]);
    table_titles = (char*)(ptr + table_index->sh_offset);
    for (int i = 0; i < zz->header->e_shnum; i++)
    if (!ft_strncmp((char *)(table_titles + zz->sections[i].sh_name), ".strtab", 8)) {
        zz->strtab_section = &zz->sections[i];
    }
    zz->strtab = (char *)(ptr + zz->strtab_section->sh_offset);
}

bool parsing_elf64(char *ptr, t_data *zz)
{
    init_pointers_64bits(ptr, zz);
    for (int i = 0; i < zz->header->e_shnum; i++)
    if (zz->sections[i].sh_type == SHT_SYMTAB)
    {
        zz->sym = (Elf64_Sym*)(ptr + zz->sections[i].sh_offset);
        char *buf;
        for (unsigned long int j = 0; j < zz->sections[i].sh_size / sizeof(Elf64_Sym); ++j)
        {
            if (zz->sym[j].st_name)
            {
                buf = ft_substr_st_name(zz->strtab + zz->sym[j].st_name);
                if (!malloc_secure((void*)buf, &zz))
                    return (false);
                if (!add_elem(&zz->elem, new_elem(buf, symtab_section_type(zz->sym[j], zz->sections), zz->sym[j].st_value, zz)))
                    return (writing(ERR_MALLOC), false);
            }
        }
    }
    // if (zz.sections[i].sh_type == SHT_HASH)
    // if (zz.sections[i].sh_type == SHT_DYNSYM)
    return true;
}
