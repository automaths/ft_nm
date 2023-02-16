char	*ft_strrchr(char *s, int c)
{
	int		i;

	c = c % 256;
	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (&s[i]);
		i--;
	}
	return (NULL);
}
