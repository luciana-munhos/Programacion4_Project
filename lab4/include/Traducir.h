#ifndef TRADUCIR
#define TRADUCIR

#include "./Ejercicio.h"


class Traducir: public Ejercicio{
    private:
        string Solucion;
    public:
        Traducir();
        Traducir(string&,string&,list<string>);

        string getSolucion();

        void setSolucion(string);
        bool corregirResp(list<string>);

};

#endif
