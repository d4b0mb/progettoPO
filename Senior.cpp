#include "Senior.h"
#include "Junior.h"

Senior::Senior(const std::string& matricola,
               const std::string& nome,
               const std::string& cognome,
               double stipendio,
               const std::vector<std::string>& reperibilita)
    : Dipendente(matricola, nome, cognome, stipendio),
      reperibilita(reperibilita) {
}

const std::vector<std::string>& Senior::getReperibilita() const {
    return reperibilita;
}

const std::vector<Junior*>& Senior::getSubordinati() const {
    return subordinati;
}

void Senior::addSubordinato(Junior* j) {
    subordinati.push_back(j);
}

std::string Senior::getTipo() const {
    return "Senior";
}
