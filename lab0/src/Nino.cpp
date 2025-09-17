#include "../include/Nino.h"

Nino::Nino(string n,int e,string dir,string tel){
    nombre = n;
    edad = e;
    direccion = dir;
    telefono = tel;
}

Nino::Nino(const Nino& nino2){
    nombre = nino2.nombre;
    edad = nino2.edad ;
    direccion = nino2.direccion;
    telefono = nino2.telefono;
    objetosPrestados = map<string, Objeto*> (nino2.objetosPrestados); //
}

Nino::~Nino(){
    map<string, Objeto*>::iterator it; //
    for(it = objetosPrestados.begin();it!=objetosPrestados.end();++it)
        (*it).second->setPrestadoA(NULL); //accedo al campo second: {first, second} 
                                          //el campo second tiene el objeto (el first tiene la key que es el nombre)
}

void Nino::setNombre(string n){
    nombre = n;
}

void Nino::setEdad(int e){
    edad = e;
}

void Nino::setDireccion(string d){
    direccion = d;
}

void Nino::setTelefono(string t){
    telefono = t;
}

string Nino::getNombre() const{
    return nombre;
}

int Nino::getEdad() const{
    return edad;
}

string Nino::getDireccion() const{
    return direccion;
}

string Nino::getTelefono() const{
    return telefono;
}

void Nino::insertarObjetoPrestado(Objeto* objeto){
    objetosPrestados.insert({objeto->getNombre(), objeto}); //inserto {nombre_objeto, objeto} al map
}

void Nino::eliminarObjetoPrestado(Objeto* objeto){
    objetosPrestados.erase(objeto->getNombre()); //remuevo el objeto de map segun su key (su key es su nombre)
    
}

vector<string> Nino::listarObjetosPrestados() const{ //
    vector<string> res;  //

    map<string, Objeto*>::iterator it; //
    for(auto it = objetosPrestados.begin();it != objetosPrestados.end();++it){
        res.push_back((*it).first);
    }

    return res;
}

ostream& operator<<(ostream& o, vector<string> conjunto){ //
    for (auto it = conjunto.begin(); it != conjunto.end(); ++it) {
        o << *it;
        if(it < conjunto.end()-1)
            o << ", ";
    }
    return o;
}

void consultarPrestamos(map<string,Nino*>& ninos){
    map<string, Nino*>::iterator itera = ninos.begin(); //
    while (itera != ninos.end()){
        cout << (*itera).second->getNombre() << ": " << (*itera).second->listarObjetosPrestados() << endl;
        itera++;
    }
    cout << endl;
}

void liberarMapNinos(map<string,Nino*>& mapNinos){
    map<string, Nino*>::iterator i = mapNinos.begin();
    while (i != mapNinos.end()){
        delete (*i).second;
        i++;
    }
}
