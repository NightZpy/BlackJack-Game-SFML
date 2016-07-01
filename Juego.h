#ifndef JUEGO_H
#define JUEGO_H
#include "Mazo.h"
#include "Jugador.h"
#include "Repartidor.h"
#include "stdio.h"

class Juego
{
    public:
        Juego(int dineroJugador);
        virtual ~Juego(){}

        //Getters and Setters
        Repartidor* getRepartidor(){ return Juego::repartidor; }
        Jugador* getJugador(){ return Juego::jugador; }
        int     getDineroJugador(){ return Juego::dineroJugador; }
        int     getPozo(){ return Juego::pozo; }
        bool    isPrimeraRonda() { return Juego::primeraRonda; }
        void    setPrimeraRonda(bool primeraRonda) { Juego::primeraRonda = primeraRonda; }
        bool    isSegundaRonda() { return Juego::segundaRonda; }
        void    setSegundaRonda(bool segundaRonda) { Juego::segundaRonda = segundaRonda; }
        void    setPozo(int pozo) { Juego::pozo = pozo; }

        //Métodos
        void    repartir();
        void    reiniciar(int dineroJugador);
        void    cargarPozo(int apuesta);
        void    verCartasJugador();
        void    verCartasRepartidor();
        void    verPuntaje();
        void    darCartaAJugador();
        void    darCartaARepartidor();
        void    nuevaMesa();
        void    darPozoAJugador();
        bool    hayBlackJack();
        bool    hayGanador();
        bool    ganoJugador();
        bool    empate();


    protected:
    private:
        Mazo        *mazo;
        Jugador     *jugador;
        Repartidor  *repartidor;
        int         dineroJugador;
        int         pozo;
        bool        ganaJugador;
        bool        primeraRonda;
        bool        segundaRonda;
};

Juego::Juego(int dineroJugador)
{
    Juego::dineroJugador    = dineroJugador;

    Juego::mazo         = new Mazo(52);

    Juego::jugador      = new Jugador(Juego::dineroJugador);

    Juego::repartidor   = new Repartidor();

    Juego::pozo         = 0;
    Juego::ganaJugador  = false;
    Juego::primeraRonda = false;
    Juego::segundaRonda = false;
}

void Juego::verCartasJugador()
{
    ListaEnlazada<Carta> cartas = Juego::jugador->getCartas();
    IteradorLista<Carta> itr = cartas.getIterador();
    printf("\n--Cartas Jugador--");
    while(itr.valido())
    {
        Carta carta = itr.info();
        printf("\n%c-%d",carta.getFigura(), carta.getValor());
        itr.siguiente();
    }
}

void Juego::verPuntaje()
{
    printf("\n-----Puntaje----");
    printf("\nJugador: %d", Juego::jugador->ptsTotales());
    printf("\nRepartidor: %d", Juego::repartidor->ptsTotales());
}

void Juego::verCartasRepartidor()
{
    ListaEnlazada<Carta> cartas = Juego::repartidor->getCartas();
    IteradorLista<Carta> itr = cartas.getIterador();
    printf("\n--Cartas Repartidor--");
    while(itr.valido())
    {
        Carta carta = itr.info();
        printf("\n%c-%d",carta.getFigura(), carta.getValor());
        itr.siguiente();
    }
}

void Juego::repartir()
{
    for(int i=0; i<2; i++)
    {
        Carta carta = Juego::mazo->sacar();
        Juego::jugador->agregarCarta(carta);
        carta = Juego::mazo->sacar();
        Juego::repartidor->agregarCarta(carta);
    }
    Juego::primeraRonda = true;
}

void Juego::reiniciar(int dineroJugador)
{
    Juego::dineroJugador= dineroJugador;

    Juego::mazo         = new Mazo(52);

    Juego::jugador      = new Jugador(Juego::dineroJugador);

    Juego::repartidor   = new Repartidor();

    Juego::pozo         = 0;
    Juego::ganaJugador  = false;
    Juego::primeraRonda = false;
}

void Juego::cargarPozo(int apuesta)
{
    if(Juego::jugador->apostar(apuesta))
        Juego::pozo += apuesta * 2;
}

void Juego::darCartaAJugador()
{
    Carta carta = Juego::mazo->sacar();
    Juego::jugador->agregarCarta(carta);
}

void Juego::darCartaARepartidor()
{
    Carta carta = Juego::mazo->sacar();
    Juego::repartidor->agregarCarta(carta);
}

void Juego::nuevaMesa()
{
    Juego::setPrimeraRonda(false);
    Juego::setSegundaRonda(false);
    Juego::ganaJugador  = false;
    Juego::pozo = 0;
    Juego::jugador->vaciarConjunto();
    Juego::repartidor->vaciarConjunto();
    Juego::mazo = new Mazo(52);
}

void Juego::darPozoAJugador()
{
    Juego::jugador->setDinero(Juego::pozo + Juego::jugador->getDinero());
    Juego::pozo = 0;
}

bool Juego::hayBlackJack()
{
    if(Juego::jugador->ptsTotales() == 21)
    {
        Juego::ganaJugador = true;
        return true;
    }

    if(Juego::repartidor->ptsTotales() == 21)
        return true;

    return false;
}

bool Juego::hayGanador()
{
    if(Juego::hayBlackJack())
    {
        return true;
    }

    if(Juego::jugador->ptsTotales() > 21)
    {
        if(Juego::repartidor->ptsTotales() < Juego::jugador->ptsTotales())
        {
            Juego::ganaJugador = false;
            return true;
        }
        else
        {
            //printf("\nGana Jugador");
            Juego::ganaJugador = true;
            return true;
        }
    }

    if(Juego::jugador->ptsTotales() < 21)
    {
        if(Juego::repartidor->ptsTotales() < 21 && Juego::repartidor->ptsTotales() > Juego::jugador->ptsTotales())
        {
            Juego::ganaJugador = false;
            return true;
        }
        else
        {
            Juego::ganaJugador = true;
            return true;
        }
    }
    return false;

}

bool Juego::ganoJugador()
{
    return Juego::ganaJugador;
}

bool Juego::empate()
{
    return (Juego::repartidor->ptsTotales() == Juego::jugador->ptsTotales());
}

#endif // JUEGO_H
