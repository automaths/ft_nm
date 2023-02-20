#include "ft_nm.h"

t_elem    *new_elem(char *name, char type, Elf64_Addr st_value, t_data *zz)
{
    t_elem    *new;

    new = (t_elem *)malloc(sizeof(t_elem));
    if (!malloc_secure(new, &zz))
        return (NULL);
    new->name = name;
    new->type = type;
    new->st_value = st_value;
    new->sorted = false;
    new->next = NULL;
    return (new);
}

bool    add_elem(t_elem **elem, t_elem *new)
{
    if (new == NULL)
        return false;
    else
    {
        new->next = *elem;
        *elem = new;
    }
    return true;
}

int	ft_lstsize(t_elem *elem)
{
	int		i;

	i = 0;
	while (elem)
	{
		i++;
		elem = elem->next;
	}
	return (i);
}

