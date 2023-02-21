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

int check_architecture(char *ptr)
{
    if (ft_strlen(ptr) < 7)
        return 0;
    else if (ptr[0] != 127)
        return 0;
    else if (ft_strncmp(&ptr[1], "ELF", 3))
        return 0;
    else if (ptr[4] != 1 && ptr[4] != 2)
        return 0;
    else if (ptr[4] == 1)
        return 1;
    else
        return 2;
}

int main(int argc, char **argv)
{
    char *ptr;
    struct stat file_stats;
    t_data zz;
    
    (&zz)->elem = NULL;
    (&zz)->elem32 = NULL;
    (&zz)->grb = NULL;
    (&zz)->sorted = NULL;
    (&zz)->sorted32 = NULL;
    if (!parse_argv(argc, argv, &zz))
        return (clean_grb(&zz.grb), 0);
    //loop on all files
    ptr = init_file(zz.argv.files[0], &file_stats);
    if (ptr == NULL)
        return (clean_grb(&zz.grb), 0);
    
    zz.arch = check_architecture(ptr);
    if (!zz.arch)
        return (writing("Wrong architecure"), clean_grb(&zz.grb), 0);
    if (zz.arch == 1)
    {
        if (!parsing_elf32(ptr, &zz))
            return (clean_grb(&zz.grb), 0);
        if (!sorting_elements32(&zz))
            return (clean_grb(&zz.grb), 0);
        t_elem32 *tmp32 = zz.sorted32;
        while (tmp32 != NULL)
        {
            print_element32(tmp32);
            tmp32 = tmp32->next;
        }
    }
    else
    {
        if (!parsing_elf64(ptr, &zz))
            return (clean_grb(&zz.grb), 0);
        if (!sorting_elements(&zz))
            return (clean_grb(&zz.grb), 0);
        t_elem *tmp = zz.sorted;
        while (tmp != NULL)
        {
            print_element(tmp);
            tmp = tmp->next;
        }
    }
    if (munmap(ptr, file_stats.st_size) != 0)
        return (writing("Error: Munmnap failed\n"), clean_grb(&zz.grb), 0);
    clean_grb(&zz.grb);
    return (0);
}