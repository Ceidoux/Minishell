/!\ Apparemment, bash ne supprime pas le token s'il est vide /!\
	e.g.	$>		Output: rien
			$>""	Output: command not found

Attention: le chevron ne redirige QUE stdout (et laisse stderr sur le terminal)
ex: ls fichier_qui_n_existe_pas > outfile
=> la sortie erreur (ici, "No such file or directory") est redirigée par défaut vers le terminal.

/!\ le checker doit vérifier que :
- si tous les " et les ' sont fermés (sauf s'ils sont à l'intérieur d'un double quote)
- après une redirection (< ou >), le token qui suit existe, et qu'il est bien de type WORD
  à défaut : bash: syntax error near unexpected token 'newline' / '|' / '>' ...
- deux pipes ne se suivent pas
- pas de pipe en début ou en fin de ligne de commandes

/!\ en principe cat -e <>file 	-> le fichier est ouvert pour lecture ET écriture
(mais cette commande ne semble pas entrainer une écriture en sortie sur le fichier 'file' ?)

Salut