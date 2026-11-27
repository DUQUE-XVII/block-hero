#pragma once

#include    "Obstaculo.h"
#include    "stdafx.h"
#include    "Jogador.h"


class Lava : public Obstaculo{
    private:
        const int Dano;
        sf::Clock relogioDano;   // controla o intervalo entre danos
        int Probabilidade;
    public:
        Lava();
        ~Lava();

        void obstaculizar(Jogador* pJogador);
        void executar();

        void salvar();
        int Chance();
};
