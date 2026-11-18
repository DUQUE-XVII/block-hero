#ifndef FASE_BOSS_H
#define FASE_BOSS_H

#include "Fase.h"

class Fase_Boss : public Fase {
private:
    const int maxChefes;
    const int maxObstaculos;

public:
    Fase_Boss();
    ~Fase_Boss();

    void iniciarFase() override; // Instancia o Herói e o Boitatá
    void executar() override;

    void salvar() override;
    void carregar() override;
};

#endif
