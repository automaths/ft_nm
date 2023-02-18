#include "ft_nm.h"

bool    malloc_secure(void *ptr, t_data *zz)
{
    if (ptr == NULL)
        return (writing(ERR_MALLOC), clean_grb(&zz->grb), false);
    if(!add_grb(&zz->grb, new_grb(ptr)))
        return (writing(ERR_MALLOC), clean_grb(&zz->grb), false);
    return true;
}

t_grb    *new_grb(void *content)
{
    t_grb    *new;

    new = (t_grb *)malloc(sizeof(t_grb));
    //if (new == NULL)
        //upstream the error
    new->grb = content;
    new->next = NULL;
    return (new);
}

bool    add_grb(t_grb **grb, t_grb *new)
{
    t_grb    *tmp;

    if (new == NULL)
        return false;
    if (*grb)
    {
        tmp = *grb;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    else if (grb)
        *grb = new;
    return true;
}

void    clean_grb(t_grb **grb)
{
    t_grb    *tmp;
    t_grb    *next;

    tmp = *grb;
    while (tmp)
    {
        next = tmp->next;
        if (tmp->grb)
            free(tmp->grb);
        free(tmp);
        tmp = next;
    }
    *grb = NULL;
}
