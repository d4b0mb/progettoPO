#include <iostream>
#include <ctime>
#include <vector>
#include <unordered_set>
using namespace std;

char alfabeto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','y','w','z'};
vector<string> nomi = {"Agostino", "Alberto", "Alessandro", "Alessio", "Alfio", "Alfonso", "Amedeo", "Angelo", "Antonio", "Aurelio", "Baldassarre", "Baldo", "Bastiano", "Bartolo", "Bartolomeo", "Benito", "Bernardo", "Biagio", "Boris", "Bruno", "Calogero", "Carlo", "Carmelo", "Casimiro", "Cesare", "Cirillo", "Ciro", "Claudio", "Corrado", "Cosimo", "Daniele", "Danilo", "Dante", "Dario", "Davide", "Diego", "Dino", "Dionisio", "Domenico", "Duccio", "Egidio", "Elio", "Eliseo", "Emanuele", "Emiliano", "Emilio", "Ennio", "Enrico", "Enzo", "Ezio", "Fabiano", "Fabio", "Fabrizio", "Fausto", "Fedele", "Felice", "Filippo", "Flavio", "Fortunato", "Francesco", "Gabriele", "Gaetano", "Gaspare", "Gennaro", "Gerlando", "Giacomo", "Giancarlo", "Giovanni", "Giulio", "Giuseppe", "Iacopo", "Ignazio", "Igor", "Isacco", "Isaia", "Iside", "Isidoro", "Italo", "Ivano", "Ivo", "Leandro", "Leo", "Lino", "Livio", "Lorenzo", "Loris", "Luca", "Luciano", "Lucio", "Luigi", "Manuele", "Marcello", "Marco", "Mario", "Martino", "Massimo", "Matteo", "Mattia", "Michele", "Mirco", "Narciso", "Natale", "Nazario", "Nazzareno", "Nestore", "Nico", "Nicola", "Nino", "Noè", "Nunzio", "Oliviero", "Omar ", "Omero", "Onofrio", "Orazio", "Orlando", "Oscar", "Osvaldo", "Otello", "Ottavio", "Paolo", "Pasquale", "Patrizio", "Paride", "Pierluigi", "Piero", "Pietro", "Pio", "Pippo", "Prisco", "Angela", "Ada", "Adelaide", "Anna", "Antonella", "Anita", "Alice", "Amelia", "Anna", "Agnese", "Alessandra", "Alessia", "Aurora", "Angelica", "Barbara", "Betty", "Beatrice", "Calogera", "Claudia", "Carlotta", "Carmen", "Carola", "Caterina", "Cinzia", "Clara", "Clarissa", "Clelia", "Concetta", "Corinna", "Cristina", "Daniela", "Dina", "Domenica", "Debora", "Denise", "Danila", "Dorotea", "Emanuela", "Emilia", "Evelyn", "Erica", "Elena", "Elisa", "Eva", "Fiorella", "Francesca", "Federica", "Fabiola", "Flavia", "Floriana", "Giovannna", "Gabriella", "Gerlanda", "Giulia", "Giuseppina", "Giorgia", "Gaia", "Gemma", "Greta", "Ida", "Iole", "Iolanda", "Irene", "Isabella", "Iside"};
vector<string> cognomi = {"Rossi", "Ferrari", "Russo", "Bianchi", "Romano", "Gallo", "Costa", "Fontana", "Conti", "Esposito", "Ricci", "Bruno", "De Luca", "Moretti", "Marino", "Greco", "Barbieri", "Lombardi", "Giordano", "Cassano", "Colombo", "Mancini", "Longo", "Leone", "Martinelli", "Marchetti", "Martini", "Galli", "Gatti", "Mariani", "Ferrara", "Santoro", "Marini", "Bianco", "Conte", "Serra", "Farina", "Gentile", "Caruso", "Morelli", "Ferri", "Testa", "Ferraro", "Pellegrini", "Grassi", "Rossetti", "D'Angelo", "Bernardi", "Mazza", "Rizzi"};
string rep[7] = {"lun", "mar", "mer", "gio", "ven", "sab", "dom"};

