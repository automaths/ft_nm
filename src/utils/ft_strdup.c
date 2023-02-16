char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	i;
	size_t	n;

	n = ft_strlen(str);
	ptr = (char *) malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[n] = '\0';
	i = 0;
	while (i < n)
	{
			ptr[i] = str[i];
			i++;
	}
	return (ptr);
}
