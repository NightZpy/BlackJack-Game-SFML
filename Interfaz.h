#ifndef VENTANA_H
#define VENTANA_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include "Boton.h"


class Interfaz
{
    public:
        Interfaz(int ancho, int alto, int profundidad, std::string titulo, int dineroInicialJugador);
        virtual ~Interfaz() {}

        sf::RenderWindow* getVentana()   { return Interfaz::ventana; }
        bool ventanaActiva()            { return Interfaz::ventana->IsOpened(); }
        //bool eventos(sf::Event& evento)  { return Interfaz::ventana->GetEvent(evento); }
        void cerrar()                   { Interfaz::ventana->Close(); }

        //Getters and Setters

        bool    isPosterior()  { return Interfaz::posterior; }
        void    setPosterior(bool posterior)  { Interfaz::posterior = posterior; }

        bool    isPlayActivo()  { return Interfaz::playActivo; }
        void    setPlayActivo(bool playActivo)  { Interfaz::playActivo = playActivo; }

        bool    isJuegoActivo()  { return Interfaz::juegoActivo; }
        void    setJuegoActivo(bool juegoActivo)  { Interfaz::juegoActivo = juegoActivo; }

        bool    isEsperarActivo()  { return Interfaz::esperarActivo; }
        void    setEsperarActivo(bool esperarActivo)  { Interfaz::esperarActivo = esperarActivo; }

        bool    isPedirActivo()  { return Interfaz::pedirActivo; }
        void    setPedirActivo(bool pedirActivo)  { Interfaz::pedirActivo = pedirActivo; }

        bool    isApuesta100Activo()  { return Interfaz::apuesta100Activo;  }
        bool    isApuesta100Efecto()  { return Interfaz::efecto100Activo;   }
        void    setApuesta100Activo (bool apuesta100Activo)  { Interfaz::apuesta100Activo    = apuesta100Activo; }
        void    setEfecto100Activo  (bool  efecto100Activo)  { Interfaz::efecto100Activo     = efecto100Activo;  }

        bool    isApuesta50Activo()                         { return Interfaz::apuesta50Activo; }
        bool    isApuesta50Efecto()                         { return Interfaz::efecto50Activo;  }
        void    setApuesta50Activo  (bool apuesta50Activo)  { Interfaz::apuesta50Activo = apuesta50Activo;  }
        void    setEfecto50Activo   (bool  efecto50Activo)  { Interfaz::efecto50Activo  = efecto50Activo;   }
        void    setStrDineroJugador(int dineroJugador);
        void    setStrPozo(int pozo);
        void    setStrPts(int ptsJugador, int ptsRepartidor);
        void    setStrMsgPrincipal(std::string msg);

        void reiniciar();
        void mostrar() { Interfaz::ventana->Display(); }
        void dibujar();
        void agregarCartasInterfaz(ListaEnlazada<Carta> jugador, ListaEnlazada<Carta> repartidor);
        void limpiarPantalla();
        void desactivarBotones();
        void activarPlay();
        void msgGanoJugador();
        void msgPerdioJugador();
        void msgEmpate();

        int  apuestaRealizada(int mX, int mY);
        bool aguantar();
        bool jugar();
        bool pedirCarta();

    protected:
    private:
        sf::RenderWindow* ventana;

        ListaEnlazada<Carta> jugador;
        ListaEnlazada<Carta> repartidor;

        Boton *play;
        Boton *esperar;
        Boton *pedir;

        Boton *apuesta100;
        Boton *apuesta50;

        sf::Sprite spCartaPosterior;
        sf::Image  imgCartaPosterior;
        sf::Sprite spMazo;
        sf::Image  imgMazo;
        sf::Sprite spFondo;
        sf::Image  imgFondo;

        sf::String strMsgPrincipal;
        sf::String strPtsJugador;
        sf::String strPtsRepartidor;
        sf::String strDineroJugador;
        sf::String strPozo;

        bool posterior;
        bool empate;
        bool juegoActivo;
        bool perdioJugador;
        bool ganoJugador;
        bool playActivo;
        bool esperarActivo;
        bool pedirActivo;
        bool apuesta100Activo;
        bool efecto100Activo;
        bool apuesta50Activo;
        bool efecto50Activo;
};

