#pragma once

#include "Ente.h"
#include "stdafx.h"

class Menu : public Ente {
private:
    std::string titulo;
    std::vector<std::string> opcoes;
    int opcaoSelecionada;
    int numeroOpcoes;

    bool teclaCimaAnterior;
    bool teclaBaixoAnterior;
    bool teclaEnterAnterior;
    bool opcaoConfirmada;

public:
    Menu();
    virtual ~Menu();

    void configurar(const std::string& novoTitulo, const std::vector<std::string>& novasOpcoes);
    void resetarEstado();

    void executar() override;
    void executar(int comando);
    void desenhar();

    int getOpcaoSelecionada() const;
    bool foiConfirmado() const;
    void resetarConfirmacao();

    void imprimirMenu();
};
