#ifndef INSCRIPTOLECCION
#define INSCRIPTOLECCION

#include "./Leccion.h"
#include "./Progreso.h"

class Leccion;
class Progreso;

class InscriptoLeccion{
    private:
        bool Aprobado;

        Leccion* MiLeccion;
        set<Progreso*> MisProgresos; 

    public:
        InscriptoLeccion();
        InscriptoLeccion(bool);
        ~InscriptoLeccion();

        bool getAprobado();
        Leccion* getMiLeccion();
        set<Progreso*> getMisProgresos();
    
        set<DataEjercicio> getEjsNoAprobUltLec();

        void setAprobado(bool);
        void setMiLeccion(Leccion*);

        void destruirProgresos();
        
        bool esLec(string);
        bool revisarSiLecTerminada(string);

        void addProgreso(Progreso*);
        void removeProgreso(Progreso*);

        //para consultar estadisticas
        int getEjerciciosAprobadosInscriptoLeccion();
        int getEjerciciosTotalesInscriptoLeccion();
};

#endif