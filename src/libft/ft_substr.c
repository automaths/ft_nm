#include "ft_nm.h"

static int	number_char(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while ((i < len) && start < ft_strlen(s) && s[start])
	{
		i++;
		start++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (s == NULL)
		return (NULL);
	dest = NULL;
	i = 0;
	dest = malloc(sizeof(char) * (number_char(s, start, len) + 1));
	if (dest == NULL)
		return (NULL);
	while ((i < len) && (start < ft_strlen(s)) && (s[start]))
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = 0;
	return (dest);
}
