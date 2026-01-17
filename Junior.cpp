#include "Junior.h"

Junior::Junior(const std::string& matricola,
               const std::string& nome,
               const std::string& cognome,
               double stipendio,
               const std::vector<std::string>& skills,
               Junior* stagista)
    : Dipendente(matricola, nome, cognome, stipendio),
      skills(skills), stagista(stagista) {
}

const std::vector<std::string>& Junior::getSkills() const {
    return skills;
}

Junior* Junior::getStagista() const {
    return stagista;
}

void Junior::setStagista(Junior* j) {
    stagista = j;
}

std::string Junior::getTipo() const {
    return "Junior";
}
