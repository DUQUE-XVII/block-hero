#include "Capanga_Cogumelo.h"
#include "Jogador.h"

Capanga_Cogumelo::Capanga_Cogumelo()
    : direcao(-1),
      velocidadeAndar(2.5f),
      limiteEsquerdo(25.f),
      limiteDireito(775.f)
{
    posX = 600.f;
    posY = 510.f;
    x = posX;
    y = posY;
    vidas = 1;
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

void Capanga_Cogumelo::definirLimitesPatrulha(float esq, float dir) {
    limiteEsquerdo = esq;
    limiteDireito = dir;
}

void Capanga_Cogumelo::setEstado(int v, int dir) {
    vidas = v;
    direcao = dir;
}

void Capanga_Cogumelo::danificar(Jogador* pJogador) {
    pJogador->receberDano(danoContato);

    const float centroCogumelo = posX + retangulo->getSize().x / 2.f;
    const float centroJogador = pJogador->getX() + pJogador->getForma()->getSize().x / 2.f;
    const float dirEmpurrao = (centroJogador >= centroCogumelo) ? 1.f : -1.f;
    pJogador->arremessar(dirEmpurrao);

    inverterDirecao();
}

void Capanga_Cogumelo::mover() {
    posX += velocidadeAndar * direcao;
    const float largura = retangulo->getSize().x;

    if (posX <= limiteEsquerdo) {
        posX = limiteEsquerdo;
        direcao = 1;
    } else if (posX + largura >= limiteDireito) {
        posX = limiteDireito - largura;
        direcao = -1;
    }

    x = posX;
    y = posY;
    retangulo->setPosition({posX, posY});
}

void Capanga_Cogumelo::salvar() {
    x = posX;
    y = posY;

    salvarDataBuffer();

    Salvamento << " " << vidas
               << " " << direcao
               << " " << limiteEsquerdo
               << " " << limiteDireito;
}

bool Capanga_Cogumelo::estaVivo() {
    return vidas > 0;
}
