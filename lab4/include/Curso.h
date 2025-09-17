#ifndef CURSO
#define CURSO

#include <stdio.h>
#include <iostream>
#include <set>
#include <map>

#include "./Datatypes.h"
#include "./Leccion.h"
#include "./Ejercicio.h"
#include "./Inscripcion.h"
#include "./Idioma.h"
#include "./Profesor.h"

using namespace std;

class Inscripcion;
class Profesor;
class Ejercicio;

class Curso{
    private:
        string Nombre;
        string Descripcion;
        nivelDif Dificultad;
        bool Habilitado; 

        Profesor* MiProfesor;
        Idioma* MiIdioma;
        set<Inscripcion*> MisInscripciones;
        map<string,Curso*> MisPrevias;
        map<string,Curso*> CursosPosteriores;
        list<Leccion*> MisLecciones;
        
        
    public:
        Curso();
        Curso(string&,string&,nivelDif,bool);
        Curso(DataCursoCompleto);
        ~Curso();

        set<Inscripcion*> getMisIncripciones();
        string getNombre();
        string getDescripcion();
        nivelDif getDificultad();
        bool getHabilitado();
        Profesor* getProfesor();
        Idioma* getIdioma();
        Ejercicio* getEj(string);
        Leccion* getLeccion(string);
        map<string,Curso*> getPrevias();
        map<string,Curso*> getCursosPosteriores();
        int getCantLecciones();
        int getCantEjercicios();

        list<Leccion*> getMisLecciones();

        void setNombre(string);
        void setDescripcion(string);
        void setDificultad(nivelDif);
        void setHabilitado(bool);
        void setProfesor(Profesor*);
        void setIdioma(Idioma*);

        void addLeccion(Leccion*);
        void addCursoPosterior(Curso*);
        void addPrevia(Curso*);
        void addInscripcion(Inscripcion*);

        void removePrevia(Curso*);
        void removePosterior(Curso*);
        void removeInscripcion(Inscripcion*);

        void desvincularProfDeCurso();
        void eliminarLeccionesYEjercicios();
        void desvincularInscripcionesYEliminar();
        void sacarDePrevias();
        void eliminarNotificaciones();
        
        list<DataLeccion> obtenerLeccionesOrdenadas();
        void habilitarC(string);

        float getPorcentajeAvanceDeEsteCurso();
        list<DataLeccionCompleta> obtenerLeccionesCompletasOrdenadasDelCurso(); 
        list<DataInscripcionConsulta> obtenerInscriptosCurso();
};


#endif