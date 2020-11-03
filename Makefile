CC	:=	gcc

SRC_DIR	:=	src
OBJ_DIR	:=	bin/obj
BIN_DIR	:=	bin

EXE	:=	$(BIN_DIR)/osh
SRC	:=	$(wildcard	$(SRC_DIR)/*.c)
OBJ	:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS	:=	-Iinclude	-MMD	-MP
CFLAGS	:=	-Wall

.PHONY:	all	clean

all:	$(EXE)

$(EXE):	$(OBJ)	|	$(BIN_DIR)
	$(CC)	$^	-o	$@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c	|	$(OBJ_DIR)
	$(CC)	$(CPPFLAGS)	$(CFLAGS)	-c	$<	-o	$@

$(BIN_DIR)	$(OBJ_DIR):
	mkdir	-p	$@

clean:
	@$(RM)	-rf	$(BIN_DIR)	$(OBJ_DIR)

-include	$(OBJ:.o=.d)