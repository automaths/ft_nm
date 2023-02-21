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

int main(int argc, char **argv)
{
    char *ptr;
    struct stat file_stats;
    t_data zz;
    (&zz)->elem = NULL;
    (&zz)->grb = NULL;
    (&zz)->sorted = NULL;
    if (!parse_argv(argc, argv, &zz))
        return (clean_grb(&zz.grb), 0);
    //loop on all files
    ptr = init_file(zz.argv.files[0], &file_stats);
    if (ptr == NULL)
        return (clean_grb(&zz.grb), 0);
    //check 64 or 32 binary        
    init_pointers_64bits(ptr, &zz);

    if (!parsing_elf64(ptr, &zz))
        return (clean_grb(&zz.grb), 0);

    if (munmap(ptr, file_stats.st_size) != 0)
        return (writing("Error: Munmnap failed\n"), clean_grb(&zz.grb), 0);

    if (!sorting_elements(&zz))
        return (clean_grb(&zz.grb), 0);

    // t_elem *tmp = zz.sorted;
    // while (tmp != NULL)
    // {
    //     print_element(tmp);
    //     tmp = tmp->next;
    // }
    clean_grb(&zz.grb);
    return (0);
}