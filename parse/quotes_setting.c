/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:44:43 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 17:46:03 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_quotes(char str, int ch_quotes, t_cmd_info *cmd) 
{
	int	ret;

	ret = ch_quotes;
	if (str == '$')
		cmd->ft_dollar_flag = true;
	if (str == '\'') 
	{
		if (ch_quotes == 1) 
			ret = 0;
		else if (ch_quotes == 2) 
			ret = 2;
		else 
			ret = 1;
	}
	else if (str == '\"') 
	{
		if (ch_quotes == 2) 
			ret = 0;
		else if (ch_quotes == 1) 
			ret = 1;
		else 
			ret = 2;
	}
	return (ret);
}
