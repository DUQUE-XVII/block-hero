#include "Fase.h"
#include "Boitata.h"
#include "Planta_Acida.h"
#include "Projetil_Acido.h"
#include "Lama.h"
#include "Lava.h"

Fase::Fase(int num, Jogador* jogador, int limiteInimigos, int limiteObstaculos)
    : numeroFase(num),
      concluida(false),
      maxInimigos(limiteInimigos),
      maxObstaculos(limiteObstaculos),
      numInimigos(0),
      numObstaculos(0),
      pJogador(jogador)
{
    pFisica = new Gerenciador_CL();
}

Fase::~Fase() {
    listaEntidades.limpar();
    if (pFisica != nullptr) {
        pFisica->destruirEntidades(); // deleta obstáculos e inimigos, poupando pJogador
        delete pFisica;
        pFisica = nullptr;
    }
}

std::mt19937& Fase::geradorAleatorio()
{
    static std::mt19937 gerador{std::random_device{}()};
    return gerador;
}

int Fase::sortear(int minimo, int maximo)
{
    return std::uniform_int_distribution<int>(minimo, maximo)(geradorAleatorio());
}

void Fase::criarLimitesArena() {
    Obstaculo* limites[] = {
        new Plataforma(0, 560, 800, 40),    // chão
        new Plataforma(0, 0, 800, 20),      // teto
        new Plataforma(0, 0, 20, 600),      // parede esquerda
        new Plataforma(780, 0, 20, 600)     // parede direita
    };

    for (Obstaculo* p : limites) {
        pFisica->incluirObstaculo(p);
        listaEntidades.incluir(p);
    }
}

void Fase::desenhar() {
    if (pFisica != nullptr)
        pFisica->desenharEntidades();

    if (pGG != nullptr && pJogador != nullptr) {
        pGG->desenharTexto("Pontos: " + std::to_string(pJogador->getPontos()),
                           30.f, 28.f);
    }
}

void Fase::criarCapanga(float x, float y, float limEsq, float limDir)
{
    Capanga_Cogumelo* capanga = new Capanga_Cogumelo();
    capanga->setPosicao(x, y);
    capanga->definirLimitesPatrulha(limEsq, limDir);

    if (!registrarInimigo(capanga))
        delete capanga;
}

void Fase::espalharCapangas(int quantidade, const list<Plataforma*>& plats)
{
    const float larguraCogumelo = 44.f;
    const float alturaCogumelo  = 50.f;

    for (int i = 0; i < quantidade; ++i)
    {
        // 50% de chance de ir em plataforma (se houver), 50% de ir no chão
        bool emPlataforma = !plats.empty() && (sortear(0, 1) == 1);

        if (emPlataforma)
        {
            int idx = sortear(0, static_cast<int>(plats.size()) - 1);
            Plataforma* p = *std::next(plats.begin(), idx);
            sf::FloatRect b = p->getForma()->getGlobalBounds();

            float xMin = b.position.x + 4.f;
            float xMax = b.position.x + b.size.x - larguraCogumelo - 4.f;
            float xSpawn = (xMax > xMin)
                ? static_cast<float>(sortear(static_cast<int>(xMin), static_cast<int>(xMax)))
                : b.position.x + (b.size.x - larguraCogumelo) / 2.f;

            criarCapanga(xSpawn, b.position.y - alturaCogumelo,
                         b.position.x, b.position.x + b.size.x);
        }
        else
        {
            // Espalhado pelo chão (longe do spawn inicial do herói em x=100..180)
            float xSpawn = static_cast<float>(sortear(200, 720));
            criarCapanga(xSpawn, 560.f - alturaCogumelo, 25.f, 775.f);
        }
    }
}

void Fase::criarPlataforma(float x, float y, int largura, int altura,
                           Obstaculo* plataforma)
{
    if (numObstaculos >= maxObstaculos)
        return;

    plataforma->getForma()->setSize({
        static_cast<float>(largura),
        static_cast<float>(altura)
    });
    plataforma->setPosicao(x, y);

    ++numObstaculos;
    pFisica->incluirObstaculo(plataforma);
    listaEntidades.incluir(plataforma);
}

bool Fase::registrarInimigo(CriaturaHostil* inimigo)
{
    if (inimigo == nullptr || numInimigos >= maxInimigos)
        return false;

    ++numInimigos;
    pFisica->incluirInimigos(inimigo);
    listaEntidades.incluir(inimigo);

    return true;
}

