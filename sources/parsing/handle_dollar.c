/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:26:00 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/17 10:10:59 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// remplie la chaine en fonction des caracteres rencontres
static int	put_char_to_str(t_data *data, char *cmd, char *str, int *i_n)
{
	int	n;

	n = 1;
	while (cmd[i_n[0]] != '\0' && n == 1)
	{
		if (cmd[i_n[0]] == '\'')
			put_simple_quote(cmd, str, i_n);
		else if (cmd[i_n[0]] == '\"')
			n = put_double_quote(data, cmd, str, i_n);
		else if (cmd[i_n[0]] == '$' && cmd[i_n[0] + 1] == '?')
			n = put_exit_status(str, i_n);
		else if (cmd[i_n[0]] == '$' && ft_isspace(cmd[i_n[0] + 1]) == 0
			&& cmd[i_n[0] + 1] != '\0')
			n = put_env_var_value(data, cmd, str, i_n);
		else if (cmd[i_n[0]] != '\0')
		{
			copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
		}
	}
	str[i_n[1]] = '\0';
	return (n);
}

// verifier que la chaine a bien ete creee et qu'elle sera bien remplie
static char	*handle_dollar_copy_str(t_data *data, char *cmd, int n)
{
	char	*str;
	int		i_n[2];

	i_n[0] = 0;
	i_n[1] = 0;
	str = malloc((n + 1) * sizeof(char));
	if (str == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	if (put_char_to_str(data, cmd, str, i_n) == 0)
		return (free(str), NULL);
	return (str);
}

// n est la longueur total de la chaine de carateres a creer
char	*handle_dollars(t_data *data, char *cmd)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'')
			n = get_len_simple_quote(cmd, &i, n);
		else if (cmd[i] == '\"')
			n = get_len_double_quote(data, cmd, &i, n);
		else if (cmd[i] == '$' && ft_isspace(cmd[i + 1]) == 0
			&& cmd[i + 1] != '\0')
			n = len_env_var_value(data, cmd, &i, n);
		else
		{
			n++;
			i++;
		}
		if (n == -1)
			return (NULL);
	}
	return (handle_dollar_copy_str(data, cmd, n));
}
