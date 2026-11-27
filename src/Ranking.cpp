#include "Ranking.h"
#include <filesystem>

Ranking::Ranking(const std::string& arquivo)
    : caminhoArquivo(arquivo)
{
    carregarArquivo();
}

void Ranking::carregarArquivo()
{
    registros.clear();
    std::ifstream arq(caminhoArquivo);
    if (!arq.is_open())
        return;

    std::string nome;
    int pontos;
    while (arq >> nome >> pontos)
    {
        registros.push_back({nome, pontos});
    }

    std::sort(registros.begin(), registros.end(),
              [](const Registro& a, const Registro& b) { return a.pontos > b.pontos; });
}

void Ranking::salvarArquivo() const
{
    std::filesystem::create_directories("saves");
    std::ofstream arq(caminhoArquivo);
    if (!arq.is_open())
        return;

    for (const auto& r : registros)
        arq << r.nome << " " << r.pontos << "\n";
}

void Ranking::adicionarPontuacao(const std::string& nome, int pontos)
{
    if (pontos <= 0)
        return;

    carregarArquivo();
    registros.push_back({nome.empty() ? "Heroi" : nome, pontos});

    std::sort(registros.begin(), registros.end(),
              [](const Registro& a, const Registro& b) { return a.pontos > b.pontos; });

    if (registros.size() > 5)
        registros.resize(5);

    salvarArquivo();
}

void Ranking::desenhar(GerenciadorGrafico& pGG) const
{
    pGG.desenharTexto("RANKING - TOP 5", 265.f, 90.f, 34);

    if (registros.empty())
    {
        pGG.desenharTexto("Nenhuma pontuacao registrada ainda.", 210.f, 250.f, 22);
    }
    else
    {
        for (size_t i = 0; i < registros.size(); ++i)
        {
            std::string linha = std::to_string(i + 1) + ". "
                              + registros[i].nome + " - "
                              + std::to_string(registros[i].pontos) + " pts";

            pGG.desenharTexto(linha, 240.f, 190.f + i * 50.f, 24);
        }
    }

    pGG.desenharTexto("Pressione ESC para voltar", 255.f, 510.f, 20);
}
