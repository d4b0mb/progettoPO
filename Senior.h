#ifndef SENIOR_H
#define SENIOR_H

#include "Dipendente.h"
#include <string>
#include <vector>

class Junior;  // Forward declaration

class Senior : public Dipendente {
private:
    std::vector<std::string> reperibilita;
    std::vector<Junior*> subordinati;

public:
    Senior(const std::string& matricola, 
           const std::string& nome, 
           const std::string& cognome, 
           double stipendio,
           const std::vector<std::string>& reperibilita);

    // Getters
    const std::vector<std::string>& getReperibilita() const;
    const std::vector<Junior*>& getSubordinati() const;

    // Modifiers
    void addSubordinato(Junior* j);

    // Override
    std::string getTipo() const override;
};

#endif
