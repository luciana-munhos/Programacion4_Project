#ifndef NINO_H
#define NINO_H

#include <string>
#include <map>
#include <vector> 
#include "Objeto.h"

using namespace std;

class Objeto;

class Nino{
    private:
        string nombre;
        int edad;
        string direccion;
        string telefono;
        map<string, Objeto*> objetosPrestados;   
             
    public:
        Nino();
        Nino(string,int,string,string);
        Nino(const Nino&);
        ~Nino();

        void setNombre(string);
        void setEdad(int);
        void setDireccion(string);
        void setTelefono(string);
        void insertarObjetoPrestado(Objeto*);
        void eliminarObjetoPrestado(Objeto*);

        string getNombre() const;
        int getEdad() const;
        string getDireccion() const;
        string getTelefono() const;

        vector<string> listarObjetosPrestados() const; //
};

ostream& operator<<(ostream &o,map<string,Nino*>&);

ostream& operator<<(ostream& o, vector<string> conjunto);

/*
Itera en los elementos de ninos e imprime el nombre del nino, seguido por dos puntos y sus elementos prestados.
*/
void consultarPrestamos(map<string,Nino*>& ninos);

/*
Libera la memoria asignada a cada elemento del map mapNinos.
Además, los quita del map.
*/
void liberarMapNinos(map<string,Nino*>& mapNinos);



#endif
