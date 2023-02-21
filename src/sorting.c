#include "ft_nm.h"

int	name_cmp(const char *s1, const char *s2)
{
	size_t			i;
    size_t			j;
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	i = 0;
    j = 0;
	while (one[i] && two[j] && (ft_tolower(one[i]) == ft_tolower(two[j]) || (!ft_isalpha(one[i]) || !ft_isalpha(two[j]))))
    {
        if (!ft_isalpha(one[i]) || !ft_isalpha(two[j]))
        {
            while (one[i] && !ft_isalpha(one[i]))
                ++i;
            while (two[j] && !ft_isalpha(two[j]))
                ++j;
            if (!one[i] || !two[j])
                break;
        }
        else
        {
            j++;
            i++;
        }
    }
	return (ft_tolower(one[i]) - ft_tolower(two[j]));
}

bool sorting_elements(t_data *zz)
{
    t_elem *tmp = zz->elem;
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
            if (name_cmp(lowest.name, tmp->name) < 0 || (name_cmp(lowest.name, tmp->name) == 0 && (ft_strlen(lowest.name) > ft_strlen(tmp->name))))
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