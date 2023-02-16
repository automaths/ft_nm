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

    char *ptr = mmap(NULL,file_stats.st_size,
            PROT_READ|PROT_WRITE,MAP_PRIVATE,
            fd,0);
    if(ptr == MAP_FAILED){
        printf("Mapping Failed\n");
        return 1;
    }
    close(fd);

    char *buffer = (char *)malloc(file_stats.st_size + 1);
    if (buffer == NULL)
        exiting("malloc error\n");
    buffer[file_stats.st_size] = '\0';
    ft_memcpy(buffer, ptr, file_stats.st_size);

    write(1, buffer, file_stats.st_size);

    // write(1, "\n\nGOGO\n\n", 8);
    // ssize_t n = write(1,ptr,file_stats.st_size);
    // if(n != file_stats.st_size){
    //     printf("Write failed");
    // }

    int err = munmap(ptr, file_stats.st_size);
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    return (0);
}