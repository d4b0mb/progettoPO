#include "Gestore.h"
#include <algorithm>

// Destructor - clean up all dynamically allocated memory
Gestore::~Gestore() {
    for (Junior* j : juniors) {
        delete j;
    }
    for (Senior* s : seniors) {
        delete s;
    }
}

// ============================================================================
// SEZIONE A - Required for passing (10 points)
// ============================================================================

void Gestore::aggiungiDipendenteJunior(string matricola, string nome, string cognome,
                                        double stipendio, const list<string>& skill,
                                        string stagista) {
    // Convert list<string> to vector<string>
    vector<string> skillVec(skill.begin(), skill.end());
    
    // Look up stagista pointer (nullptr if empty string or not found)
    Junior* stagistaPtr = nullptr;
    if (!stagista.empty()) {
        auto it = juniorMap.find(stagista);
        if (it != juniorMap.end()) {
            stagistaPtr = it->second;
        }
    }
    
    // Create the Junior and store it
    Junior* newJunior = new Junior(matricola, nome, cognome, stipendio, skillVec, stagistaPtr);
    juniors.push_back(newJunior);
    
    // Add to lookup map
    juniorMap[matricola] = newJunior;
}

void Gestore::aggiungiDipendenteSenior(string matricola, string nome, string cognome,
                                        double stipendio, const list<string>& reperibilita,
                                        const list<string>& subordinati) {
    // Convert list<string> to vector<string>
    vector<string> repVec(reperibilita.begin(), reperibilita.end());
    
    // Create the Senior
    Senior* seniorPtr = new Senior(matricola, nome, cognome, stipendio, repVec);
    seniors.push_back(seniorPtr);
    
    // Add to lookup map
    seniorMap[matricola] = seniorPtr;
    
    // Link subordinati (look up each Junior by matricola)
    for (const string& subMatr : subordinati) {
        auto it = juniorMap.find(subMatr);
        if (it != juniorMap.end()) {
            seniorPtr->addSubordinato(it->second);
        }
    }
}

void Gestore::aggiungiProgetto(string nome, string data, int durata,
                               double budget, string responsabile) {
    // Look up the responsible Senior
    Senior* respPtr = nullptr;
    auto it = seniorMap.find(responsabile);
    if (it != seniorMap.end()) {
        respPtr = it->second;
    }
    
    // Create and store the project
    progetti.push_back(Progetto(nome, data, durata, budget, respPtr));
    
    // Add to lookup map
    progettoMap[nome] = &progetti.back();
}

vector<Dipendente*> Gestore::getDipendenti() const {
    vector<Dipendente*> result;
    
    // Add all juniors
    for (Junior* j : juniors) {
        result.push_back(j);
    }
    
    // Add all seniors
    for (Senior* s : seniors) {
        result.push_back(s);
    }
    
    return result;
}

vector<Progetto*> Gestore::getProgetti() const {
    vector<Progetto*> result;
    
    for (size_t i = 0; i < progetti.size(); i++) {
        result.push_back(const_cast<Progetto*>(&progetti[i]));
    }
    
    return result;
}

// ============================================================================
// SEZIONE B - 14 points (1 each)
// ============================================================================

// B1: All projects where a senior is responsible
vector<Progetto*> Gestore::b1(string matricola) const {
    vector<Progetto*> result;
    
    auto it = seniorMap.find(matricola);
    if (it == seniorMap.end()) return result;
    
    Senior* senior = it->second;
    for (size_t i = 0; i < progetti.size(); i++) {
        if (progetti[i].getResponsabile() == senior) {
            result.push_back(const_cast<Progetto*>(&progetti[i]));
        }
    }
    
    return result;
}

// B2: All projects where a junior participates
vector<Progetto*> Gestore::b2(string matricola) const {
    vector<Progetto*> result;
    
    auto it = juniorMap.find(matricola);
    if (it == juniorMap.end()) return result;
    
    Junior* junior = it->second;
    
    for (size_t i = 0; i < progetti.size(); i++) {
        Senior* resp = progetti[i].getResponsabile();
        if (resp) {
            const vector<Junior*>& team = resp->getSubordinati();
            if (find(team.begin(), team.end(), junior) != team.end()) {
                result.push_back(const_cast<Progetto*>(&progetti[i]));
            }
        }
    }
    
    return result;
}

