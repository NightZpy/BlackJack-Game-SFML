#ifndef CARTA_H
#define CARTA_H

#include <iostream>
#include <SFML/Graphics.hpp>


class Carta
{
    public:
        Carta(){}
        Carta(int valor, int codigo, char figura, std::string ruta);
        virtual ~Carta(){}

    //Métodos
        void    posicion(int x, int y);

	//Getters
		int 	getCodigo() { return Carta::codigo; }
		int 	getValor()  { return Carta::valor;  }
		char 	getFigura() { return Carta::figura; }
		std::string 	getRuta() { return Carta::ruta; }
		sf::Sprite* getSpFigura() { return Carta::spFigura; }
		sf::Image   getImgFigura(){ return Carta::imagen; }


    //Setters


    protected:
    private:
        std::string ruta;
		int 	valor;
		int 	codigo;
		char 	figura;
		sf::Sprite* spFigura;
		sf::Image imagen;
};

Carta::Carta(int valor, int codigo, char figura, std::string ruta)
{
    Carta::ruta = ruta;
    Carta::imagen.LoadFromFile(ruta);
    sf::Image imagen;
    if(!imagen.LoadFromFile(ruta))
    {
        std::cout<<std::endl<<"Imagen: "<<ruta<<". No cargada.";
        return;
    }

    Carta::valor  = valor;
    Carta::codigo = codigo;
    Carta::figura = figura;
    Carta::spFigura = new sf::Sprite(imagen);

}

void Carta::posicion(int x, int y)
{
    Carta::spFigura->SetX(x);
    Carta::spFigura->SetY(y);
}
#endif // CARTA_H
