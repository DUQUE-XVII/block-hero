#pragma once

#include "Fase.h"
#include "Boitata.h"

class Fase_Boss : public Fase {
private:
    const int maxChefoes;
    const int maxCogumelos;
    int chefoesRestantes;
    Boitata* chefaoAtual;

    void invocarProximoChefao();

public:
    Fase_Boss(Jogador* jogador);
    ~Fase_Boss();

    void iniciarFase() override;
    void executar() override;
    void salvar(const std::string& pasta = "saves/") override;
    void carregar() override;
};
