#pragma once

#include    "stdafx.h"
#include    "GerenciadorGrafico.h"

class Ente{

    protected:
        int id;
        static GerenciadorGrafico* pGG ;
        sf::RectangleShape* retangulo;
        sf::Texture textura;
        bool carregarTextura(const std::string& caminho,
                             const sf::IntRect& area = sf::IntRect());

    public:
        Ente();
        virtual ~Ente();

        virtual void executar() =0;

        sf::RectangleShape* getForma();
        void desenhar();
        static void setGG(GerenciadorGrafico *GG);

};
