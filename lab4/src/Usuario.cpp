#include "../include/Usuario.h"
Usuario::~Usuario(){};
IObserver::~IObserver(){}

string Usuario::getNickname(){
    return Nickname;
}
string Usuario::getContrasenia(){
    return Contrasenia;
}
string Usuario::getNombre(){
    return Nombre;
}
string Usuario::getDescripcion(){
    return Descripcion;
}

list<DataNotif> Usuario::getDataNotifCompleto(){
    return DataNotifCompleto;
}
void Usuario::setNickname(string s){
    Nickname = s;
}
void Usuario::setContrasenia(string s){
    Contrasenia = s;
}
void Usuario::setNombre(string s){
    Nombre = s;
}
void Usuario::setDescripcion(string s){
    Descripcion = s;
}
void Usuario::setDataNotifCompleto(list<DataNotif> s){
    DataNotifCompleto = s;
}

