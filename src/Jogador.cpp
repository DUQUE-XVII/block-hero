#include "Jogador.h"
#include "Plataforma.h"


Jogador::Jogador()
    :   vidas(20),
        pontos(0),
        velocidadeX(0),
        velocidadeY(0),
        yAnterior(0),
        noChao(true),
        teclaCimaAnterior(false)
{
    x = 150;
    y = 200;
    xAnterior = x;
    yAnterior = y;

    retangulo->setSize({60.f, 40.f});
    retangulo->setFillColor(sf::Color::White);
    carregarTextura("assets/Jogador/Heroi.png");
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

    // Movimento horizontal pelo teclado
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        x += velocidade;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        x -= velocidade;


    x += velocidadeX;
    velocidadeX *= 0.85f;
    if (std::abs(velocidadeX) < 0.2f)
        velocidadeX = 0.f;


    bool cima = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

    if (cima && !teclaCimaAnterior && noChao)
    {
        velocidadeY = forcaPulo;
    }

    teclaCimaAnterior = cima;


    noChao = false;
    velocidadeY += gravidade;
    y += velocidadeY;


    retangulo->setPosition({x, y});
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

void Jogador::arremessar(float direcaoX)
{
    velocidadeX = direcaoX * 14.f; // Empurra forte para o lado
    velocidadeY = -10.f;           // Joga para cima
    noChao = false;
}

void Jogador::reduzirVelocidade()
{
    velocidade = 2.f;
}

void Jogador::restaurarVelocidade()
{
    velocidade = 4.f;
}

int Jogador::getPontos() const
{
    return pontos;
}

void Jogador::adicionarPontos(int p)
{
    pontos += p;
}
