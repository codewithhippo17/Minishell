#include "../minishell.h"

t_pipe	*create_command_node(const char *cmd)
{
	t_pipe	*new_node;

	new_node = (t_pipe *)malloc(sizeof(t_pipe));
	new_node->cmd = strdup(cmd);
	new_node->next_redir = NULL;
	new_node->next_cmd = NULL;
	new_node->next_arg = NULL;
	return (new_node);
}

t_pipe	*create_argument_node(const char *arg)
{
	t_pipe	*new_arg;

	new_arg = (t_pipe *)malloc(sizeof(t_pipe));
	new_arg->cmd = strdup(arg);
	new_arg->next_redir = NULL;
	new_arg->next_cmd = NULL;
	new_arg->next_arg = NULL;
	return (new_arg);
}

char	**ft_swich_arry(t_pipe *cmd)
{
	int		l;
	int		i;
	char	**arr_cmd;
	t_pipe	*head;

	l = 0;
	i = 0;
	head = cmd;
	while (head)
	{
		l++;
		head = head->next_cmd;
	}
	head = cmd;
	arr_cmd = malloc((l + 1) * sizeof(char *));
	if (!arr_cmd)
		return (NULL);
	while (head)
	{
		arr_cmd[i] = ft_strdup(head->cmd);
		head = head->next_arg;
		i++;
	}
	arr_cmd[l + 1] = NULL;
	return (arr_cmd);
}

t_shell	*revampstruct(t_pipe *cmd)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->arr_cmd = ft_swich_arry(cmd);
	shell->next_redir = cmd->next_redir;
	shell->next_cmd = NULL;
	return (shell);
}

/*
t_shell *shell(t_minishell *mini)
{

  int i = 0;
  char **cmd = ft_split(mini->input, '|');

  t_shell *curent = mini->shell;
  while (cmd[i])
  {
    curent->arr_cmd = ft_split(cmd[i], ' ');
    curent->next_redir = NULL;
    curent = mini->shell->next_cmd;
    i++;
  }
  return (mini->shell);
}*/
