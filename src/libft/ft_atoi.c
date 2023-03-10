int	ft_atoi(const char *str)
{
	int			i;
	int			t;
	long long	x;

	t = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] == ' ')
		if (str[i++] == '-')
			t = -1;
	x = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (x * t > 2147483647)
			return (-1);
		if (x * t < -2147483648)
			return (0);
		x = (x * 10) + (str[i++] - '0');
	}
	x *= t;
	return (x);
}