Interfaz::Interfaz(int ancho, int alto, int profundidad, std::string titulo, int dineroInicialJugador)
{
    Interfaz::ventana = new sf::RenderWindow(sf::VideoMode(ancho, alto, profundidad), titulo);
    sf::Image ico;
    ico.LoadFromFile("imagenes/blackjack.png");
    Interfaz::ventana->SetIcon(40, 40, ico.GetPixelsPtr());

    Interfaz::posterior         = true;
    Interfaz::empate            = false;
    Interfaz::ganoJugador       = false;
    Interfaz::perdioJugador     = false;
    Interfaz::playActivo        = false;
    Interfaz::juegoActivo       = false;
    Interfaz::esperarActivo     = false;
    Interfaz::pedirActivo       = false;
    Interfaz::apuesta100Activo  = true;
    Interfaz::efecto100Activo   = false;
    Interfaz::apuesta50Activo   = true;
    Interfaz::efecto50Activo    = false;

    //Cargamos las imagenes para cada boton
    if(!Interfaz::imgFondo.LoadFromFile("imagenes/fondo.jpg"))
    {
        std::cout<<std::endl<<"fondo.jpg no cargado.";
        return;
    }

    sf::Sprite sprite(Interfaz::imgFondo);
    Interfaz::spFondo = sprite;

    if(!Interfaz::imgMazo.LoadFromFile("imagenes/cartas/mazo.png"))
    {
        std::cout<<std::endl<<"mazo.png no cargado.";
        return;
    }

    sf::Sprite sprite2(Interfaz::imgMazo);
    Interfaz::spMazo = sprite2;

    if(!Interfaz::imgCartaPosterior.LoadFromFile("imagenes/cartas/posterior_carta.png"))
    {
        std::cout<<std::endl<<"posterior_carta.png no cargada.";
        return;
    }

    sf::Sprite sprite3(Interfaz::imgCartaPosterior);
    Interfaz::spCartaPosterior = sprite3;

    Interfaz::play = new Boton("imagenes/botones/JugarActivo.png",      "imagenes/botones/JugarInactivo.png",   650, 500,  Interfaz::playActivo);

    Interfaz::esperar = new Boton("imagenes/botones/EsperarActivo.png", "imagenes/botones/EsperarInactivo.png", 500, 500,  Interfaz::esperarActivo);

    Interfaz::pedir = new Boton("imagenes/botones/PedirActivo.png",     "imagenes/botones/PedirInactivo.png",   350, 500,  Interfaz::pedirActivo);

    Interfaz::apuesta100 = new Boton("imagenes/fichas/100Activo.png",   "imagenes/fichas/100Inactivo.png",      "imagenes/fichas/100click.png", 5,      440,  Interfaz::apuesta100Activo);

    Interfaz::apuesta50 = new Boton("imagenes/fichas/50Activo.png",     "imagenes/fichas/50Inactivo.png",       "imagenes/fichas/50click.png",  155,    440,  Interfaz::apuesta50Activo);

    //Cargamos una fuente
    sf::Font fuente;
    if (!fuente.LoadFromFile("imagenes/COOPBL.ttf"))
        return ;

	// Configuramos los textos que mostraremos
    Interfaz::strPtsJugador.SetFont(sf::Font::GetDefaultFont());
	Interfaz::strPtsJugador.SetSize(40.f);
    Interfaz::strPtsJugador.SetX(20);
    Interfaz::strPtsJugador.SetY(300);
    Interfaz::strPtsJugador.SetColor(sf::Color::White);

	// Configuramos los textos que mostraremos
    Interfaz::strPtsRepartidor.SetFont(sf::Font::GetDefaultFont());
	Interfaz::strPtsRepartidor.SetSize(40.f);
    Interfaz::strPtsRepartidor.SetX(20);
    Interfaz::strPtsRepartidor.SetY(380);
    Interfaz::strPtsRepartidor.SetColor(sf::Color::White);


    Interfaz::strMsgPrincipal.SetFont(sf::Font::GetDefaultFont());
	Interfaz::strMsgPrincipal.SetSize(40.f);
    Interfaz::strMsgPrincipal.SetX(100);
    Interfaz::strMsgPrincipal.SetY((alto /  2) - 70);
    Interfaz::strMsgPrincipal.SetColor(sf::Color::White);

    //Un flujo de string para poder convertir de numeros a std::string
    std::stringstream st;
    //Convierto de int a stringstream
    st << dineroInicialJugador;
    //Obtengo el std::string
    std::string strDineroInicialJugador = st.str();

    Interfaz::strDineroJugador.SetFont(sf::Font::GetDefaultFont());
	Interfaz::strDineroJugador.SetSize(40.f);
	Interfaz::strDineroJugador.SetX(550.f);
	Interfaz::strDineroJugador.SetY(450.f);
    Interfaz::strDineroJugador.SetColor(sf::Color::White);
    Interfaz::strDineroJugador.SetText(strDineroInicialJugador);

    Interfaz::strPozo.SetFont(sf::Font::GetDefaultFont());
	Interfaz::strPozo.SetSize(40.f);
	Interfaz::strPozo.SetX(550.f);
	Interfaz::strPozo.SetY(50.f);
    Interfaz::strPozo.SetColor(sf::Color::White);
}

