#include "../includes/philosophers.h"

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		res = 10 * res + *(str++) - '0';
	return (res); 
}
