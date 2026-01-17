#ifndef DIPENDENTE_H
#define DIPENDENTE_H

#include <string>

class Dipendente {
private:
    std::string matricola;
    std::string nome;
    std::string cognome;
    double stipendio;

public:
    Dipendente(const std::string& matricola,
               const std::string& nome,
               const std::string& cognome,
               double stipendio);

    virtual ~Dipendente() = default;

    std::string getMatricola() const;
    std::string getNome() const;
    std::string getCognome() const;
    double getStipendio() const;

    virtual std::string getTipo() const = 0;
};

#endif
