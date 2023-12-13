/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitriinikiforov <dmitriinikiforov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:07:52 by dnikifor          #+#    #+#             */
/*   Updated: 2023/12/14 00:32:31 by dmitriiniki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	array_length(char **arr)
{
	int	length;

	length = 0;
	while (arr[length] != NULL)
		length++;
	free_array((void **)arr, length);
	return (length);
}

static int	text_runner(int fd, t_map *matrix, char *line, char *buffer)
{
	int		line_count;
	int		bytes_read;
	char	*newline_pos;
	char	*end;

	line_count = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		if (bytes_read < 0)
			exit(free_mtx_gnl_buf(buffer, matrix, fd, line));
		newline_pos = buffer;
		end = buffer + bytes_read;
		newline_pos = ft_memchr(newline_pos, '\n', end - newline_pos);
		while (newline_pos)
		{
			line_count++;
			newline_pos++;
			newline_pos = ft_memchr(newline_pos, '\n', end - newline_pos);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (line_count);
}

static int	count_rows(char **argv, int fd, t_map *matrix, char *line)
{
	int		line_count;
	char	*buffer;

	line_count = 0;
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		exit(free_mtx_gnl(matrix, fd, line));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(free_mtx_gnl_buf(buffer, matrix, fd, line));
	line_count = text_runner(fd, matrix, line, buffer);
	free(buffer);
	if (close(fd) < 0)
		exit(free_mtx_gnl(matrix, fd, line));
	return (line_count);
}

char	*matrix_initializer(t_map *matrix, char **argv, int fd)
{
	char	*line;
	char	**split_line;

	line = get_next_line(fd);
	if (!line)
	{
		free(matrix);
		exit(1);
	}
	matrix->size_y = count_rows(argv, fd, matrix, line);
	split_line = ft_split(line, ' ');
	if (!split_line)
		exit(free_mtx_gnl(matrix, fd, line));
	matrix->size_x = array_length(split_line);
	matrix->map = (int **)malloc((matrix->size_y) * sizeof(int *));
	if (!matrix->map)
		exit(free_mtx_gnl(matrix, fd, line));
	return (line);
}

t_map	*map_creation(t_map *matrix, int fd, char *line)
{
	char	**temp;
	int		i;
	int		j;

	j = 0;
	while (line && *line != '\n')
	{
		i = 0;
		temp = ft_split(line, ' ');
		matrix->map[j] = (int *)malloc(matrix->size_x * sizeof(int));
		if (!matrix->map[j])
		{
			free(line);
			exit(free_mtx_map_tmp_gnl(matrix, temp, fd, j));
		}
		while (++i - 1 < matrix->size_x)
			matrix->map[j][i - 1] = ft_atoi(temp[i - 1]);
		free_array((void **)temp, matrix->size_x);
		free(line);
		j++;
		line = get_next_line(fd);
		if (line == NULL && j != matrix->size_y)
			exit(free_mtx_map(matrix, j));
	}
	return (matrix);
}