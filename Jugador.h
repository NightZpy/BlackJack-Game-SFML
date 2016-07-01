#ifndef JUGADOR_H
#define JUGADOR_H


class Jugador
{
    public:
        Jugador() {}
        Jugador(int dinero);
        virtual ~Jugador(){};
        //Getters and Setters
        int getDinero()             { return Jugador::dinero; }
        void setDinero(int dinero)   { Jugador::dinero = dinero; }
        ListaEnlazada<Carta> getCartas()    { return Jugador::conjunto; }

        //Obtengo los puntos totales de la suma de cartas
        int ptsTotales();
        void agregarCarta(Carta carta);
        void mostrarCartas();
        bool apostar(int dinero);
        void vaciarConjunto();

    protected:
    private:
        int dinero;
        ListaEnlazada<Carta> conjunto;
};

Jugador::Jugador(int dinero)
{
    Jugador::dinero = dinero;
}

void Jugador::vaciarConjunto()
{
    ListaEnlazada<Carta> lista;
    Jugador::conjunto = lista;
}

void Jugador::agregarCarta(Carta carta)
{
    Jugador::conjunto.agregarInicio(carta);
}

bool Jugador::apostar(int apuesta)
{
    if (Jugador::dinero >= apuesta)
    {
        Jugador::dinero -= apuesta;
        return true;
    }
    return false;
}

int Jugador::ptsTotales()
{
    int pts = 0;
    bool haz = false;
    IteradorLista<Carta> itr = Jugador::conjunto.getIterador();
    itr.irInicio();
    while(itr.valido())
    {
        Carta carta = itr.info();
        if(carta.getValor() == 11 || carta.getValor() == 12 || carta.getValor() == 13)
        {
            pts += 10;
        }
        else
        {
            if(carta.getValor() == 1)
                haz = true;
            else
                pts += carta.getValor();
        }
        itr.siguiente();
    }
    if(haz)
    {
        if(pts <= 10)
            pts += 11;
        else
            pts++;
    }
    return pts;
}

#endif // JUGADOR_H
