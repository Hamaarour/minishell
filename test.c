
typedef enum s_type_redir
{
	INPUT,
	OUTPUT,
	APPAND,
	HERE_DOC
}	t_type_redir;

typedef struct s_redir
{
	t_type_redir	type;
	char			*filename;
	int				heredoc[2];
}	t_redir;

typedef struct s_AST
{
	char			**args;
	int				size_args;
	t_redir			**redirec;
	int				size_redirec;
	int				is_builten;
}	t_AST;

typedef struct s_pipes
{
	t_AST	**tab_cmd;
	int		nbre_pipes;
}	t_pipes;

typedef struct s_parser
{
	t_lexer		*lexer;
	t_tocken	*cur_tocken;
	t_tocken	*prev_tocken;
	int			lex_ambg;
}	t_parser;

/* Check if there any unexpected tocken */
int	not_redirect(t_tocken *tocken)
{
	if (tocken)
	{
		if (tocken->type == TOCKEN_GREAT
			|| tocken->type == TOCKEN_DGREAT || tocken->type == TOCKEN_LESS
			|| tocken->type == TOCKEN_HER_DOC)
			return (0);
	}
	return (1);
}
int	parser_expected(t_parser *parser, t_tocken_type type)
{
	if (parser->cur_tocken)
	{
		if (parser->cur_tocken->type == type)
		{
			if (parser->lexer->env_vide && not_redirect(parser->prev_tocken))
				free(parser->cur_tocken->value);
			free_tocken(parser->prev_tocken);
			parser->prev_tocken = parser->cur_tocken;
			parser->cur_tocken = lexer_get_next_tocken(parser->lexer);
			return (0);
		}
		write(2, "Minishell: syntax error`", 48);
		g_data.exit_status = 258;
	}
	return (1);
}
/* Syntax Error */
int	check_syntax_cmd(t_parser *parser)
{
	if (!parser->cur_tocken)
		return (1);
	if (parser->cur_tocken->type == T_PIPE || parser->cur_tocken->type == T_EOF)
		return (parser_expected(parser, TOCKEN_WORD));
	return (0);
}

/* fill the node by Simple Commande */

t_AST	*get_ast_simple_cmd(t_parser *parser)
{
	t_AST	*ast;

	if (check_syntax_cmd(parser))
		return (NULL);
	ast = init_ast();
	while (parser->cur_tocken && parser->cur_tocken->type != TOCKEN_PIPE
		&& parser->cur_tocken->type != TOCKEN_EOF)
	{
		if (parser->cur_tocken->type == TOCKEN_WORD)
			collect_args(parser, ast);
		else if (collect_redirect(parser, ast))
			return (free_ast_cmd(ast));
	}
	if (!parser->cur_tocken)
		return (free_ast_cmd(ast));
	if (ast->args)
	{
		ast->args = ft_realloc_er(ast->args, sizeof(char *), ast->size_args);
		ast->args[ast->size_args] = NULL;
	}
	if (parser->lex_ambg)
		free_args_in_ambg_cas(&ast, &parser);
	return (ast);
}

t_pipes	*parser_parse(t_parser *parser)
{
	t_pipes	*pipes;
	t_AST	*ast_simple_cmd;

	ast_simple_cmd = get_ast_simple_cmd(parser);
	if (!ast_simple_cmd)
		return (NULL);
	pipes = malloc(sizeof(t_pipes));
	if (pipes == NULL)
		ft_error(errno);
	pipes->tab_cmd = malloc(sizeof(t_AST *));
	if (pipes->tab_cmd == NULL)
		ft_error(errno);
	pipes->nbre_pipes = 0;
	if (ast_simple_cmd->size_args != 0 || ast_simple_cmd->size_redirec != 0)
	{
		pipes->tab_cmd[0] = ast_simple_cmd;
		pipes->nbre_pipes += 1;
	}
	else
		free_ast_cmd(ast_simple_cmd);
	while (pipes && parser->cur_tocken
		&& parser->cur_tocken->type == TOCKEN_PIPE)
		get_ast_pipeline(parser, &pipes);
	return (pipes);
}
/* free a parser */


void	run_minishell(t_pipes *ast, t_parser *parser, int input, char *cmd_line)
{

	if (parser->cur_tocken && parser->cur_tocken->type == 6)
		continue ;

	ast = parser_parse(parser);
	free_parser(parser);
}