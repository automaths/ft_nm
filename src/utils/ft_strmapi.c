char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	char	*ptr;
	int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	str = (char *)s;
	ptr = ft_strdup(str);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (ptr[i])
	{
		ptr[i] = (*f)(i, ptr[i]);
		i++;
	}
	return (ptr);
}
