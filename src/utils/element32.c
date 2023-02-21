#include "ft_nm.h"

t_elem32 *new_elem32(char *name, char type, Elf32_Addr st_value, t_data *zz)
{
    t_elem32    *new;

    new = (t_elem32 *)malloc(sizeof(t_elem32));
    if (!malloc_secure(new, &zz))
        return (NULL);
    new->name = name;
    new->type = type;
    new->st_value = st_value;
    new->sorted = false;
    new->next = NULL;
    return (new);
}

bool    add_elem32(t_elem32 **elem, t_elem32 *new)
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

int	ft_lstsize32(t_elem32 *elem)
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

