/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirotsu <ahirotsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:52:53 by ahirotsu          #+#    #+#             */
/*   Updated: 2023/10/18 19:22:54 by ahirotsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getline(char *stastr)
{
	int		i;
	char	*le;

	i = 0;
	if (!stastr[0])
		return (NULL);
	while (stastr[i] != '\0' && stastr[i] != '\n')
		i++;
	le = (char *)malloc(sizeof(char) * (i + 2));
	if (le == NULL)
		return (NULL);
	i = 0;
	while (stastr[i] != '\0' && stastr[i] != '\n')
	{
		le[i] = stastr[i];
		i++;
	}
	if (stastr[i] == '\n')
	{
		le[i] = stastr[i];
		i++;
	}
	le[i] = '\0';
	return (le);
}

char	*ft_disline(char *stastr)
{
	int		i;
	char	*new;
	int		s;

	i = 0;
	while (stastr[i] != '\0' && stastr[i] != '\n')
		i++;
	if (!stastr[i])
	{
		free(stastr);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(stastr) - i + 1));
	if (!new)
		return (NULL);
	s = 0;
	while (stastr[i] != '\0')
		new[s++] = stastr[1 + i++];
	new[s] = '\0';
	free(stastr);
	return (new);
}

char	*read_data(int fd, char *stastr)
{
	char	*buffer;
	int		ret;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ret = 1;
	while (!ft_strchr(stastr, '\n') && ret != 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[ret] = '\0';
		stastr = ft_strjoin(stastr, buffer);
	}
	free(buffer);
	return (stastr);
}

char	*get_next_line(int fd)
{
	static char	*stastr;
	char		*le;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stastr = read_data(fd, stastr);
	if (!stastr)
		return (NULL);
	le = ft_getline(stastr);
	stastr = ft_disline(stastr);
	return (le);
}
