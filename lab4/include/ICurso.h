#ifndef ICURSO
#define ICURSO

#include <iostream>
#include <stdio.h>
#include <set>


#include "./Datatypes.h"

using namespace std;

class ICurso { //interfaz de curso
    public:
        virtual ~ICurso()=0; 

        virtual set<string> listarNicknamesProfesores() = 0;
        virtual void seleccionarProfesor(string) = 0;
        virtual set<string> ingresarDatosCurso(string, string, nivelDif) = 0;
        virtual void seleccionarIdiomaCurso(string) = 0;
        virtual set<string> listarNombresCursosHabilitados() = 0;
        virtual void seleccionarPrevias(set<string>) = 0;
        virtual void ingresarDatosNuevaLeccion(string, string, string) = 0;
        virtual void ingresarDatosEjercicio(bool,string, string,list<string>) = 0;
        
        virtual void darAltaCurso() = 0;
        
        virtual void eliminarCurso(string) = 0;

        virtual set<string> listarNombresCursos() = 0; 
        virtual DataCursoConsulta mostrarInfoCompletaCurso(string) = 0; 
        virtual list<DataLeccionCompleta> obtenerLeccionesOrdenadasCompletas(string)=0; 
        virtual list<DataInscripcionConsulta> obtenerInscriptosDelCurso(string) = 0;

        virtual set<string> obtenerCursosNoHabilitados()=0;
        virtual void darAltaLeccion()=0;
        virtual list<DataLeccion> obtenerLeccionesOrdenadas(string)=0;
        virtual void ingresarDatosEjercicioDeLeccion(DataLeccion,bool,string,string,list<string>)=0;
        virtual void darAltaEjercicio()=0;
        virtual bool ejEsCompletar(string,string)=0;
        virtual int cantRespuestas(string,string,bool) = 0;

        virtual void habilitarCurso(string)=0;
};

#endif