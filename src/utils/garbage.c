#include "ft_nm.h"

t_grb    *new_grb(void *content)
{
    t_grb    *new;

    new = (t_grb *)malloc(sizeof(t_grb));
    //if (new == NULL)
        //upstream the error
    new->grb = NULL;
    new->next = NULL;
    return (new);
}

void    add_grb(t_grb **grb, t_grb *new)
{
    t_grb    *tmp;

    if (*grb)
    {
        tmp = *grb;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    else if (grb)
        *grb = new;
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