// B3: All unique skills of participants in a project
vector<string> Gestore::b3(string nomeProgetto) const {
    vector<string> result;
    
    auto it = progettoMap.find(nomeProgetto);
    if (it == progettoMap.end()) return result;
    
    Progetto* prog = it->second;
    Senior* resp = prog->getResponsabile();
    if (!resp) return result;
    
    // Collect all skills from subordinati, avoiding duplicates
    for (Junior* j : resp->getSubordinati()) {
        for (const string& skill : j->getSkills()) {
            if (find(result.begin(), result.end(), skill) == result.end()) {
                result.push_back(skill);
            }
        }
    }
    
    return result;
}

// B4: Skills present in ALL employees (intersection)
vector<string> Gestore::b4() const {
    vector<string> result;
    
    if (juniors.empty()) return result;
    
    // Start with skills from first junior
    result = juniors[0]->getSkills();
    
    // Intersect with each subsequent junior
    for (size_t i = 1; i < juniors.size(); i++) {
        const vector<string>& skills = juniors[i]->getSkills();
        vector<string> intersection;
        
        for (const string& s : result) {
            if (find(skills.begin(), skills.end(), s) != skills.end()) {
                intersection.push_back(s);
            }
        }
        
        result = intersection;
        if (result.empty()) break;
    }
    
    return result;
}

// B5: Top 5 most common skills
vector<string> Gestore::b5() const {
    // Count skill occurrences
    map<string, int> skillCount;
    
    for (Junior* j : juniors) {
        for (const string& skill : j->getSkills()) {
            skillCount[skill]++;
        }
    }
    
    // Convert to vector of pairs for sorting
    vector<pair<string, int>> skillPairs(skillCount.begin(), skillCount.end());
    
    // Sort by count descending
    sort(skillPairs.begin(), skillPairs.end(),
         [](const pair<string,int>& a, const pair<string,int>& b) {
             return a.second > b.second;
         });
    
    // Take top 5
    vector<string> result;
    for (size_t i = 0; i < 5 && i < skillPairs.size(); i++) {
        result.push_back(skillPairs[i].first);
    }
    
    return result;
}

// B6: Projects whose participants have NO skills in common
vector<Progetto*> Gestore::b6() const {
    vector<Progetto*> result;
    
    for (size_t i = 0; i < progetti.size(); i++) {
        Senior* resp = progetti[i].getResponsabile();
        if (!resp) continue;
        
        const vector<Junior*>& team = resp->getSubordinati();
        if (team.size() < 2) {
            // 0 or 1 participant - no common skills possible (or vacuously true?)
            // Based on interpretation: if no participants, skip; if 1, no intersection needed
            continue;
        }
        
        // Find intersection of all team members' skills
        vector<string> common = team[0]->getSkills();
        
        for (size_t j = 1; j < team.size(); j++) {
            const vector<string>& skills = team[j]->getSkills();
            vector<string> intersection;
            
            for (const string& s : common) {
                if (find(skills.begin(), skills.end(), s) != skills.end()) {
                    intersection.push_back(s);
                }
            }
            
            common = intersection;
            if (common.empty()) break;
        }
        
        if (common.empty()) {
            result.push_back(const_cast<Progetto*>(&progetti[i]));
        }
    }
    
    return result;
}

// B7: Projects with lowest budget among a senior's projects
vector<Progetto*> Gestore::b7(string matricola) const {
    vector<Progetto*> seniorProjects = b1(matricola);
    if (seniorProjects.empty()) return seniorProjects;
    
    // Find minimum budget
    double minBudget = seniorProjects[0]->getBudget();
    for (Progetto* p : seniorProjects) {
        if (p->getBudget() < minBudget) {
            minBudget = p->getBudget();
        }
    }
    
    // Return all with minimum budget
    vector<Progetto*> result;
    for (Progetto* p : seniorProjects) {
        if (p->getBudget() == minBudget) {
            result.push_back(p);
        }
    }
    
    return result;
}

