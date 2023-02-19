#include "ft_nm.h"

void init_struct(t_data *zz)
{
    zz->argv.a = false;
    zz->argv.g = false;
    zz->argv.p = false;
    zz->argv.r = false;
    zz->argv.u = false;
    zz->elem->next = NULL;
    zz->grb->next = NULL;
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

bool is_option(char *arg, t_data *zz)
{
    if (ft_strlen(arg) && arg[0] == '-')
    {
        parse_options(arg, zz);
        return true;
    }
    return false;
}

bool parse_argv(int argc, char **argv, t_data *zz)
{
    int i;
    int j;

    if (argc == 1 || (argc == 2 && is_option(argv[1], zz)))
    {
        zz->argv.files = (char**)malloc(sizeof(char*) * 2);
        if (!malloc_secure((void*)zz->argv.files, &zz))
            return false;
        zz->argv.files[1] = NULL;
        zz->argv.files[0] = ft_strdup("a.out");
        if (!malloc_secure((void*)zz->argv.files[0], &zz))
            return false;
    }
    else
    {
        i = 0;
        if (is_option(argv[1], zz))
            ++i;
        zz->argv.files = (char**)malloc(sizeof(char*) * (argc - i));
        if (!malloc_secure((void*)zz->argv.files, &zz))
            return false;
        zz->argv.files[argc - i] = NULL;
        j = 0;
        while (++i < argc)
        {
            zz->argv.files[j] = argv[i];
            ++j;
        }
    }
    return true;
}