#include "Gerenciador_CL.h"
#include "Projetil_Acido.h"
#include "Lava.h"
#include "Lama.h"
#include "Plataforma.h"
#include "Capanga_Cogumelo.h"
#include "Boitata.h"
#include "Planta_Acida.h"

Gerenciador_CL::Gerenciador_CL()
    : pJog1(nullptr)
{
}

Gerenciador_CL::~Gerenciador_CL()
{
}

bool Gerenciador_CL::verificaColi(Entidade* pe1, Entidade* pe2) const
{
    if (pe1 == nullptr || pe2 == nullptr ||
        pe1->getForma() == nullptr || pe2->getForma() == nullptr)
        return false;

    return pe1->getForma()->getGlobalBounds()
        .findIntersection(pe2->getForma()->getGlobalBounds()).has_value();
}

void Gerenciador_CL::colisaoObstaculo()
{
    if (pJog1 == nullptr)
        return;

    pJog1->restaurarVelocidade();

    for (Obstaculo* pObstaculo : LOs)
    {
        if (pObstaculo == nullptr || !verificaColi(pJog1, pObstaculo))
            continue;

        pObstaculo->obstaculizar(pJog1);
    }
}

void Gerenciador_CL::getJogador(Jogador* jog)
{
    pJog1 = jog;
}

void Gerenciador_CL::incluirObstaculo(Obstaculo* p)
{
    if (p != nullptr)
        LOs.push_back(p);
}

void Gerenciador_CL::incluirInimigos(CriaturaHostil* p)
{
    if (p != nullptr)
        LIs.push_back(p);
}

void Gerenciador_CL::incluirProjetil(Projetil_Acido* p)
{
    if (p != nullptr)
        LPs.push_back(p);
}

void Gerenciador_CL::colisaoinimigo()
{
    if (pJog1 == nullptr)
        return;

    for (CriaturaHostil* pInimigo : LIs)
    {
        if (pInimigo == nullptr || !pInimigo->estaVivo())
            continue;

        if (!verificaColi(pJog1, pInimigo))
            continue;

        sf::FloatRect jogador = pJog1->getForma()->getGlobalBounds();
        sf::FloatRect inimigo = pInimigo->getForma()->getGlobalBounds();

        const bool sobrepoeX =
            jogador.position.x + jogador.size.x > inimigo.position.x &&
            jogador.position.x < inimigo.position.x + inimigo.size.x;

        const bool caiuSobre =
            pJog1->getVelocidadeY() > 0.f &&
            pJog1->getYAnterior() + jogador.size.y <= inimigo.position.y &&
            jogador.position.y + jogador.size.y >= inimigo.position.y &&
            sobrepoeX;

        if (caiuSobre)
        {
            pJog1->setY(inimigo.position.y - jogador.size.y);
            pInimigo->receberDano(100);
            pJog1->quicar();

            if (!pInimigo->estaVivo())
                pJog1->adicionarPontos(pInimigo->getPontos());
        }
        else
        {
            pInimigo->danificar(pJog1);
        }
    }
}

void Gerenciador_CL::colisaoProjetil()
{
    if (pJog1 == nullptr || !pJog1->estaVivo())
        return;

    for (Projetil_Acido* pProjetil : LPs)
    {
        if (pProjetil == nullptr || !pProjetil->estaAtivo())
            continue;

        if (verificaColi(pJog1, pProjetil))
        {
            pJog1->receberDano(pProjetil->getDano());
            pProjetil->desativar();
        }
    }
}

void Gerenciador_CL::desenharEntidades() const
{
    for (Obstaculo* o : LOs)
        if (o != nullptr) o->desenhar();

    for (CriaturaHostil* i : LIs)
        if (i != nullptr && i->estaVivo()) i->desenhar();

    for (Projetil_Acido* p : LPs)
        if (p != nullptr && p->estaAtivo()) p->desenhar();

    if (pJog1 != nullptr)
        pJog1->desenhar();
}

bool Gerenciador_CL::todosInimigosMortos() const
{
    for (CriaturaHostil* inimigo : LIs)
        if (inimigo != nullptr && inimigo->estaVivo())
            return false;

    return true;
}

int Gerenciador_CL::totalEntidades() const
{
    return (pJog1 != nullptr ? 1 : 0)
         + static_cast<int>(LOs.size())
         + static_cast<int>(LIs.size());
}

void Gerenciador_CL::salvarEntidades(std::ostream& arquivo) const
{
    if (pJog1 != nullptr)
    {
        pJog1->salvar();
        arquivo << "JOGADOR " << pJog1->getDadosSalvos() << "\n";
    }

    for (Obstaculo* o : LOs)
    {
        if (o == nullptr) continue;
        o->salvar();

        if (dynamic_cast<Lava*>(o))            arquivo << "LAVA ";
        else if (dynamic_cast<Lama*>(o))       arquivo << "LAMA ";
        else if (dynamic_cast<Plataforma*>(o)) arquivo << "PLATAFORMA ";

        arquivo << o->getDadosSalvos() << "\n";
    }

    for (CriaturaHostil* i : LIs)
    {
        if (i == nullptr) continue;
        i->salvar();

        if (dynamic_cast<Capanga_Cogumelo*>(i))  arquivo << "CAPANGA ";
        else if (dynamic_cast<Boitata*>(i))      arquivo << "BOITATA ";
        else if (dynamic_cast<Planta_Acida*>(i)) arquivo << "PLANTA ";

        arquivo << i->getDadosSalvos() << "\n";
    }
}

