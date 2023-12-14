/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:34:16 by dnikifor          #+#    #+#             */
/*   Updated: 2023/12/14 19:52:06 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	gnl_cleaner(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line != '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	array_length(char **split_line)
{
	int	length;

	length = 0;
	while (split_line[length] != NULL)
	{
		if (split_line[length][0] == '\n')
		{
			free(split_line[length]);
			split_line[length] = NULL;
			free_array((void **)split_line, length);
			return (length);
		}
		length++;
	}
	free_array((void **)split_line, length);
	return (length);
}

static int	is_valid_args(char *str, int i, int j, int temp)
{
	if (str[j] == 0)
		return (1);
	if (str[j] == '-' || str[j] == '+')
		j++;
	while (str[j] != '\n' && str[j] != '\0')
	{
		temp = ft_atoi(str);
		if (temp == 0)
		{
			while (str[i] != '\0')
			{
				i = 0;
				if (str[i] != '0')
					return (1);
				i++;
			}
		}
		if (str[j] < 48 || str[j] > 57)
			return (1);
		j++;
	}
	return (0);
}

int	atoi_checker(t_map *matrix, char **temp, int i, int j)
{
	int	k;

	k = 0;
	while (temp[k] != NULL && temp[k][0] != '\n')
		k++;
	if (k != matrix->size_x)
		return (1);
	while (i < matrix->size_x)
	{
		if (is_valid_args(temp[i], 0, 0, 0))
			return (1);
		matrix->map[j][i] = ft_atoi(temp[i]);
		i++;
	}
	return (0);
}
