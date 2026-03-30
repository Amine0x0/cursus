/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:47:53 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/12 03:18:44 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}							t_token_type;

typedef struct s_export_data
{
	char					*key;
	char					*value;
	int						is_append;
	int						has_equal;
	int						found;
}							t_export_data;

typedef struct s_process_tracker
{
	pid_t					*pids;
	int						count;
}							t_process_tracker;

typedef struct s_word_state
{
	int						word_pos;
	int						in_quotes;
	char					quote_char;
}							t_word_state;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	int						quoted;
	struct s_token			*next;
}							t_token;

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_heredoc
{
	char					*delimiter;
	int						quoted;
	int						fd;
	struct s_heredoc		*next;
}							t_heredoc;

typedef struct s_cmd
{
	char					**args;
	t_redirection			*redirections;
	t_heredoc				*heredocs;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_heredoc_data
{
	char					**envp;
	int						exit_status;
	int						quoted;
}							t_heredoc_data;

typedef struct s_child_process_args
{
	t_cmd					*cmd;
	int						cmd_index;
	int						cmd_count;
	int						*pipes;
	char					***envp;
}							t_child_process_args;

typedef struct s_launch_children_args
{
	t_cmd					*commands;
	int						cmd_count;
	int						*pipes;
	char					***envp;
	t_process_tracker		*tracker;
}							t_launch_children_args;

typedef struct s_shell_data
{
	char					**my_envp;
	int						exit_status;
}							t_shell_data;

typedef struct s_process_data
{
	t_token					*tokens;
	char					**my_envp;
	int						exit_status;
	char					*line;
}							t_process_data;

typedef struct s_exec_data
{
	char					***envp;
	t_token					*tokens;
	char					*line;
	int						exit_status;
}							t_exec_data;

typedef struct s_update_data
{
	char					***envp;
	int						i;
	char					*key;
	char					*value;
	int						is_append;
}							t_update_data;

// tokenize
t_token						*tokenize_word(char *input, int *i);
t_token						*tokenize(char *input);

// token_utils
t_token						*create_token(t_token_type type, char *value);
void						add_token_to_list(t_token **head,
								t_token *new_token);
void						free_tokens(t_token *tokens);

// utils
int							is_whitespace(char c);
int							is_delimiter(char c);
int							ft_strcmp(const char *s1, const char *s2);
int							handle_quotes(char c, int *in_quotes,
								char *quote_char);
char						*allocate_word_buffer(char *input);

// check_syntax
int							check_syntax(t_token *tokens);

// expand
void						expand_tokens(t_token *tokens, char **envp,
								int exit_status);
char						*expand_str(char *str, char **envp,
								int exit_status);
char						*expand_var(char *str, int *i, char **envp,
								int exit_status);

// expand utils
char						*ft_strjoin_free(char *s1, char *s2, int to_free);

// parse token
t_cmd						*parse_tokens(t_token *tokens);
int							is_redirection(t_token_type type);
int							handle_redirection(t_cmd *cmd, t_token **current);
t_cmd						*finale_validation(t_cmd *cmd_list);
int							check_heredocs(t_cmd *current_cmd,
								t_token *current);

// error
void						print_error(const char *context,
								const char *message);
int							syntax_error(char *mssg);

// builtins
int							is_builtin(char *cmd);
int							execute_builtin(char **args, char ***envp);
int							builtin_echo(char **args);
int							builtin_cd(char **args, char ***envp);
int							builtin_pwd(char **envp);
int							builtin_env(char **envp);
int							builtin_export(char **args, char ***envp);
int							builtin_unset(char **args, char ***envp);
int							builtin_exit(char **args);

char						**initialize_default_env(void);
char						**setup_environment(char **original_env);
int							update_underscore_var(char ***envp, char *last_arg);

// cmd
int							add_argument(t_cmd *cmd, t_token *token);
t_cmd						*init_cmd(void);
void						free_commands(t_cmd *commands);

// ecx
int							execute_commands(t_cmd *commands, char ***envp,
								int *exit_status);
int							exec_simple_command(t_cmd *cmd, char ***envp,
								int exit_status);

// libft
int							ft_atoi(const char *str);
void						*ft_memset(void *b, int c, size_t len);
int							ft_isalnum(int c);
int							ft_isspace(int c);
int							ft_isalpha(int c);
size_t						ft_strlcat(char *s1, const char *s2, size_t n);
int							ft_isdigit(int c);
char						*ft_itoa(int n);
char						*ft_strchr(const char *s, int c);
int							ft_strcmp(const char *s1, const char *s2);
char						*ft_strdup(const char *src);
char						*ft_strjoin(char *s1, char *s2);
size_t						ft_strlen(const char *s);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
size_t						ft_strlcpy(char *dst, const char *src,
								size_t dstsize);
void						*ft_memcpy(void *dst, const void *src, size_t n);
char						**ft_split(const char *s, char c);
char						*ft_strnstr(const char *haystack,
								const char *needle, size_t len);
char						*ft_strrchr(const char *s, int c);

char						**dup_env(char **env);
void						free_env(char **env);
void						close_extra_fds(void);
int							is_env_var(const char *env, const char *name);
int							ensure_env_var(char ***envp, const char *key);

void						handle_signals(int sig);
void						msh_signals(void);
void						heredoc_signal_handler(int sig);

int							set_env_var_cd(char ***envp, char *name,
								char *value);

int							handle_all_heredocs(t_heredoc *heredocs,
								char **envp, int exit_status);
int							apply_redirections(t_redirection *redirections,
								t_heredoc *heredocs, char **envp,
								int exit_status);
int							create_pipe_if_needed(int pipefd[2]);

int							execute_commands(t_cmd *commands, char ***envp,
								int *exit_status);
int							exec_simple_command(t_cmd *cmd, char ***envp,
								int exit_status);

void						increment_shlvl(char **envp);
char						*process_heredoc_delimiter(char *raw_delimiter,
								int quoted);
void						disable_parent_signals(void);
void						restore_parent_signals(void);
void						replace_env_array(char ***envp, char **new_env);

void						free_words(char **words);
t_token						*create_single_token(char *word);
int							should_split_word(char *str);
char						*expand_str(char *str, char **envp,
								int exit_status);
void						add_token(t_token **first, t_token **last,
								t_token *new_token);
t_token						*create_word_tokens(char *expanded_value);
int							create_pipe_if_needed(int pipefd[2]);
void						write_heredoc_line(int fd, char *line,
								t_heredoc_data *data);

char						*get_last_arg(char **args);
int							count_commands(t_cmd *commands);
void						close_all_pipes(int *pipes, int pipe_count);
char						*find_command_path(char *cmd, char **envp);
int							exec_simple_command(t_cmd *cmd, char ***envp,
								int exit_status);
int							exec_external_cmd(t_cmd *cmd, char ***envp);
int							wait_for_all_children(t_process_tracker *tracker);
void						handle_child_process(t_child_process_args *args);
int							execute_pipeline(t_cmd *commands, char ***envp,
								int *exit_status);
int							setup_redirections(t_cmd *cmd);
int							apply_redirections(t_redirection *redirections,
								t_heredoc *heredocs, char **envp,
								int exit_status);
int							get_signal_status(int status);
int							get_exit_status(int status);
int							*create_pipes(int cmd_count);
pid_t						*allocate_pids(int cmd_count);
int							wait_for_all_children(t_process_tracker *tracker);
void						handle_child_process(t_child_process_args *args);
void						run_child(t_cmd *current,
								t_launch_children_args *args, int i);
int							launch_children(t_launch_children_args *args);
int							handle_file_checks(char *path, char *cmd_name);
int							handle_path_errors(char *path, char *cmd_name);
int							handle_signal_status(int status);
int							handle_heredocs_check(t_cmd *cmd, char **envp,
								int exit_status);
int							handle_special_args(char **args, char ***envp);
int							update_pwd_and_oldpwd(char ***envp,
								char *target_dir);
int							handle_getcwd_failure(char ***envp,
								char *target_dir);
int							build_relative_path(char ***envp, char *target_dir);
int							handle_cd_dotdot_deleted_dir(char ***envp);
int							handle_getcwd_error(char ***envp);
int							cd_to_home(char ***envp);
char						*get_default_path(void);
char						*get_default_pwd(void);
char						*get_default_shlvl(void);
char						*get_default_oldpwd(void);
int							append_new_entry(char ***envp, char *new_entry);
int							update_if_exists(char ***envp, char *name,
								char *new_entry);
int							is_env_var(const char *env, const char *name);
char						*create_env_entry(char *key, char *value,
								int has_equal);
t_token						*get_tokens(char *line);
int							initialize_shell(char **envp, char ***my_envp);
int							check_non_empty_tokens(t_token *tokens);
char						**dup_env(char **env);
t_cmd						*process_tokens(t_process_data *data,
								int *should_continue);
int							handle_tokens(char *line, t_shell_data *shell_data);
int							execute_shell_command(t_cmd *commands,
								t_exec_data *exec_data);
char						*create_env_entry_basic(char *name, char *value);
int							is_valid_identifier(const char *key);
void						print_env_vars(char **envp);
void						parse_export_arg(char *arg, char **key,
								char **value, int *is_append);
int							update_existing_var(char ***envp, char *key,
								char *value, int is_append);
void						add_new_var(char ***envp, char *key, char *value,
								int has_equal);
int							process_export_arg(char *arg, char ***envp,
								int ret);
void						cleanup_export_data(t_export_data *data);

void						apply_heredocs(t_heredoc *hd);
char						*expand_odd_dollar(char *str, int *i,
								char **envp, int exit_status);
void						print_err(const char *format, const char *arg);
#endif