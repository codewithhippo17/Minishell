/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:43:52 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:43:52 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			append_token(&head, &tail, parse_spaces(&i, input));
		else if (is_quote(input[i]))
			append_token(&head, &tail, parse_quoted(&i, input, input[i]));
		else if (is_operator_start(input[i]))
			append_token(&head, &tail, parse_operator(&i, input, input[i]));
		else
			append_token(&head, &tail, parse_word(&i, input));
	}
	return (head);
}
