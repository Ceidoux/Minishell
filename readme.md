/?\ SHOW ALL LEAKS:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=readline.supp ./minishell

/!\ Pour ignorer les leaks de la lib readline : fichier .supp contenant {Memcheck:Leak fun:readline fun:add_history} 
ET lancer minishell avec la commande suivante : valgrind --suppressions=readline.supp ./minishell


/!\ Apparemment, bash ne supprime pas le token s'il est vide /!\
	e.g.	$>		Output: rien
			$>""	Output: command not found

/!\ le checker doit vérifier que :
- après une redirection (< ou >), le token qui suit existe, et qu'il est bien de type WORD
  à défaut : bash: syntax error near unexpected token 'newline' / '|' / '>' ...
