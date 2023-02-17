#include "ft_nm.h"

void writing(char *str)
{
    write(2, str, strlen(str));
}

int main(int argc, char *argv[])
{
    struct stat file_stats;

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

    char *ptr = mmap(NULL,file_stats.st_size, PROT_READ|PROT_WRITE,MAP_PRIVATE, fd,0);
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
    // Elf64_Shdr * sh_strtab = (Elf64_Shdr *)(&sections[header->e_shstrndx]);
    // const char * sh_strtab_p = ptr + sh_strtab->sh_offset;

    // for (int i = 0; i < header->e_shnum; ++i) {
    // printf("%2d: %4d '%s'\n", i, sections[i].sh_name,
    //        sh_strtab_p + sections[i].sh_name);
    // }

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
        sym = (Elf64_Sym*)(ptr + sections[i].sh_offset);
        for (unsigned long int j = 0; j < sections[i].sh_size / sizeof(Elf64_Sym); ++j)
        {
            printf("\nNUMBER %ld\n", j);
            printf("name %d\n", sym[j].st_name);
            printf("info %d\n", sym[j].st_info);
            printf("other %d\n", sym[j].st_other);
            printf("shndx %d\n", sym[j].st_shndx);
            printf("value %ld\n", sym[j].st_value);
            printf("size %ld\n", sym[j].st_size);
        }
        printf("size %ld\n", sym->st_size);
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