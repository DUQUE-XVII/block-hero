#pragma once

#include    "Ente.h"


class Entidade : public Ente {

    protected:
        float x;
        float y;
        ostringstream Salvamento;

        void salvarDataBuffer();

    public:
        Entidade();
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void salvar() = 0;
};
