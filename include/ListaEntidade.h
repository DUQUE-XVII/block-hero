#pragma once

#include "Lista.h"
#include "Entidade.h"

class ListaEntidades
{
private:

    Lista<Entidade*> LEs;

public:

    ListaEntidades() = default;

    ~ListaEntidades() = default;

    ListaEntidades(const ListaEntidades&) = delete;

    ListaEntidades& operator=(const ListaEntidades&) = delete;

    void incluir(Entidade* p)
    {
        if(p != nullptr)
            LEs.incluir(p);
    }

    void percorrer()
    {
        LEs.percorrer([](Entidade* p)
        {
            if(p != nullptr)
                p->executar();
        });
    }

    void limpar()
    {
        LEs.limpar();
    }

    bool vazia() const
    {
        return LEs.vazia();
    }
};
