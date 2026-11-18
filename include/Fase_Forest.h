#ifndef FASE_FOREST_H
#define FASE_FOREST_H

#include "Fase.h"

class Fase_Forest : public Fase {
private:
    const int maxInimigos;
    const int maxObstaculos;

public:
    Fase_Forest();
    ~Fase_Forest();

    void iniciarFase() override; // Instancia o Herói, Cogumelos e Plantas
    void executar() override;

    void salvar() override;
    void carregar() override;
};

#endif
