/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llugez <llugez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:05:45 by llugez            #+#    #+#             */
/*   Updated: 2026/01/30 13:28:57 by llugez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"

typedef struct Command
{
	char			**cmd;
	char			*path_cmd;
	struct Command	*next;
	struct Command	*prev;
}					t_cmd_constructor;

typedef struct Data
{
	char			*limiter;
	char			*infile;
	char			*outfile;
	char			**list_cmd;
	char			**envp;
	char			*shell;
	int				*pids;
	int				(*tube)[2];
	int				get_outfile_perm;
	int				fd_inf;
	int				fd_out;
	int				fd_tmp;
	int				nb_cmd;
	int				nb_tube;
}					t_data;

# define ENV_PATH "PATH="
# define SHELL_PATH "SHELL="
# define EXIT_CODE_PERMISSION 1
# define EXIT_CODE_COMMAND 127

// Main.c
void				pipe_tube(t_data *data);

// Clear.c
void				clean_2d_tab(char **tab);
void				clean_list(t_cmd_constructor *list);
void				clean_data(t_data *data);
void				clean_all(t_cmd_constructor *list, t_data *data);

// Utils.c
char				*prepend_slash(const char *cmd);
char				**build_list_cmd(int nb_cmd, char *argv[], int start);

// File.c
int					handle_outfile(t_data *data, char *outfile_path);
int					handle_infile(t_data *data, char *infile_path);
int					handle_tempfile(t_data *data);
int					handle_outfile_heredoc(t_data *data, char *outfile_path);

// List_utils.c
t_cmd_constructor	*create_node(char *full_cmd);
void				push_back(t_cmd_constructor **head, char *full_cmd);
void				init_list(t_cmd_constructor **head, char **list_cmd, int n);

// PATH.c
char				*get_path_cmd(char *envp[], char *cmd);
char				*get_path_env(char *envp[], char *var);
char				*get_shell_path(char *envp[], t_data *data);

// Error.c
void				handle_error(const char *message, t_data *data);
void				handle_execve_error(t_data *data,
						t_cmd_constructor *act_cmd);

// Pipex.c
void				close_fds(t_data *data, int i);
void				execute_command(t_cmd_constructor *act_cmd, t_data *data);
void				close_parent_fd(t_data *data);
void				wait_for_child_pr(t_data *data, t_cmd_constructor *act_cmd);
void				pipex(t_data *data, t_cmd_constructor *act_cmd);

// HereDoc.c
void				handle_heredoc(t_cmd_constructor **act_cmd, t_data *data,
						char *argv[], int argc);
void				init_heredoc_data(t_data *data, int argc, char *argv[]);
void				check_for_limiter(t_data *data);

// Dup.c
void				dup_first_command(int i, t_data *data);
void				dup_inter_command(int i, t_data *data);
void				dup_last_command(int i, t_data *data);

#endif
