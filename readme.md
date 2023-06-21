/!\ Apparemment, bash ne supprime pas le token s'il est vide /!\
	e.g.	$>		Output: rien
			$>""	Output: command not found

Attention: le chevron ne redirige QUE stdout

e.g. ls fichier_qui_n_existe_pas > outfile
=> la sortie erreur (ici, "No such file or directory") est redirigée par défaut vers le terminal.

/!\ le checker doit vérifier que :
- après une redirection (< ou >), le token qui suit existe, et qu'il est bien de type WORD
  à défaut : bash: syntax error near unexpected token 'newline' / '|' / '>' ...
- deux pipes ne se suivent pas (ou est-ce possible ?)