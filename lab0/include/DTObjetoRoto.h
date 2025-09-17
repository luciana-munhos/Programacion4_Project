#ifndef OBJETO_ROTO
#define OBJETO_ROTO
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "./Objeto.h"
using namespace std;

class DTObjetoRoto{
    private:
        string NombreObjeto;
        bool Prestado;
        string NombreNino;
    public:
        DTObjetoRoto();
        //En caso de que el objeto no este prestado, no se pone falso, solamente el nombre
        DTObjetoRoto(string objeto); 
        //En caso de que el objeto este prestado se pasa como parametro NombreObjeto y NombreNino
        DTObjetoRoto(string objeto,string nino);
        ~DTObjetoRoto();
        string getNombreObjeto();
        bool getPrestado();
        string getNombreNino();
};

ostream &operator<<(ostream &o,DTObjetoRoto &oR);

ostream &operator<<(ostream& o,vector<DTObjetoRoto> objR);

vector<DTObjetoRoto> crearListaObjRoto(map<string, Objeto*> objetos);

#endif
