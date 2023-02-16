#include "ft_nm.h"

void exiting(char *str)
{
    write(2, str, strlen(str));
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    struct stat file_stats;
    long int preferred_block_size;
    long long int file_size;
    long long int blocks_allocated;

    if (argc != 2)
        exiting("two arguments are needed\n");
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exiting("open error\n");
    if (fstat(fd, &file_stats) == -1)
        exiting("fstat error\n");
    if ((file_stats.st_mode & S_IFMT) != S_IFREG)
        exiting("argument need to be regular file\n");
    if (!(file_stats.st_mode & S_IRUSR))
        exiting("no read access to file\n");
    preferred_block_size = (long)file_stats.st_blksize;
    file_size = (long long)file_stats.st_size;
    blocks_allocated = (long long)file_stats.st_blocks;
    printf("preferred block size: %ld\nfile size: %lld\nblocks allocated: %lld\n", preferred_block_size, file_size, blocks_allocated);
    printf("test ft_strlen: %ld\n", ft_strlen("coucou"));
    return (0);
}