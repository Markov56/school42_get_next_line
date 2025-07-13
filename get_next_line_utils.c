#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (s + i);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return (s + i);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_join_buffers(char *previous, char *current)
{
	size_t	prev_len;
	size_t	curr_len;
	char	*new_str;

	prev_len = ft_strlen(previous);
	curr_len = ft_strlen(current);
	new_str = (char *)malloc(prev_len + curr_len + 1);
	if (!new_str)
		return (NULL);
	if (previous)
	{
		ft_memcpy(new_str, previous, prev_len);
		free(previous);
	}
	ft_memcpy(new_str + prev_len, current, curr_len);
	new_str[prev_len + curr_len] = '\0';
	return (new_str);
}