string generaStringa(unsigned int length, unsigned int letterToUse=26) {
    if(letterToUse > 26) letterToUse = 26;
    string res = "";
    for(int i = 0; i < length; i++) {
        res += alfabeto[rand()%letterToUse];
    }
    return res;
}

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

string generaData() {
    int anno = 2000 + (rand() % 31);
    int mese = 1 + (rand() % 12);
    int giorno = 1 + (rand() % 31);
    if(giorno == 31 && (mese == 4 || mese == 6 || mese == 9 || mese == 11))
        giorno = 1 + (rand() % 30);
    if(giorno > 28 && mese == 2)
        giorno = 1 + (rand() % 28);
    
    string res = to_string(anno) + "/" + (mese < 10 ? "0"+to_string(mese) : to_string(mese)) + "/" + (giorno < 10 ? "0"+to_string(giorno) : to_string(giorno));
    return res;
}

int main(int argc, char** args) {
    if(argc != 4) {
        cerr << "Uso "<< args[0] << " #dj #ds #prog"<< endl;
        exit(1);
    }
    srand(time(0));
    int dj = atoi(args[1]);
    int ds = atoi(args[2]);
    int prog = atoi(args[3]);
    if(dj < 5 || ds < 5 || prog < 5) {
        cerr << "Errore: il numero di dipendenti junior, senior e dei progetti non può essere inferiore a 5" << endl;
        exit(1);
    }
        
    
    vector<string> dipendentiJunior;
    vector<string> dipendentiSenior;
    vector<string> progetti;
    
    for(int i = 0; i < dj; i++)
        dipendentiJunior.push_back("matr"+to_string(i));
    for(int i = 0; i < ds; i++)
        dipendentiSenior.push_back("matr"+to_string(dj+i));
    for(int i = 0; i < prog; i++)
        progetti.push_back("prog"+to_string(i));
    
    vector<string> skill;
    for(int i = 0; i < 100; i++)
        skill.push_back(generaStringa(3, 4));
        
    
    for(int i = 0; i < dj; i++) {
        cout << "DJ;"<< dipendentiJunior[i] << ";"<< nomi[rand()%nomi.size()] << ";"<< cognomi[rand()%cognomi.size()] << ";"<< fRand(1.0,10000.0) << ";";
        int nSkills = 1+(rand() % 30);
        unordered_set<string> skills;
        while(skills.size() != nSkills)
            skills.insert(skill[rand()%skill.size()]);            
        
        auto it = skills.begin();
        cout << *it;
        ++it;
        for(; it != skills.end(); ++it)
            cout << ","<< *it;
        cout << ";";
        if(rand()%3==0 && i != 0) cout << dipendentiJunior[rand() % i];        
        cout << endl;
    }
    
    for(int i = 0; i < ds; i++) {
        cout << "DS;"<< dipendentiSenior[i] << ";"<< nomi[rand()%nomi.size()] << ";"<< cognomi[rand()%cognomi.size()] << ";"<< fRand(1.0,10000.0) << ";";
        unordered_set<string> reper;
        int n = 1+rand() % 5;
        while(reper.size() != n)
            reper.insert(rep[rand()%7]);
        
        auto it = reper.begin();
        cout << *it;
        ++it;
        for(; it != reper.end(); ++it)
            cout << ","<< *it;
        cout << ";";
        
        n = (rand() % 5);
        
        if(n > 0) {
            unordered_set<string> subordinati;
            while(subordinati.size() != n)
                subordinati.insert(dipendentiJunior[rand()%dipendentiJunior.size()]);        
            auto it = subordinati.begin();
            cout << *it;
            ++it;
            for(; it != subordinati.end(); ++it)
                cout << ","<< *it;
        }
        cout << endl;
    }
    for(int i = 0; i < prog; i++)
        cout << "P;" << progetti[i] << ";" << generaData() << ";" << 2 + (rand() % 23) << ";" << fRand(1000.0, 100000.0) << ";" << dipendentiSenior[rand()%dipendentiSenior.size()] << endl;            
}