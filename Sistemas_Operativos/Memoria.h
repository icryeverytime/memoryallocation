#ifndef MEMORIA_H
#define MEMORIA_H
#include <list>

class Nodo{
public:
    int id,tam,cuanto;
    Nodo(int id, int tam, int cuanto){
        this->id=id;
        this->tam=tam;
        this->cuanto=cuanto;
    }
};


class Memoria
{
    public:
        Memoria(int _tamMem, int _tamPr, int _tamCunato, int _tamSim);
        ~Memoria();
    private:
        int tamMem,tamPr,tamCuanto,tamSim;
        list<Nodo> mmry;
        list<Nodo>::iterator it;
        list<Nodo> procesos;
};

#endif // MEMORIA_H
