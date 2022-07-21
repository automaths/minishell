#include "../execution.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			t;
	long long	x;

	t = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] == ' ')
		if (str[i++] == '-')
			t = -1;
	x = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (x * t > 2147483647)
			return (-1);
		if (x * t < -2147483648)
			return (0);
		x = (x * 10) + (str[i++] - '0');
	}
	x *= t;
	return (x);
}

static int	is_charset(char const *str, char charset)
{
	if (charset == *str)
		return (1);
	return (0);
}

static int	num_lines(char const *str, char charset)
{
	int	n;

	n = 0;
	while (*str)
	{
		while (*str && is_charset(str, charset))
			str++;
		if (*str)
			n++;
		while (*str && !is_charset(str, charset))
			str++;
	}
	return (n);
}

static int	num_char(char const *str, char charset)
{
	int	n;

	n = 0;
	while (*str && !is_charset(str, charset))
	{
		str++;
		n++;
	}
	return (n);
}

static char	*ft_fill(char const *str, char charset)
{
	char	*ptr;
	int		i;
	int		n;

	n = num_char(str, charset);
	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[n] = '\0';
	i = 0;
	while (i < n)
	{
		ptr[i] = str[i];
		i++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		n;
	int		i;

	n = num_lines(s, c);
	split = (char **)malloc(sizeof(char *) * (n + 1));
	if (split == NULL)
		return (NULL);
	split[n] = NULL;
	i = 0;
	while (*s)
	{
		while (*s && is_charset(s, c))
			s++;
		if (*s)
		{
			split[i] = ft_fill(s, c);
			if (split[i++] == NULL)
				return (NULL);
		}
		while (*s && !is_charset(s, c))
			s++;
	}
	return (split);
}

char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	i;
	size_t	n;

	n = ft_strlen(str);
	ptr = (char *) malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[n] = '\0';
	i = 0;
	while (i < n)
	{
			ptr[i] = str[i];
			i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (one[i] && two[i] && one[i] == two[i] && i < n - 1)
		i++;
	return (one[i] - two[i]);
}

static int	is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	word_start(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (is_set(s1[i], set))
		i++;
	return (i);
}

static int	word_end(const char *s1, const char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (is_set(s1[i], set))
		i--;
	return ((ft_strlen(s1) - (i + 1)));
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	diff;
	char	*dest;

	i = 0;
	j = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	diff = word_start(s1, set) + word_end(s1, set);
	if (diff == (ft_strlen(s1) * 2))
		diff = ft_strlen(s1);
	dest = malloc(sizeof(char) * ((ft_strlen(s1) - diff) + 1));
	if (dest == NULL)
		return (NULL);
	while (is_set(s1[i], set))
		i++;
	while (i < (ft_strlen(s1) - word_end(s1, set)))
	{
		dest[j] = s1[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

