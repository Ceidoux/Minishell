
$> :
$> !
$> ""''echo hola""'''' que""'' tal""''
$> echo -n -n
$> e'cho hola'
$> e"cho hola"
$> "e"'c'ho 'b'"o"nj"o"'u'r

$> cd "srcs"
$> cd -
$> cd $HOME

$> pwd>bonjour (pas de redirection)

<!-- Corrected errors -->
<!-- $> ""
[1]    240079 segmentation fault (core dumped)  ./minishell

$> ''
[1]    240079 segmentation fault (core dumped)  ./minishell -->

<!-- $> echo $? | echo $? | echo $? -->


<!-- xxx | cat -e -->
<!-- 
- Parsing error
$> echo coucou | >file -->

<!-- $> echo $"HOME" -->




<!-- env -i puis ctrl-D  => core dump -->

<!-- $> echo NEW FILE > file1
==225939== Warning: invalid file descriptor -1 in syscall close() -->

<!-- cat hello <>file				doit print hello, créer le fichier file (et NE PAS MODIFIER LE FICHIER), et redirige vers stdout!
echo hello >outfile <>file 		crée (si nécessaire) les fichiers outfile et file, et redirige vers outfile (pas file ni stdout) -->
<!-- heredoc:  \n a la fin -->
<!-- cat < ''			segmentation fault -->
<!-- cmd					pointer being freed was not allocated -->
<!-- cat /dev/random | head -c 10	cat: No such file or directory -->