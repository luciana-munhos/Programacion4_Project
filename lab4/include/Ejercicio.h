#ifndef EJERCICIO
#define EJERCICIO

#include "./Leccion.h"

class Leccion;
class CompletarPalabra;
class Traducir;

class Ejercicio{
    private:
        string Descripcion;
        string Frase;
        Leccion* MiLeccion;
    public:
        Ejercicio();
        Ejercicio(string&,string&);
        Ejercicio(DataEjercicioCompleto);

        virtual ~Ejercicio(){};

        string getDescripcion();
        string getFrase();
        Leccion* getLeccion();

        void setDescripcion(string);
        void setFrase(string);
        void setLeccion(Leccion*);

        string getTemaLeccion();
        virtual bool corregirResp(list<string>) = 0;
};

#endif