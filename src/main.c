#include "ft_nm.h"

int main(int argc, char **argv)
{
    t_data zz;
    (&zz)->elem = NULL;
    (&zz)->grb = NULL;
    (&zz)->sorted = NULL;
    if (!parse_argv(argc, argv, &zz))
        return (clean_grb(&zz.grb), 0);
    if (!parsing_elf(zz.argv.files[0], &zz))
        return (clean_grb(&zz.grb), 0);
    if (!sorting_elements(&zz))
        return (clean_grb(&zz.grb), 0);
    t_elem *tmp = zz.sorted;
    while (tmp != NULL)
    {
        print_element(tmp);
        tmp = tmp->next;
    }
    clean_grb(&zz.grb);
    return (0);
}