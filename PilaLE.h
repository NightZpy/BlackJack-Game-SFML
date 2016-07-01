#ifndef PILALE_HPP
#define PILALE_HPP

#include "ListaEnlazada.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
template<class TIPO>
class PilaLE
{
    public:
        PilaLE(){}
        virtual ~PilaLE(){ PilaLE::lista.~ListaEnlazada(); }

    //Métodos
    void push(TIPO dato);
    void pop();
    TIPO top();
    int count();

    protected:
    private:
        ListaEnlazada<TIPO> lista;
};

template<class TIPO>
void PilaLE<TIPO>::push(TIPO dato)
{
    PilaLE::lista.agregarInicio(dato);
}

template<class TIPO>
void PilaLE<TIPO>::pop()
{
    IteradorLista<TIPO> itr = PilaLE::lista.getIterador();
    if(itr.valido())
        PilaLE::lista.removerInicio();
}

template<class TIPO>
TIPO PilaLE<TIPO>::top()
{
    TIPO dato;
    IteradorLista<TIPO> itr = PilaLE::lista.getIterador();
    if(itr.valido())
        dato = PilaLE::lista.getInicio()->getInfo();
    //printf("\nCarta: %c-%d", dato.getFigura(), dato.getValor());
    return dato;
}

template<class TIPO>
int PilaLE<TIPO>::count()
{
    return PilaLE::lista.getCNodos();
}



#endif // PILALE_HPP
