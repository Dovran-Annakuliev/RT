#include "../../includes/rtv1.h"

int				ft_count_words_split(const char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int		ft_count_words_space(char const *s)
{
	int	words;
	int i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			while (s[i] && !ft_isspace(s[i]))
				i++;
			words++;
		}
	}
	return (words);
}

static size_t	word_len(char const *s, size_t i)
{
	size_t j;

	j = i;
	while (s[j] && !ft_isspace(s[i]))
		j++;
	return (j - i);
}

static void		*ft_strfree(char **s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		ft_strdel(&s[i++]);
	free(s);
	s = NULL;
	return (NULL);
}

char			**ft_strsplit_space(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len = ft_count_words_space(s);
	if (!(arr = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			len = word_len(s, i);
			if (!(arr[j++] = ft_strsub(s, i, len)))
				return (ft_strfree(arr, j - 1));
			i = i + len - 1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}
