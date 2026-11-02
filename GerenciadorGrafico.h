#pragma once

#include    <SFML/Graphics.hpp>

class GerenciadorGrafico{
    private:
        sf::RenderWindow obj;

    public:
        GerenciadorGrafico();
        ~GerenciadorGrafico();
        void desenharEnte(Ente* pE);
