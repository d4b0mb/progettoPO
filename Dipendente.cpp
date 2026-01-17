#include "Dipendente.h"

Dipendente::Dipendente(const std::string& matricola,
                       const std::string& nome,
                       const std::string& cognome,
                       double stipendio)
    : matricola(matricola), nome(nome), cognome(cognome), stipendio(stipendio) {
}

std::string Dipendente::getMatricola() const {
    return matricola;
}

std::string Dipendente::getNome() const {
    return nome;
}

std::string Dipendente::getCognome() const {
    return cognome;
}

double Dipendente::getStipendio() const {
    return stipendio;
}
