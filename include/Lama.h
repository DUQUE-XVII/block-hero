#pragma once

#include    "Obstaculo.h"
#include    "Jogador.h"

class Lama : public Obstaculo{
    int Lerdo;
    int reduzir;
    public:

        Lama();
        ~Lama();

        void obstaculizar(Jogador* pJogador);
        void executar();

        void salvar();
        bool reduzVelocidade();

        int Chance();

};
