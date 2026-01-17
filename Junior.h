#ifndef JUNIOR_H
#define JUNIOR_H

#include "Dipendente.h"
#include <vector>
#include <string>

class Junior : public Dipendente {
private:
    std::vector<std::string> skills;
    Junior* stagista;  // Non-owning pointer

public:
    Junior(const std::string& matricola,
           const std::string& nome,
           const std::string& cognome,
           double stipendio,
           const std::vector<std::string>& skills,
           Junior* stagista = nullptr);

    // Getters
    const std::vector<std::string>& getSkills() const;
    Junior* getStagista() const;

    // Modifiers
    void setStagista(Junior* j);

    // Override
    std::string getTipo() const override;
};

#endif
