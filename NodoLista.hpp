#ifndef NODO_H
#define NODO_H

template<class TIPO>
class NodoLista
{
    public:

        NodoLista(TIPO info, NodoLista<TIPO> *siguiente = NULL, NodoLista<TIPO> *anterior = NULL):
            info(info), siguiente(siguiente), anterior(anterior) {}
        virtual ~NodoLista() {}

        TIPO getInfo()                      { return NodoLista::info;           }
        NodoLista<TIPO>* getSiguiente()     { return NodoLista::siguiente;      }
        NodoLista<TIPO>* getAnterior()      { return NodoLista::anterior;       }

        void setInfo(TIPO info)                  { NodoLista::info = info;           }
        void setSiguiente(NodoLista* siguiente)  { NodoLista::siguiente = siguiente; }
        void setAnterior(NodoLista* anterior)    { NodoLista::anterior = anterior;   }

    protected:
    private:
        TIPO info;
        NodoLista<TIPO> *siguiente;
        NodoLista<TIPO> *anterior;
};

#endif // NODO_H
