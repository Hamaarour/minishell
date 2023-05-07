t_token	*fetch_string(t_lexer *lexer)
{
	char	*str;//str is the string that will be returned
	char	*tmp;//stmp is a temporary string that will be used to store the characters of the word

	str = ft_strdup("");
	tmp = NULL;
	while (lexer->c != '<' && lexer->c != '>' && lexer->c != '|' && lexer->c != '\t' && lexer->c != ' ' && lexer->c != '\0')
	{
		if (lexer->c == '$')
				tmp = get_dollar(lexer);
		else if (lexer->c == '\'')
			tmp = single_quote(lexer);
		else if (lexer->c == '\"')
			tmp = hundle_quotes(lexer);		
		else
			tmp = get_char(lexer);
		str = ft_strjoin(str, tmp);
		free(tmp);
		if (!str)
			error_func(errno);
	}
	return (init_tokens(t_CHAR, str));
}
char	*get_dollar(t_lexer *lexer)
{
	char	*tmp; //str
	char	*str; //s

	str = ft_strdup("");
	advance_lexer(lexer);printf("c = %c\n", lexer->c);
	if (lexer->c == '?')
	{
		tmp = exit_value(lexer);
	}
	else if (lexer->c == '\"' || lexer->c == '\'')
	{
		tmp = hundle_quotes(lexer);
	}
	else
		tmp = envairment_var(lexer);
	if (tmp == NULL)
		return (NULL);	
	str = ft_strjoin(str, tmp);
	// add here an error function if str == NULL
	free(tmp);
	return (str);

}