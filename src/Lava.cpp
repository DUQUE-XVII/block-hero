#include    "Lava.h"

Lava::Lava()
    : Dano(3)
{
    retangulo->setSize({60.f, 12.f});               // criarPlataforma redefine
    retangulo->setFillColor(sf::Color(255, 0, 0)); // laranja
    dano = true;                                    // flag herdada de Obstaculo
}

Lava::~Lava(){
}

void Lava::executar(){
}

void Lava::salvar(){
}

void Lava::obstaculizar(Jogador* pJogador){
    // Só causa dano a cada 0.5 s de contato
    if (relogioDano.getElapsedTime().asSeconds() < 0.5f)
        return;

    relogioDano.restart();
    pJogador->receberDano(Dano);
    pJogador->quicar();   // dá um pulinho para o herói sair da lava
}
