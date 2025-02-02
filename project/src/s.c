#include "ft_printf.h"

int	no_width(char *str)
{
	ft_putstr(str);
	return (ft_strlen(str));
}

int	yes_width(char *str, t_flags flags)
{
	if (flags.minus_sign)
	{
		ft_putstr(str);
		print_width_space(flags.width - ft_strlen(str));
	}
	else
	{
		print_width_space(flags.width - ft_strlen(str));
		ft_putstr(str);
	}
	return (ft_strlen(str) + pos_width(flags.width, ft_strlen(str)));
}

int	empty_string(char *nul_str, t_flags flags)
{
	if (flags.point && flags.precision < 6)
	{
		if (flags.width)
		{
			print_width_space(flags.width);
			flags.lenght_print = flags.width;
		}
	}
	if (flags.point && flags.precision >= 6)
	{
		if (!flags.width)
			flags.lenght_print = no_width(nul_str);
		else
			flags.lenght_print = yes_width(nul_str, flags);
	}
	if (!flags.point)
	{
		if (!flags.width)
			flags.lenght_print = no_width(nul_str);
		else
			flags.lenght_print = yes_width(nul_str, flags);
	}
	return (flags.lenght_print);
}

int	print_string(char *str, t_flags flags)
{
	int	need_free;

	need_free = 0;
	if (!str)
		return (empty_string("(null)", flags));
	if (flags.point && (flags.precision < (int)ft_strlen(str)))
	{
		str = ft_strndup(str, flags.precision);
		need_free++;
	}
	if (!flags.width)
		flags.lenght_print = no_width(str);
	else
		flags.lenght_print = yes_width(str, flags);
	if (need_free)
		free(str);
	return (flags.lenght_print);
}
