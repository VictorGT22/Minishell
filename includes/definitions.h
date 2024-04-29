/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:38:26 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/29 14:41:43 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

//COLORS
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

# define READ		1
# define HEREDOC	2
# define EXEC		3

//ACTIONS
# define NUM_ACTIONS 9
# define EXIT "exit"
# define ECHO "echo"
# define PWD "pwd"
# define CD "cd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define HELP "help"

//ERROR MSG
# define WRONG_OP_NL "minishell: syntax error 'new line'\n"
# define WRONG_OP "minishell: syntax error near unexpected token"
# define NO_CLOSED "minishell: syntax error no closed quote\n"
# define NOT_FOUND "command not found\n"
# define NO_PERM "Permission denied\n"
# define NO_DIR "Not a directory\n"
# define NO_EXIST "No such file or directory.\n"
# define NO_FORK "Error. Fork no created\n"

#endif