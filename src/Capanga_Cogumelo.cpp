#include "Capanga_Cogumelo.h"
#include "Jogador.h"

Capanga_Cogumelo::Capanga_Cogumelo() {
    posX = 600; posY = 510;
    vidas = 1;
    direcao = -1;
    velocidadeAndar = 2.5f;
    danoContato = 1;
    sf::Color marrom(139, 69, 19);

    retangulo->setSize({44.f, 50.f});
    retangulo->setFillColor(marrom);
    carregarTextura("assets/Inimigos/Cogumelo.png");
    retangulo->setPosition({posX, posY});
}
Capanga_Cogumelo::~Capanga_Cogumelo() {}

void Capanga_Cogumelo::executar() {
     if (!estaVivo())
        return;
    mover();
}

void Capanga_Cogumelo::inverterDirecao() {
    direcao *= -1;
}

void Capanga_Cogumelo::danificar(Jogador* pJogador) {
    pJogador->receberDano(danoContato);

        const float centroCogumelo = posX + retangulo->getSize().x / 2.f;
        const float centroJogador = pJogador->getX() + pJogador->getForma()->getSize().x / 2.f;
        const float direcao = (centroJogador >= centroCogumelo) ? 1.f : -1.f;
    pJogador->arremessar(direcao);

    inverterDirecao();
}

void Capanga_Cogumelo::mover(){
    posX += velocidadeAndar * direcao;
    retangulo->setPosition({posX,posY});
    if(posX <150 || posX>700)
        inverterDirecao();
}

void Capanga_Cogumelo::salvar()
{
    salvarDataBuffer();
}

bool Capanga_Cogumelo::estaVivo(){
    if(vidas <= 0)
        return false;
    return true;

}
