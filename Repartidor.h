#ifndef REPARTIDOR_H
#define REPARTIDOR_H


class Repartidor
{
    public:
        Repartidor() {}
        virtual ~Repartidor() {}

        //Getters and Setters
        ListaEnlazada<Carta> getCartas() { return Repartidor::conjunto; };

        //Métodos
        bool    pedirCarta();
        int     ptsTotales();
        void    agregarCarta(Carta carta);
        void vaciarConjunto();

        //Sobrecargas
        void operator= (Repartidor repartidor);

    protected:
    private:
        ListaEnlazada<Carta> conjunto;
};

void Repartidor::agregarCarta(Carta carta)
{
    Repartidor::conjunto.agregarInicio(carta);
}

void Repartidor::vaciarConjunto()
{
    ListaEnlazada<Carta> lista;
    Repartidor::conjunto = lista;
}

int Repartidor::ptsTotales()
{
    int pts = 0;
    bool haz = false;
    IteradorLista<Carta> itr = Repartidor::conjunto.getIterador();
    itr.irInicio();
    while(itr.valido())
    {
        Carta carta = itr.info();
        if(carta.getValor() == 11 || carta.getValor() == 12 || carta.getValor() == 13)
            pts += 10;
        else
            if(carta.getValor() == 1)
                haz = true;
            else
                pts += carta.getValor();
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

bool Repartidor::pedirCarta()
{
    if(Repartidor::ptsTotales() < 17)
        return true;
    return false;
}

void Repartidor::operator= (Repartidor repartidor)
{
    Repartidor::conjunto  = repartidor.getCartas();
}

#endif // REPARTIDOR_H
