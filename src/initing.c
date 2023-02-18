#include "ft_nm.h"

void init_struct(t_data *zz)
{
    zz->argv.a = false;
    zz->argv.g = false;
    zz->argv.p = false;
    zz->argv.r = false;
    zz->argv.u = false;
    zz->grb = NULL;
}

void parse_options(char *options, t_data *zz)
{
    int i = 0;
    while (options[++i])
    {
        if (!ft_isalnum(options[i]))
            return ;
        if (options[i] == 'a')
            zz->argv.a = true;
        if (options[i] == 'g')
            zz->argv.g = true;
        if (options[i] == 'p')
            zz->argv.p = true;
        if (options[i] == 'r')
            zz->argv.r = true;
        if (options[i] == 'u')
            zz->argv.u = true;
    }
}

bool parse_argv(int argc, char **argv, t_data *zz)
{
    if (argc == 1)
    {
        zz->argv.files = (char**)malloc(sizeof(char*));
        if (!malloc_secure(zz->argv.files, zz))
            return false;
        zz->argv.files[0] = ft_strdup("a.out");
        if (!malloc_secure(zz->argv.files[0], zz))
            return false;
    }
    if (ft_strlen(argv[1]) && argv[1][0] == '-')
        parse_options(argv[1], zz);

    return true;
}