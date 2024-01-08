/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:04:40 by yboumlak          #+#    #+#             */
/*   Updated: 2024/01/08 18:07:49 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*process_line(char **stash)
{
	int		i;
	char	*line;
	char	*deref;

	i = 0;
	deref = *stash;
	if (stash && deref)
	{
		while (deref[i])
		{
			if (ft_strchr("\n", deref[i]))
				return (ft_substr(deref, 0, i + 1));
			i++;
		}
		if (deref[i] == '\0')
		{
			line = ft_substr(deref, 0, i);
			free(deref);
			*stash = NULL;
			return (line);
		}
	}
	return (NULL);
}

char	*update_stash(char *stash)
{
	int		i;
	char	*ret;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			ret = ft_substr(stash, i + 1, ft_strlen(stash) - i);
			free(stash);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			read_bytes;
	static char	*stash = NULL;
	char		*line;
	char		tmp[BUFFER_SIZE + 1];

	read_bytes = 1;
	while (read_bytes > 0)
	{
		if (fd < 0 || BUFFER_SIZE < 0)
			break ;
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		tmp[read_bytes] = '\0';
		stash = ft_strjoin(stash, tmp);
	}
	line = process_line(&stash);
	stash = update_stash(stash);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("get_next_line.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	// pause();
// }