void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	size_t	x;

	x = nmemb * size;
	if (nmemb && ((x / nmemb) != size))
		return (NULL);
	dest = (void *)malloc(size * nmemb);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, (size * nmemb));
	return (dest);
}
