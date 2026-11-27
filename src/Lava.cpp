#include    "Lava.h"

Lava::Lava()
    : Dano(3)
{
    retangulo->setSize({60.f, 12.f});               // criarPlataforma redefine
    retangulo->setFillColor(sf::Color(255, 0, 0)); // vermelho
    dano = true;
    srand(time(NULL));
}

Lava::~Lava(){
}

void Lava::executar(){
    Probabilidade = rand() %100;
}

void Lava::salvar(){

    salvarDataBuffer();
    sf::Vector2f tam = retangulo->getSize();
    Salvamento << " " << Dano << " " << tam.x << " " << tam.y;

}

void Lava::obstaculizar(Jogador* pJogador){
    // Só causa dano a cada 0.5 s de contato
    if (relogioDano.getElapsedTime().asSeconds() < 0.5f)
        return;

    relogioDano.restart();
    if(Probabilidade <5)
        pJogador->receberDano(Dano *2);
    else
        pJogador->receberDano(Dano);

     pJogador->quicar();
}


