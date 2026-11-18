#pragma once

#include    "Personagem.h"
#include    "stdafx.h"




class Jogador : public Personagem {
    private:
        int pontos;

        bool teclaCimaAnterior;
        const float velocidade = 4.f;
        const float gravidade = 0.6f;
        const float forcaPulo = -14.f;

    public:
        int vidas;
        bool noChao;
        float xAnterior;
        float yAnterior;
        float velocidadeY;


        Jogador();
        virtual ~Jogador();

        void executar() override;
        void mover() override;
        void salvar() override;

        float getX() const;
        float getY() const;
        float getVelocidadeY() const;
        float getYAnterior() const;

        void setX(float novoX);
        void setY(float novoY);
        void pararQueda();

        void receberDano(int dano);
        void quicar();
        bool estaVivo();

};
