/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:56:42 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/04 14:57:56 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_space(char c)
{
	if (c == '\t' || c == '\r' || c == '\f' || c == '\v'
		|| c == ' ' || c == '\n')
		return (1);
	return (0);
}

static int	is_in_str(char *cmd, int i)
{
	int	j;
	int	c1;
	int	c2;

	j = 0;
	c1 = 0;
	c2 = 0;
	while (j < i)
	{
		if (cmd[j] == '\"' && cmd[j - 1] != '\\')
			c1 = 1;
		else if (cmd[j] == '\'' && cmd[j - 1] != '\\')
			c2 = 1;
		else if (cmd[j] == '\"' && cmd[j - 1] != '\\' && c2 == 0 && c1 == 1)
			c1 = 0;
		else if (cmd[j] == '\'' && cmd[j - 1] != '\\' && c1 == 0 && c2 == 1)
			c2 = 0;
		j++;
	}
	if (c1 == 1 || c2 == 1)
		return (1);
	return (0);
}

static int	count_char(char *cmd)
{
	int		i;
	int		n;
	int		c;

	i = 0;
	n = 0;
	c = 0;
	while (cmd[i] != '\0')
	{
		c = is_in_str(cmd, i);
		if (c == 1
			|| (c == 0 && (is_space(cmd[i]) == 0
					|| (is_space(cmd[i]) == 1 && is_space(cmd[i + 1]) == 0
						&& cmd[i + 1] != '\0'))))
			n++;
		i++;
	}
	return (n);
}

char	*ft_clean_cmd(char *cmd)
{
	char	*str;
	int		i;
	int		n;
	int		c;

	str = malloc((count_char(cmd) + 1) * sizeof(char));
	i = -1;
	n = 0;
	c = 0;
	while (cmd[++i] != '\0')
	{
		c = is_in_str(cmd, i);
		if (c == 1 || is_space(cmd[i]) == 0)
			str[n++] = cmd[i];
		else if (is_space(cmd[i + 1]) == 0 && cmd[i + 1] != '\0' && n != 0)
			str[n++] = ' ';
	}
	str[n] = '\0';
	return (str);
}

int main()
{
	printf("%s", ft_clean_cmd("r\t h gbsrgn 	\" h\tqq rn\' po kpwa\t\'o\"kg  "));
}
