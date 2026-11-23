#pragma once

#include "stdafx.h"

class Ente;

class GerenciadorGrafico{
    private:
        sf::RenderWindow obj;
        sf::Font fonte;
        bool fonteCarregada;

    public:
        GerenciadorGrafico();
        ~GerenciadorGrafico();
        void desenharEnte(Ente* pE = NULL);
        void desenharTexto(const std::string& conteudo, float x, float y,
                           unsigned int tamanho = 22);
        sf::RenderWindow& getJanela();
};
