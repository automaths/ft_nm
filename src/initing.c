#include "ft_nm.h"

bool init_struct(t_data *zz)
{
    zz->argv.a = false;
    zz->argv.g = false;
    zz->argv.p = false;
    zz->argv.r = false;
    zz->argv.u = false;  
    return false;  
}

bool parse_argv(int argc, char **argv, t_data *zz)
{
    (void)argv;
    if (argc == 1)
    {
        zz->argv.files = (char**)malloc(sizeof(char*));
        if (zz->argv.files == NULL)
            return (writing("Error: failed malloc\n"), false);
        zz->argv.files[0] = ft_strdup("a.out");
    }
    return true;

}