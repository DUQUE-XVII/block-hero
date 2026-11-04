#pragma once

#include "stdafx.h"

class Ente;

class GerenciadorGrafico{
    private:
        sf::RenderWindow obj;

    public:
        GerenciadorGrafico();
        ~GerenciadorGrafico();
        void desenharEnte(Ente* pE = NULL);
        sf::RenderWindow& getJanela();
};
