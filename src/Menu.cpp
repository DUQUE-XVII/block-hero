#include "Menu.h"

Menu::Menu()
    : titulo("BLOCK HERO"),
      opcaoSelecionada(0),
      teclaCimaAnterior(false),
      teclaBaixoAnterior(false),
      teclaEnterAnterior(true),
      opcaoConfirmada(false)
{
    opcoes = {
        "Fase 1 - Floresta",
        "Fase 2 - Caverna do Boitata",
        "Carregar Jogo",
        "Ranking",
        "Sair"
    };
    numeroOpcoes = static_cast<int>(opcoes.size());
}

Menu::~Menu()
{
}

void Menu::configurar(const std::string& novoTitulo, const std::vector<std::string>& novasOpcoes)
{
    titulo = novoTitulo;
    opcoes = novasOpcoes;
    numeroOpcoes = static_cast<int>(opcoes.size());
    resetarEstado();
}

void Menu::resetarEstado()
{
    opcaoSelecionada = 0;
    opcaoConfirmada = false;
    teclaCimaAnterior = true;
    teclaBaixoAnterior = true;
    teclaEnterAnterior = true;
}

void Menu::executar(int comando)
{
    if (comando == 1) // Cima
    {
        opcaoSelecionada--;
        if (opcaoSelecionada < 0)
            opcaoSelecionada = numeroOpcoes - 1;
    }
    else if (comando == 2) // Baixo
    {
        opcaoSelecionada++;
        if (opcaoSelecionada >= numeroOpcoes)
            opcaoSelecionada = 0;
    }
}

void Menu::executar()
{
    bool cima  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool baixo = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);

    if (cima && !teclaCimaAnterior)
        executar(1);

    if (baixo && !teclaBaixoAnterior)
        executar(2);

    if (enter && !teclaEnterAnterior)
        opcaoConfirmada = true;

    teclaCimaAnterior  = cima;
    teclaBaixoAnterior = baixo;
    teclaEnterAnterior = enter;
}

void Menu::desenhar()
{
    if (pGG == nullptr)
        return;

    pGG->desenharTexto(titulo, 270.f, 90.f, 40);

    for (int i = 0; i < numeroOpcoes; ++i)
    {
        std::string linha = (i == opcaoSelecionada)
            ? "> " + opcoes[i]
            : "  " + opcoes[i];

        pGG->desenharTexto(linha, 230.f, 220.f + i * 55.f, 26);
    }

    pGG->desenharTexto("Use Setas (Cima/Baixo) e ENTER", 215.f, 520.f, 18);
}

int Menu::getOpcaoSelecionada() const
{
    return opcaoSelecionada;
}

bool Menu::foiConfirmado() const
{
    return opcaoConfirmada;
}

void Menu::resetarConfirmacao()
{
    opcaoConfirmada = false;
}

void Menu::imprimirMenu()
{
    std::cout << "\n=== " << titulo << " ===\n";
    for (int i = 0; i < numeroOpcoes; ++i)
    {
        if (i == opcaoSelecionada)
            std::cout << " > " << opcoes[i] << "\n";
        else
            std::cout << "   " << opcoes[i] << "\n";
    }
}
