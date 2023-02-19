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

    
    for (int i = 0; i < zz.header->e_shnum; i++)
    if (zz.sections[i].sh_type == SHT_SYMTAB) {

        zz.sym = (Elf64_Sym*)(ptr + zz.sections[i].sh_offset);
        char *buf;
        for (unsigned long int j = 0; j < zz.sections[i].sh_size / sizeof(Elf64_Sym); ++j)
        {
            // if (zz.sym[j].st_name && symtab_section_type(zz.sym[j], zz.sections) != 'a')
            if (zz.sym[j].st_name)
            {
                if (j + 1 < zz.sections[i].sh_size / sizeof(Elf64_Sym))
                    buf = ft_substr(zz.strtab + zz.sym[j].st_name, 0, zz.sym[j + 1].st_name - zz.sym[j].st_name);
                else
                    buf = ft_substr(zz.strtab + zz.sym[j].st_name, 0, zz.sections[i].sh_offset + zz.sections[i].sh_size - zz.sym[j].st_name);
                if (!malloc_secure((void*)buf, &zz))
                    return (writing(ERR_MALLOC), clean_grb(&zz.grb), 0);
                if (!add_elem(&zz.elem, new_elem(buf, symtab_section_type(zz.sym[j], zz.sections), zz.sym[j].st_value, &zz)))
                    return (writing(ERR_MALLOC), clean_grb(&zz.grb), 0);




                if (zz.sym[j].st_value || symtab_section_type(zz.sym[j], zz.sections) == 'T')
                    printf("%016lx ", zz.sym[j].st_value);
                else
                    printf("                 ");
                printf("%c ", symtab_section_type(zz.sym[j], zz.sections));
                printf("%s\n", str_loop);
            }
        }
    }
    // if (zz.sections[i].sh_type == SHT_HASH)
    // if (zz.sections[i].sh_type == SHT_DYNSYM)

    int err = munmap(ptr, file_stats.st_size);
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    return (0);
}