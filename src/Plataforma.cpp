#include    "Plataforma.h"
#include    "Jogador.h"

Plataforma::Plataforma(){

}


Plataforma::Plataforma(int x, int y, int largura, int altura)
{
    this->x = x;
    this->y = y;

    this->largura = largura;
    this->altura = altura;

    retangulo->setSize({
        static_cast<float>(largura),
        static_cast<float>(altura)
    });

    retangulo->setFillColor(sf::Color::Blue);

    retangulo->setPosition({
        static_cast<float>(x),
        static_cast<float>(y)
    });
}

Plataforma::~Plataforma()
{
}

void Plataforma::executar()
{

}

void Plataforma::salvar()
{
    salvarDataBuffer();
}

void Plataforma::obstaculizar(Jogador* pJogador)
{

}
