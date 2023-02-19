#include "ft_nm.h"

int main(int argc, char *argv[])
{
    t_data zz;
    t_elem elem;
    t_grb grb;

    elem.next = NULL;
    zz.elem = &elem;
    grb.next = NULL;
    zz.grb = &grb;
    if (!parse_argv(argc, argv, &zz))
        return (clean_grb(&zz.grb), 0);
    print_struct(&zz);
    if (!parsing_elf(zz.argv.files[0], &zz))
        return (clean_grb(&zz.grb), 0);
    t_elem *tmp = zz.elem;
    while (tmp->next != NULL)
    {
        print_element(tmp);
        tmp = tmp->next;
    }
    clean_grb(&zz.grb);
    return (0);
}