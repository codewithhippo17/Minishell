#include "pipex.h"
#include <stdlib.h>
#include <string.h>

char	*filter_input(const char *input, int *flag)
{
	int		i;
	int		j;
	int		length;
	char	*filtered_input;

	i = 0;
	j = 0;
	length = ft_strlen(input);
	filtered_input = malloc(length + 1);
	if (!filtered_input)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '|')
			i++;
		else if (input[i] == '>' && input[i + 1] != '>')
		{
			i++;
			*flag = 1;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			i += 2;
			*flag = 2;
		}
		else
			filtered_input[j++] = input[i];
		i++;
	}
	filtered_input[j] = '\0';
	return (filtered_input);
}

char	*construct_command_string(char **arguments)
{
	int		i;
	char	*command_string;

	i = 1;
	command_string = ft_strdup(arguments[0]);
	while (arguments[i])
	{
		command_string = realloc(command_string, strlen(command_string)
				+ strlen(arguments[i]) + 2);
		if (!command_string)
		{
			perror("Failed to allocate memory");
			return (NULL);
		}
		strcat(command_string, " ");
		strcat(command_string, arguments[i]);
		i++;
	}
	return (command_string);
}

void	parse_pipex(char *input, char **env)
{
	int		flag;
	char	**arguments;
	char	*filtered_input;
	char	*temp;
	char	*command_string;
	char	*final_input;

	flag = 0;
	if (ft_strchr(input, '<') && ft_strchr(input, '>') && ft_strchr(input, '|'))
	{
		filtered_input = filter_input(input, &flag);
		if (filtered_input)
		{
			arguments = ft_split(filtered_input, ' ');
			pipex(arguments, env, flag);
			free(filtered_input);
		}
	}
	else
	{
		arguments = ft_split(input, ' ');
		if (arguments[0] && arguments[1])
		{
			temp = arguments[0];
			arguments[0] = arguments[1];
			arguments[1] = temp;
		}
		command_string = construct_command_string(arguments);
		if (command_string)
		{
			final_input = filter_input(command_string, &flag);
			if (final_input)
			{
				arguments = ft_split(final_input, ' ');
				printf("%s\n", arguments[3]);
				pipex(arguments, env, flag);
				free(final_input);
			}
			free(command_string);
		}
	}
}
