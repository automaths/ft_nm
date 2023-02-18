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

bool parse_argv(int argc, char **argv, t_data *zz)
{
    (void)argv;
    if (argc == 1)
    {
        zz->argv.files = (char**)malloc(sizeof(char*));
        if (!malloc_secure(zz->argv.files, zz))
            return false;
        zz->argv.files[0] = ft_strdup("a.out");
        if (!malloc_secure(zz->argv.files[0], zz))
            return false;
    }
    return true;

}