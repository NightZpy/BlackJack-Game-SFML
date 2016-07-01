#ifndef BOTON_H
#define BOTON_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Boton
{
    public:
        Boton(){}
        Boton(std::string rutaImgActivo, std::string rutaImgInactivo, int x, int y, bool activo);
        Boton(std::string rutaImgActivo, std::string rutaImgInactivo, std::string rutaImgEfecto, int x, int y, bool activo);
        virtual ~Boton() {}

        int     getXMax()   { return (Boton::xMax = Boton::x + Boton::ancho); }
        int     getYMax()   { return (Boton::yMax = Boton::y + Boton::alto);  }
        int     getX()      { return Boton::x; }
        int     getY()      { return Boton::y; }
        bool    isActivo()  { return Boton::activo; }
        void    setActivo(bool activo) { Boton::activo = activo; }
        bool    isEfecto()  { return Boton::efecto; }
        void    setEfecto(bool efecto) { Boton::efecto = efecto; }

        sf::Sprite  getSprite()         {   return Boton::sprite; }
        sf::Image   getImgActivo()      {   return Boton::imgActivo; }
        sf::Image   getImgInactivo()    {   return Boton::imgInactivo; }
        sf::Image   getImgEfecto()      {   return Boton::imgEfecto; }

        //Métodos
        bool click(int xMouse, int yMouse);
        void verificarEstado();
        void cambiarDimension(float x, float y){ Boton::sprite.SetScale(x, y); }

        //Sobrecargas
            void operator= (Boton boton);

    protected:
    private:
        sf::Sprite  sprite;
        sf::Image   imgActivo;
        sf::Image   imgInactivo;
        sf::Image   imgEfecto;

        int ancho;
        int alto;
        int x;
        int y;
        int xMax;
        int yMax;

        bool activo;
        bool efecto;
};

Boton::Boton(std::string rutaImgActivo, std::string rutaImgInactivo, int x, int y, bool activo)
{
    //cout<<endl<<"Ruta Activo: "<<rutaImgActivo;
    //cout<<endl<<"Ruta Inactivo: "<<rutaImgInactivo;
    if(!Boton::imgActivo.LoadFromFile(rutaImgActivo))
    {
        std::cout<<std::endl<<"Imagen: "<<rutaImgActivo<<". No cargada.";
        return;
    }

    if(!Boton::imgInactivo.LoadFromFile(rutaImgInactivo))
    {
        std::cout<<std::endl<<"Imagen: "<<rutaImgInactivo<<". No cargada.";
        return;
    }

    Boton::activo   = activo;
    Boton::efecto   = false;

    Boton::x        = x;
    Boton::y        = y;
    if(Boton::activo)
    {
        sf::Sprite sprite(Boton::imgActivo);
        Boton::sprite   = sprite;
    }
    else
    {
        sf::Sprite sprite(Boton::imgInactivo);
        Boton::sprite   = sprite;
    }

    Boton::sprite.SetX(Boton::x);
    Boton::sprite.SetY(Boton::y);

    Boton::ancho    = Boton::sprite.GetImage()->GetWidth();
    Boton::alto     = Boton::sprite.GetImage()->GetHeight();
}


Boton::Boton(std::string rutaImgActivo, std::string rutaImgInactivo, std::string rutaImgEfecto, int x, int y, bool activo)
{
    if(!Boton::imgActivo.LoadFromFile(rutaImgActivo))
    {
        std::cout<<std::endl<<"Imagen: "<<rutaImgActivo<<". No cargada.";
        return;
    }

    if(!Boton::imgInactivo.LoadFromFile(rutaImgInactivo))
    {
        std::cout<<std::endl<<"Imagen: "<<rutaImgInactivo<<". No cargada.";
        return;
    }

    if(!Boton::imgEfecto.LoadFromFile(rutaImgEfecto))
    {
        std::cout<<std::endl<<"Imagen: "<<rutaImgEfecto<<". No cargada.";
        return;
    }

    Boton::activo   = activo;
    Boton::efecto   = false;

    Boton::x        = x;
    Boton::y        = y;
    if(Boton::activo)
    {
        sf::Sprite sprite(Boton::imgActivo);
        Boton::sprite   = sprite;
    }
    else
    {
        sf::Sprite sprite(Boton::imgInactivo);
        Boton::sprite   = sprite;
    }

    Boton::sprite.SetX(Boton::x);
    Boton::sprite.SetY(Boton::y);

    Boton::ancho    = Boton::sprite.GetImage()->GetWidth();
    Boton::alto     = Boton::sprite.GetImage()->GetHeight();
}

void Boton::verificarEstado()
{
    if(Boton::isEfecto())
    {
        cout<<endl<<"Efecto";
        Boton::sprite.SetImage(Boton::imgEfecto);
        Boton::setEfecto(false);
        return;
    }
    if(Boton::isActivo())
        Boton::sprite.SetImage(Boton::imgActivo);
    else
        Boton::sprite.SetImage(Boton::imgInactivo);
}

bool Boton::click(int xMouse, int yMouse)
{
    return (Boton::activo && ((Boton::x >= xMouse && x <= Boton::getXMax()) && (Boton::y >= xMouse && y <= Boton::getYMax())));
}

void Boton::operator= (Boton boton)
{
    *this = boton;
}
#endif // BOTON_H


