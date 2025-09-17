#ifndef ESTUDIANTE
#define ESTUDIANTE

#include <stdio.h>
#include <iostream>
#include <set>

#include "./Usuario.h"
#include "./Inscripcion.h"
#include "./Idioma.h"
#include "./Curso.h"
using namespace std;

class Inscripcion;
class Idioma;
class Curso;
class Estudiante:public Usuario{
    private:
        string Pais;
        Date FechaNacimiento;
        set<Inscripcion*> Inscripciones;
    public:
        Estudiante(string,string,string,string,string,int, int ,int);
        ~Estudiante();

        string getPais();
        Date getFechaNacimiento();
        void addInscripcion(Inscripcion*);
        void setPais(string);
        void setFechaNacimiento(Date);

        void removerInscripcion(Inscripcion*);
        list<DataCurso> getCursosNoAprobados();
        set<DataEjercicio> getEjsNoAprobUltLec(string);

        set<string> getCursosEst(); 
        void actualizarAprobados(string,string,string);
        
        list<DataNotif> listarNotificacionesRecibidasU();
        void eliminarNotif();
        
        void realizarInscripcion(Curso*);
        void notificarUsuario(string,string);

        list<float> getPorcentajeAvanceInscripciones(); 
        set<Inscripcion*> getInscripciones();
        void eliminarNotifC(string, string);
        list<string> listCursosEst();
};

#endif