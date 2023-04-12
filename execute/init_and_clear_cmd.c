/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:14 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/12 14:30:00 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_heredoc(t_cmd_info *cmd)
{
	t_cmd_info	*cur;

	cur = cmd;
	while (cur)
	{
		if (heredoc(cur) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}

void	clear_cmd(t_cmd_info *cmd)
{
	t_cmd_info	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->fd[READ] > 0)
			ft_close(cur->fd[READ]);
		if (cur->ft_in_files > 0)
			ft_close(cur->ft_in_files);
		if (cur->ft_out_files > 0)
			ft_close(cur->ft_out_files);
		if (cur->ft_command_path != NULL)
			cur->ft_command_path = ft_frees(cur->ft_command_path);
		cur = cur->next;
	}
	delete_tmp_file();
}