#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <iostream>
#include "NodoLista.hpp"

template<class TIPO>
class IteradorLista;

template<class TIPO>
class ListaEnlazada
{
    public:
        ListaEnlazada();
        virtual ~ListaEnlazada();

        //getters
        NodoLista<TIPO>* getInicio()            { return ListaEnlazada::inicio;   }
        NodoLista<TIPO>* getFin()               { return ListaEnlazada::fin;      }
        int getCNodos()                    { return ListaEnlazada::cNodos;   }

        //setters
        void setInicio(NodoLista<TIPO>* inicio) { ListaEnlazada::inicio = inicio; }
        void setFin(NodoLista<TIPO>* fin)       { ListaEnlazada::fin    = fin;    }
        void setCNodos(int cNodos)         { ListaEnlazada::cNodos = cNodos; }

        //Agregar
        void agregarFin(TIPO info);
        void agregarInicio(TIPO info);
        void agregar(IteradorLista<TIPO>& pIterador, TIPO info);

        //Remover
        void removerInicio();
        void removerFin();
        void remover(IteradorLista<TIPO>& pIterador);

        bool buscar(IteradorLista<TIPO>& pIterador, TIPO &dato);//, bool(*busqueda)(TIPO a, TIPO b));

        IteradorLista<TIPO> getIterador();
        void operator= (ListaEnlazada<TIPO> lista);
        TIPO operator[] (int i);

    protected:


    private:
        NodoLista<TIPO>* inicio;
        NodoLista<TIPO>* fin;
        int cNodos;
};

template<class TIPO>
class IteradorLista
{
    public:

        IteradorLista(ListaEnlazada<TIPO> *pLista = NULL, NodoLista<TIPO> *pNodo = NULL) :
            pLista(pLista), pNodo(pNodo){}

        virtual ~IteradorLista() {}

        void irInicio();
        void irFin();
        void siguiente();
        void anterior();
        TIPO info() { return IteradorLista::pNodo->getInfo(); }
        bool valido();

        //getters
        ListaEnlazada<TIPO> *getPLista() { return pLista; }
        NodoLista<TIPO>     *getPNodo()  { return pNodo;  }

        //setters
        void setPNodo(NodoLista<TIPO>  *pNodo)  { IteradorLista::pNodo  = pNodo;  }
        void setPLista(ListaEnlazada<TIPO> *pLista) { IteradorLista::pLista = pLista; }

    protected:
    private:
        ListaEnlazada<TIPO> *pLista;
        NodoLista<TIPO> *pNodo;

    friend class ListaEnlazada<TIPO>;
};

/*template<class TIPO>
void NodoLista<TIPO>::agregarDespues(TIPO info)
{
    NodoLista<TIPO>* nuevo = new NodoLista<TIPO>(info);
    nuevo->siguiente = NodoLista::siguiente;
    NodoLista::siguiente = nuevo;
}*/

template<class TIPO>
ListaEnlazada<TIPO>::ListaEnlazada()
{
    ListaEnlazada::inicio = NULL;
    ListaEnlazada::fin    = NULL;
    ListaEnlazada::cNodos = 0;
}

template<class TIPO>
ListaEnlazada<TIPO>::~ListaEnlazada()
{
    /*IteradorLista<TIPO> itr = ListaEnlazada::getIterador();
    if(itr.valido())
        itr.irInicio();
    while(itr.valido())
    {
        ListaEnlazada::remover(itr);
        itr.irInicio();
    }*/
}

template<class TIPO>
void ListaEnlazada<TIPO>::operator= (ListaEnlazada<TIPO> lista)
{
    ListaEnlazada<TIPO>::inicio = lista.getInicio();
    ListaEnlazada<TIPO>::fin    = lista.getFin();
    ListaEnlazada<TIPO>::cNodos = lista.getCNodos();
}

template<class TIPO>
TIPO ListaEnlazada<TIPO>::operator[] (int i)
{
    TIPO dato;
    if(i < ListaEnlazada::getCNodos())
    {
        IteradorLista<TIPO> itr = ListaEnlazada::getIterador();
        itr.irInicio();
        int cI=0;

        while(itr.valido())
        {
            if(cI==i)
            {
                dato = itr.info();
                break;
            }
            cI++;
            itr.siguiente();
        }
        itr.irInicio();
    }
    return dato;
}

template<class TIPO>
void ListaEnlazada<TIPO>::agregarFin(TIPO info)
{
    if(ListaEnlazada::inicio == NULL)
    {
        ListaEnlazada::inicio = ListaEnlazada::fin = new NodoLista<TIPO>(info);
    }
    else
    {
        NodoLista<TIPO> *nuevo = new NodoLista<TIPO>(info, NULL, ListaEnlazada::fin);
        ListaEnlazada::fin->setSiguiente(nuevo);
        ListaEnlazada::fin = nuevo;
    }
    ListaEnlazada::cNodos++;
}

template<class TIPO>
void ListaEnlazada<TIPO>::agregarInicio(TIPO info)
{
    if(ListaEnlazada::inicio == NULL)
    {
        ListaEnlazada::inicio = ListaEnlazada::fin = new NodoLista<TIPO>(info);
    }
    else
    {
        NodoLista<TIPO> *nuevo = new NodoLista<TIPO>(info, ListaEnlazada::inicio);
        ListaEnlazada::inicio->setAnterior(nuevo);
        ListaEnlazada::inicio = nuevo;
    }
    ListaEnlazada::cNodos++;
}

