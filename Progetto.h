#ifndef PROGETTO_H
#define PROGETTO_H

#include <string>
#include <vector>

class Senior;  // Forward declaration

class Progetto {
private:
    std::string nome;
    std::string dataInizio;  // Format: "YYYY/MM/DD"
    int durata;              // Duration in months
    double budget;
    Senior* responsabile;    // Non-owning pointer

public:
    Progetto(const std::string& nome,
             const std::string& dataInizio,
             int durata,
             double budget,
             Senior* responsabile);
    
    // Getters
    std::string getNome() const;
    std::string getDataInizio() const;
    int getDurata() const;
    double getBudget() const;
    Senior* getResponsabile() const;
};

#endif
