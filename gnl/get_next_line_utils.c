/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 13:52:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:47:09 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	gnl_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strdup(const char *s1, int n, int startpos)
{
	char	*dup;
	int		i;
	int		len;

	i = 0;
	if (n == 0)
		return (gnl_calloc(0, 0));
	if (n == -1)
		len = gnl_strlen(s1);
	else
		len = n;
	dup = (char*)gnl_calloc(len + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s1[startpos + i];
		i++;
	}
	return (dup);
}

char	*gnl_strjoiner(char *str, char *buf, int ret)
{
	int		i;
	int		n;
	char	*join;

	i = 0;
	n = 0;
	join = (char*)gnl_calloc(gnl_strlen(str) + ret + 1, sizeof(char));
	if (join == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str && str[i])
	{
		join[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	while (buf && buf[n])
	{
		join[i + n] = buf[n];
		n++;
	}
	return (join);
}

void	gnl_bzero(char *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
}
