/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:12:10 by dnikifor          #+#    #+#             */
/*   Updated: 2023/12/18 11:08:26 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./libft/libft/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_map
{
	int		size_y;
	int		size_x;
	int		**map;
	char	***colmap;
	char	*line;
	int		fd;
}	t_map;

char	*matrix_initializer(t_map *matrix, char **argv);
t_map	*map_creation(t_map *matrix, int j, int i);

int		count_rows(char **argv, t_map *matrix);

int		free_mtx_map_gnl(t_map *matrix, int j);
int		free_mtx_gnl(t_map *matrix);
int		free_mtx_map(t_map *matrix, int j);

int		free_mtx_gnl_buf(char *buffer, t_map *matrix);
int		free_mtx_map_tmp_gnl(t_map *matrix, char **temp, int j, int i);
void	free_array(void **arr, int length);
void	free_triple_pointer(t_map *matrix, int length);

void	gnl_cleaner(int fd);
int		array_length_with_free(char **split_line);
int		array_length(char **split_line);
char	*ft_strdup_nl(const char *s1);

t_map	*reader(char **argv);
void	print(t_map *matrix); //delete before submission

int		atoi_checker(t_map *matrix, char **temp, int i, int j);

void	colour_extractor(char **str, t_map *matrix, int j);

#endif