void Interfaz::setStrPts(int ptsJugador, int ptsRepartidor)
{
    //Un flujo de string para poder convertir de numeros a std::string
    std::stringstream st;
    //Convierto de int a stringstream
    st << ptsJugador;
    //Obtengo el std::string
    std::string strPtsJugador = "Jugador: " + st.str();

    st << ptsRepartidor;
    std::string strPtsRepartidor = "Repartidor: " + st.str();

    Interfaz::strPtsJugador.SetText(strPtsJugador);
    Interfaz::strPtsRepartidor.SetText(strPtsRepartidor);
}

void Interfaz::agregarCartasInterfaz(ListaEnlazada<Carta> jugador, ListaEnlazada<Carta> repartidor)
{
    Interfaz::jugador    = jugador;
    Interfaz::repartidor = repartidor;
}

void Interfaz::reiniciar()
{
    Interfaz::posterior         = true;
    Interfaz::empate            = false;
    Interfaz::ganoJugador       = false;
    Interfaz::perdioJugador     = false;
    Interfaz::playActivo        = false;
    Interfaz::juegoActivo       = false;
    Interfaz::esperarActivo     = false;
    Interfaz::pedirActivo       = false;
    Interfaz::apuesta100Activo  = true;
    Interfaz::efecto100Activo   = false;
    Interfaz::apuesta50Activo   = true;
    Interfaz::efecto50Activo    = false;
}

void Interfaz::limpiarPantalla()
{
    Interfaz::ventana->Clear(sf::Color::Green);
}

void Interfaz::setStrMsgPrincipal(std::string msg)
{
    Interfaz::strMsgPrincipal.SetText(msg);
}

void Interfaz::setStrPozo(int pozo)
{
    //Un flujo de string para poder convertir de numeros a std::string
    std::stringstream st;
    //Convierto de int a stringstream
    st << pozo;
    //Obtengo el std::string
    std::string strPozo = "Pozo: " + st.str();
    Interfaz::strPozo.SetText(strPozo);
}

void Interfaz::setStrDineroJugador(int dineroJugador)
{
    //Un flujo de string para poder convertir de numeros a std::string
    std::stringstream st;
    //Convierto de int a stringstream
    st << dineroJugador;
    //Obtengo el std::string
    std::string strDineroJugador = "Dinero: " + st.str();
    Interfaz::strDineroJugador.SetText(strDineroJugador);
}

