#include <iostream>
#include <list>
#include <iterator>
#include <time.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

class Nodo{
public:
    int id,tam,cuanto;
    Nodo(int id, int tam, int cuanto){
        this->id=id;
        this->tam=tam;
        this->cuanto=cuanto;
    }
};

void Menu();
bool Condensacion(list<Nodo> &Memoria, int &sim, list<Nodo>::iterator it);
bool PeorAjuste(list<Nodo> &Memoria,int &id, int tPr, int tCuanto, int &sim);
bool MejorAjuste(list<Nodo> &Memoria,int &id, int tPr, int tCuanto, int &sim);
bool PrimerAjuste(list<Nodo> &Memoria,int &id, int tPr, int tCuanto, int &sim);
bool cuanto(list<Nodo> &Memoria,list<Nodo>::iterator &aux, int &sim);

int main()
{
    Menu();
    return 0;
}

void Menu()
{
    int opc;
    srand(time(NULL));
    list<Nodo> Memoria;
    int tamMem,tamPr,tamCuanto,tamSim;
    bool Simulacion=false;
    cout<<"Tamanio de memoria: ";
    cin>>tamMem;
    cout<<"Tamanio maximo de memoria por proceso: ";
    cin>>tamPr;
    cout<<"Tamanio maximo de cuanto por proceso: ";
    cin>>tamCuanto;
    cout<<"Tiempo total de simulacion: ";
    cin>>tamSim;
    system("cls");
    list<Nodo>::iterator it=Memoria.begin();

    for(it=Memoria.begin();it!=Memoria.end();++it){
        cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"]-";
    }
    cout<<"{"<<tamSim<<"}";
    cout<<endl;

    do{
        system("cls");
        Memoria.clear();
        Nodo* inicio=new Nodo(0,tamMem,0);
        int tSim=tamSim;
        Simulacion=false;
        Memoria.push_back(*inicio);
        int id=1;
        it=Memoria.begin();
        list<Nodo>::iterator pr=Memoria.end();
        cout<<"Opciones: "<<endl;
        cout<<"1.-Peor Ajuste"<<endl;
        cout<<"2.-Mejor Ajuste"<<endl;
        cout<<"3.-Primer Ajuste"<<endl;
        cout<<"4.-Salir"<<endl;
        cout<<"Elige una opcion: ";
        cin>>opc;

        switch(opc){
        case 1:
            cout<<endl;
            while(Simulacion==false){
                Simulacion=PeorAjuste(Memoria,id,tamPr,tamCuanto,tSim);
                if(Simulacion==true)
                    break;
                Simulacion=cuanto(Memoria,pr,tSim);
                if(Simulacion==true)
                    break;
                Simulacion=Condensacion(Memoria,tSim);
                if(Simulacion==true)
                    break;
                cout<<endl<<endl;
            }
            system("pause");
            break;
        case 2:
            cout<<endl;
            while(Simulacion==false){
                Simulacion=MejorAjuste(Memoria,id,tamPr,tamCuanto,tSim);
                if(Simulacion==true)
                    break;
                Simulacion=cuanto(Memoria,pr,tSim);
                if(Simulacion==true)
                    break;
                Simulacion=Condensacion(Memoria,tSim);
                if(Simulacion==true)
                    break;
                cout<<endl<<endl;
            }
            system("pause");
            break;
        case 3:
            cout<<endl;
            while(Simulacion==false){
                Simulacion=PrimerAjuste(Memoria,id,tamPr,tamCuanto,tSim);
                if(Simulacion==true)
                    break;
                Simulacion=cuanto(Memoria,pr,tSim);
                if(Simulacion==true)
                    break;
                Simulacion=Condensacion(Memoria,tSim);
                if(Simulacion==true)
                    break;
                cout<<endl<<endl;
            }
            system("pause");
            break;
        case 4:
            system("cls");
            cout<<"Saliendo...";
            break;
        default: cout<<"Opcion incorrecta";
        }
    }while(opc!=4);

}


