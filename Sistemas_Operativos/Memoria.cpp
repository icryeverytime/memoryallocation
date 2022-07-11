#include "Memoria.h"
#include <list>

Memoria::Memoria(int _tamMem, int _tamPr, int _tamCuanto, int _tamSim)
{
    tamMem=_tamMem;
    tamPr=_tamPr;
    tamCuanto=_tamCuanto;
    tamSim=_tamSim;
    mmry.clear();
    Nodo* inicio = new Nodo(0,tamMem,0);
    mmry.push_back(*inicio);
    int id=1;
    list<Nodo>::iterator it=mmry.begin();
    list<Nodo>::iterator pr=mmry.end();
}

Memoria::~Memoria(){}
