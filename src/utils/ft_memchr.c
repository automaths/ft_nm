void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	let;

	str = (unsigned char *)s;
	let = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == let)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
