/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:03:41 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 18:04:07 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*key;

	len = 0;
	while (key_value[len] != 0 && key_value[len] != '=')
	{
		++len;
	}
	if (key_value[len] == '\0')
		return (NULL);
	key = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = key_value[i];
		++i;
	}
	key[i] = 0;
	return (key);
}

char	*get_env_value(char *key_value)
{
	size_t	i;
	size_t	len;
	char	*value;

	len = 0;
	while (key_value[len] != 0 && key_value[len] != '=')
		++key_value;
	if (key_value[len] == 0)
		return (NULL);
	len = ft_strlen(++key_value);
	value = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		value[i] = key_value[i];
		++i;
	}
	value[i] = 0;
	return (value);
}

t_info_env	*compare_env_key(t_info_env *env_head, char *key)
{
	t_info_env	*cur;

	cur = env_head;
	// while (cur->key != 0 && ft_strncmp(key, cur->key, ft_strlen(cur->key)))
	while (cur->key != 0 && ft_strncmp(key, cur->key, ft_strlen(key)))
		cur = cur->next;
	return (cur);
}

t_info_env	*new_env(char *key_value)
{
	t_info_env	*new;

	new = (t_info_env *)ft_malloc(sizeof(t_info_env), 1);
	if (key_value == NULL)
	{
		new->key = NULL;
		new->value = NULL;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->key = get_env_key(key_value);
		if (new->key == NULL)
			return (NULL);
		new->value = get_env_value(key_value);
		if (new->value == NULL)
			return (NULL);
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

int	ft_env_init(t_info_env *cur, char **envp)
{
	size_t	i;
	t_info_env	*new;

	i = 0;
	//export 혹은 env로 확인, 
	cur->key = get_env_key(envp[1]); // 환경변수 aaa=key 에서 aaa
	if (cur->key == NULL)
		return (-1);
	cur->value = get_env_value(envp[1]); // aaa=key에서 key
	// printf("value == %s", cur->value); ->경로
	if (cur->value == NULL)
		return (-1);
	cur->next = 0;
	cur->prev = 0;
	while (envp[++i])
	{
		new = new_env(envp[i]); //노드 생성후 이어줌 모든 환경변수 넣어줌.
		if (new == NULL)
			return (-1);
		cur->next = new;
		new->prev = cur;
		cur = cur->next;
	}
	new = new_env(NULL);
	new->prev = cur;
	cur->next = new;
	return (0);
}

int	ft_str_isspace(char *str)
{
	while (*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
		{
			return (0);
		}
		str++;
	}
	return (1);
}

void	ft_main_init(int argc, char **argv)
{
	struct termios	term_sig;

	if (argc != 1)
		exit_errno("argument input error", NULL, 126);
	tcgetattr(STDIN_FILENO, &term_sig);
	term_sig.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_sig);
	set_signal(SHE, SHE);
	g_exit_signal_code = 0;
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	struct termios		term_sig;
	char				*input;
	t_cmd_info			*cmd;
	t_info_env			info_env;

	tcgetattr(STDIN_FILENO, &term_sig); 
	ft_main_init(argc, argv);
	ft_env_init(&info_env, envp);
	while (42)
	{
		input = readline("minishell $ ");
		if (!input) 
			break ;
		if (*input != '\0')
			add_history(input); 
		if (*input != '\0' && !ft_str_isspace(input))
		{
			cmd = ft_cmd_init();
			ft_parse(input, cmd);
			ft_tokenize(cmd, &info_env);
			ft_arg_check(&cmd);
			print_checker(cmd);
			ft_free_list(cmd);
		}
		free(input);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term_sig);
}
