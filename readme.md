===========PRESENTATION==================

Apres 21 jours de travail intense, le projet minishell est a present termine ! :) 
Le but etait de recreer une invite de commande fonctionnelle, ayant des comportements fortements similaires a bash (en mode posix)

Le programme est munie d'un prompt, qui peut, tel BASH,  executer des commandes en chemin absolu/relatif, des commandes dans la variable d'environnement PATH,
ou certains builtins tels que pwd, cd ou encore exit. 

Il est egalement possible d'executer plusieurs commandes via des pipes, ainsi que d'utiliser des redirections et des here docs.

L'expansion et l'unquoting des variables est egalement gere.

Pour fonctionner, le code source est divise en 2 parties : 

-D'un cote, le lexer et le parser, qui servent a analyser les elements ecrits par l'utilisateur sur l'invite de commande, afin de 
determiner ce qui est une commande, ce qui est une redirection ou un pipe, etc, et gerer les erreurs de syntaxe. Le parser classe ensuite chaque mot dans une categorie
specifique, afin que tout soit bien trie.

-D'un autre cote, l'executer, qui recoit les informations du parser et execute les commandes tout en effectuant les bonnes redirections, ainsi que en prenant 
en compte tous les pipes.

Le projet possede des comportements similaire au mode interactif de BASH (qui se lance en tapant "bash --posix" dans le terminal).

==========LANCER LE PROGRAMME===============

Pour lancer le programme, il suffit d'executer la commande "make" dans la racine du projet, puis lancer l'executable
"minishell", avec la commande "./minishell" si vous etes dans le dossier courant.

===========CONTRIBUTEURS================

-Seydou, alias l'executeur fou

-Jeremie, aussi connu comme le parse master

=========================================






/!\ Pour ignorer les leaks de la lib readline : fichier .supp contenant {Memcheck:Leak fun:readline fun:add_history} 
ET lancer minishell avec la commande suivante : valgrind --suppressions=readline.supp ./minishell

