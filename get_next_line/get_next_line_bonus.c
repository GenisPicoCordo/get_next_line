/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:54:45 by gpico-co          #+#    #+#             */
/*   Updated: 2024/12/03 11:28:02 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*read_buffer(int fd, char *stash)
{
	char	*buffer;
	int		bytes;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stash));
	buffer[0] = '\0';
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			stash = ft_strjoin(stash, buffer);
		}
	}
	free(buffer);
	if (bytes == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*get_result(char *stash)
{
	char	*nl;
	char	*result;
	int		len;

	nl = ft_strchr(stash, '\n');
	len = (nl - stash) + 1;
	result = ft_substr(stash, 0, len);
	if (!result)
		return (NULL);
	return (result);
}

char	*new_stash(char *stash)
{
	int		len;
	char	*nstash;
	char	*ptr;

	ptr = ft_strchr(stash, '\n');
	if (!ptr)
	{
		nstash = NULL;
		return (ft_free(&stash));
	}
	else
		len = (ptr - stash) + 1;
	if (!stash[len])
		return (ft_free(&stash));
	nstash = ft_substr(stash, len, ft_strlen(stash) - len);
	ft_free(&stash);
	if (!nstash)
		return (NULL);
	return (nstash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*result;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if ((stash[fd] && !ft_strchr(stash[fd], '\n')) || !stash[fd])
		stash[fd] = read_buffer(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	result = get_result(stash[fd]);
	if (!result)
		return (ft_free(&stash[fd]));
	stash[fd] = new_stash(stash[fd]);
	return (result);
}
