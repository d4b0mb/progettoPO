#include "Progetto.h"
#include "Senior.h"

Progetto::Progetto(const std::string& nome,
                   const std::string& dataInizio,
                   int durata,
                   double budget,
                   Senior* responsabile)
    : nome(nome), dataInizio(dataInizio), durata(durata), 
      budget(budget), responsabile(responsabile) {
}

std::string Progetto::getNome() const {
    return nome;
}

std::string Progetto::getDataInizio() const {
    return dataInizio;
}

int Progetto::getDurata() const {
    return durata;
}

double Progetto::getBudget() const {
    return budget;
}

Senior* Progetto::getResponsabile() const {
    return responsabile;
}