void Interfaz::dibujar()
{

    //Interfaz::ventana->Draw(Interfaz::spFondo);
    Interfaz::ventana->Draw(Interfaz::spMazo);

    if(Interfaz::juegoActivo)
    {
        int jX = 350;
        int jY = 220;
        IteradorLista<Carta> itrJug = Interfaz::jugador.getIterador();
        itrJug.irInicio();
        while(itrJug.valido())
        {
            Carta carta = itrJug.info();
            sf::Image img;
            img.LoadFromFile(carta.getRuta());
            sf::Sprite sprite(img);
            jX += 25;
            sprite.SetX(jX);
            sprite.SetY(jY);
            Interfaz::ventana->Draw(sprite);
            itrJug.siguiente();
        }
        jY = 20;
        jX = 350;
        int cC = 0;
        IteradorLista<Carta> itrRep = Interfaz::repartidor.getIterador();
        itrRep.irInicio();
        while(itrRep.valido())
        {
            Carta carta = itrRep.info();
            sf::Image img;
            img.LoadFromFile(carta.getRuta());
            sf::Sprite sprite(img);
            jX += 25;
            if(cC < 1 && Interfaz::posterior)
            {
                Interfaz::spCartaPosterior.SetX(375);
                Interfaz::spCartaPosterior.SetY(20);
                Interfaz::ventana->Draw(Interfaz::spCartaPosterior);
            }
            else
            {
                sprite.SetX(jX);
                sprite.SetY(jY);
                Interfaz::ventana->Draw(sprite);
            }
            itrRep.siguiente();
            cC++;
        }
    }

    if(Interfaz::empate)
    {
        Interfaz::setStrMsgPrincipal("¡Hay Pust!");
        Interfaz::ventana->Draw(Interfaz::strMsgPrincipal);
    }

    if(Interfaz::ganoJugador)
    {
        Interfaz::setStrMsgPrincipal("¡Has ganado!");
        Interfaz::ventana->Draw(Interfaz::strMsgPrincipal);
    }

    if(Interfaz::perdioJugador)
    {
        Interfaz::setStrMsgPrincipal("¡Has perdido!");
        Interfaz::ventana->Draw(Interfaz::strMsgPrincipal);
    }

    if(Interfaz::juegoActivo)
    {
        Interfaz::ventana->Draw(Interfaz::strPtsJugador);
        Interfaz::ventana->Draw(Interfaz::strPtsRepartidor);
        Interfaz::ventana->Draw(Interfaz::strPozo);
        Interfaz::ventana->Draw(Interfaz::strDineroJugador);
    }

    Interfaz::play->setActivo(Interfaz::playActivo);
    Interfaz::play->verificarEstado();
    Interfaz::ventana->Draw(Interfaz::play->getSprite());

    Interfaz::esperar->setActivo(Interfaz::esperarActivo);
    Interfaz::esperar->verificarEstado();
    Interfaz::ventana->Draw(Interfaz::esperar->getSprite());

    Interfaz::pedir->setActivo(Interfaz::pedirActivo);
    Interfaz::pedir->verificarEstado();
    Interfaz::ventana->Draw(Interfaz::pedir->getSprite());

    Interfaz::apuesta100->setActivo(Interfaz::apuesta100Activo);
    Interfaz::apuesta100->setEfecto(Interfaz::efecto100Activo);
    Interfaz::apuesta100->verificarEstado();
    Interfaz::ventana->Draw(Interfaz::apuesta100->getSprite());

    Interfaz::apuesta50->setActivo(Interfaz::apuesta50Activo);
    Interfaz::apuesta50->setEfecto(Interfaz::efecto50Activo);
    Interfaz::apuesta50->verificarEstado();
    Interfaz::ventana->Draw(Interfaz::apuesta50->getSprite());
}

int Interfaz::apuestaRealizada(int mX, int mY)
{
    if(Interfaz::ventana->GetInput().IsMouseButtonDown(sf::Mouse::Left))
    {
        if(Interfaz::apuesta100->click(mX, mY))
            return 100;

        if(Interfaz::apuesta50->click(mX, mY))
            return 50;
    }
    return 0;
}

bool Interfaz::jugar()
{
    if(Interfaz::ventana->GetInput().IsMouseButtonDown(sf::Mouse::Left))
    {
        int mX = Interfaz::ventana->GetInput().GetMouseX();
        int mY = Interfaz::ventana->GetInput().GetMouseY();

        if(Interfaz::play->click(mX, mY))
            return true;
    }
    return false;
}

bool Interfaz::aguantar()
{
    if(Interfaz::ventana->GetInput().IsMouseButtonDown(sf::Mouse::Left))
    {
        int mX = Interfaz::ventana->GetInput().GetMouseX();
        int mY = Interfaz::ventana->GetInput().GetMouseY();

        if(Interfaz::esperar->click(mX, mY))
            return true;
    }
    return false;
}

bool Interfaz::pedirCarta()
{
    if(Interfaz::ventana->GetInput().IsMouseButtonDown(sf::Mouse::Left))
    {
        int mX = Interfaz::ventana->GetInput().GetMouseX();
        int mY = Interfaz::ventana->GetInput().GetMouseY();
        std::cout<<std::endl<<"LeftPedir";
        if(Interfaz::pedir->click(mX, mY))
            return true;
    }
    return false;
}

void Interfaz::msgPerdioJugador()
{
    Interfaz::ganoJugador    = false;
    Interfaz::perdioJugador  = true;
    Interfaz::empate         = false;
}

void Interfaz::msgGanoJugador()
{
    Interfaz::ganoJugador    = true;
    Interfaz::perdioJugador  = false;
    Interfaz::empate         = false;
}

void Interfaz::msgEmpate()
{
    Interfaz::empate        = true;
    Interfaz::ganoJugador   = false;
    Interfaz::perdioJugador = false;
}

void Interfaz::desactivarBotones()
{
    Interfaz::esperarActivo = false;
    Interfaz::playActivo    = false;
    Interfaz::pedirActivo   = false;
}

void Interfaz::activarPlay()
{
    Interfaz::playActivo    = true;
}
#endif // VENTANA_H


