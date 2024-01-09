/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:02:33 by spipitku          #+#    #+#             */
/*   Updated: 2023/10/03 19:15:24 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s[i] != c && s[i])
		j++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i])
				i++;
			if (s[i] != c && s[i])
				j++;
			if (!s[i])
				break ;
		}
		i++;
	}
	return (j);
}

char	*word_insert(const char *s, size_t ptr, unsigned char c)
{
	size_t		i;
	size_t		j;
	char		*word;

	j = 0;
	i = ptr;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	word = ft_substr(s, ptr, j);
	if (word == NULL)
		return (word);
	return (word);
}

char	**return_null(char ***s, size_t j);

char	**insert_word_to_splite(size_t all_word, char const *s, char c)
{
	size_t		i;
	size_t		j;
	char		**splite;
	size_t		length;

	length = ft_strlen(s);
	i = 0;
	j = 0;
	splite = malloc(sizeof(char *) * (all_word + 1));
	if (splite == NULL)
		return (splite);
	while (i < length)
	{
		if (s[i] != c && s[i])
		{
			(splite)[j] = word_insert(s, i, c);
			if (!splite[j])
				return (return_null(&splite, j));
			i = i + ft_strlen(splite[j]);
			j++;
		}
		i++;
	}
	(splite)[j] = 0;
	return (splite);
}

char	**return_null(char ***s, size_t j)
{
	char		**splite;
	size_t		i;

	splite = *s;
	if (j == 0)
	{
		splite = malloc(sizeof(char *));
		splite[0] = 0;
		return (splite);
	}
	i = 0;
	while (i < j)
	{
		free(splite[i++]);
	}
	free(splite);
	splite = NULL;
	return (splite);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	char		**splite;

	splite = NULL;
	if (!s)
		return (NULL);
	i = count_word(s, c);
	if (((!ft_strlen(s) && (!c || c))) || (!i && ft_strlen(s)))
		return (return_null(&splite, 0));
	if (ft_strlen(s) && !c)
	{
		splite = malloc(sizeof(char *) * 2);
		if (!splite)
			return (splite);
		splite[0] = ft_strdup(s);
		splite[1] = 0;
		return (splite);
	}
	if (i && c)
		splite = insert_word_to_splite(i, s, c);
	return (splite);
}

// int	main(void)
// {
// 	char *string = "                  ";
//     char **result = ft_split("aaa", 'z');
// 	printf("%s",result[0]);
// }
