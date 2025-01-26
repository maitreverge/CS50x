#include "ft_printf.h"

int	print_hashtag_low(t_flags flags, unsigned long nb)
{
	if (flags.hashtag && nb != 0)
	{
		ft_putstr("0x");
		return (2);
	}
	return (0);
}

int	print_hashtag_up(t_flags flags, unsigned long nb)
{
	if (flags.hashtag && nb != 0)
	{
		ft_putstr("0X");
		return (2);
	}
	return (0);
}

int	determine_hashtag(t_flags flags, unsigned long nb)
{
	if (flags.hashtag && nb != 0)
		return (2);
	return (0);
}

int	intlen_hexa(unsigned long n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	intlen_hexa_zero(unsigned long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}
