#include "Planta_Acida.h"
#include "Projetil_Acido.h"
#include "Jogador.h"

Planta_Acida::Planta_Acida()
    : tempoRecarga(90), contadorTempo(0), pAcido(new Projetil_Acido()),
    pontosAoMorrer(150)
{
    // A planta fica apoiada no chão (que começa em y = 560).
    x = 680.f;
    y = 510.f;
    vidas = 2;
    danoContato = 1;

    retangulo->setSize({47.f, 50.f});
    retangulo->setFillColor(sf::Color(30, 150, 45));
    carregarTextura("assets/Inimigos/Planta.png");
    retangulo->setPosition({x, y});
}

Planta_Acida::~Planta_Acida()
{
    delete pAcido;
    pAcido = nullptr;
}

void Planta_Acida::executar()
{
    if (!estaVivo())
        return;

    // O projétil continua se movimentando mesmo depois de ser disparado.
    pAcido->executar();

    if (alvo == nullptr || pAcido->estaAtivo())
        return;

    // Conta quadros: 90 quadros equivalem a cerca de 1,5 s em 60 FPS.
    ++contadorTempo;
    if (contadorTempo < tempoRecarga)
        return;

    // Compara os centros para decidir para qual lado atirar.
    const float centroPlanta = x + retangulo->getSize().x / 2.f;
    const float centroJogador = alvo->getX() + 20.f;
    const float direcao = (centroJogador >= centroPlanta) ? 1.f : -1.f;

    const float larguraProjetil = 14.f;
    const float inicioX = (direcao > 0.f) ? x + retangulo->getSize().x : x - larguraProjetil;
    const float inicioY = y + 20.f;

    pAcido->ativar(inicioX, inicioY, direcao);
    contadorTempo = 0;
}

void Planta_Acida::mover()
{
    // Planta estacionária: o método existe para cumprir o contrato de Personagem.
}

void Planta_Acida::salvar()
{
    salvarDataBuffer();

    Salvamento << " " << vidas
               << " " << contadorTempo;

    pAcido->salvar();
    Salvamento << " " << pAcido->getDadosSalvos();
}

void Planta_Acida::danificar(Jogador* pJogador)
{
    if (pJogador != nullptr)
        pJogador->receberDano(danoContato);
}

Projetil_Acido* Planta_Acida::getProjetil() const
{
    return pAcido;
}
