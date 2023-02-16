int	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (n == 0 || !dest || !src)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (n - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
