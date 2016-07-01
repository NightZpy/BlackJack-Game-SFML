#ifndef MAZO_H
#define MAZO_H
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "Carta.h"
#include "PilaLE.h"
#include "ListaEnlazada.hpp"

const int CORAZON           =   3;
const int DIAMANTE          =   4;
const int TREBOL            =   5;
const int PICA              =   6;


class Mazo
{
	public:
        Mazo() {}
		Mazo(int cCartas);
		virtual ~Mazo();

	//Métodos

	//Getters
		PilaLE<Carta> 	       getPCartas() { return Mazo::pCartas; }
		ListaEnlazada<Carta>   getLECartas(){ return Mazo::lECartas; }
		int				        getCCartas() { return Mazo::cCartas; }

    //Métodos
        Carta* repartir(int nJugadores);
        Carta  sacar();

    //Sobrecargas
        void operator= (Mazo mazo);

	protected:

    private:
		PilaLE<Carta>           pCartas;
		ListaEnlazada<Carta>    lECartas;
		int 		            cCartas;
};

Mazo::Mazo(int cCartas)
{
            Mazo::cCartas = cCartas;
            std::string ruta1 = "imagenes/cartas/";
            std::string ext   = ".png";

            IteradorLista<Carta> itr = Mazo::lECartas.getIterador();

            int cPorGrupo = Mazo::getCCartas() / 4;
            int cCodigo = 0;

            for(int i=3; i<=6; i++)
            {
                for(int j=1; j<=cPorGrupo; j++)
                {
                    std::stringstream st;
                    st << j;
                    if(i==CORAZON)
                    {
                       std::string ruta2 = ruta1 + "corazones" + st.str() + ext;
                       Carta carta(j, cCodigo+1, CORAZON, ruta2);
                       Mazo::lECartas.agregar(itr, carta);
                    }
                    if(i==DIAMANTE)
                    {
                       std::string ruta2 = ruta1 + "diamantes" + st.str() + ext;
                       Carta carta(j, cCodigo+1, DIAMANTE, ruta2);
                       Mazo::lECartas.agregar(itr, carta);
                    }
                    if(i==TREBOL)
                    {
                       std::string ruta2 = ruta1 + "treboles" + st.str() + ext;
                       Carta carta(j, cCodigo+1, TREBOL, ruta2);
                       Mazo::lECartas.agregar(itr, carta);
                    }
                    if(i==PICA)
                    {
                       std::string ruta2 = ruta1 + "picas" + st.str() + ext;
                       Carta carta(j, cCodigo+1, PICA, ruta2);
                       Mazo::lECartas.agregar(itr, carta);
                    }
                    cCodigo++;
                }

            }

            srand(time(NULL));
            for(int i=0; i<cCartas; i++)
            {
                int cartaAleatoria = (rand() % Mazo::cCartas);
                //std::cout<<std::endl<<i<<".-Aletorio: "<<cartaAleatoria;
                Carta carta = Mazo::lECartas[cartaAleatoria];
                Mazo::pCartas.push(carta);
            }

}

Mazo::~Mazo()
{
    Mazo::cCartas = 0;
    PilaLE<Carta> pila;
    Mazo::pCartas = pila;
    ListaEnlazada<Carta> lista;
    Mazo::lECartas = lista;
}

Carta Mazo::sacar()
{
    Carta carta = Mazo::pCartas.top();
    Mazo::pCartas.pop();
    return carta;
}

void Mazo::operator= (Mazo mazo)
{
    Mazo::cCartas  = mazo.getCCartas();

    Mazo::lECartas = mazo.getLECartas();

    Mazo::pCartas  = mazo.getPCartas();
}



#endif // MAZO_H
