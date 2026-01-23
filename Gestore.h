#ifndef GESTORE_H
#define GESTORE_H

#include "Junior.h"
#include "Senior.h"
#include "Progetto.h"
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;

class Gestore {
public:
    // Destructor - clean up dynamic memory
    ~Gestore();
    
    // SEZIONE A
    void aggiungiDipendenteSenior(string matricola, string nome, string cognome, 
                                  double stipendio, const list<string>& reperibilita, 
                                  const list<string>& subordinati);
    
    void aggiungiDipendenteJunior(string matricola, string nome, string cognome, 
                                  double stipendio, const list<string>& skill, 
                                  string stagista);

    void aggiungiProgetto(string nome, string data, int durata, 
                         double budget, string responsabile);
    
    vector<Dipendente*> getDipendenti() const;
    vector<Progetto*> getProgetti() const;
    
    // SEZIONE B
    vector<Progetto*> b1(string matricola) const;
    vector<Progetto*> b2(string matricola) const;
    vector<string> b3(string nomeProgetto) const;
    vector<string> b4() const;
    vector<string> b5() const;
    vector<Progetto*> b6() const;
    vector<Progetto*> b7(string matricola) const;
    vector<Progetto*> b8(string matricola) const;
    double b9(string matricola) const;
    vector<Progetto*> b10() const;
    vector<Progetto*> b11() const;
    vector<Progetto*> b12() const;
    vector<Progetto*> b13() const;
    vector<Progetto*> b14() const;
    
    // SEZIONE C
    vector<string> c1() const;
    vector<Dipendente*> c2() const;
    vector<Dipendente*> c3(string matricola) const;
    vector<Progetto*> c4(string nomeProgetto) const;
    vector<pair<Dipendente*, Dipendente*>> c5() const;
    
private:
    vector<Junior*> juniors;
    vector<Senior*> seniors;
    vector<Progetto*> progetti;
    
    map<string, Junior*> juniorMap;
    map<string, Senior*> seniorMap;
    map<string, Progetto*> progettoMap;
};

#endif
