#include <iostream>
#include "Juego.h"
#include "Interfaz.h"

using namespace std;

//Constantes usadas para identificar cada figura en las cartas
const int DINERO_INICIAL    =   2000;

int main()
{
    bool jugando  = false;
    int  apuestaJugador = 0;
    Juego juego(DINERO_INICIAL);

    Interfaz interfaz(800, 600, 32, "BlackJack", juego.getJugador()->getDinero());

    while(interfaz.ventanaActiva())
    {
        sf::Event evento;
        while(interfaz.getVentana()->GetEvent(evento))
        {
            //Si se hizo una apuesta
            if(apuestaJugador > 0)
            {
                cout<<endl<<"Apuesta: "<<apuestaJugador;
                juego.cargarPozo(apuestaJugador);
                cout<<endl<<"Pozo: "<<juego.getPozo();
                cout<<endl<<"Dinero: "<<juego.getJugador()->getDinero();
                apuestaJugador = 0;

                if(juego.isSegundaRonda())
                {
                    interfaz.setStrDineroJugador(juego.getJugador()->getDinero());
                    interfaz.setPosterior(false);
                }
                else
                {
                    interfaz.setStrDineroJugador(juego.getJugador()->getDinero());
                    interfaz.setPlayActivo(true);
                    interfaz.setEsperarActivo(false);
                    interfaz.setPedirActivo(false);
                    juego.setSegundaRonda(true);
                }
                interfaz.setStrPozo(juego.getPozo());
                interfaz.setStrPts(juego.getJugador()->ptsTotales(), juego.getRepartidor()->ptsTotales());
            }

            // Verifico si se sale del programa con escape o la X de la ventanita
            if(evento.Type == sf::Event::Closed)
            {
                interfaz.cerrar();
                break;
            }

            if(evento.Type == sf::Event::KeyPressed)
            {
                if(evento.Key.Code == sf::Key::Escape)
                {
                    interfaz.cerrar();
                    break;
                }

                if(evento.Key.Code == sf::Key::Return)
                {
                    if(interfaz.isPlayActivo())
                    {
                        interfaz.setJuegoActivo(true);
                        interfaz.setPlayActivo(false);
                        interfaz.setEsperarActivo(true);
                        interfaz.setPedirActivo(true);
                        jugando = true;
                        juego.repartir();
                        juego.verPuntaje();
                        juego.verCartasJugador();
                        juego.verCartasRepartidor();
                    }
                }

                if(evento.Key.Code == sf::Key::Space)
                {
                    if (interfaz.isPedirActivo())
                    {
                        cout<<endl<<"Pedir----------------";
                        //Sólo si nadie tiene 21 ni pasado de 21
                        if(juego.getJugador()->ptsTotales() < 21 && juego.getRepartidor()->ptsTotales() < 21)
                        {
                            juego.darCartaAJugador();
                        }
                        else
                        {
                            interfaz.setPedirActivo(false);
                        }
                        juego.verCartasJugador();
                        juego.verCartasRepartidor();
                    }

                }

                if(evento.Key.Code == sf::Key::LAlt)
                {
                    if (interfaz.isEsperarActivo())
                    {
                        cout<<endl<<"Esperar";
                        interfaz.setEsperarActivo(false);
                        interfaz.setPedirActivo(false);
                        juego.verPuntaje();
                        juego.verCartasJugador();
                        juego.verCartasRepartidor();
                    }
                }

                if(evento.Key.Code == sf::Key::Left)
                {
                    if(interfaz.isApuesta100Activo())
                        apuestaJugador = 100;
                }

                if(evento.Key.Code == sf::Key::Right)
                {
                    if(interfaz.isApuesta50Activo())
                        apuestaJugador = 50;
                }
            }
        }

        if(jugando)
        {
            //Reviso si inicialmente alguien tiene un blackJack;
            if(juego.isPrimeraRonda())
            {
                if(juego.hayBlackJack())
                {
                    //Reviso quien gano
                    if(juego.empate())
                    {
                        cout<<endl<<"Push";
                        interfaz.msgEmpate();
                        int devuelto = juego.getJugador()->getDinero() + (juego.getPozo() / 2);
                        juego.getJugador()->setDinero(devuelto);
                    }
                    else
                    {
                        if(juego.ganoJugador())
                        {
                            cout<<endl<<"Gano jugador";
                            interfaz.msgGanoJugador();
                            juego.darPozoAJugador();
                        }
                        else
                        {
                            interfaz.msgPerdioJugador();
                            juego.setPozo(0);
                            cout<<endl<<"Gano Repartidor";
                        }
                    }
                    jugando = false;

                    juego.nuevaMesa();
                    apuestaJugador = 0;
                    //interfaz.reiniciar();
                    bool parar = true;
                    do{
                        interfaz.getVentana()->GetEvent(evento);
                        if(evento.Type == sf::Event::KeyPressed)
                        {
                            if(evento.Key.Code == sf::Key::Back)
                                parar = false;
                        }
                    }while (parar);

                }
                juego.setPrimeraRonda(false);
            }
            else
            {
                if(juego.hayGanador())
                {
                    //Reviso quien gano
                    if(juego.empate())
                    {
                        interfaz.msgEmpate();
                        int devuelto = juego.getJugador()->getDinero() + (juego.getPozo() / 2);
                        juego.getJugador()->setDinero(devuelto);
                    }
                    else
                    {
                        if(juego.ganoJugador())
                        {
                            interfaz.msgGanoJugador();
                            juego.darPozoAJugador();
                        }
                        else
                        {
                            interfaz.msgPerdioJugador();
                            juego.setPozo(0);
                        }
                    }
                    jugando = false;

                    juego.nuevaMesa();
                    apuestaJugador = 0;
                    //interfaz.reiniciar();
                    bool parar = true;
                    do{
                        interfaz.getVentana()->GetEvent(evento);
                        if(evento.Type == sf::Event::KeyPressed)
                        {
                            if(evento.Key.Code == sf::Key::Back)
                                parar = false;
                        }
                    }while (parar);
                }
            }
            if(interfaz.isJuegoActivo())
            {
                interfaz.agregarCartasInterfaz(juego.getJugador()->getCartas(), juego.getRepartidor()->getCartas());
                if(juego.getRepartidor()->pedirCarta())
                    juego.darCartaARepartidor();
            }
        }

        interfaz.limpiarPantalla();

        interfaz.dibujar();

        interfaz.mostrar();
    }

    return 0;
}
