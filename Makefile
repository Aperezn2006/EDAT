##########  Variables  ##########
CFLAGS = -Wall -pedantic -ansi 
CC = gcc

##########  General rules  ##########
all: p4_e1 p4_e2

p4_e1: p4_e1.o bstree.o file_utils.o vertex.o
	@$(CC) $(CFLAGS) -o  p4_e1 bstree.o vertex.o file_utils.o p4_e1.o
	@echo "--> p4_e1 executable succesfully created"

p4_e2: p4_e2.o bstree.o file_utils.o search_queue.o
	@$(CC) $(CFLAGS) -o p4_e2 p4_e2.o bstree.o file_utils.o search_queue.o 
	@echo "--> p4_e2 executable succesfully created"

##########  Object creation  ##########
p4_e1.o: p4_e1.c
	@$(CC) $(CFLAGS) -c p4_e1.c -o p4_e1.o
	@echo "--> p4_e1.o object file created"
p4_e2.o: p4_e2.c
	@$(CC) $(CFLAGS) -c p4_e2.c -o p4_e2.o
	@echo "--> p4_e2.o object file created"
bstree.o: bstree.c
	@$(CC) $(CFLAGS) -c bstree.c -o bstree.o
	@echo "--> bstree.o object file created"
file_utils.o: file_utils.c
	@$(CC) $(CFLAGS) -c file_utils.c -o file_utils.o
	@echo "--> file_utils.o object file created"
vertex.o: vertex.c		
	@$(CC) $(CFLAGS) -c vertex.c -o vertex.o
	@echo "--> vertex.o object file created"
search_queue.o: search_queue.c
	@$(CC) $(CFLAGS) -c search_queue.c -o search_queue.o
	@echo "--> search_queue.o object file created"

##########  Cleaning and execution  ##########
clean:
	@rm -f *.o
	@echo "--> object files removed"
	@rm -f p4_e1
	@echo "--> all executable files removed"

runv_e1: p4_e1
	@echo "--> running e1 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all -s ./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" normal
	@echo ""
	valgrind --leak-check=full --show-leak-kinds=all -s ./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" sorted
	@echo ""
	valgrind --leak-check=full --show-leak-kinds=all -s ./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" normal
	@echo ""
	valgrind --leak-check=full --show-leak-kinds=all -s ./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" sorted


runv_e2: p4_e2
	@echo "--> running e2 with valgrind"
	valgrind --leak-check=full --show-leak-kinds=all -s ./p4_e2 ./data/data_string_10.txt ./out/data_string_10.out
	@echo ""
	valgrind --leak-check=full --show-leak-kinds=all -s ./p4_e2 ./data/data_string_1K.txt ./out/data_string_1K.out
	@echo ""
	valgrind --leak-check=full --show-leak-kinds=all -s ./p4_e2 ./data/data_string_2K.txt ./out/data_string_2K.out
include Makefile_ext