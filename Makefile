DCMT_DIR = dcmt0.6.1
INC_DIR = $(DCMT_DIR)/include
LIB_DIR = $(DCMT_DIR)/lib
CFLAGS = -Wall -O3
CC = g++
EXEC = dcmt_to_file dcmt_to_file_static 

all: $(EXEC)

dcmt_to_file:   dcmt_to_file.c 
	$(CC) $(CFLAGS) -I$(INC_DIR) -L$(LIB_DIR) -o $@ $< -ldcmt

dcmt_to_file_static:   dcmt_to_file.c 
	$(CC) -static $(CFLAGS) -I$(INC_DIR) -L$(LIB_DIR) -o $@ $< $(LIB_DIR)/libdcmt.a

clean :
	/bin/rm -f *.o $(EXEC)

