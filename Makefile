FILE = choice.c debugfunc.c gestiondata.c main.c move.c algo.c auto.c
FILEAPI = ticketToRide.c clientAPI.c
SRCDIR = src/
APIDIR = tickettorideapi/
SRC = $(addprefix $(SRCDIR),$(FILE)) $(addprefix $(APIDIR),$(FILEAPI))

OBJ= $(SRC:.c=.o)

main : $(OBJ)
	gcc -g -o $@ $^ 

%.o : %.c
	gcc -Wall -Werror -g -c -o $@ $^

.PHONY : clean
clean : 
	echo $(FILE)
	echo $(SRC)
	echo $(SRCDIR)
	rm -f $(OBJ)
	rm -f main