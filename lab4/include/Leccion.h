#ifndef LECCION
#define LECCION

#include "./Curso.h"
#include "./Ejercicio.h"


class Curso;

class Leccion{
private:
    string Tema;
    string Objetivo;

    Curso* MiCurso;
    map<string,Ejercicio*> MisEjercicios;
    
public:
    Leccion();
    Leccion(string,string);
    Leccion(Curso*,DataLeccion,list<DataEjercicioCompleto>);
    ~Leccion();

    string getTema();
    string getObjetivo();
    Curso* getCurso();
    map<string,Ejercicio*> getMisEjercicios();

    int getCantEjercicios();

    set<Ejercicio*> getEjerciciosLeccion();

    Ejercicio* getEj(string);
    bool esEjercicio(string);

    void setTema(string);
    void setObjetivo(string);
    void setCurso(Curso*);

    void addEjercicio(Ejercicio*);
    void removeEjercicio(Ejercicio*);

    void destruirEjerciciosLeccion();
};


#endif 