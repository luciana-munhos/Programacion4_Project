#ifndef LIBRO_H
#define LIBRO_H
#include <string>
#include <iostream>

#include "Objeto.h"

using namespace std;

class Libro : public Objeto{
    private:
        string autor;
        int cantPaginas;

    public:
        //constructores
        Libro(); 
        Libro(string, int, Estado, string, int); 

        //destructor
        ~Libro();

        //setters
        void set_autor(string); 
        void set_cantPaginas(int); 

        //getters
        string get_autor();
        int get_cantPaginas(); 

        //operacion que devuelve el string ---> Nombre, AnioComprado, Estado, Autor, CantPaginas
        string toString(); 
};

#endif
