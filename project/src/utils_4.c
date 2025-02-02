#include "ft_printf.h"

int	determine_plus_or_space(long nb, t_flags flags)
{
	int	plus_sign;
	int	space_sign;

	plus_sign = 0;
	space_sign = 0;
	if (flags.plus_sign && nb >= 0 && !flags.space)
		plus_sign++;
	else if (flags.space && !flags.plus_sign && nb >= 0)
		space_sign++;
	return (plus_sign + space_sign);
}

int	determine_plus(long nb, t_flags flags)
{
	int	plus_sign;

	plus_sign = 0;
	if (flags.plus_sign && nb >= 0 && !flags.space)
		plus_sign++;
	return (plus_sign);
}

long	positive_nb(long nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

void	putnbr_hexa(unsigned long nb, char c)
{
	if (c == 'x')
	{
		if (nb > 15)
			putnbr_hexa((nb / 16), 'x');
		ft_putchar("0123456789abcdef"[(nb % 16)]);
	}
	else if (c == 'X')
	{
		if (nb > 15)
			putnbr_hexa((nb / 16), 'X');
		ft_putchar("0123456789ABCDEF"[(nb % 16)]);
	}
}
