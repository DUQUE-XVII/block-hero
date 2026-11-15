#pragma once

#include    "stdafx.h"
#include    "Entidade.h"

class Jogador;

class Obstaculo : public Entidade
{
    protected:
        bool dano;

    public:
        Obstaculo();
        virtual ~Obstaculo();

        void salvarDataBuffer();

        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void obstaculizar(Jogador* pJogador) = 0;
};
