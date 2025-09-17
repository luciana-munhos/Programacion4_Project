#ifndef PROFESOR
#define PROFESOR

#include <stdio.h>
#include <iostream>
#include <map>

#include "./Usuario.h"
#include "./Curso.h"

using namespace std;

class Profesor:public Usuario{
    private:
        string Instituto;
        map<string,Idioma*> MisIdiomas;
        map<string,Curso*> MisCursos;

    public:
        Profesor(string,string,string,string,string,set<Idioma*>);
        ~Profesor();

        string getInstituto();
        void setInstituto(string);
        void addIdioma(Idioma*);
        void addCurso(Curso*);
        
        void removerCursoDeProf(string); //Le paso por parametro el identificador del curso a elimianar
        list<float> getPorcentajeAvanceCurso(); 
        set<string> getCursosProf();
        set<string> getIdiomas(); //Retorna los idiomas del profesor

        list<DataNotif> listarNotificacionesRecibidasU();
        void eliminarNotif();
        
        void notificarUsuario(string,string);
        void eliminarNotifC(string, string);
        list<string> listCursosProf();

};

#endif