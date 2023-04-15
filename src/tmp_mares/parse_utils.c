/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 14:04:42 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/04/04 11:49:48 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_double_array(char **double_array)
{
	int	i;

	i = 0;
	while (double_array[i] != NULL)
	{
		free(double_array[i]);
		i++;
	}
	free(double_array);
	return ;
}

char	**make_double_array(int word_count)
{
	char	**result;
	int		i;

	i = 0;
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < word_count)
	{
		result[i] = (char *)malloc(1024 * sizeof(char));
		if (!result[i])
			return (NULL);
		i++;
	}
	return (result);
}

int	ft_word_counter(char const *s, char c)
{
	size_t	i;
	size_t	word_count;
	size_t	len_str;
	char	*str;

	word_count = 0;
	str = (char *)s;
	i = 0;
	len_str = ft_strlen(str);
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word_count++;
		i++;
	}
	if (len_str > 0 && str[len_str - 1] != c)
		word_count++;
	return (word_count);
}




/*
	Sets up pipe for inter-process communication
*/
void set_up_pipe(int *fd_pipe)
{
	if (pipe(fd_pipe) < 0)
		return (minishell_error("Pipe failed"));
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1) // Redirect stdout to write end of pipe
		return (minishell_error("dup2 error for write end of pipe"));
	if (close(fd_pipe[1]) == -1) // Close write end of pipe
		return (minishell_error("close fd_pipe[1] error"));
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1) // Redirect stdin to read end of pipe
		return (minishell_error("dup2 error for read end of pipe"));
	if (close(fd_pipe[0]) == -1) // Close read end of pipe
		return (minishell_error("close fd_pipe[0] error"));
}

int	dup_fds(int fd, int std_fd)
{
	if (fd == std_fd)
		return SUCCESS;
	if (dup2(fd, std_fd) == ERROR)
		return (minishell_error("Dup error\n"), ERROR);
	// close(fd);
	return SUCCESS;
}

/*
	Handles output (redirection)
*/
void handle_output(t_cmd *cmd)
{
    int     fd_file;
	t_redir *redirect;

	redirect = cmd->redir;
    while(redirect != NULL)
    {
		// handle output redirection
		if (redirect->redir == OUT) // check if there is output redirection
		{
			fd_file = open(redirect->file, O_TRUNC | O_CREAT | O_RDWR, 0644); // if so: open outfile and save it in fd_file
			if (fd_file < 0 || (access(redirect->file, W_OK) != 0))
				return (minishell_error("failed to open output file"));
			if (dup2(fd_file, STDOUT_FILENO) == -1) // redirect stdout to fd_file
				return (minishell_error("Dup error stdoutput < - > outfile\n"));
			close(fd_file);	
		}
        redirect = redirect->next;
    }
}

/*
	Handles input (redirection)
*/
void handle_input(t_cmd *cmd)
{
    int     fd_file;
	t_redir *redirect;

	redirect = cmd->redir;
    while(redirect != NULL)
    {
		// handle input redirection
		if (redirect->redir == IN) // check if there is input redirection
		{
			fd_file = open(redirect->file, O_RDONLY); // if so: open infile and save it in fd_file
			if (fd_file < 0 || (access(redirect->file, R_OK) != 0))
				return (minishell_error("failed to open input file"));
			if (dup2(fd_file, STDIN_FILENO) == -1) // redirect stdin to fd_file
				return (minishell_error("Dup error stdinput < - > infile\n"));
			close(fd_file);
		}
        redirect = redirect->next;
    }
}


int	handle_input_redirect(t_cmd *cmd)
{
	int	fd_file = 0;

	// handle input redirection
	if (cmd->redir == NULL) // if there's no file redirection
		return (dup_fds(fd_file, STDIN_FILENO)); // redirect stdin to fd_file
	while(cmd->redir != NULL)
	{
		if (cmd->redir->redir == IN) // check if there is input file redirection
		{
			fd_file = open(cmd->redir->file, O_RDONLY); // if so: open infile and save it in fd_file
			if (fd_file < 0 || (access(cmd->redir->file, R_OK) != 0))
				return (minishell_error("failed to open input file"), ERROR);
		}
		// handle HEREDOC redirection
		// if (cmd->redir->redir == HERE) // check if there is heredoc redirection
		// {
			// heredoc_function();
		// }
		cmd->redir = cmd->redir->next;
	}
	return (dup_fds(fd_file, STDIN_FILENO)); // redirect stdin to fd_file
}

// int	handle_output_redirect(t_cmd *cmd)
// {
// 	int		fd_file = 0;

// 	// handle output redirection
// 	if (cmd->next != NULL) // there's a command coming after this current one
// 		return (dup_fds(fd_pipe[WRITE], STDOUT_FILENO)); // Redirect stdout to write end of pipe
// 	if (cmd->redir == NULL) // check for redirect
// 		return (dup_fds(fd_file, STDOUT_FILENO));
//     while(cmd->redir != NULL)
//     {
// 		if (cmd->redir->redir == OUT) // check if there is output redirection
// 		{
// 			fd_file = open(cmd->redir->file, O_TRUNC | O_CREAT | O_RDWR, 0644); // if so: open outfile and save it in fd_file
// 			if (fd_file < 0 || (access(cmd->redir->file, W_OK) != 0))
// 				return (minishell_error("failed to open output file"), ERROR);
// 		}
// 		// handle APPEND redirection
// 		// if (cmd->redir->redir == APP) // check if there is append redirection
// 		// {
// 		// 	fd_file = open(cmd->redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644); // if so: open outfile and save it in fd_file
// 		// 	if (fd_file < 0 || (access(cmd->redir->file, W_OK) != 0))
// 		// 		return (minishell_error("failed to open append file"), ERROR);
// 		// }
// 		cmd->redir = cmd->redir->next;
//     }
// 	return (dup_fds(fd_file, STDOUT_FILENO)); // redirect stdout to fd_file
// }