//Recorrer la lista buscando vacios contiguos y sumarlos
bool Condensacion(list<Nodo> &Memoria, int &sim, list<Nodo>::iterator it)
{
    list<Nodo>::iterator aux1 = it;
    list<Nodo>::iterator aux2 = it;
    aux1--;
    aux2++;
    int r=0;

    sim--;
    if(sim==0)
        return true;

    if(aux1->cuanto==0 && aux2->cuanto==0){
        sim--;
        r=1;
    }else if(aux1->cuanto==0){
        sim--;
        r=2;
    }else if(aux2->cuanto==0){
        sim--;
        r=3;
    }

    switch (r){
    case 1:
        cout<<endl<<"Uniendo nodos atras y adelante: ";
        cout<<"["<<aux1->id<<"|"<<aux1->tam<<"|"<<aux1->cuanto<<"] , ";
        cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"] y ";
        cout<<"["<<aux2->id<<"|"<<aux2->tam<<"|"<<aux2->cuanto<<"]"<<endl;
        it->tam=it->tam + aux1->tam;
        it->tam=it->tam + aux2->tam;
        Memoria.erase(aux1);
        Memoria.erase(aux2);
        for(list<Nodo>::iterator otro=Memoria.begin();otro!=Memoria.end();++otro){
            cout<<"["<<otro->id<<"|"<<otro->tam<<"|"<<otro->cuanto<<"]-";
        }
        cout<<"  {"<<sim<<"}";
        cout<<endl;
        break;
    case 2:
        cout<<endl<<"Uniendo nodo atras: ";
        cout<<"["<<aux1->id<<"|"<<aux1->tam<<"|"<<aux1->cuanto<<"] y ";
        cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"]"<<endl;
        it->tam=it->tam + aux1->tam;
        Memoria.erase(aux1);
        for(list<Nodo>::iterator otro=Memoria.begin();otro!=Memoria.end();++otro){
            cout<<"["<<otro->id<<"|"<<otro->tam<<"|"<<otro->cuanto<<"]-";
        }
        cout<<"  {"<<sim<<"}";
        cout<<endl;
        break;
    case 3:
        cout<<endl<<"Uniendo nodo adelante: ";
        cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"] y ";
        cout<<"["<<aux2->id<<"|"<<aux2->tam<<"|"<<aux2->cuanto<<"]"<<endl;
        it->tam=it->tam + aux2->tam;
        Memoria.erase(aux2);
        for(list<Nodo>::iterator otro=Memoria.begin();otro!=Memoria.end();++otro){
            cout<<"["<<otro->id<<"|"<<otro->tam<<"|"<<otro->cuanto<<"]-";
        }
        cout<<"  {"<<sim<<"}";
        cout<<endl;
        break;
    default:
        break;
    }

    if(sim==0)
        return true;
    return false;
}

//Algoritmo de Peor ajuste
bool PeorAjuste(list<Nodo> &Memoria,int &id, int tPr, int tCuanto, int &sim)
{
    list<Nodo>::iterator it=Memoria.begin();
    list<Nodo>::iterator aux=Memoria.begin();
    it++;
    for(;it!=Memoria.end();++it){
        if(it->tam > aux->tam && it->id==0)
            aux=it;
    }
        int tam=1+rand()%(tPr);
        int cuanto=1+rand()%(tCuanto);
        Nodo* nuevo=new Nodo(id,tam,cuanto);
        sim--;
        if(sim==0)
            return true;
        if(aux->tam >= tam && aux->id==0){
            sim--;
            cout<<"Insertando proceso:";
            cout<<"["<<nuevo->id<<"|"<<nuevo->tam<<"|"<<nuevo->cuanto<<"]"<<endl;
            aux->tam=aux->tam-tam;
            Memoria.insert(aux,*nuevo);
            id++;
            if(aux->tam==0)
                Memoria.erase(aux);
            for(it=Memoria.begin();it!=Memoria.end();++it){
                cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"]-";
            }
            cout<<"  {"<<sim<<"}";
            cout<<endl;
        }
        if(sim==0)
            return true;

        return false;
}

