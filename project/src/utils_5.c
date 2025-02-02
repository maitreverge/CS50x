#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	print_real_width_1(int real_width)
{
	if (real_width > 0)
	{
		print_width_space(real_width);
		return (real_width);
	}
	return (0);
}

int	print_real_width_2(int real_width, t_flags flags)
{
	if (real_width > 0)
	{
		if (flags.zero)
			print_zero(real_width);
		else
			print_width_space(real_width);
		return (real_width);
	}
	return (0);
}

int	zero_case(t_flags flags)
{
	print_width_space(flags.width);
	return (flags.width);
}

int	check_flags(char c)
{
	if (c == '#' || c == ' ' || c == '+' || c == '-')
		return (1);
	return (0);
}
