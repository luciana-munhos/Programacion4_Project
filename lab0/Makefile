CC = g++
CFLAGS = -Wall -g
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = include
FUENTES = lab0.cpp $(SRC_DIR)/* $(INC_DIR)/* $(OBJ_DIR)

OBJS = $(OBJ_DIR)/DTObjetoRoto.o $(OBJ_DIR)/JuegoMesa.o $(OBJ_DIR)/Libro.o $(OBJ_DIR)/Nino.o $(OBJ_DIR)/Objeto.o $(OBJ_DIR)/lab0.o

all: lab0

# $@ --> regla
# $< --> primera dependencia

lab0: $(OBJS)
	$(CC) $(CFLAGS) -o lab0 $(OBJS)

$(OBJ_DIR)/DTObjetoRoto.o: $(SRC_DIR)/DTObjetoRoto.cpp $(INC_DIR)/DTObjetoRoto.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/JuegoMesa.o: $(SRC_DIR)/JuegoMesa.cpp $(INC_DIR)/JuegoMesa.h $(INC_DIR)/Objeto.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/Libro.o: $(SRC_DIR)/Libro.cpp $(INC_DIR)/Libro.h $(INC_DIR)/Objeto.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/Nino.o: $(SRC_DIR)/Nino.cpp $(INC_DIR)/Nino.h $(INC_DIR)/Objeto.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/Objeto.o: $(SRC_DIR)/Objeto.cpp $(INC_DIR)/Objeto.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/lab0.o: lab0.cpp $(INC_DIR)/DTObjetoRoto.h $(INC_DIR)/JuegoMesa.h $(INC_DIR)/Libro.h $(INC_DIR)/Nino.h $(INC_DIR)/Objeto.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f lab0 $(OBJ_DIR)/*

zip: $(FUENTES) Makefile
	rm -f 46_lab0.tar.gz
	tar -cvf 46_lab0.tar $(FUENTES) Makefile
	gzip 46_lab0.tar


