/!\ Pour ignorer les leaks de la lib readline : fichier .supp contenant {Memcheck:Leak fun:readline fun:add_history} 
ET lancer minishell avec la commande suivante : valgrind --suppressions=readline.supp ./minishell

