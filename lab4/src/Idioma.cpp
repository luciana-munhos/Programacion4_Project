#include <set>
#include "../include/Idioma.h"


Idioma:: Idioma(string s){
    Nombre= s;
    map<string,IObserver*> io;
    ColecObserver = io;
}


Idioma::~Idioma(){
    map<string,IObserver*>:: iterator it= ColecObserver.begin();
    while((it!=ColecObserver.end())){
        string nick = it->first;
        ++it;
        eliminarSuscriptor(nick);
    }
}


string Idioma:: getNombre(){
    return Nombre;
};

void Idioma:: setNombre(string n){
    Nombre=n;
}


void Idioma::notificar(string nomC){
    string nomI=getNombre();
    map<string,IObserver*>::iterator it;
    for(it = ColecObserver.begin(); it != ColecObserver.end(); ++it){
        it->second->notificarUsuario(nomI,nomC);
    }
}


bool Idioma::noEstaSuscrito(string Nickname){
    map<string,IObserver*>::iterator it;
    bool esta=false;
    for(it=ColecObserver.begin();it!=ColecObserver.end();it++){
        if(Nickname==it->first){
            esta=true;
        }
    }
    return (esta==false);
}


void Idioma::agregarSuscriptor(string s,IObserver* u){
    ColecObserver.insert(make_pair(s,u));
}


void Idioma::eliminarSuscriptor(string Nickname ){
    ColecObserver.erase(Nickname);
}

map<string,IObserver*> Idioma::getColecObserver(){
    return ColecObserver;
}

void Idioma::eliminarNotifC(string s){
    string nomId = getNombre();
    map<string,IObserver*>::iterator itr;

    for(itr = ColecObserver.begin(); itr != ColecObserver.end(); ++itr){
        itr->second->eliminarNotifC(s, nomId);
    }

}