bool Fase::todosInimigosMortos() const
{
    return (pFisica != nullptr) ? pFisica->todosInimigosMortos() : true;
}

list<Plataforma*> Fase::gerarPlataformasAleatorias(int quantidade)
{
    auto sorteia = [&](int a, int b) { return sortear(a, b); };

    const int andares[3] = {425, 290, 155};
    const int espessura  = 20;
    const int xMin = 40, xMax = 760;
    const int folga   = 60;
    const int alcance = 110;

    struct Dados { int andar, x, largura; };
    list<Dados> feitas;
    list<Plataforma*> criadas;
    int maiorAndar = -1;

    for (int tentativa = 0; tentativa < 300 && static_cast<int>(criadas.size()) < quantidade; ++tentativa)
    {
        if (numObstaculos >= maxObstaculos)
            break;

        int andar   = sorteia(0, std::min(maiorAndar + 1, 2));
        int largura = sorteia(110, 200);
        int x       = sorteia(xMin, xMax - largura);
        int y       = andares[andar] + sorteia(-8, 8);

        bool ok = true;
        bool temApoio = (andar == 0);
        for (const Dados& d : feitas)
        {
            int vao = std::max(x - (d.x + d.largura), d.x - (x + largura));
            if (d.andar == andar && vao < folga)        { ok = false; break; }
            if (d.andar == andar - 1 && vao <= alcance) temApoio = true;
        }
        if (!ok || !temApoio)
            continue;

        Plataforma* p = new Plataforma(x, y, largura, espessura);
        criarPlataforma(x, y, largura, espessura, p);
        criadas.push_back(p);
        feitas.push_back({andar, x, largura});
        maiorAndar = std::max(maiorAndar, andar);
    }
    return criadas;
}

Jogador* Fase::getJogador() const { return pJogador; }
int Fase::getNumeroFase() const { return numeroFase; }
bool Fase::estaConcluida() const { return concluida; }

void Fase::salvar(const std::string& pasta)
{
    std::filesystem::create_directories(pasta);

    // 4. fase.txt (metadados da fase atual)
    std::ofstream arqFase(pasta + "fase.txt");
    if (arqFase.is_open())
    {
        arqFase << numeroFase << " " << concluida << "\n";
    }

    if (pFisica != nullptr)
        pFisica->salvarArquivos(pasta);
}

