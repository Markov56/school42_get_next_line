#include "get_next_line.h"

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
	if (!remainder)
	{
		free(line);
		return (NULL);
	}
	free(*buff);
	*buff = remainder;
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
	while(bytes_read > 0 && !ft_strchr(buff, '\n'))
	{
		bytes_read = read(fd, current_buff, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
		{
			free (current_buff);
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
	static char	*buff = NULL;
	char		*line;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_get_buff(fd, buff);
	if (!buff)
		return (NULL);	
	line = ft_extract_line(&buff);
	return (line);
}

/*
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("line: %s", line);
		free(line);
		line = get_next_line(fd);
	}
	
	return (0);
}
/*