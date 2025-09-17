#include "../include/Objeto.h"

Objeto:: Objeto(){
    nombre = "";
    anioComprado = 2023; 
    estado = Nuevo; 
    prestadoA = NULL;
}

Objeto:: Objeto(string &s, int anio, Estado est){
    nombre = s;
    anioComprado = anio; 
    estado = est; 
    prestadoA = NULL;
}

Objeto:: Objeto(Objeto& obj){
    nombre = obj.nombre;
    anioComprado = obj.anioComprado;
    estado = obj.estado;
    prestadoA = obj.prestadoA;
}

Objeto:: ~Objeto(){
    if(prestadoA != NULL)
        prestadoA->eliminarObjetoPrestado(this);

}

string Objeto:: getNombre() const{
    return nombre;
}

int Objeto:: getAnioComprado() const{
    return anioComprado;
}

Estado Objeto:: getEstado() const{
    return estado;
}

Nino* Objeto:: getPrestadoA() const{
    return prestadoA;
}

void Objeto::setNombre(string &s){
    nombre = s;
}

void Objeto:: setAnioComprado(int anio){
    anioComprado = anio;
}

void Objeto:: setEstado(Estado est){
    estado = est;
}

void Objeto:: setPrestadoA(Nino* nino){
    prestadoA = nino;
}

//sobrecarga de << para map de objetos
ostream& operator<<(ostream& o, map<string, Objeto*> conjunto){ 
    for (auto it = conjunto.begin(); it != conjunto.end(); ++it) {
        o << (*it).first << " - ";
    }
    o << endl;
    return o;
}

void consultarObjetos(map<string,Objeto*> &mapObjetos){
    map<string, Objeto*>::iterator i = mapObjetos.begin(); 
    while (i != mapObjetos.end()){
        cout << (*i).second->toString() << endl;
        i++;
    }
}

void liberarMapObjetos(map<string,Objeto*>& mapObjetos){
    map<string, Objeto*>::iterator i = mapObjetos.begin();
    while (i != mapObjetos.end()){
        delete (*i).second;
        i++;
    }
}

void eliminarObjeto(map<string,Objeto*>& mapObjetos,Objeto* obj){
    mapObjetos.erase(obj->getNombre());        
    delete obj;  
}
