#pragma once

#include    "Obstaculo.h"
#include    "Gerenciador_CL.h"

class Jogador;

class Plataforma : public Obstaculo
{
    private:
        int altura;
        int largura;
        bool  movel = false;
        float yBase = 0.f;           // ponto mais baixo (posição original)
        float amplitude = 0.f;       // quanto sobe a partir de yBase
        float velocidadeMov = 0.f;   // px por frame
        int   direcao = -1;          // -1 sobe, +1 desce
        float deslocamentoY = 0.f;   // quanto andou neste frame
        Jogador* jogadorApoiado = nullptr;


    public:
        Plataforma();
        Plataforma(int x, int y, int largura, int altura);
        virtual ~Plataforma();

        void executar() override;
        void salvar() override;
        void obstaculizar(Jogador* pJogador) override;

        void tornarMovel(float amplitude, float velocidade);
        bool ehMovel() const;
        void configurarMovel(bool m, float yB, float amp, float vel, int dir);

    };
