int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	m;

	n = ft_strlen(dest);
	m = ft_strlen(src);
	if (size <= n)
		return (m + size);
	i = 0;
	while (src[i] && n + i < size - 1)
	{
		dest[n + i] = src[i];
		i++;
	}
	dest[n + i] = '\0';
	return (n + m);
}
