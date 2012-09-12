# $@ : nom de la cible ;
# $< : première dépendance de la liste des dépendances ;
# $? : Les dépendances plus récentes que la cible ;
# $^ : Toutes les dépendances ;
# $* : représente le ' * ' de shell, donc n'importe quel nom;

CC=gcc
CFLAGS=-g
EXEC=split_old reverse plot_ranking


#mylib.o:mylib_old.c
#	$(CC) -c $^

#arrgt_new.o:arrgt_new.c
#	$(CC) -c $^

split_old:mylib.h mylib_old.c split_old.c
	$(CC) $(CFLAGS) -o $@ $^

reverse:mylib.h mylib_old.c arrgt_new.h arrgt_new.c reverse.c
	$(CC) $(CFLAGS) -o $@ $^

plot_ranking:mylib.h mylib_old.c plot_ranking.c
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	rm *.o	

all: plot_ranking reverse split_old
