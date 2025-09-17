#ifndef PROGRESO
#define PROGRESO

#include "./Ejercicio.h"

class Ejercicio;
class CompletarPalabra;
class Traducir;

class Progreso{
    private:
        bool Aprobado;

        Ejercicio* MiEjercicio;

    public:
        Progreso();
        Progreso(bool);
        ~Progreso();

        bool getAprobado();
        Ejercicio* getMiEjercicio();

        void setAprobado(bool);
        void setMiEjercicio(Ejercicio*);

        bool esProgresoBuscado(string);
};

#endif