// B8: Projects with highest budget among a senior's projects
vector<Progetto*> Gestore::b8(string matricola) const {
    vector<Progetto*> seniorProjects = b1(matricola);
    if (seniorProjects.empty()) return seniorProjects;
    
    // Find maximum budget
    double maxBudget = seniorProjects[0]->getBudget();
    for (Progetto* p : seniorProjects) {
        if (p->getBudget() > maxBudget) {
            maxBudget = p->getBudget();
        }
    }
    
    // Return all with maximum budget
    vector<Progetto*> result;
    for (Progetto* p : seniorProjects) {
        if (p->getBudget() == maxBudget) {
            result.push_back(p);
        }
    }
    
    return result;
}

// B9: Average budget of a senior's projects
double Gestore::b9(string matricola) const {
    vector<Progetto*> seniorProjects = b1(matricola);
    if (seniorProjects.empty()) return 0.0;
    
    double total = 0.0;
    for (Progetto* p : seniorProjects) {
        total += p->getBudget();
    }
    
    return total / seniorProjects.size();
}

// B10: All projects sorted by budget ascending
vector<Progetto*> Gestore::b10() const {
    vector<Progetto*> result = getProgetti();
    
    sort(result.begin(), result.end(),
         [](Progetto* a, Progetto* b) {
             return a->getBudget() < b->getBudget();
         });
    
    return result;
}

// B11: All projects sorted by budget descending
vector<Progetto*> Gestore::b11() const {
    vector<Progetto*> result = getProgetti();
    
    sort(result.begin(), result.end(),
         [](Progetto* a, Progetto* b) {
             return a->getBudget() > b->getBudget();
         });
    
    return result;
}

// B12: All projects sorted by start date ascending
vector<Progetto*> Gestore::b12() const {
    vector<Progetto*> result = getProgetti();
    
    // Date format "YYYY/MM/DD" sorts correctly as string
    sort(result.begin(), result.end(),
         [](Progetto* a, Progetto* b) {
             return a->getDataInizio() < b->getDataInizio();
         });
    
    return result;
}

// B13: All projects sorted by start date descending
vector<Progetto*> Gestore::b13() const {
    vector<Progetto*> result = getProgetti();
    
    sort(result.begin(), result.end(),
         [](Progetto* a, Progetto* b) {
             return a->getDataInizio() > b->getDataInizio();
         });
    
    return result;
}

// B14: Projects sorted by duration desc, then budget asc, then name alphabetically
vector<Progetto*> Gestore::b14() const {
    vector<Progetto*> result = getProgetti();
    
    sort(result.begin(), result.end(),
         [](Progetto* a, Progetto* b) {
             if (a->getDurata() != b->getDurata())
                 return a->getDurata() > b->getDurata();  // duration descending
             if (a->getBudget() != b->getBudget())
                 return a->getBudget() < b->getBudget();  // budget ascending
             return a->getNome() < b->getNome();          // name alphabetically
         });
    
    return result;
}

// ============================================================================
// SEZIONE C - 10 points (2 each)
// ============================================================================

// C1: Skills with highest total "earnings" (sum of budgets of projects they participate in)
vector<string> Gestore::c1() const {
    map<string, double> skillEarnings;
    
    // For each project, add its budget to each skill of its participants
    for (size_t i = 0; i < progetti.size(); i++) {
        Senior* resp = progetti[i].getResponsabile();
        if (!resp) continue;
        
        double budget = progetti[i].getBudget();
        
        // Collect unique skills in this project
        vector<string> projectSkills;
        for (Junior* j : resp->getSubordinati()) {
            for (const string& skill : j->getSkills()) {
                if (find(projectSkills.begin(), projectSkills.end(), skill) == projectSkills.end()) {
                    projectSkills.push_back(skill);
                }
            }
        }
        
        // Add budget to each skill
        for (const string& skill : projectSkills) {
            skillEarnings[skill] += budget;
        }
    }
    
    if (skillEarnings.empty()) return vector<string>();
    
    // Find maximum earnings
    double maxEarnings = 0.0;
    for (const auto& pair : skillEarnings) {
        if (pair.second > maxEarnings) {
            maxEarnings = pair.second;
        }
    }
    
    // Return all skills with max earnings
    vector<string> result;
    for (const auto& pair : skillEarnings) {
        if (pair.second == maxEarnings) {
            result.push_back(pair.first);
        }
    }
    
    return result;
}