template<class TIPO>
void ListaEnlazada<TIPO>::removerInicio()
{
    if(ListaEnlazada::inicio)
    {
        if(ListaEnlazada::inicio == ListaEnlazada::fin)
        {
            delete ListaEnlazada::inicio;
            ListaEnlazada::inicio = ListaEnlazada::fin = NULL;
        }
        else
        {
            NodoLista<TIPO> *nuevo = ListaEnlazada::inicio->getSiguiente();
            delete ListaEnlazada::inicio;
            nuevo->setAnterior(NULL);
            ListaEnlazada::inicio = nuevo;
        }
        ListaEnlazada::cNodos--;
        return;
    }
}

template<class TIPO>
void ListaEnlazada<TIPO>::removerFin()
{
    if(ListaEnlazada::inicio)
    {
        if(ListaEnlazada::inicio == ListaEnlazada::fin)
        {
            delete ListaEnlazada::inicio;
            ListaEnlazada::inicio = ListaEnlazada::fin = NULL;
        }
        else
        {
            NodoLista<TIPO> *nuevo = ListaEnlazada::fin->getAnterior();
            delete ListaEnlazada::fin;
            nuevo->setSiguiente(NULL);
            ListaEnlazada::fin = nuevo;
        }
        ListaEnlazada::cNodos--;
        return;
    }
}

template<class TIPO>
IteradorLista<TIPO> ListaEnlazada<TIPO>::getIterador()
{
    return IteradorLista<TIPO>(this, ListaEnlazada::inicio);
}

template<class TIPO>
void IteradorLista<TIPO>::irInicio()
{
    if(IteradorLista::pLista)
        IteradorLista::pNodo = IteradorLista::pLista->getInicio();
}

template<class TIPO>
void IteradorLista<TIPO>::irFin()
{
    if(IteradorLista::pLista)
        IteradorLista::pNodo = IteradorLista::pLista->getFin();
}

template<class TIPO>
void IteradorLista<TIPO>::siguiente()
{
    if(IteradorLista::pNodo)
            IteradorLista::pNodo = IteradorLista::pNodo->getSiguiente();
}

template<class TIPO>
void IteradorLista<TIPO>::anterior()
{
    if(IteradorLista::pNodo)
        IteradorLista::pNodo = IteradorLista::pNodo->getAnterior();
}

template<class TIPO>
bool IteradorLista<TIPO>::valido()
{
    return (IteradorLista::pNodo != NULL);
}

template<class TIPO>
void ListaEnlazada<TIPO>::agregar(IteradorLista<TIPO>& pIterador, TIPO info)
{
    if(pIterador.getPLista() != this)
        return;

    if(pIterador.getPNodo())
    {
        NodoLista<TIPO> *siguiente = pIterador.getPNodo()->getSiguiente();
        NodoLista<TIPO> *anterior = pIterador.getPNodo();
        NodoLista<TIPO> *nuevo = new NodoLista<TIPO>(info, siguiente, anterior);
        anterior->setSiguiente(nuevo);
        siguiente->setAnterior(nuevo);
        pIterador.setPNodo(nuevo);

        if(pIterador.getPNodo() == ListaEnlazada::fin)
            ListaEnlazada::fin = pIterador.getPNodo()->getSiguiente();

        ListaEnlazada::cNodos++;
    }
    else
    {
        ListaEnlazada::agregarFin(info);
    }

}

template<class TIPO>
void ListaEnlazada<TIPO>::remover(IteradorLista<TIPO>& pIterador)
{
    if(pIterador.getPLista() != this)
        return;

    if(!pIterador.getPNodo())
        return;

    if(pIterador.getPNodo() == ListaEnlazada::inicio)
    {
        std::cout<<std::endl<<"REMOVIENDO INICIO";
        ListaEnlazada::removerInicio();
        pIterador.siguiente();
    }
    else
        if(pIterador.getPNodo() == ListaEnlazada::fin)
        {
            std::cout<<std::endl<<"REMOVIENDO FINAL";
            ListaEnlazada::removerFin();
            pIterador.anterior();
        }
        else
        {
            NodoLista<TIPO> *actual    = pIterador.getPNodo();
            NodoLista<TIPO> *anterior = actual->getAnterior();
            NodoLista<TIPO> *siguiente = actual->getSiguiente();
            anterior->setSiguiente(siguiente);
            siguiente->setAnterior(anterior);
            pIterador.setPNodo(anterior);
        }
    ListaEnlazada::cNodos--;
}

template<class TIPO>
bool ListaEnlazada<TIPO>::buscar(IteradorLista<TIPO>& pIterador, TIPO &dato)//, bool(*busqueda)(TIPO a, TIPO b))
{
    bool enc=false;
    for(pIterador.irInicio(); pIterador.valido(); pIterador.siguiente())
    {
        enc = pIterador.info() == dato;
        if(enc)
            break;
    }

    return enc;
}

#endif // LISTAENLAZADA_H
