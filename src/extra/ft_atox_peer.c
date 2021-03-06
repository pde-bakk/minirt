/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atox_peer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:17:19 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:17:20 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int			ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
	{
		return (1);
	}
	else if (c == ',')
		return (1);
	return (0);
}

static int	ft_power(int dec)
{
	int	power;

	power = 1;
	while (dec > 0)
	{
		power = power * 10;
		dec--;
	}
	return (power);
}

double		ft_decimal_double(const char *str, double result, int *i)
{
	int		dec;
	double	tmp;

	if (str[*i] == '.')
	{
		(*i)++;
		dec = 1;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			tmp = str[*i] - '0';
			result = result + tmp / ft_power(dec);
			(*i)++;
			dec++;
		}
	}
	return (result);
}

double		ft_atof_peer(const char *str, int *i)
{
	int		sign;
	double	result;

	result = 0.0;
	sign = 1;
	while (ft_iswhitespace(str[*i]))
		(*i)++;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = 10 * result + str[*i] - '0';
		(*i)++;
	}
	result = ft_decimal_double(str, result, i);
	return (sign * result);
}

int			ft_atoi_peer(const char *str, int *i)
{
	int					sign;
	unsigned long int	result;

	result = 0;
	sign = 1;
	while (ft_iswhitespace(str[*i]))
		(*i)++;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = (10 * result) + (str[*i] - '0');
		(*i)++;
	}
	if (result > 9223372036854775807 && sign == -1)
		return (0);
	else if (result >= 9223372036854775807)
		return (-1);
	return (sign * result);
}
