#include "ft_nm.h"

int	name_cmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	i = 0;
	while (one[i] && two[i] && one[i] == two[i] && ft_isalpha(one[i]) && ft_isalpha(two[i]))
		i++;
	return (one[i] - two[i]);
}

bool sorting_elements(t_data *zz)
{
    t_elem *tmp = zz->elem;
    int i = -1;
    int j = -1;
    int size = ft_lstsize(zz->elem);
    t_elem lowest;
    t_elem *keep;

    if (tmp == NULL)
        return true;
    lowest.name = "AAAA";
    while (size > 0)
    {
        tmp = zz->elem;
        lowest.name = "AAAA";
        while (tmp != NULL)
        {
            while (tmp != NULL && tmp->sorted)
                tmp = tmp->next;
            if (tmp == NULL)
                break;
            i = -1;
            j = -1;
            while (lowest.name[++i] && !ft_isalpha(lowest.name[i]))
                ;
            while (tmp->name[++j] && !ft_isalpha(tmp->name[j]))
                ;
            if (name_cmp(&lowest.name[i], &tmp->name[j]) < 0)
            {
                lowest.name = tmp->name;
                lowest.st_value = tmp->st_value;
                lowest.type = tmp->type;
                keep = tmp;
            }
            tmp = tmp->next;
        }
        if (!add_elem(&zz->sorted, new_elem(lowest.name, lowest.type, lowest.st_value, zz)))
            return (writing(ERR_MALLOC), false);
        keep->sorted = true;
        keep = NULL;
        --size;
    }
    return true;
}