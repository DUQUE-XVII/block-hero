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

        sf::FloatRect jogador = pJogador->getForma()->getGlobalBounds();
        sf::FloatRect plataforma = this->getForma()->getGlobalBounds();

        // Pouso: o jogador estava acima e está descendo.
        if (pJogador->getVelocidadeY() > 0.f &&
            pJogador->getYAnterior() + jogador.size.y <= plataforma.position.y &&
            jogador.position.y + jogador.size.y >= plataforma.position.y)
        {
            pJogador->setY(plataforma.position.y - jogador.size.y);
            pJogador->pararQueda();
            jogador = pJogador->getForma()->getGlobalBounds();
        }

        const float esquerdaJ = jogador.position.x;
        const float direitaJ = jogador.position.x + jogador.size.x;
        const float topoJ = jogador.position.y;
        const float baixoJ = jogador.position.y + jogador.size.y;
        const float esquerdaO = plataforma.position.x;
        const float direitaO = plataforma.position.x + plataforma.size.x;
        const float topoO = plataforma.position.y;
        const float baixoO = plataforma.position.y + plataforma.size.y;

        const bool sobrepoeY = baixoJ > topoO && topoJ < baixoO;

        if (sobrepoeY &&
            pJogador->xAnterior + jogador.size.x <= esquerdaO &&
            direitaJ >= esquerdaO)
        {
            pJogador->setX(esquerdaO - jogador.size.x);
        }
        else if (sobrepoeY &&
                 pJogador->xAnterior >= direitaO &&
                 esquerdaJ <= direitaO)
        {
            pJogador->setX(direitaO);
        }

}
