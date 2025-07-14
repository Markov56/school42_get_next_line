/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:14:22 by rmarkov           #+#    #+#             */
/*   Updated: 2025/07/14 14:14:24 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_copy_buff(char *buff, size_t len)
{
	char	*new_str;

	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, buff, len);
	new_str[len] = '\0';
	return (new_str);
}

static char	*ft_extract_line(char **buff)
{
	char	*pos;
	char	*line;
	char	*remainder;

	pos = ft_strchr(*buff, '\n');
	if (!pos)
	{
		line = ft_copy_buff(*buff, ft_strlen(*buff));
		free(*buff);
		*buff = NULL;
		return (line);
	}
	line = ft_copy_buff(*buff, pos - *buff + 1);
	if (!line)
		return (NULL);
	remainder = ft_copy_buff(pos + 1, ft_strlen(pos + 1));
	free(*buff);
	if (remainder && *remainder)
		*buff = remainder;
	else
	{
		free(remainder);
		*buff = NULL;
	}
	return (line);
}

static char	*ft_get_buff(int fd, char *buff)
{
	char	*current_buff;
	ssize_t	bytes_read;

	bytes_read = 1;
	current_buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!current_buff)
		return (NULL);
	while (bytes_read > 0 && !ft_strchr(buff, '\n'))
	{
		bytes_read = read(fd, current_buff, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
		{
			free (current_buff);
			free (buff);
			return (NULL);
		}
		current_buff[bytes_read] = '\0';
		buff = ft_join_buffers(buff, current_buff);
	}
	free(current_buff);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buffs[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffs[fd] = ft_get_buff(fd, buffs[fd]);
	if (!buffs[fd])
		return (NULL);
	line = ft_extract_line(&buffs[fd]);
	return (line);
}

/*
#include <stdio.h>

int	main(void)
{
	int		fd1, fd2;
	char	*line1, *line2;

	fd1 = open("text.txt", O_RDONLY);
	fd2 = open("text1.txt", O_RDONLY);
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line1 && !line2)
			break;
		if (line1)
		{
			printf("File1: %s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("File2: %s", line2);
			free(line2);
		}
	}
	close (fd1);
	close (fd2);
	
	return (0);
}
*/
