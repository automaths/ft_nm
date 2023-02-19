#include "ft_nm.h"

void writing(char *str)
{
    write(2, str, strlen(str));
}

char	symtab_section_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char    c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (sym.st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
             && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
        {
            c = 'W';
            if (sym.st_shndx == SHN_UNDEF)
                c = 'w';
        }
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
        {
            c = 'V';
            if (sym.st_shndx == SHN_UNDEF)
                c = 'v';
        }
    else
        c = '?';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}

void print_struct(t_data *zz)
{
    int i;

    printf("the options are: \na: %d, g: %d, p: %d, r: %d, u: %d\n", zz->argv.a, zz->argv.g, zz->argv.p, zz->argv.r, zz->argv.u);
    i = -1;
    while (zz->argv.files[++i] != NULL)
        printf("file %d: %s\n", i + 1, zz->argv.files[i]);
}

int main(int argc, char *argv[])
{
    t_data zz;
    struct stat file_stats;

    if (!parse_argv(argc, argv, &zz))
        return (0);

    print_struct(&zz);

    return (0);


    if (argc != 2)
        return (writing("two arguments are needed\n"), 0);

        
    int fd = open(argv[1], O_RDONLY);
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

	// Elf64_Phdr * program = (Elf64_Phdr *)((char*)ptr + header->e_phoff);

    // for (int i = 0; i < header->e_shnum; ++i) {
    // printf("%2d: %4d '%s'\n", i, sections[i].sh_name,
    //        sh_strtab_p + sections[i].sh_name);
    // }

    // char *sh_strtab_str = (char*)sh_strtab;

    Elf64_Shdr *strtab_ptr;
    for (int i = 0; i < header->e_shnum; i++)
    if (!ft_strncmp((char *)(sh_strtab_p + sections[i].sh_name), ".strtab", 8)) {
        strtab_ptr = &sections[i];
    }
    char *str = (char *)(ptr + strtab_ptr->sh_offset);
    Elf64_Sym *sym;
    for (int i = 0; i < header->e_shnum; i++)
    if (sections[i].sh_type == SHT_SYMTAB) {
        // printf("flags: %lx\n", sections[i].sh_flags);
        // printf("size: %ld\n", sections[i].sh_size);
        // printf("addr: %p\n", &sections[i].sh_addr);
        // printf("offset: %ld\n", sections[i].sh_offset);
        // printf("link: %d\n", sections[i].sh_link);
        // printf("info: %d\n", sections[i].sh_info);
        // printf("addralign: %ld\n", sections[i].sh_addralign);
        // printf("entsize: %ld\n", sections[i].sh_entsize);
        // printf("name: %d\n", sections[i].sh_name);
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
                // printf("%d, %d %d %d %d ", ELF64_ST_BIND(sym[j].st_info), ELF64_ST_TYPE(sym[j].st_info), sym[j].st_info, sym[j].st_shndx, sym[j].st_other);
                // printf("st_name %d\n", sym[j].st_name);
                // printf("st_info %d\n", sym[j].st_info);
                // printf("st_other %d\n", sym[j].st_other);
                // printf("st_shndx %d\n", sym[j].st_shndx);
                // printf("st_value %ld\n", sym[j].st_value);
                // printf("st_size %ld\n", sym[j].st_size);
            }
        }
    }

    // for (int i = 0; i < header->e_shnum; i++)
    // if (sections[i].sh_type == SHT_HASH) {
    //     write(1, "\nhash\n", 6);
    //     if (i + 1 < header->e_shnum)
    //     {
    //         size_symtab = sections[i + 1].sh_offset - sections[i].sh_offset + sections[i].sh_size;
    //     }
    //     write(1, &buffer[sections[i].sh_offset], sections[i].sh_size);
    // }

    // for (int i = 0; i < header->e_shnum; i++)
    // if (sections[i].sh_type == SHT_DYNSYM) {
    //     write(1, "\ndyna\n", 6);
    //     if (i + 1 < header->e_shnum)
    //     {
    //         size_symtab = sections[i + 1].sh_offset - sections[i].sh_offset + sections[i].sh_size;
    //     }
    //     write(1, &buffer[sections[i].sh_offset + sections[i].sh_size], size_symtab);
    // }

    int err = munmap(ptr, file_stats.st_size);
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    return (0);
}