// C2: Indispensable seniors - D1 is indispensable if there exists D2 where
//     skills(D1.subordinati) is a proper superset of skills(D2.subordinati)
vector<Dipendente*> Gestore::c2() const {
    vector<Dipendente*> result;
    
    // Helper lambda to get all skills from a senior's subordinates
    auto getTeamSkills = [](Senior* s) -> vector<string> {
        vector<string> skills;
        for (Junior* j : s->getSubordinati()) {
            for (const string& skill : j->getSkills()) {
                if (find(skills.begin(), skills.end(), skill) == skills.end()) {
                    skills.push_back(skill);
                }
            }
        }
        return skills;
    };
    
    // Helper lambda to check if A is proper superset of B
    auto isProperSuperset = [](const vector<string>& a, const vector<string>& b) -> bool {
        if (a.size() <= b.size()) return false;  // Can't be proper superset if not larger
        
        // Check that all of B is in A
        for (const string& s : b) {
            if (find(a.begin(), a.end(), s) == a.end()) {
                return false;
            }
        }
        return true;  // A contains all of B and is larger
    };
    
    for (Senior* s1 : seniors) {
        vector<string> skills1 = getTeamSkills(s1);
        
        for (Senior* s2 : seniors) {
            if (s1 == s2) continue;
            
            vector<string> skills2 = getTeamSkills(s2);
            
            if (isProperSuperset(skills1, skills2)) {
                result.push_back(s1);
                break;  // Found one D2, so D1 is indispensable
            }
        }
    }
    
    return result;
}

// C3: All juniors influenced by a senior
//     Junior D1 influences D2 if: D2 is D1's stagista, or D1 influences someone who influences D2
//     Senior DS influences DJ if: DJ is subordinate of DS, or a subordinate of DS influences DJ
vector<Dipendente*> Gestore::c3(string matricola) const {
    vector<Dipendente*> result;
    
    auto it = seniorMap.find(matricola);
    if (it == seniorMap.end()) return result;
    
    Senior* senior = it->second;
    
    // Helper: recursively find all juniors influenced by a junior
    // Using a set to track visited to avoid infinite loops
    vector<Junior*> influenced;
    vector<Junior*> toProcess;
    
    // Start with direct subordinates
    for (Junior* j : senior->getSubordinati()) {
        toProcess.push_back(j);
    }
    
    while (!toProcess.empty()) {
        Junior* current = toProcess.back();
        toProcess.pop_back();
        
        // Skip if already processed
        if (find(influenced.begin(), influenced.end(), current) != influenced.end()) {
            continue;
        }
        
        influenced.push_back(current);
        
        // Add this junior's stagista (if any) to be processed
        Junior* stagista = current->getStagista();
        if (stagista && find(influenced.begin(), influenced.end(), stagista) == influenced.end()) {
            toProcess.push_back(stagista);
        }
    }
    
    // Convert to Dipendente*
    for (Junior* j : influenced) {
        result.push_back(j);
    }
    
    return result;
}

