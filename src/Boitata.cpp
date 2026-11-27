#include "Boitata.h"
#include "Projetil_Acido.h"
#include "Jogador.h"

Boitata::Boitata()
    : velocidadePerseguicao(1.5f),
      tempoRecargaFogo(120), // 120 quadros: aproximadamente 2 segundos a 60 FPS
      contadorTempoFogo(0),
      pFogo(new Projetil_Acido())

{
    posX = 600.f;
    posY = 200.f;
    x = posX;
    y = posY;
    vidas = 100;
    danoContato = 5;
    pontosAoMorrer = 1000;

    retangulo->setSize({97.f, 60.f});
    retangulo->setFillColor(sf::Color(190, 45, 35));
    carregarTextura("assets/Inimigos/Boitata.png");
    retangulo->setPosition({posX, posY});

    // Reutiliza a entidade de projétil do projeto, mas dá a ela aparência de fogo.
    pFogo->getForma()->setFillColor(sf::Color(255, 105, 20));
}

Boitata::~Boitata()
{
    delete pFogo;
    pFogo = nullptr;
}

void Boitata::executar()
{
    // O projétil precisa continuar andando mesmo quando o Boitatá não tem alvo.
    if (pFogo != nullptr)
        pFogo->executar();

    if (!estaVivo() || alvo == nullptr)
        return;

    mover();

    // Só dispara novamente quando o projétil anterior já saiu da tela.
    if (pFogo->estaAtivo())
        return;

    ++contadorTempoFogo;
    if (contadorTempoFogo < tempoRecargaFogo)
        return;

    const sf::Vector2f posAlvo = alvo->getForma()->getPosition();
    const sf::Vector2f tamanhoAlvo = alvo->getForma()->getSize();
    const float centroAlvo = posAlvo.x + tamanhoAlvo.x / 2.f;
    const float centroBoitata = posX + retangulo->getSize().x / 2.f;
    const float direcao = (centroAlvo >= centroBoitata) ? 1.f : -1.f;

    const float larguraProjetil = pFogo->getForma()->getSize().x;
    const float inicioX = (direcao > 0.f)
        ? posX + retangulo->getSize().x
        : posX - larguraProjetil;
    const float inicioY = posY + retangulo->getSize().y / 2.f;

    pFogo->ativar(inicioX, inicioY, direcao);
    contadorTempoFogo = 0;
}

void Boitata::mover()
{
    if (alvo == nullptr)
        return;

    const sf::Vector2f posAlvo = alvo->getForma()->getPosition();
    const sf::Vector2f tamanhoAlvo = alvo->getForma()->getSize();
    const float centroAlvoX = posAlvo.x + tamanhoAlvo.x / 2.f;
    const float centroAlvoY = posAlvo.y + tamanhoAlvo.y / 2.f;

    const float centroBoitataX = posX + retangulo->getSize().x / 2.f;
    const float centroBoitataY = posY + retangulo->getSize().y / 2.f;

    // Movimento horizontal (eixo X)
    if (centroAlvoX > centroBoitataX)
        posX += velocidadePerseguicao;
    else if (centroAlvoX < centroBoitataX)
        posX -= velocidadePerseguicao;

    // Movimento vertical (eixo Y)
    const float velocidadeVertical = velocidadePerseguicao * 0.8f;
    if (centroAlvoY > centroBoitataY)
        posY += velocidadeVertical;
    else if (centroAlvoY < centroBoitataY)
        posY -= velocidadeVertical;

    // Limites horizontais da arena (paredes em x=20 e x=780)
    if (posX < 20.f)
        posX = 20.f;
    if (posX + retangulo->getSize().x > 780.f)
        posX = 780.f - retangulo->getSize().x;

    // Limites verticais da arena (teto em y=20 e chão em y=560)
    if (posY < 20.f)
        posY = 20.f;
    if (posY + retangulo->getSize().y > 560.f)
        posY = 560.f - retangulo->getSize().y;

    x = posX;
    y = posY;
    retangulo->setPosition({posX, posY});
}

void Boitata::salvar()
{
    x = posX;
    y = posY;

    salvarDataBuffer();

    Salvamento << " " << vidas
               << " " << contadorTempoFogo;

    pFogo->salvar();
    Salvamento << " " << pFogo->getDadosSalvos();
}

void Boitata::danificar(Jogador* pJogador)
{
    if (pJogador != nullptr)
    {
        pJogador->receberDano(danoContato);

        const float centroBoitata = posX + retangulo->getSize().x / 2.f;
        const float centroJogador = pJogador->getX() + pJogador->getForma()->getSize().x / 2.f;
        const float direcao = (centroJogador >= centroBoitata) ? 1.f : -1.f;

        pJogador->arremessar(direcao);
    }
}

Projetil_Acido* Boitata::getProjetil() const
{
    return pFogo;
}

void Boitata::setEstado(int v, int cont)
{
    vidas = v;
    contadorTempoFogo = cont;
}
