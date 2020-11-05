#Name of complier
CC	:=	gcc

#Source file directory
SRC_DIR	:=	src
#Object file directory
OBJ_DIR	:=	bin/obj
#Binary file directory (executable file)
BIN_DIR	:=	bin

#Executable file is in bin dir and has name "osh"
EXE	:=	$(BIN_DIR)/osh
#All resource files					
SRC	:=	$(wildcard	$(SRC_DIR)/*.c)
#All Object files corresspongding with source files	
OBJ	:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#Automatic add header dependencies and rebuilt only the file header that changed
#If source changed make file will rebuilt all
CPPFLAGS	:=	-Iinclude	-MMD	-MP

#Prevent duplicated name in other directory
.PHONY:	all	clean

all:	$(EXE)

#Complie all obj files to bin file (create bin dir if not exists)
$(EXE):	$(OBJ)	|	$(BIN_DIR)
	$(CC)	$^	-o	$@

#Complie each source file to corressponding obj file (create obj dir if not exists)
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c	|	$(OBJ_DIR)
	$(CC)	$(CPPFLAGS)	-c	$<	-o	$@

#Create bin dir and obj dir
$(BIN_DIR)	$(OBJ_DIR):
	mkdir	-p	$@

#Clear complied file
clean:
	@$(RM)	-rf	$(BIN_DIR)	$(OBJ_DIR)

#Include corressponding dependency file and obj file
-include	$(OBJ:.o=.d)