bool Fase::carregarArquivos(const std::string& pasta)
{
    std::ifstream arqJog(pasta + "jogador.txt");
    std::ifstream arqObs(pasta + "obstaculos.txt");
    std::ifstream arqIni(pasta + "inimigos.txt");

    if (!arqJog.is_open() || !arqObs.is_open() || !arqIni.is_open())
        return false;

    // Limpa o estado atual da fase antes de recriar tudo do arquivo
    listaEntidades.limpar();
    if (pFisica != nullptr)
        pFisica->destruirEntidades();

    numInimigos = 0;
    numObstaculos = 0;

    // 1. Carrega o Jogador (ordem salva em Jogador::salvar)
    if (pJogador != nullptr)
    {
        float jx, jy, vx, vy;
        int vidas, pontos;

        if (arqJog >> jx >> jy >> vidas >> pontos >> vx >> vy)
        {
            pJogador->setX(jx);
            pJogador->setY(jy);
            pJogador->setEstado(vx, vy, vidas, pontos);

            pFisica->getJogador(pJogador);
            listaEntidades.incluir(pJogador);
        }
    }

    // 2. Carrega os Obstáculos (limites da arena, plataformas, lamas e lavas)
    std::string tipo;
    while (arqObs >> tipo)
    {
        float ox, oy;
        bool dano;
        arqObs >> ox >> oy >> dano;

        if (tipo == "PLATAFORMA")
        {
            int larg, alt, dir;
            bool movel;
            float yBase, amp, vel;
            arqObs >> larg >> alt >> movel >> yBase >> amp >> vel >> dir;

            Plataforma* p = new Plataforma(static_cast<int>(ox), static_cast<int>(oy), larg, alt);
            if (movel)
                p->configurarMovel(movel, yBase, amp, vel, dir);

            pFisica->incluirObstaculo(p);
            listaEntidades.incluir(p);
        }
        else if (tipo == "LAMA")
        {
            float larg, alt;
            arqObs >> larg >> alt;

            Lama* l = new Lama();
            l->getForma()->setSize({larg, alt});
            l->setPosicao(ox, oy);

            pFisica->incluirObstaculo(l);
            listaEntidades.incluir(l);
        }
        else if (tipo == "LAVA")
        {
            int danoLava;
            float larg, alt;
            arqObs >> danoLava >> larg >> alt;

            Lava* lv = new Lava();
            lv->getForma()->setSize({larg, alt});
            lv->setPosicao(ox, oy);

            pFisica->incluirObstaculo(lv);
            listaEntidades.incluir(lv);
        }
    }

    // 3. Carrega os Inimigos e o estado de seus projéteis
    while (arqIni >> tipo)
    {
        float ix, iy;
        int vidas;
        arqIni >> ix >> iy >> vidas;

        if (tipo == "CAPANGA")
        {
            int dir;
            float limEsq, limDir;
            arqIni >> dir >> limEsq >> limDir;

            Capanga_Cogumelo* c = new Capanga_Cogumelo();
            c->setPosicao(ix, iy);
            c->setEstado(vidas, dir);
            c->definirLimitesPatrulha(limEsq, limDir);
            registrarInimigo(c);
        }
        else if (tipo == "BOITATA" || tipo == "PLANTA")
        {
            int contTempo, projDano;
            float px, py, pvx;
            bool projAtivo;
            arqIni >> contTempo >> px >> py >> pvx >> projDano >> projAtivo;

            if (tipo == "BOITATA")
            {
                Boitata* b = new Boitata();
                b->setPosicao(ix, iy);
                b->setEstado(vidas, contTempo);
                b->definirAlvo(pJogador);
                b->getProjetil()->restaurar(px, py, pvx, projAtivo);

                registrarInimigo(b);
                pFisica->incluirProjetil(b->getProjetil());
            }
            else
            {
                Planta_Acida* pl = new Planta_Acida();
                pl->setPosicao(ix, iy);
                pl->setEstado(vidas, contTempo);
                pl->definirAlvo(pJogador);
                pl->getProjetil()->restaurar(px, py, pvx, projAtivo);

                registrarInimigo(pl);
                pFisica->incluirProjetil(pl->getProjetil());
            }
        }
    }

    return true;
}

void Fase::tornarPlataformasMoveis(const list<Plataforma*>& plats,
                                   const list<Plataforma*>& fixas)
{
    const float alturaHeroi = (pJogador != nullptr)
        ? pJogador->getForma()->getSize().y : 40.f;
    const float folgaMinima = alturaHeroi + 15.f;
    const float amplitudeMax = 40.f;

    for (Plataforma* p : plats)
    {
        if (std::find(fixas.begin(), fixas.end(), p) != fixas.end())
            continue;

        sf::FloatRect a = p->getForma()->getGlobalBounds();
        float baixoAcima = 20.f;  // teto da arena
        float topoAbaixo = 560.f; // chão da arena

        for (Obstaculo* o : pFisica->getObstaculos())
        {
            if (o == nullptr || o == p) continue;

            sf::FloatRect b = o->getForma()->getGlobalBounds();
            bool sobrepoeX = a.position.x < b.position.x + b.size.x &&
                             b.position.x < a.position.x + a.size.x;
            if (!sobrepoeX) continue;

            float baixoObs = b.position.y + b.size.y;
            float basePlat = a.position.y + a.size.y;

            // Obstáculo acima da plataforma
            if (baixoObs <= a.position.y)
                baixoAcima = std::max(baixoAcima, baixoObs);

            // Obstáculo abaixo da plataforma (pega Lava no chão em y = 548 ou outra plataforma)
            if (b.position.y >= basePlat)
                topoAbaixo = std::min(topoAbaixo, b.position.y);
        }

        float folgaAcima  = (a.position.y - baixoAcima) - folgaMinima;
        float folgaAbaixo = (topoAbaixo - (a.position.y + a.size.y)) - 10.f; // 10px de margem antes da lava/chão

        float amplitude = std::min({ amplitudeMax, folgaAcima, folgaAbaixo });
        if (amplitude < 15.f)
            continue;

        float velocidade = sortear(5, 12) / 10.f;
        p->tornarMovel(amplitude, velocidade);
    }
}
