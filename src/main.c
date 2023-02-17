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

    // write(1, buffer, file_stats.st_size);

    Elf64_Ehdr * header = (Elf64_Ehdr *) ptr;
    Elf64_Shdr * sections = (Elf64_Shdr *)((char *)ptr + header->e_shoff);
    // Elf64_Sym * symtab;

    // long int size_symtab = 0;
    for (int i = 0; i < header->e_shnum; i++)
    if (sections[i].sh_type == SHT_SYMTAB) {
        // printf("section found\n");
        // printf("flags: %lx\n", sections[i].sh_flags);
        // printf("size: %ld\n", sections[i].sh_size);
        // printf("addr: %ld\n", sections[i].sh_addr);
        // printf("offset: %ld\n", sections[i].sh_offset);
        // printf("link: %d\n", sections[i].sh_link);
        // printf("info: %d\n", sections[i].sh_info);
        // printf("addralign: %ld\n", sections[i].sh_addralign);
        // printf("entsize: %ld\n", sections[i].sh_entsize);
        
        // if (i + 1 < header->e_shnum)
        // {
            // size_symtab = sections[i + 1].sh_offset - sections[i].sh_offset + sections[i].sh_size;
        // }
        // write(1, &buffer[sections[i].sh_offset + sections[i].sh_size], size_symtab);

        Elf64_Phdr *segments = (Elf64_Phdr *)&buffer[sections[i].sh_offset + sections[i].sh_size];

        printf("p_align: %ld\n", segments->p_align);
        printf("p_filesz: %ld\n", segments->p_filesz);
        printf("p_flags: %d\n", segments->p_flags);
        printf("p_memsz: %ld\n", segments->p_memsz);
        printf("p_offset: %ld\n", segments->p_offset);
        printf("p_addr: %ld\n", segments->p_paddr);
        printf("p_type: %d\n", segments->p_type);
        printf("p_vaddr: %ld\n", segments->p_vaddr);

        // write(1, &buffer[sections[i].sh_offset], sections[i].sh_size);


        // symtab = (Elf64_Sym *)((char *)ptr + sections[i].sh_offset);
        // break; 
    }


    int err = munmap(ptr, file_stats.st_size);
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    return (0);
}