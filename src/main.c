#include "ft_nm.h"

char* init_file(char *files, struct stat *file_stats)
{
    int fd;
    char *ptr;

    fd = open(files, O_RDONLY);
    if (fd == -1)
        return (writing("open error\n"), NULL);
    if (fstat(fd, file_stats) == -1)
        return (close(fd), writing("fstat error\n"), NULL);
    if ((file_stats->st_mode & S_IFMT) != S_IFREG)
        return (close(fd), writing("argument need to be regular file\n"), NULL);
    if (!(file_stats->st_mode & S_IRUSR))
        return (close(fd), writing("no read access to file\n"), NULL);
    ptr = mmap(NULL, file_stats->st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(ptr == MAP_FAILED)
        return (close(fd), writing("no read access to file\n"), NULL);
    close(fd);
    return ptr;
}

void init_pointers(char *ptr, t_data *zz)
{
    Elf64_Shdr *sh_strtab;
    char *sh_strtab_p;

    zz->header = (Elf64_Ehdr*)ptr;
    zz->sections = (Elf64_Shdr*)((char *)ptr + zz->header->e_shoff);
    sh_strtab = (Elf64_Shdr*)(&zz->sections[zz->header->e_shstrndx]);
    sh_strtab_p = (char*)(ptr + sh_strtab->sh_offset);
    for (int i = 0; i < zz->header->e_shnum; i++)
    if (!ft_strncmp((char *)(sh_strtab_p + zz->sections[i].sh_name), ".strtab", 8)) {
        zz->strtab_ptr = &zz->sections[i];
    }
}

int main(int argc, char *argv[])
{
    t_data zz;
    struct stat file_stats;
    char *ptr;

    if (!parse_argv(argc, argv, &zz))
        return (clean_grb(&zz.grb), 0);
    print_struct(&zz);
    ptr = init_file(zz.argv.files[0], &file_stats);
    if (ptr == NULL)
        return (clean_grb(&zz.grb), 0);
    init_pointers(ptr, &zz);

    Elf64_Ehdr *header = zz.header;
    Elf64_Shdr *sections = zz.sections;
    Elf64_Shdr *strtab_ptr = zz.strtab_ptr;


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