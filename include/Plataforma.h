#pragma once

#include    "Obstaculo.h"
#include    "Gerenciador_CL.h"

class Jogador;

class Plataforma : public Obstaculo
{
    private:
        int altura;
        int largura;

    public:
        Plataforma();
        Plataforma(int x, int y, int largura, int altura);
        virtual ~Plataforma();

        void executar() override;
        void salvar() override;
        void obstaculizar(Jogador* pJogador) override;
    };