// C4: Similar projects - projects that share skills and end in same month/year
vector<Progetto*> Gestore::c4(string nomeProgetto) const {
    vector<Progetto*> result;
    
    auto it = progettoMap.find(nomeProgetto);
    if (it == progettoMap.end()) return result;
    
    Progetto* target = it->second;
    
    // Get target's skills
    vector<string> targetSkills = b3(nomeProgetto);
    
    // Calculate target's end month/year
    // Parse "YYYY/MM/DD"
    string targetDate = target->getDataInizio();
    int targetYear = stoi(targetDate.substr(0, 4));
    int targetMonth = stoi(targetDate.substr(5, 2));
    
    // Add duration months
    targetMonth += target->getDurata();
    while (targetMonth > 12) {
        targetMonth -= 12;
        targetYear++;
    }
    
    for (size_t i = 0; i < progetti.size(); i++) {
        if (&progetti[i] == target) continue;
        
        // Calculate this project's end month/year
        string date = progetti[i].getDataInizio();
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        month += progetti[i].getDurata();
        while (month > 12) {
            month -= 12;
            year++;
        }
        
        // Check same end month/year
        if (year != targetYear || month != targetMonth) continue;
        
        // Get this project's skills
        vector<string> skills = b3(progetti[i].getNome());
        
        // Count common and different skills
        int common = 0;
        for (const string& s : targetSkills) {
            if (find(skills.begin(), skills.end(), s) != skills.end()) {
                common++;
            }
        }
        
        // Skills not in common = (targetSkills - common) + (skills - common)
        int notInCommon = (targetSkills.size() - common) + (skills.size() - common);
        
        // Similar if common >= 2 * notInCommon
        if (notInCommon == 0 || common >= 2 * notInCommon) {
            result.push_back(const_cast<Progetto*>(&progetti[i]));
        }
    }
    
    return result;
}

// C5: Optimal senior pairs - cover all 7 days AND no project date overlaps
vector<pair<Dipendente*, Dipendente*>> Gestore::c5() const {
    vector<pair<Dipendente*, Dipendente*>> result;
    
    // Helper: check if two seniors cover all 7 days
    auto coversWeek = [](Senior* s1, Senior* s2) -> bool {
        vector<string> allDays;
        for (const string& d : s1->getReperibilita()) {
            if (find(allDays.begin(), allDays.end(), d) == allDays.end())
                allDays.push_back(d);
        }
        for (const string& d : s2->getReperibilita()) {
            if (find(allDays.begin(), allDays.end(), d) == allDays.end())
                allDays.push_back(d);
        }
        return allDays.size() >= 7;
    };
    
    // Helper: calculate end date as YYYYMM integer for comparison
    auto getEndDate = [](const Progetto* p) -> int {
        string date = p->getDataInizio();
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        month += p->getDurata();
        while (month > 12) {
            month -= 12;
            year++;
        }
        return year * 100 + month;
    };
    
    auto getStartDate = [](const Progetto* p) -> int {
        string date = p->getDataInizio();
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        return year * 100 + month;
    };
    
    // Helper: check if two date ranges overlap
    auto rangesOverlap = [](int start1, int end1, int start2, int end2) -> bool {
        return !(end1 < start2 || end2 < start1);
    };
    
    // Helper: check if any projects of s1 overlap with any of s2
    auto projectsOverlap = [&](Senior* s1, Senior* s2) -> bool {
        vector<Progetto*> p1, p2;
        
        for (size_t i = 0; i < progetti.size(); i++) {
            if (progetti[i].getResponsabile() == s1)
                p1.push_back(const_cast<Progetto*>(&progetti[i]));
            if (progetti[i].getResponsabile() == s2)
                p2.push_back(const_cast<Progetto*>(&progetti[i]));
        }
        
        for (Progetto* a : p1) {
            int startA = getStartDate(a);
            int endA = getEndDate(a);
            for (Progetto* b : p2) {
                int startB = getStartDate(b);
                int endB = getEndDate(b);
                if (rangesOverlap(startA, endA, startB, endB)) {
                    return true;
                }
            }
        }
        return false;
    };
    
    // Check all pairs (avoid duplicates by only checking i < j)
    for (size_t i = 0; i < seniors.size(); i++) {
        for (size_t j = i + 1; j < seniors.size(); j++) {
            Senior* s1 = seniors[i];
            Senior* s2 = seniors[j];
            
            if (coversWeek(s1, s2) && !projectsOverlap(s1, s2)) {
                result.push_back(make_pair(static_cast<Dipendente*>(s1), 
                                           static_cast<Dipendente*>(s2)));
            }
        }
    }
    
    return result;
}
