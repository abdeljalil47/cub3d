#include "../header/cub3d.h"

char	ft_putnbr_base(long nbr, const char *base)
{
	long	size_base;

	size_base = ft_strlen(base);
	if (nbr < 0)
	{
		nbr = -nbr;
	}
	if (nbr >= size_base)
	{
		ft_putnbr_base(nbr / size_base, base);
	}
	return (base[nbr % size_base]);
}
