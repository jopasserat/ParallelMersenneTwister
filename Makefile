DCMT_DIR = dcmt0.6.1
INC_DIR = $(DCMT_DIR)/include
LIB_DIR = $(DCMT_DIR)/lib
CFLAGS = -Wall -O3
CC = g++

all: dcmt_to_file

dcmt_to_file:   dcmt_to_file.c 
	$(CC) $(CFLAGS) -I$(INC_DIR) -L$(LIB_DIR) -o dcmt_to_file dcmt_to_file.c -ldcmt

clean :
	/bin/rm -f *.o dcmt_to_file 

