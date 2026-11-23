#ifndef FASE_FOREST_H
#define FASE_FOREST_H

#include    "Fase.h"

class Fase_Forest : public Fase {

public:
    Fase_Forest(Jogador* jogador);
    ~Fase_Forest();

    void iniciarFase() override;
    void executar() override;

    void criarLama(int x, int y);
    void salvar() override;
    void carregar() override;
};

#endif
