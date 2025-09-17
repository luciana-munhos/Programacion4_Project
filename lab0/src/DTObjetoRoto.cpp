#include "../include/DTObjetoRoto.h"

//Constructores y destructor
DTObjetoRoto::DTObjetoRoto(){};
DTObjetoRoto::DTObjetoRoto(string objeto): NombreObjeto(objeto),Prestado(false){};
DTObjetoRoto::DTObjetoRoto(string objeto,string nino):NombreObjeto(objeto),Prestado(true),NombreNino(nino){};
DTObjetoRoto::~DTObjetoRoto(){};
//Getters, no hay setters pues los DV no se modifican
string DTObjetoRoto::getNombreObjeto(){
    return NombreObjeto;
}
bool DTObjetoRoto::getPrestado(){
    return Prestado;
}
string DTObjetoRoto::getNombreNino(){
    return NombreNino;
}

ostream &operator<<(ostream &o,DTObjetoRoto &oR){
    o << oR.getNombreObjeto();
    if(oR.getPrestado())
        o << ", prestado SI a " << oR.getNombreNino();
    else   
        o << ", prestado NO";
    o << "\n";
    return o; 
}

ostream& operator<<(ostream& o,vector<DTObjetoRoto> objR){
    vector<DTObjetoRoto>::iterator iter; 
    iter = objR.begin();
    while (iter != objR.end()){
        cout << *iter;
        iter++;
    }
   cout<< endl;
   return o;
}

vector<DTObjetoRoto> crearListaObjRoto(map<string, Objeto*> objetos){ //
    map<string, Objeto*>::iterator i;
    vector<DTObjetoRoto> objR; 
    i = objetos.begin();
    while (i != objetos.end()){
        if ((*i).second->getEstado()==Roto){
            if ((*i).second->getPrestadoA()!=NULL)
                objR.push_back(DTObjetoRoto((*i).second->getNombre(),((*i).second->getPrestadoA())->getNombre()));
            else    
                objR.push_back(DTObjetoRoto((*i).second->getNombre()));
        } 
        i++;
    }
    return objR;
}



