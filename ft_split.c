/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbullock <vbullock@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:58:11 by vbullock          #+#    #+#             */
/*   Updated: 2025/09/22 19:03:24 by vbullock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_initiate_vars(size_t *index, int *counter, int *s_word)
{
	*index = 0;
	*counter = 0;
	*s_word = -1;
}

void	*ft_free(char **strs, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		free(strs[index]);
		index++;
	}
	free(strs);
	return (NULL);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		index;

	index = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[index] = str[start];
		index++;
		start++;
	}
	word[index] = 0;
	return (word);
}

static int	word_count(const char *str, char c)
{
	int	count;
	int	chk;

	count = 0;
	chk = 0;
	while (*str)
	{
		if (*str != c && chk == 0)
		{
			chk = 1;
			count++;
		}
		else if (*str == c)
			chk = 0;
		str++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	index;
	int		counter;
	int		s_word;

	ft_initiate_vars(&index, &counter, &s_word);
	res = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (index <= ft_strlen(s))
	{
		if (s[index] != c && s_word < 0)
			s_word = index;
		else if ((s[index] == c || index == ft_strlen(s)) && s_word >= 0)
		{
			res[counter] = fill_word(s, s_word, index);
			if (!(res[counter]))
				return (ft_free(res, counter));
			s_word = -1;
			counter++;
		}
		index++;
	}
	return (res);
}
