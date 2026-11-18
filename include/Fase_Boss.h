#ifndef FASE_BOSS_H
#define FASE_BOSS_H

#include "Fase.h"

class Fase_Boss : public Fase {
private:
    const int maxChefes;
    const int maxObstaculos;

public:
    Fase_Boss(Jogador* jogador);
    ~Fase_Boss();

    void iniciarFase() override;
    void executar() override;

    void salvar() override;
    void carregar() override;
};

#endif
