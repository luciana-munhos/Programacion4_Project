#ifndef USUARIO
#define USUARIO

#include <stdio.h>
#include <iostream>
#include <set>

#include "./Datatypes.h"
#include "./IObserver.h"

using namespace std;

class Usuario:public IObserver{
    private:
        string Nickname;
        string Contrasenia;
        string Nombre;
        string Descripcion;
        list<DataNotif> DataNotifCompleto;
    public:
        virtual ~Usuario()=0;
        string getNickname();
        string getContrasenia();
        string getNombre();
        string getDescripcion();
        list<DataNotif> getDataNotifCompleto();
        
        void setNickname(string);
        void setContrasenia(string);
        void setNombre(string);
        void setDescripcion(string);
        void setDataNotifCompleto(list<DataNotif>);

        virtual list<DataNotif> listarNotificacionesRecibidasU()=0;
        virtual void eliminarNotif()=0;
        
        virtual void eliminarNotifC(string, string)=0; 
        virtual void notificarUsuario(string,string)=0;
};



#endif