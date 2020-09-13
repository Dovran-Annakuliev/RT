#include "../../includes/rtv1.h"

static int		order(int numerator)
{
	int del;

	del = 1;
	while (numerator)
	{
		del *= 10;
		numerator /= 10;
	}
	return (del);
}

static float	denominator(const char *str, int i)
{
	float	result;
	int		res;
	int		del;

	res = ft_atoi(str + i);
	del = order(res);
	while (str[i] == '0')
	{
		del *= 10;
		i++;
	}
	del == 0 ? del = 1 : 0;
	result = (float)res / (float)del;
	return (result);
}

float			ft_atof(const char *str)
{
	int		res1;
	float	res2;
	float	result;
	int		i;
	int		neg;

	i = 0;
	while (!ft_isdigit(str[i]) && str[i] != '-')
		i++;
	neg = str[i] == '-' ? -1 : 1;
	neg == -1 ? i++ : 0;
	res1 = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == '-')
		i++;
	res2 = 0;
	if (str[i] == '.')
		res2 = denominator(str, i + 1);
	result = (float)res1 + res2;
	result *= (float)neg;
	return (result);
}
