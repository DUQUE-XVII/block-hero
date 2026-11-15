#include "Jogador.h"
#include "Plataforma.h"


Jogador::Jogador()
    :   vidas(10),
        pontos(0),
        velocidadeY(0),
        yAnterior(0),
        noChao(true),
        teclaCimaAnterior(false)
{
    x = 150;
    y = 200;
    xAnterior = x;
    yAnterior = y;

    retangulo->setSize({40.f, 60.f});
    retangulo->setFillColor(sf::Color::White);
    retangulo->setPosition({x, y});
}

Jogador::~Jogador() {}

void Jogador::executar()
{
    mover();
}

void Jogador::mover()
{

    xAnterior = x;
    yAnterior = y;

    // Movimento horizontal
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        x += velocidade;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        x -= velocidade;

    // Verifica se a tecla de pulo foi pressionada
    bool cima = sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::Up
    );

    if (cima && !teclaCimaAnterior && noChao)
    {
        velocidadeY = forcaPulo;
    }

    teclaCimaAnterior = cima;

    // Guarda a posição vertical anterior
    yAnterior = y;

    // A gravidade atua continuamente
    noChao = false;
    velocidadeY += gravidade;
    y += velocidadeY;

    // Atualiza a posição do retângulo
    retangulo->setPosition({(float)x, y});
}

float Jogador::getX() const
{
    return x;
}

float Jogador::getY() const
{
    return y;
}

float Jogador::getVelocidadeY() const
{
    return velocidadeY;
}

float Jogador::getYAnterior() const
{
    return yAnterior;
}

void Jogador::setY(float novoY)
{
    y = novoY;

    retangulo->setPosition({x,y});
}

void Jogador::setX(float novoX)
{
    x = novoX;

    retangulo->setPosition({x,y});
}

void Jogador::pararQueda()
{
    velocidadeY = 0;
    noChao = true;
}

void Jogador::salvar()
{
    salvarDataBuffer();
}

void Jogador::receberDano(int dano) {
    vidas -= dano;
}

void Jogador::quicar()
{
    velocidadeY = -10.f;
    noChao = false;
}

bool Jogador::estaVivo(){
    if(vidas<=0)
        return false;
    return true;
}
