#pragma once

#include    "stdafx.h"
#include    "GerenciadorGrafico.h"

class Ente{

    protected:
        int id;
        static GerenciadorGrafico* pGG;
        sf::RectangleShape* retangulo;

    public:
        Ente();
        virtual ~Ente();
        void desenhar();
        static void setGG(GerenciadorGrafico *GG);

};
