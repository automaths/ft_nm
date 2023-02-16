char	*ft_strchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	let;
	int				i;

	ptr = NULL;
	let = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == let)
		{
			ptr = (char *)(s + i);
			return (ptr);
		}
		i++;
	}
	if (s[i] == let)
	{
		ptr = (char *)(s + i);
		return (ptr);
	}
	return (ptr);
}
