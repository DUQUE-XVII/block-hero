#include    "Fase.h"
#include    "Boitata.h"
#include    "Planta_Acida.h"
#include    "Lama.h"
#include    "Lava.h"

Fase::Fase(int num, Jogador* jogador,int limiteInimigos, int limiteObstaculos)
    : numeroFase(num),
      concluida(false),
      maxInimigos(limiteInimigos),
      maxObstaculos(limiteObstaculos),
      pJogador(jogador)
{
    pFisica = new Gerenciador_CL();
}

Fase::~Fase() {
    delete pFisica;
    pFisica = nullptr;

    for (CriaturaHostil* inimigo : listaInimigos) {
        delete inimigo;
    }
    listaInimigos.clear();

    for (Obstaculo* plat : listaPlataformas) {
        delete plat;
    }
    listaPlataformas.clear();
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
    // Mesmas bordas usadas originalmente em Jogo.cpp (janela 800x600)
    Plataforma* chao = new Plataforma(0, 560, 800, 40);
    Plataforma* teto = new Plataforma(0, 0, 800, 20);
    Plataforma* paredeEsquerda = new Plataforma(0, 0, 20, 600);
    Plataforma* paredeDireita = new Plataforma(780, 0, 20, 600);

    listaPlataformas.push_back(chao);
    listaPlataformas.push_back(teto);
    listaPlataformas.push_back(paredeEsquerda);
    listaPlataformas.push_back(paredeDireita);

    for (Obstaculo* p : listaPlataformas) {
        pFisica->incluirObstaculo(p);
        listaEntidades.incluir(p);
    }
}

void Fase::desenhar() {
    if (pJogador != nullptr && pJogador->estaVivo()) {
        pJogador->desenhar();
    }

    for (CriaturaHostil* inimigo : listaInimigos) {
        if (inimigo != nullptr && inimigo->estaVivo()) {
            inimigo->desenhar();
        }
    }

    for (Obstaculo* plat : listaPlataformas) {
        if (plat != nullptr) {
            plat->desenhar();
        }
    }

    if (pGG != nullptr && pJogador != nullptr) {
        pGG->desenharTexto("Pontos: " + std::to_string(pJogador->getPontos()),
                           30.f, 28.f);
    }
}
void Fase::criarCapanga(float x, float y)
{
     Capanga_Cogumelo* capanga = new Capanga_Cogumelo();

    capanga->setPosicao(x, y);

    if (!registrarInimigo(capanga))
        delete capanga;
}
void Fase::criarPlataforma(float x, float y, int largura, int altura,
    Obstaculo* plataforma)
{
    // Os quatro limites da arena não contam como obstáculos adicionais.
    if (listaPlataformas.size() - 4 >= maxObstaculos)
        return;

     plataforma->getForma()->setSize({
        static_cast<float>(largura),
        static_cast<float>(altura)
    });
    plataforma->getForma()->setPosition({
        static_cast<float>(x),
        static_cast<float>(y)
    });


    listaPlataformas.push_back(plataforma);

    pFisica->incluirObstaculo(plataforma);

    listaEntidades.incluir(plataforma);
}

vector<Plataforma*> Fase::gerarPlataformasAleatorias(int quantidade)
{
    auto sorteia = [&](int a, int b) { return sortear(a, b); };


    const int andares[3] = {440, 330, 220}; // topo de cada andar
    const int espessura  = 20;
    const int xMin = 40, xMax = 760;        // dentro das paredes (20..780)
    const int folga   = 60;                 // vão mínimo no mesmo andar
    const int alcance = 110;                // distância máx. para subir de andar

    struct Dados { int andar, x, largura; };
    vector<Dados> feitas;
    vector<Plataforma*> criadas;
    int maiorAndar = -1;

    for (int tentativa = 0; tentativa < 300 && (int)criadas.size() < quantidade; ++tentativa)
    {
        // Respeita o limite de obstáculos (os 4 primeiros são as bordas da arena)
        if (static_cast<int>(listaPlataformas.size()) - 4 >= maxObstaculos)
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
            if (d.andar == andar && vao < folga)           { ok = false; break; }
            if (d.andar == andar - 1 && vao <= alcance)    temApoio = true;
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

bool Fase::registrarInimigo(CriaturaHostil* inimigo)
{
    if (inimigo == nullptr || listaInimigos.size() >= maxInimigos)
        return false;

    listaInimigos.push_back(inimigo);
    pFisica->incluirInimigos(inimigo);
    listaEntidades.incluir(inimigo);

    return true;
}

Jogador* Fase::getJogador() const { return pJogador; }

int Fase::getNumeroFase() const { return numeroFase; }

bool Fase::estaConcluida() const { return concluida; }
void Fase::salvar(std::ostream& arquivo)
{
    arquivo << "FASE " << numeroFase << "\n";
    arquivo << "CONCLUIDA " << concluida << "\n";

    // Salvar jogador
    if (pJogador != nullptr)
    {
        pJogador->salvar();
        arquivo << "JOGADOR " << pJogador->getDadosSalvos() << "\n";
    }

    // Quantidade de obstáculos
    arquivo << "OBSTACULOS " << listaPlataformas.size() << "\n";

    for (Obstaculo* obstaculo : listaPlataformas)
    {
        if (obstaculo == nullptr)
            continue;

        obstaculo->salvar();

        if (dynamic_cast<Lava*>(obstaculo))
            arquivo << "LAVA ";
        else if (dynamic_cast<Lama*>(obstaculo))
            arquivo << "LAMA ";
        else if (dynamic_cast<Plataforma*>(obstaculo))
            arquivo << "PLATAFORMA ";

        arquivo << obstaculo->getDadosSalvos() << "\n";
    }

    // Quantidade de inimigos
    arquivo << "INIMIGOS " << listaInimigos.size() << "\n";

    for (CriaturaHostil* inimigo : listaInimigos)
    {
        if (inimigo == nullptr)
            continue;

        inimigo->salvar();

        if (dynamic_cast<Capanga_Cogumelo*>(inimigo))
            arquivo << "CAPANGA ";
        else if (dynamic_cast<Boitata*>(inimigo))
            arquivo << "BOITATA ";
        else if (dynamic_cast<Planta_Acida*>(inimigo))
            arquivo << "PLANTA ";

        arquivo << inimigo->getDadosSalvos() << "\n";
    }
}

vector<CriaturaHostil*> Fase::getInimigos() const { return listaInimigos; }
