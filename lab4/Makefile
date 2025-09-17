CC = g++
CFLAGS = -Wall -Wextra -g -std=c++17
OBJDIR = obj
INCDIR = include
SRCDIR = src

main: main.cpp $(OBJDIR)/Menu.o $(OBJDIR)/Fabrica.o $(OBJDIR)/Datatypes.o $(OBJDIR)/ContUsuario.o $(OBJDIR)/ContCurso.o $(OBJDIR)/Curso.o $(OBJDIR)/Leccion.o $(OBJDIR)/Ejercicio.o $(OBJDIR)/CompletarPalabra.o $(OBJDIR)/Traducir.o $(OBJDIR)/Idioma.o $(OBJDIR)/Usuario.o $(OBJDIR)/Estudiante.o $(OBJDIR)/Profesor.o $(OBJDIR)/Inscripcion.o $(OBJDIR)/InscriptoLeccion.o $(OBJDIR)/Progreso.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/Menu.o: $(SRCDIR)/Menu.cpp $(INCDIR)/Menu.h $(INCDIR)/Fabrica.h
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(OBJDIR)/Fabrica.o: $(SRCDIR)/Fabrica.cpp $(INCDIR)/Fabrica.h $(INCDIR)/IUsuario.h $(INCDIR)/ICurso.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Datatypes.o: $(SRCDIR)/Datatypes.cpp $(INCDIR)/Datatypes.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/ContUsuario.o: $(SRCDIR)/ContUsuario.cpp $(INCDIR)/ContUsuario.h $(INCDIR)/ContCurso.h $(INCDIR)/IUsuario.h $(INCDIR)/Usuario.h $(INCDIR)/Idioma.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/ContCurso.o: $(SRCDIR)/ContCurso.cpp $(INCDIR)/ContCurso.h $(INCDIR)/ContUsuario.h $(INCDIR)/ICurso.h $(INCDIR)/Curso.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Curso.o: $(SRCDIR)/Curso.cpp $(INCDIR)/Curso.h $(INCDIR)/Datatypes.h $(INCDIR)/Leccion.h $(INCDIR)/Ejercicio.h $(INCDIR)/Inscripcion.h $(INCDIR)/Idioma.h $(INCDIR)/Profesor.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Leccion.o: $(SRCDIR)/Leccion.cpp $(INCDIR)/Leccion.h $(INCDIR)/Curso.h $(INCDIR)/Ejercicio.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Ejercicio.o: $(SRCDIR)/Ejercicio.cpp $(INCDIR)/Ejercicio.h $(INCDIR)/Leccion.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/CompletarPalabra.o: $(SRCDIR)/CompletarPalabra.cpp $(INCDIR)/CompletarPalabra.h $(INCDIR)/Ejercicio.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Traducir.o: $(SRCDIR)/Traducir.cpp $(INCDIR)/Traducir.h $(INCDIR)/Ejercicio.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Idioma.o: $(SRCDIR)/Idioma.cpp $(INCDIR)/Idioma.h $(INCDIR)/IObserver.h $(INCDIR)/Curso.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Usuario.o: $(SRCDIR)/Usuario.cpp $(INCDIR)/Usuario.h $(INCDIR)/IObserver.h $(INCDIR)/Datatypes.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Estudiante.o: $(SRCDIR)/Estudiante.cpp $(INCDIR)/Estudiante.h $(INCDIR)/Usuario.h $(INCDIR)/Inscripcion.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Profesor.o: $(SRCDIR)/Profesor.cpp $(INCDIR)/Profesor.h $(INCDIR)/Usuario.h $(INCDIR)/Curso.h $(INCDIR)/Idioma.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Inscripcion.o: $(SRCDIR)/Inscripcion.cpp $(INCDIR)/Inscripcion.h $(INCDIR)/Estudiante.h $(INCDIR)/Curso.h $(INCDIR)/InscriptoLeccion.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/InscriptoLeccion.o: $(SRCDIR)/InscriptoLeccion.cpp $(INCDIR)/InscriptoLeccion.h $(INCDIR)/Leccion.h $(INCDIR)/Progreso.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJDIR)/Progreso.o: $(SRCDIR)/Progreso.cpp $(INCDIR)/Progreso.h $(INCDIR)/Ejercicio.h 
	$(CC) $(CFLAGS) -c -o $@ $< 

valgrind: main
	valgrind --leak-check=full --track-origins=yes -s ./main

gdb: main
	gdb ./main

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCDIR)/*~