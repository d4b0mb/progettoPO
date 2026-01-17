#include "Gestore.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Helper function to split a string by delimiter
vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

// A6: Read from file
void leggiDaFile(Gestore& g, const string& filename) {
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        vector<string> parts = split(line, ';');
        string tipo = parts[0];
        
        if (tipo == "DJ") {
            // DJ;matricola;nome;cognome;stipendio;skill1,skill2,...;matricola_stagista
            string matricola = parts[1];
            string nome = parts[2];
            string cognome = parts[3];
            double stipendio = stod(parts[4]);
            
            vector<string> skillVec = split(parts[5], ',');
            list<string> skills(skillVec.begin(), skillVec.end());
            
            string stagista = "";
            if (parts.size() > 6 && !parts[6].empty()) {
                stagista = parts[6];
            }
            
            g.aggiungiDipendenteJunior(matricola, nome, cognome, stipendio, skills, stagista);
        }
        else if (tipo == "DS") {
            // DS;matricola;nome;cognome;stipendio;rep1,rep2,...;sub1,sub2,...
            string matricola = parts[1];
            string nome = parts[2];
            string cognome = parts[3];
            double stipendio = stod(parts[4]);
            
            vector<string> repVec = split(parts[5], ',');
            list<string> reperibilita(repVec.begin(), repVec.end());
            
            list<string> subordinati;
            if (parts.size() > 6 && !parts[6].empty()) {
                vector<string> subVec = split(parts[6], ',');
                subordinati = list<string>(subVec.begin(), subVec.end());
            }
            
            g.aggiungiDipendenteSenior(matricola, nome, cognome, stipendio, reperibilita, subordinati);
        }
        else if (tipo == "P") {
            // P;nome;data;durata;budget;matricola_responsabile
            string nome = parts[1];
            string data = parts[2];
            int durata = stoi(parts[3]);
            double budget = stod(parts[4]);
            string responsabile = parts[5];
            
            g.aggiungiProgetto(nome, data, durata, budget, responsabile);
        }
    }
}

int main() {
    Gestore g;
    
    cout << "=== Test Gestore ===" << endl;
    
    // Add some test data manually
    list<string> skills1 = {"cpp", "java", "python"};
    list<string> skills2 = {"cpp", "rust"};
    list<string> skills3 = {"java", "go"};
    
    g.aggiungiDipendenteJunior("J001", "Mario", "Rossi", 2500.0, skills1, "");
    g.aggiungiDipendenteJunior("J002", "Luigi", "Verdi", 2200.0, skills2, "J001");
    g.aggiungiDipendenteJunior("J003", "Anna", "Bianchi", 2800.0, skills3, "");
    
    list<string> rep1 = {"lun", "mar", "mer"};
    list<string> sub1 = {"J001", "J002"};
    g.aggiungiDipendenteSenior("S001", "Giuseppe", "Neri", 5000.0, rep1, sub1);
    
    list<string> rep2 = {"gio", "ven", "sab", "dom"};
    list<string> sub2 = {"J003"};
    g.aggiungiDipendenteSenior("S002", "Carla", "Gialli", 5500.0, rep2, sub2);
    
    g.aggiungiProgetto("Progetto1", "2024/01/15", 6, 50000.0, "S001");
    g.aggiungiProgetto("Progetto2", "2024/06/01", 12, 80000.0, "S002");
    
    // A4: Test getDipendenti
    cout << "\n--- A4: Tutti i dipendenti ---" << endl;
    vector<Dipendente*> dipendenti = g.getDipendenti();
    for (Dipendente* d : dipendenti) {
        cout << d->getTipo() << ": " << d->getMatricola() << " - " 
             << d->getNome() << " " << d->getCognome() << endl;
    }
    
    // A5: Test getProgetti
    cout << "\n--- A5: Tutti i progetti ---" << endl;
    vector<Progetto*> progetti = g.getProgetti();
    for (Progetto* p : progetti) {
        cout << p->getNome() << " - Budget: " << p->getBudget() 
             << " - Resp: " << (p->getResponsabile() ? p->getResponsabile()->getMatricola() : "N/A") << endl;
    }
    
    // B1: Projects of a senior
    cout << "\n--- B1: Progetti di S001 ---" << endl;
    vector<Progetto*> b1Result = g.b1("S001");
    for (Progetto* p : b1Result) {
        cout << p->getNome() << endl;
    }
    
    // B3: Skills in project
    cout << "\n--- B3: Skills in Progetto1 ---" << endl;
    vector<string> b3Result = g.b3("Progetto1");
    for (const string& s : b3Result) {
        cout << s << " ";
    }
    cout << endl;
    
    // B5: Top 5 skills
    cout << "\n--- B5: Top 5 skills ---" << endl;
    vector<string> b5Result = g.b5();
    for (const string& s : b5Result) {
        cout << s << " ";
    }
    cout << endl;
    
    // C5: Optimal pairs
    cout << "\n--- C5: Coppie ottimali ---" << endl;
    auto c5Result = g.c5();
    for (const auto& pair : c5Result) {
        cout << pair.first->getMatricola() << " + " << pair.second->getMatricola() << endl;
    }
    
    cout << "\n=== Test completato ===" << endl;
    
    return 0;
}
