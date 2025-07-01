/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtarvain <jtarvain@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:26:59 by jtarvain          #+#    #+#             */
/*   Updated: 2025/07/01 16:03:56 by jtarvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_byte;
	unsigned char	*s_byte;

	i = 0;
	d_byte = (unsigned char *)dest;
	s_byte = (unsigned char *)src;
	while (i < n)
	{
		d_byte[i] = s_byte[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*final_str;
	size_t	total_len;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_len = len1 + len2;
	final_str = (char *)malloc((total_len + 1) * sizeof(char));
	if (!final_str)
		return (0);
	ft_memcpy(final_str, s1, len1);
	ft_memcpy((final_str + len1), s2, len2);
	final_str[total_len] = '\0';
	return (final_str);
}
