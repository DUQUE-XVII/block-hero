#ifndef FASE_BOSS_H
#define FASE_BOSS_H

#include    "Fase.h"
#include    "Lava.h"


class Fase_Boss : public Fase {


    public:
        Fase_Boss(Jogador* jogador);
        ~Fase_Boss();

        void iniciarFase() override;
        void executar() override;


        void carregar() override;
};

#endif
