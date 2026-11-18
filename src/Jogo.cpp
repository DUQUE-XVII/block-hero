#include "Jogo.h"

Jogo::Jogo() : faseAtual(nullptr) {
    Ente::setGG(&pGG);

    faseAtual = new Fase_Forest(&pJog1);
    faseAtual->iniciarFase();
}

Jogo::~Jogo() {
    delete faseAtual;
    faseAtual = nullptr;
}

void Jogo::executar() {
    while (pGG.getJanela().isOpen()) {
        while (const auto evento = pGG.getJanela().pollEvent()) {
            if (evento->is<sf::Event::Closed>())
                pGG.getJanela().close();
        }

        pGG.getJanela().clear(sf::Color::Black);

        if (faseAtual != nullptr) {
            faseAtual->executar();

            // Avança automaticamente para a Fase_Boss ao derrotar os inimigos da Fase 1
            if (faseAtual->estaConcluida() && faseAtual->getNumeroFase() == 1) {
                delete faseAtual;
                faseAtual = new Fase_Boss(&pJog1);
                faseAtual->iniciarFase();
            }
        }

        pGG.getJanela().display();
    }
}
