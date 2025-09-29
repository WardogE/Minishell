/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbullock <vbullock@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:28:54 by vbullock          #+#    #+#             */
/*   Updated: 2025/09/22 19:18:21 by vbullock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count])
	{
		count++;
	}
	return (count);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		index;
	int		count;

	index = 0;
	count = 0;
	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[index])
	{
		res[count] = s1[index];
		count++;
		index++;
	}
	index = 0;
	while (s2[index])
	{
		res[count] = s2[index];
		count++;
		index++;
	}
	res[count] = 0;
	return (res);
}
