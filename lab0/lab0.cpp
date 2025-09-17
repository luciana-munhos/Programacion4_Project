#define CANT_NINOS 2
#define CANT_OBJETOS 6

#include "./include/Objeto.h"
#include "./include/Nino.h"
#include "./include/DTObjetoRoto.h"
#include "./include/JuegoMesa.h"
#include "./include/Libro.h"

#include <map>
#include <vector> 

using namespace std;

/*
Crea el link de nino a objeto y viceversa
*/
void asignarRelacion(Nino* nino,Objeto* objeto){
    nino->insertarObjetoPrestado(objeto);
    objeto->setPrestadoA(nino);
}


int main(){

    //PARTE A
    Objeto* libro_nacidos = new Libro("Nacidos de la brúma: El imperio final",2022,Roto,"Brandon Sanderson",688);
    Objeto* libro_malas = new Libro("Las Malas",2022,Nuevo,"Camila Sosa Villada",240);
    Objeto* libro_cocodrilo = new Libro("El cocodrilo al que no le gustaba el agua",2016,Roto,"Gemma Merino",32);

    //PARTE B
    Objeto* jm_uno = new JuegoMesa("Juego Uno",2022,Roto,7,10);
    Objeto* jm_mazo = new JuegoMesa("Juego Mazo de Cartas",2019,Nuevo,7,4);   
    Objeto* jm_dados = new JuegoMesa("Dados",2020,Roto,2,6);
    map<string, Objeto*> objetos = { 
                                        {libro_nacidos->getNombre(), libro_nacidos},
                                        {libro_malas->getNombre(), libro_malas},
                                        {libro_cocodrilo->getNombre(), libro_cocodrilo},
                                        {jm_uno->getNombre(), jm_uno},
                                        {jm_mazo->getNombre(), jm_mazo},
                                        {jm_dados->getNombre(), jm_dados} 
                                    }; 
    
    //PARTE C
    consultarObjetos(objetos);

    //PARTE D
    Nino* nino_mariaLaura = new Nino("Maria Laura",10,"Nueva Palmira 1521","099298190");
    Nino* nino_alex = new Nino("Alex",5,"Humberto Primo 1501","29094141");
    map<string, Nino*> ninos =  { 
                                    {nino_mariaLaura->getNombre(), nino_mariaLaura},
                                    {nino_alex->getNombre(), nino_alex} 
                                }; 

    //PARTE E
    asignarRelacion(nino_mariaLaura,jm_mazo);
    asignarRelacion(nino_mariaLaura,libro_nacidos);
    asignarRelacion(nino_mariaLaura,jm_dados);
    asignarRelacion(nino_alex,jm_uno);
    asignarRelacion(nino_alex,libro_cocodrilo);

    //PARTE F
    consultarPrestamos(ninos);
    
    //PARTE G
    vector<DTObjetoRoto> objR = crearListaObjRoto(objetos);
    cout << objR;
    
    //PARTE H
    cout << nino_alex->listarObjetosPrestados() << endl; //Confirmo los elementos de dicho nino

    eliminarObjeto(objetos,jm_uno); 

    cout << nino_alex->listarObjetosPrestados() << endl; //Verifico si lo saco efectivamente de los libros prestados
    objR = crearListaObjRoto(objetos); 

    cout << endl;
    cout << objR;   //Creo lista de objetosRotos y verifico que efectivamente no se encuentra    
    

    //LIBERACION DE MEMORIA
    liberarMapNinos(ninos);
    liberarMapObjetos(objetos);

    return 0;
}
