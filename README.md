MABTools
========
Pour toute incompréhension

Contact:james.tombi@gmail.com

Ces fichiers sont ceux qui sont à l'origine de MABTools Ceci est la version 1 du README

Le générateur en tant que tel est au niveau du dossier x86\_64Gentests/Gentests

Pour obtenir la génération d'un fichier de micro-Benchmarks le script GenGramTest-V5.awk(Générateur de motif) et les codes dans les fichiers split\_old.c mylib\_old.c et mylib.h(Générateur de boucles) sont présents dans le script GenGramTest.sh (qui se charge du lancement, de nettoyer une partie de l'ISA, et du scripting du fichier au format compatible avec les travaux de Bertrand) N'empèche que quelques retouches de ce script peuvent permettre de modifier la sortie.

Le lancement se fait avec des paramètres obligatoires. Un lancement général peut être:

./GenGramTest.sh -I <InstructionList> -C<ConfigurationList> -L<LauncherFile> -P<ParameterFile> -X <UnrollingSize> -D<destinationFile>

InstructionFile: se trouve au niveau du dossier InstructionLists 
ConfigurationFile : pour mes travaux j'en avais deux : Congig\_64\_james.csv et ConfigGen\_std\_MAB.csv 
LauncherFile: se place dans le dossier Launcher
ParameterFile: se place dans le dossier Param et doit matcher avec l'ordre des opérandes des instructions dans le LauncherFile à lancer
UnrollingSize: détermine la taille de déroulage voulue dans la boucle
DestinationFile: ne mettre que le nom qu'on souhaite et non le chemin, GenGramTest se charge de copier celui-ci au format C et au niveau du dossier Results et dans le dossier custom(cette copie était en relation avec la volonté de lier mon travail à celui de Bertrand)

Pour lancer les tests de plusieurs instructions : il suffit de ré-orienter vers un fichier .csv la sortie d'une ligne de script du fichier useful\_script,
puis avec le format de fichier d'allocation correcte pour ces instructions lancer le script ./my\_script.sh -F <FichierdeRedirection> pour avoir la génération 
de multiples instructions 

Le module d'ordonnancement des instructions se trouve dans le dossier src/

Il se compile avec "make reverse"(d'ailleurs je pouvais aussi compiler les autres exécutables avec le même makefile, ceci a été fait pour)

il s'exécute en faisant

./reverse -f <LaunchingFile> -C<Configfile> -s <size>

LaunchingFile: possède l'ensemble des instructions en code réel(voir fichier daxpy.tmp dans ce dossier) qui vont être ordonné(au format .tmp)

Configfile: possède les paramètres qui seront affectés à chaque fichier particulier(cette fonction pourra être utilisé pour automatiser complètement 
le ParameterFile de GenGramtest.sh)(voir fichier Configen\_64.csv)

size: le nombre de parametres voulus pour chaque opérande(size=4 ==> j aurai par exemple 4 registres à choisir dans le cas où jai un opérande registre)

La sortie de cette fonction se fait dans un dossier au nom possédant le mm nom suivi d'un suffixe \_gen\_dir(dans notre cas daxpy\_gen\_dir) 

les fichiers dans le dossier sont les différents ordonnancement des instructions de départ et les fichiers de paramétrage spécifiques à chaque ordonnancent et un fichier launcher.csv qui matche chaque fichier d'ordonnancement avec le fichier de paramètres.

Le script reverse\_script\_benching.sh permet de générer pour chaque fichier d'ordonnancement le micro-benchmark qui lui est propre(Grace a GenGramTest.sh)

