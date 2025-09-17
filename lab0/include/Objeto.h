#ifndef OBJETO_H
#define OBJETO_H

#include <string>
#include <iostream>
#include "Nino.h"

using namespace std;

enum Estado {
    Nuevo, BienConservado, Roto
};

class Nino;

class Objeto {
    private:
        string nombre;
        int anioComprado;
        Estado estado;
        Nino* prestadoA;
        
    public:
        Objeto();
        Objeto(string&,int,Estado);
        Objeto(Objeto&);
        virtual ~Objeto();

        string getNombre() const;
        int getAnioComprado() const;
        Estado getEstado() const;
        Nino* getPrestadoA() const;

        void setNombre(string&);
        void setAnioComprado(int);
        void setEstado(Estado);
        void setPrestadoA(Nino*);

        virtual string toString() = 0;
};

//Sobrecarga de << para map de objetos
ostream& operator<<(ostream&, map<string, Objeto*>);

/*
Imprime lo que retorna el metodo toString() aplicado a cada Objeto en obj
*/
void consultarObjetos(map<string,Objeto*> & mapObjetos);

/*
Libera la memoria de cada Objeto* en el map mapObjetos
*/
void liberarMapObjetos(map<string,Objeto*>& mapObjetos);

/*
Libera la memoria asignada a obj y lo elimina del map mapObjetos
*/
void eliminarObjeto(map<string,Objeto*>& mapObjetos,Objeto* obj);

#endif