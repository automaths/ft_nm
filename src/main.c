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
    Elf64_Shdr * sh_strtab = (Elf64_Shdr *)(&sections[header->e_shstrndx]);
    // const char * sh_strtab_p = ptr + sh_strtab->sh_offset;

    // for (int i = 0; i < header->e_shnum; ++i) {
    // printf("%2d: %4d '%s'\n", i, sections[i].sh_name,
    //        sh_strtab_p + sections[i].sh_name);
    // }

    Elf64_Sym *sym;
    for (int i = 0; i < header->e_shnum; i++)
    if (sections[i].sh_type == SHT_SYMTAB) {

        printf("cava");
        sym = (Elf64_Sym*)(ptr + sections[i].sh_offset);
        char* str = (char*)(ptr + sh_strtab->sh_offset);
        printf("name %d\n", sym->st_name);
        printf("info %d\n", sym->st_info);
        printf("other %d\n", sym->st_other);
        printf("shndx %d\n", sym->st_shndx);
        printf("value %ld\n", sym->st_value);
        printf("size %ld\n", sym->st_size);


        for (size_t i = 0; i < sections[i].sh_size / sizeof(Elf64_Sym); i++) {
            printf("coucou");
            printf("%s\n", str + sym[i].st_name);
        }

        // symtab = (Elf64_Sym *)&sections[i];
        // Elf64_Sym *symtab2 = &symtab[1];
        // printf("name %d\n", symtab->st_name);
        // printf("info %d\n", symtab->st_info);
        // printf("other %d\n", symtab->st_other);
        // printf("shndx %d\n", symtab->st_shndx);
        // printf("value %ld\n", symtab->st_value);
        // printf("size %ld\n", symtab->st_size);



        // printf("name %d\n", symtab2->st_name);
        // printf("info %d\n", symtab2->st_info);
        // printf("other %d\n", symtab2->st_other);
        // printf("shndx %d\n", symtab2->st_shndx);
        // printf("value %ld\n", symtab2->st_value);
        // printf("size %ld\n", symtab2->st_size);
        // printf("section found\n");
        // printf("flags: %lx\n", sections[i].sh_flags);
        // printf("size: %ld\n", sections[i].sh_size);
        // printf("addr: %p\n", &sections[i].sh_addr);
        // printf("offset: %ld\n", sections[i].sh_offset);
        // printf("link: %d\n", sections[i].sh_link);
        // printf("info: %d\n", sections[i].sh_info);
        // printf("addralign: %ld\n", sections[i].sh_addralign);
        // printf("entsize: %ld\n", sections[i].sh_entsize);
        // printf("name: %d\n", sections[i].sh_name);



        // char *name = (char *)malloc(sizeof(sections[i].sh_size));
        // ft_memcpy(name, &buffer[sections[i].sh_offset], sections[i].sh_size);

        // write(1, &buffer[sections[i].sh_offset], sections[i].sh_size);

        // printf("the name is: %s\n", name);



        
        // if (i + 1 < header->e_shnum)
        // {
            // size_symtab = sections[i + 1].sh_offset - sections[i].sh_offset + sections[i].sh_size;
        // }
        // printf("first characters: %d\n", buffer[sections[i].sh_offset + sections[i].sh_size]);
        // printf("first characters: %p\n", &buffer[sections[i].sh_offset + sections[i].sh_size]);
        // write(1, &buffer[sections[i].sh_offset + sections[i].sh_size], size_symtab);

        // Elf64_Phdr *segments = (Elf64_Phdr *)&buffer[sections[i].sh_offset + sections[i].sh_size];

        // printf("p_align: %ld\n", segments->p_align);
        // printf("p_filesz: %ld\n", segments->p_filesz);
        // printf("p_flags: %d\n", segments->p_flags);
        // printf("p_memsz: %ld\n", segments->p_memsz);
        // printf("p_offset: %ld\n", segments->p_offset);
        // printf("p_addr: %ld\n", segments->p_paddr);
        // printf("p_type: %d\n", segments->p_type);
        // printf("p_vaddr: %ld\n", segments->p_vaddr);

        // write(1, &buffer[sections[i].sh_offset], sections[i].sh_size);


        // symtab = (Elf64_Sym *)((char *)ptr + sections[i].sh_offset);
        // break; 
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