void Gerenciador_CL::destruirEntidades()
{
    for (Obstaculo* o : LOs)
        delete o;
    LOs.clear();

    for (CriaturaHostil* i : LIs)
        delete i;
    LIs.clear();

    // Projéteis pertencem aos inimigos (Planta_Acida / Boitata) e são deletados nos destrutores deles
    LPs.clear();
}

const list<Obstaculo*>& Gerenciador_CL::getObstaculos() const
{
    return LOs;
}

void Gerenciador_CL::salvarArquivos(const std::string& pasta) const
{
    // 1. jogador.txt
    if (pJog1 != nullptr)
    {
        std::ofstream arqJog(pasta + "jogador.txt");
        if (arqJog.is_open())
        {
            pJog1->salvar();
            arqJog << pJog1->getDadosSalvos() << "\n";
        }
    }

    // 2. obstaculos.txt
    std::ofstream arqObs(pasta + "obstaculos.txt");
    if (arqObs.is_open())
    {
        for (Obstaculo* o : LOs)
        {
            if (o == nullptr) continue;
            o->salvar();

            if (dynamic_cast<Lava*>(o))            arqObs << "LAVA ";
            else if (dynamic_cast<Lama*>(o))       arqObs << "LAMA ";
            else if (dynamic_cast<Plataforma*>(o)) arqObs << "PLATAFORMA ";

            arqObs << o->getDadosSalvos() << "\n";
        }
    }

    // 3. inimigos.txt
    std::ofstream arqIni(pasta + "inimigos.txt");
    if (arqIni.is_open())
    {
        for (CriaturaHostil* i : LIs)
        {
            if (i == nullptr || !i->estaVivo()) continue;
            i->salvar();

            if (dynamic_cast<Capanga_Cogumelo*>(i))  arqIni << "CAPANGA ";
            else if (dynamic_cast<Boitata*>(i))      arqIni << "BOITATA ";
            else if (dynamic_cast<Planta_Acida*>(i)) arqIni << "PLANTA ";

            arqIni << i->getDadosSalvos() << "\n";
        }
    }
}

void Gerenciador_CL::colisaoInimigoObstaculo()
{
    for (CriaturaHostil* pInimigo : LIs)
    {
        if (pInimigo == nullptr || !pInimigo->estaVivo())
            continue;

        const bool ehBoitata = (dynamic_cast<Boitata*>(pInimigo) != nullptr);

        for (Obstaculo* pObstaculo : LOs)
        {
            // Apenas Plataforma é sólida (Lama e Lava não bloqueiam inimigos)
            Plataforma* pPlat = dynamic_cast<Plataforma*>(pObstaculo);
            if (pPlat == nullptr)
                continue;

            sf::FloatRect ini = pInimigo->getForma()->getGlobalBounds();
            sf::FloatRect plat = pPlat->getForma()->getGlobalBounds();

            const float iniEsq = ini.position.x;
            const float iniDir = ini.position.x + ini.size.x;
            const float iniTopo = ini.position.y;
            const float iniBase = ini.position.y + ini.size.y;

            const float platEsq = plat.position.x;
            const float platDir = plat.position.x + plat.size.x;
            const float platTopo = plat.position.y;
            const float platBase = plat.position.y + plat.size.y;

            const bool sobrepoeX = (iniDir > platEsq) && (iniEsq < platDir);

            // Se cogumelo/planta estiver apoiado em uma plataforma móvel descendo, acompanha ela
            if (!ehBoitata && sobrepoeX && std::abs(iniBase - platTopo) <= 3.f)
            {
                pInimigo->setPosicao(pInimigo->getX(), platTopo - ini.size.y);
                continue;
            }

            if (!verificaColi(pInimigo, pPlat))
                continue;

            // Calcula o quanto penetrou em cada eixo para empurrar pelo caminho mais curto
            const float sobreposicaoX = std::min(iniDir, platDir) - std::max(iniEsq, platEsq);
            const float sobreposicaoY = std::min(iniBase, platBase) - std::max(iniTopo, platTopo);

            const float centroIniX = iniEsq + ini.size.x / 2.f;
            const float centroPlatX = platEsq + plat.size.x / 2.f;
            const float centroIniY = iniTopo + ini.size.y / 2.f;
            const float centroPlatY = platTopo + plat.size.y / 2.f;

            if (sobreposicaoY < sobreposicaoX)
            {
                if (centroIniY < centroPlatY)
                    pInimigo->setPosicao(pInimigo->getX(), platTopo - ini.size.y);
                else
                    pInimigo->setPosicao(pInimigo->getX(), platBase);
            }
            else
            {
                if (centroIniX < centroPlatX)
                    pInimigo->setPosicao(platEsq - ini.size.x, pInimigo->getY());
                else
                    pInimigo->setPosicao(platDir, pInimigo->getY());

                if (Capanga_Cogumelo* cap = dynamic_cast<Capanga_Cogumelo*>(pInimigo))
                    cap->inverterDirecao();
            }
        }
    }
}


void Gerenciador_CL::executar()
{
    colisaoObstaculo();
    colisaoInimigoObstaculo();
    colisaoinimigo();
    colisaoProjetil();

}
