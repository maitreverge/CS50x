#include "ft_printf.h"

int	print_char(char c, t_flags flags)
{
	if (flags.width > 1 && c != '%')
	{
		if (!flags.minus_sign)
		{
			print_width_space(flags.width - 1);
			ft_putchar(c);
		}
		else
		{
			ft_putchar(c);
			print_width_space(flags.width - 1);
		}
		return (flags.width);
	}
	ft_putchar(c);
	return (1);
}