//Algoritmo de Mejor Ajuste
bool MejorAjuste(list<Nodo> &Memoria,int &id, int tPr, int tCuanto, int &sim)
{
    list<Nodo>::iterator it=Memoria.begin();// al principio +1
    list<Nodo>::iterator aux=Memoria.begin();// al principio
    it++;

    int tam=1+rand()%(tPr); //generamos aleatorios para tamanio p/ proceso y cuanto
    int cuanto=1+rand()%(tCuanto);

    int x=100000; //100,000
    for(;it!=Memoria.end();++it){
        if(it->tam-tam >= 0 && it->id==0){
            if(it->tam-tam < x)
                x=it->tam-tam;
            aux=it;
        }
    }

    Nodo* nuevo=new Nodo(id,tam,cuanto);

    sim--;
    if(sim==0)
        return true;

    if(aux->id==0 && aux->tam >= tam){ //si el espacio mas chico puede albergar a TAM y su id es cero
        sim--;
        cout<<"Insertando proceso:";
        cout<<"["<<nuevo->id<<"|"<<nuevo->tam<<"|"<<nuevo->cuanto<<"]"<<endl;
        aux->tam=aux->tam-tam;
        Memoria.insert(aux,*nuevo);
        id++;
        if(aux->tam==0)
            Memoria.erase(aux);
        for(it=Memoria.begin();it!=Memoria.end();++it){
            cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"]-";
        }
        cout<<"  {"<<sim<<"}";
        cout<<endl;
    }
    if(sim==0)
        return true;
    return false;
}

//Algoritmo Primer Ajuste
bool PrimerAjuste(list<Nodo> &Memoria,int &id, int tPr, int tCuanto, int &sim)
{
    list<Nodo>::iterator it=Memoria.begin();

    int tam=1+rand()%(tPr);
    int cuanto=1+rand()%(tCuanto);
    Nodo* nuevo=new Nodo(id,tam,cuanto);

    for(;it!=Memoria.end();++it){
        if(it->tam >=tam && it->id==0){
            break;
        }
    }

    sim--;
    if(sim==0)
        return true;

    if(it->tam >= tam && it->id==0){
        sim--;
        cout<<"Insertando proceso:";
        cout<<"["<<nuevo->id<<"|"<<nuevo->tam<<"|"<<nuevo->cuanto<<"]"<<endl;
        it->tam=it->tam-tam;
        Memoria.insert(it,*nuevo);
        id++;
        if(it->tam==0)
            Memoria.erase(it);
        for(it=Memoria.begin();it!=Memoria.end();++it){
                cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"]-";
        }
        cout<<"  {"<<sim<<"}";
        cout<<endl;
    }
    if(sim==0)
        return true;

    return false;
}

//Avance de cuanto en proceso
bool cuanto(list<Nodo> &Memoria,list<Nodo>::iterator &aux, int &sim)
{
    if(Memoria.size()==2)
        aux=Memoria.begin();

    list<Nodo>::iterator it=Memoria.begin();
    list<Nodo>::iterator fin=Memoria.end();
    int b=0;
    cout<<"Ejecutando proceso: ";
    cout<<"["<<aux->id<<"|"<<aux->tam<<"|"<<aux->cuanto<<"]"<<endl;
    aux->cuanto--;
    sim--;
    if(sim==0)
        return true;

    for(it=Memoria.begin();it!=Memoria.end();++it){
        cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"]-";
    }
    cout<<"  {"<<sim<<"}";
    cout<<endl;
    sim--;
    if(sim==0)
        return true;

    if(aux->cuanto==0){
        cout<<"Descargando proceso: ";
        cout<<"["<<aux->id<<"|"<<aux->tam<<"|"<<aux->cuanto<<"]"<<endl;
        aux->id=0;
        sim--;
        for(it=Memoria.begin();it!=Memoria.end();++it){
            cout<<"["<<it->id<<"|"<<it->tam<<"|"<<it->cuanto<<"]-";
        }
        cout<<"  {"<<sim<<"}";
    }
    cout<<endl;
    if(sim==0)
        return true;


    do{
        aux++;
        if(aux==fin){
            b++;
            aux=Memoria.begin();
        }

    }while(aux->cuanto<=0 && b<2);

    return false;
}



