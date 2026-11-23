#pragma once

#include    "Personagem.h"
#include    "stdafx.h"

class Jogador : public Personagem {
    private:
        int pontos;

        bool teclaCimaAnterior;
        float velocidade = 4.f;
        const float gravidade = 0.6f;
        const float forcaPulo = -14.f;

    public:
        int vidas;
        bool noChao;
        float xAnterior;
        float yAnterior;
        float velocidadeX;
        float velocidadeY;

        Jogador();
        virtual ~Jogador();

        void executar();
        void mover();
        void salvar();

        float getX() const;
        float getY() const;
        float getVelocidadeY() const;
        float getYAnterior() const;

        void setX(float novoX);
        void setY(float novoY);
        void pararQueda();

        void receberDano(int dano);
        void quicar();
        void arremessar(float direcaoX);
        bool estaVivo();

        void reduzirVelocidade();
        void restaurarVelocidade();

        int  getPontos() const;
        void adicionarPontos(int p);
};

