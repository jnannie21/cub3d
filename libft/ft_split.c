/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 03:43:38 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/14 13:38:47 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static char		*skip_delim(char *str, char c)
{
	while (*str == c && *str != '\0')
		str++;
	return (str);
}

static size_t	w_count(char *str, char c)
{
	size_t	w_count;

	w_count = 0;
	str = skip_delim(str, c);
	while (*str != '\0')
	{
		str = str + word_len(str, c);
		str = skip_delim(str, c);
		w_count++;
	}
	return (w_count);
}

static char		**fill_the_tab(char **tab, char *str, char c)
{
	size_t	w;

	w = 0;
	str = skip_delim(str, c);
	while (*str != '\0')
	{
		tab[w] = malloc(word_len(str, c) + 1);
		if (tab[w] == 0)
		{
			while (w--)
				free(tab[w]);
			return (0);
		}
		ft_strlcpy(tab[w], str, word_len(str, c) + 1);
		str = str + word_len(str, c);
		str = skip_delim(str, c);
		w++;
	}
	tab[w] = 0;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;

	if (s == 0)
		return (0);
	tab = malloc((w_count((char *)s, c) + 1) * (sizeof(char **)));
	if (tab == 0)
		return (0);
	if (fill_the_tab(tab, (char *)s, c))
		return (tab);
	free(tab);
	return (0);
}
