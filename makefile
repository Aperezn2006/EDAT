##########  Variables  ##########
CFLAGS = -Wall -pedantic -ansi 
CC = gcc

##########  General rules  ##########

all: p4_e1 

p4_e1: p4_e1.o bstree.o file_utils.o vertex.o
	@$(CC) $(CFLAGS) -o  p4_e1 bstree.o vertex.o file_utils.o p4_e1.o
	@echo "--> p4_e1 executable succesfully created"


##########  Object creation  ##########
p4_e1.o: p4_e1.c
	@$(CC) $(CFLAGS) -c p4_e1.c -o p4_e1.o
	@echo "--> p4_e1.o object file created"
bstree.o: bstree.c
	@$(CC) $(CFLAGS) -c bstree.c -o bstree.o
	@echo "--> bstree.o object file created"
file_utils.o: file_utils.c
	@$(CC) $(CFLAGS) -c file_utils.c -o file_utils.o
	@echo "--> file_utils.o object file created"
vertex.o: vertex.c		
	@$(CC) $(CFLAGS) -c vertex.c -o vertex.o
	@echo "--> vertex.o object file created"

##########  Cleaning and execution  ##########
clean:
	@rm -f *.o
	@echo "--> object files removed"
	@rm -f p4_e1
	@echo "--> all executable files removed"
run1: p4_e1
	@echo "--> running e1"
	./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" normal
	@echo ""
	./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" sorted
	@echo ""
	./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" normal
	@echo ""
	./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" sorted
runv1: p4_e1
	@echo "--> running e1 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all ./p4_e1

