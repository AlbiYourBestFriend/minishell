/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_and_inc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:49:15 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/14 20:14:11 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_and_inc(char *str1, int *i, char *str2, int *j)
{
	if (str1 != NULL && i != NULL && str2 != NULL && j != NULL)
		str1[*i] = str2[*j];
	if (i != NULL)
		(*i)++;
	if (j != NULL)
		(*j)++;
}
