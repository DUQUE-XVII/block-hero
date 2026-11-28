#include "Jogo.h"

Jogo::Jogo()
    : faseAtual(nullptr),
      estadoAtual(Estado::MENU),
      teclaSalvarAnterior(false),
      teclaEscAnterior(false),
      mensagemPausa("")
{
    Ente::setGG(&pGG);

    menuPausa.configurar("JOGO PAUSADO", {
        "Continuar",
        "Salvar Jogo",
        "Voltar ao Menu Principal"
    });
}

Jogo::~Jogo()
{
    delete faseAtual;
    faseAtual = nullptr;
}

void Jogo::iniciarFaseEscolhida(int opcao)
{
    delete faseAtual;
    faseAtual = nullptr;

    pJog1.reiniciar();

    if (opcao == 0)
        faseAtual = new Fase_Forest(&pJog1);
    else if (opcao == 1)
        faseAtual = new Fase_Boss(&pJog1);

    if (faseAtual != nullptr)
    {
        faseAtual->iniciarFase();
        estadoAtual = Estado::JOGANDO;
    }
}

void Jogo::carregarJogoSalvo()
{
    std::ifstream arqFase("saves/fase.txt");
    int numFase = 0;
    bool concluida = false;

    if (!(arqFase >> numFase >> concluida))
    {
        std::cout << "[JOGO] Nenhum jogo salvo encontrado.\n";
        return;
    }

    delete faseAtual;
    faseAtual = nullptr;
    pJog1.reiniciar();

    if (numFase == 1)
        faseAtual = new Fase_Forest(&pJog1);
    else if (numFase == 2)
        faseAtual = new Fase_Boss(&pJog1);

    if (faseAtual != nullptr)
    {
        faseAtual->carregar();
        estadoAtual = Estado::JOGANDO;
    }
}

void Jogo::executar()
{
    while (pGG.getJanela().isOpen())
    {
        while (const auto evento = pGG.getJanela().pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
                pGG.getJanela().close();
        }

        // Controle de borda da tecla ESC para não alternar estados várias vezes seguidas
        bool teclaEsc = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
        bool escPressionado = (teclaEsc && !teclaEscAnterior);
        teclaEscAnterior = teclaEsc;

        pGG.getJanela().clear(sf::Color::Black);

        if (estadoAtual == Estado::MENU)
        {
            menu.executar();
            menu.desenhar();

            if (menu.foiConfirmado())
            {
                int opcao = menu.getOpcaoSelecionada();
                menu.resetarConfirmacao();

                if (opcao == 0 || opcao == 1)
                {
                    iniciarFaseEscolhida(opcao);
                }
                else if (opcao == 2)
                {
                    carregarJogoSalvo();
                }
                else if (opcao == 3)
                {
                    estadoAtual = Estado::RANKING;
                }
                else if (opcao == 4)
                {
                    pGG.getJanela().close();
                }
            }
        }
        else if (estadoAtual == Estado::RANKING)
        {
            ranking.desenhar(pGG);

            if (escPressionado)
                estadoAtual = Estado::MENU;
        }
        else if (estadoAtual == Estado::JOGANDO)
        {
            if (escPressionado)
            {
                mensagemPausa.clear();
                menuPausa.resetarEstado();
                estadoAtual = Estado::PAUSADO;
            }
            else if (faseAtual != nullptr)
            {
                faseAtual->executar();

                // 1. Se o jogador morreu, salva a pontuação e volta ao Menu
                if (!pJog1.estaVivo())
                {
                    ranking.adicionarPontuacao("Heroi", pJog1.getPontos());
                    delete faseAtual;
                    faseAtual = nullptr;
                    menu.resetarEstado();
                    estadoAtual = Estado::MENU;
                }
                // 2. Se concluiu a fase
                else if (faseAtual->estaConcluida())
                {
                    if (faseAtual->getNumeroFase() == 1)
                    {
                        delete faseAtual;
                        faseAtual = new Fase_Boss(&pJog1);
                        faseAtual->iniciarFase();
                    }
                    else
                    {
                        ranking.adicionarPontuacao("Heroi", pJog1.getPontos());
                        relogioVitoria.restart();
                        estadoAtual = Estado::VITORIA;
                    }
                }
            }
        }
        else if (estadoAtual == Estado::PAUSADO)
        {
            // Mantém a fase congelada desenhada ao fundo
            if (faseAtual != nullptr)
                faseAtual->desenhar();

            // Fundo escuro semitransparente por cima da fase
            sf::RectangleShape fundoPausa({800.f, 600.f});
            fundoPausa.setFillColor(sf::Color(0, 0, 0, 175));
            pGG.getJanela().draw(fundoPausa);

            // Apertar ESC novamente volta direto para o jogo
            if (escPressionado)
            {
                estadoAtual = Estado::JOGANDO;
            }
            else
            {
                menuPausa.executar();
                menuPausa.desenhar();

                if (!mensagemPausa.empty())
                    pGG.desenharTexto(mensagemPausa, 260.f, 430.f, 22);

                if (menuPausa.foiConfirmado())
                {
                    int opcao = menuPausa.getOpcaoSelecionada();
                    menuPausa.resetarConfirmacao();

                    if (opcao == 0) // Continuar
                    {
                        estadoAtual = Estado::JOGANDO;
                    }
                    else if (opcao == 1) // Salvar Jogo
                    {
                        if (faseAtual != nullptr)
                        {
                            faseAtual->salvar();
                            mensagemPausa = "Jogo salvo com sucesso!";
                        }
                    }
                    else if (opcao == 2) // Voltar ao Menu Principal
                    {
                        delete faseAtual;
                        faseAtual = nullptr;
                        menu.resetarEstado();
                        estadoAtual = Estado::MENU;
                    }
                }
            }
        }
        else if (estadoAtual == Estado::VITORIA)
        {
            float tempoDecorrido = relogioVitoria.getElapsedTime().asSeconds();
            int segundosRestantes = std::max(0, 10 - static_cast<int>(tempoDecorrido));

            // Mantém a arena congelada ao fundo mostrando que o último Boitatá morreu
            if (faseAtual != nullptr)
                faseAtual->desenhar();

            sf::RectangleShape fundoVitoria({800.f, 600.f});
            fundoVitoria.setFillColor(sf::Color(0, 0, 0, 175));
            pGG.getJanela().draw(fundoVitoria);

            pGG.desenharTexto("VITORIA! ULTIMO BOITATA DERROTADO!", 145.f, 210.f, 28);
            pGG.desenharTexto("Pontuacao Final: " + std::to_string(pJog1.getPontos()), 265.f, 275.f, 24);
            pGG.desenharTexto("Voltando ao menu em " + std::to_string(segundosRestantes) + "s...", 255.f, 340.f, 20);

            if (tempoDecorrido >= 10.0f)
            {
                delete faseAtual;
                faseAtual = nullptr;
                menu.resetarEstado();
                estadoAtual = Estado::MENU;
            }
        }

        pGG.getJanela().display();
    }
}
