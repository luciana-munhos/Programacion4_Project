#ifndef IDIOMA
#define IDIOMA

#include <stdio.h>
#include <iostream>
#include <set>

#include "./IObserver.h"
#include "./Curso.h"

using namespace std;


class Idioma{
    private:
        string Nombre;
        map<string,IObserver*> ColecObserver;
        
    public:
        Idioma(string);
        ~Idioma();
        string getNombre();
        map<string,IObserver*> getColecObserver();

        void eliminarNotifC(string);

        void setNombre(string);

        bool noEstaSuscrito(string);
        void agregarSuscriptor(string,IObserver*);
        void eliminarSuscriptor(string);
        void notificar(string);

};

#endif