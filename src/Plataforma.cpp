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
     deslocamentoY = 0.f;

    if (movel)
    {
        const float yTopo = yBase - amplitude;
        float novoY = y + direcao * velocidadeMov;

        if (novoY <= yTopo)       { novoY = yTopo; direcao = 1;  }   // chegou no alto: desce
        else if (novoY >= yBase)  { novoY = yBase; direcao = -1; }   // chegou embaixo: sobe

        deslocamentoY = novoY - y;
        setPosicao(x, novoY);

        // Leva junto o jogador que está em cima
        if (jogadorApoiado != nullptr)
            jogadorApoiado->setY(jogadorApoiado->getY() + deslocamentoY);
    }

    jogadorApoiado = nullptr;
}

void Plataforma::salvar()
{
   salvarDataBuffer();
    Salvamento << " " << largura << " " << altura
               << " " << movel << " " << yBase << " " << amplitude
               << " " << velocidadeMov << " " << direcao;
}

void Plataforma::obstaculizar(Jogador* pJogador)
{
    sf::FloatRect jogador = pJogador->getForma()->getGlobalBounds();
    sf::FloatRect plataforma = this->getForma()->getGlobalBounds();

    const float esquerdaJ = jogador.position.x;
    const float direitaJ = jogador.position.x + jogador.size.x;

    const float topoJ = jogador.position.y;
    const float baixoJ = jogador.position.y + jogador.size.y;

    const float esquerdaO = plataforma.position.x;
    const float direitaO = plataforma.position.x + plataforma.size.x;

    const float topoO = plataforma.position.y;
    const float baixoO = plataforma.position.y + plataforma.size.y;

    // Verifica se existe sobreposição horizontal
    const bool sobrepoeX =
        direitaJ > esquerdaO &&
        esquerdaJ < direitaO;

    // Colisão por cima: jogador está caindo
    // (tolerância: a plataforma pode ter subido ao encontro do jogador neste frame)
    const float tolerancia = 1.f + std::abs(deslocamentoY);

    if (sobrepoeX &&
        pJogador->getVelocidadeY() > 0.f &&
        pJogador->getYAnterior() + jogador.size.y <= topoO + tolerancia &&
        baixoJ >= topoO)
    {
        pJogador->setY(topoO - jogador.size.y);
        pJogador->pararQueda();
        jogadorApoiado = pJogador;      // <-- NOVO: será levado no próximo frame
    }

    // Colisão por baixo: jogador está subindo
    else if (sobrepoeX &&
             pJogador->getVelocidadeY() < 0.f &&
             pJogador->getYAnterior() >= baixoO &&
             topoJ <= baixoO)
    {
        pJogador->setY(baixoO);
        pJogador->pararSubida();
    }

    // Atualiza os limites após possíveis correções
    jogador = pJogador->getForma()->getGlobalBounds();

    const float esquerdaAtual = jogador.position.x;
    const float direitaAtual = jogador.position.x + jogador.size.x;

    const float topoAtual = jogador.position.y;
    const float baixoAtual = jogador.position.y + jogador.size.y;

    const bool sobrepoeY =
        baixoAtual > topoO &&
        topoAtual < baixoO;

    // Colisão pela esquerda
    if (sobrepoeY &&
        pJogador->xAnterior + jogador.size.x <= esquerdaO &&
        direitaAtual >= esquerdaO)
    {
        pJogador->setX(esquerdaO - jogador.size.x);
    }

    // Colisão pela direita
    else if (sobrepoeY &&
             pJogador->xAnterior >= direitaO &&
             esquerdaAtual <= direitaO)
    {
        pJogador->setX(direitaO);
    }
}

void Plataforma::tornarMovel(float amp, float velocidade)
{
    movel = true;
    yBase = y;               // a posição atual vira o ponto mais baixo
    amplitude = amp;
    velocidadeMov = velocidade;
    direcao = -1;            // começa subindo
}

bool Plataforma::ehMovel() const
{
    return movel;
}

void Plataforma::configurarMovel(bool m, float yB, float amp, float vel, int dir)
{
    movel = m;
    yBase = yB;
    amplitude = amp;
    velocidadeMov = vel;
    direcao = dir;
}
