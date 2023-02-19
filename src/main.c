#include "ft_nm.h"

int main(int argc, char *argv[])
{
    t_data zz;
    struct stat file_stats;

    if (!parse_argv(argc, argv, &zz))
        return (0);
    print_struct(&zz);
        
    int fd = open(zz.argv.files[0], O_RDONLY);
    if (fd == -1)
        return (writing("open error\n"), 0);

    if (fstat(fd, &file_stats) == -1)
        return (close(fd), writing("fstat error\n"), 0);
    if ((file_stats.st_mode & S_IFMT) != S_IFREG)
        return (close(fd), writing("argument need to be regular file\n"), 0);
    if (!(file_stats.st_mode & S_IRUSR))
        return (close(fd), writing("no read access to file\n"), 0);

    char *ptr = mmap(NULL, file_stats.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(ptr == MAP_FAILED)
        return (close(fd), writing("no read access to file\n"), 0);
    close(fd);

    char *buffer = (char *)malloc(file_stats.st_size + 1);
    if (buffer == NULL)
        return (close(fd), writing("malloc error\n"), 0);
    buffer[file_stats.st_size] = '\0';
    ft_memcpy(buffer, ptr, file_stats.st_size);

    Elf64_Ehdr * header = (Elf64_Ehdr *) ptr;
    Elf64_Shdr * sections = (Elf64_Shdr *)((char *)ptr + header->e_shoff);
    Elf64_Shdr * sh_strtab = (Elf64_Shdr *)(&sections[header->e_shstrndx]);
    const char * sh_strtab_p = ptr + sh_strtab->sh_offset;

    Elf64_Shdr *strtab_ptr;
    for (int i = 0; i < header->e_shnum; i++)
    if (!ft_strncmp((char *)(sh_strtab_p + sections[i].sh_name), ".strtab", 8)) {
        strtab_ptr = &sections[i];
    }
    char *str = (char *)(ptr + strtab_ptr->sh_offset);
    Elf64_Sym *sym;
    for (int i = 0; i < header->e_shnum; i++)
    if (sections[i].sh_type == SHT_SYMTAB) {
        // print_section(&sections[i]);
		char **names = (char **)malloc((sections[i].sh_size / sizeof(Elf64_Sym) * sizeof(char*)));
		if (names == NULL)
			return (0);
        sym = (Elf64_Sym*)(ptr + sections[i].sh_offset);
        char *str_loop;
        for (unsigned long int j = 0; j < sections[i].sh_size / sizeof(Elf64_Sym); ++j)
        {
            if (sym[j].st_name && symtab_section_type(sym[j], sections) != 'a')
            {
                if (j + 1 < sections[i].sh_size / sizeof(Elf64_Sym))
                    str_loop = ft_substr(str + sym[j].st_name, 0, sym[j + 1].st_name - sym[j].st_name);
                else
                    str_loop = ft_substr(str + sym[j].st_name, 0, sections[i].sh_offset + sections[i].sh_size - sym[j].st_name);
                if (sym[j].st_value || symtab_section_type(sym[j], sections) == 'T')
                    printf("%016lx ", sym[j].st_value);
                else
                    printf("                 ");
                printf("%c ", symtab_section_type(sym[j], sections));
                printf("%s\n", str_loop);
                free(str_loop);
                // print_symtab(&sym[j]);
            }
        }
    }
    // if (sections[i].sh_type == SHT_HASH)
    // if (sections[i].sh_type == SHT_DYNSYM)

    int err = munmap(ptr, file_stats.st_size);
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    return (0);
}