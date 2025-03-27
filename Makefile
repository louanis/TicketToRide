SRC= src/choice.c src/debugfunc.c src/gestiondata.c src/main.c src/move.c src/algo.c src/manual.c tickettorideapi/ticketToRide.c tickettorideapi/codingGameServer.c

OBJ= $(SRC:.c=.o)

main : $(OBJ)
	gcc -o $@ $^ 

%.o : %.c
	gcc -Wall -Werror -c -o $@ $^

.PHONY : clean
clean : 
	rm -f $(OBJ)