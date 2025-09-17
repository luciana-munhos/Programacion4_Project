#ifndef COMPLETAR_PALABRA
#define COMPLETAR_PALABRA

#include "./Ejercicio.h"

class Ejercicio;
class CompletarPalabra: public Ejercicio{
private:
    list<string> Solucion;
public:
    CompletarPalabra();
    CompletarPalabra(string&,string&,list<string>);


    list<string> getSolucion();
    bool corregirResp(list<string>);
    void setSolucion(list<string>);


};

#endif 