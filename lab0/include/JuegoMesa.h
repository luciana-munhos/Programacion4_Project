#ifndef JUEGOMESA
#define JUEGOMESA
#include <string>
#include <iostream>
#include "Objeto.h"
using namespace std;

class JuegoMesa : public Objeto {
    private:
        int edadRecomendada;
        int cantJugadores;

    public:
        //constructores
        JuegoMesa();
        JuegoMesa(string,int,Estado,int,int);
        
        //destructor
        ~JuegoMesa();

        //setters
        void setEdadRecomendada(int);
        void setCantJugadores(int);
  
        //getters
        int getEdadRecomendada();
        int getCantJugadores();
  

        /*operacion que devuelve el string ---> Nombre, AnioComprado, Estado, 
                                                EdadRecomendada, CantJugadores*/

        string toString();

};

#endif