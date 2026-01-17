#include "Gestore.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

void leggiDaFile(Gestore& g, const string& filename) {
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        vector<string> parts = split(line, ';');
        string tipo = parts[0];
        
        if (tipo == "DJ") {
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
    
    cout << "=== Loading file1.txt ===" << endl;
    leggiDaFile(g, "file1.txt");
    
    vector<Dipendente*> dip = g.getDipendenti();
    vector<Progetto*> prj = g.getProgetti();
    
    cout << "Loaded " << dip.size() << " dipendenti" << endl;
    cout << "Loaded " << prj.size() << " progetti" << endl;
    
    // Count juniors and seniors
    int juniors = 0, seniors = 0;
    for (Dipendente* d : dip) {
        if (d->getTipo() == "Junior") juniors++;
        else seniors++;
    }
    cout << "  - " << juniors << " juniors" << endl;
    cout << "  - " << seniors << " seniors" << endl;
    
    // Test B10: sorted by budget ascending
    cout << "\n--- B10: First 5 projects by budget (asc) ---" << endl;
    vector<Progetto*> b10 = g.b10();
    for (int i = 0; i < 5 && i < (int)b10.size(); i++) {
        cout << b10[i]->getNome() << ": " << b10[i]->getBudget() << endl;
    }
    
    // Test B5: top 5 skills
    cout << "\n--- B5: Top 5 skills ---" << endl;
    vector<string> b5 = g.b5();
    for (const string& s : b5) {
        cout << s << " ";
    }
    cout << endl;
    
    // Test B1: projects of matr50
    cout << "\n--- B1: Projects where matr50 is responsible ---" << endl;
    vector<Progetto*> b1 = g.b1("matr50");
    for (Progetto* p : b1) {
        cout << p->getNome() << " - Budget: " << p->getBudget() << endl;
    }
    
    // Test C2: indispensable seniors
    cout << "\n--- C2: Indispensable seniors ---" << endl;
    vector<Dipendente*> c2 = g.c2();
    cout << "Found " << c2.size() << " indispensable seniors" << endl;
    for (int i = 0; i < 5 && i < (int)c2.size(); i++) {
        cout << c2[i]->getMatricola() << " - " << c2[i]->getNome() << endl;
    }
    
    cout << "\n=== Test completato ===" << endl;
    return 0;
}
