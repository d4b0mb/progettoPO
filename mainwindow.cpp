#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QFile>
#include <QTextStream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Gestione Dipendenti e Progetti");
    resize(1000, 700);
    setupUI();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    // Menu bar
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* loadAction = fileMenu->addAction("Carica da File...");
    connect(loadAction, &QAction::triggered, this, &MainWindow::caricaDaFile);
    fileMenu->addSeparator();
    QAction* exitAction = fileMenu->addAction("Esci");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    
    // Central widget con splitter
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    setCentralWidget(splitter);
    
    // Tab widget per le sezioni
    QTabWidget* tabs = new QTabWidget();
    
    QWidget* tabA = new QWidget();
    QWidget* tabB = new QWidget();
    QWidget* tabC = new QWidget();
    
    setupSezioneA(tabA);
    setupSezioneB(tabB);
    setupSezioneC(tabC);
    
    tabs->addTab(tabA, "Sezione A - Base");
    tabs->addTab(tabB, "Sezione B - Query");
    tabs->addTab(tabC, "Sezione C - Avanzate");
    
    splitter->addWidget(tabs);
    
    // Output area
    QGroupBox* outputGroup = new QGroupBox("Output");
    QVBoxLayout* outputLayout = new QVBoxLayout(outputGroup);
    outputArea = new QTextEdit();
    outputArea->setReadOnly(true);
    outputArea->setFont(QFont("Courier", 10));
    outputLayout->addWidget(outputArea);
    
    QPushButton* clearButton = new QPushButton("Pulisci Output");
    connect(clearButton, &QPushButton::clicked, outputArea, &QTextEdit::clear);
    outputLayout->addWidget(clearButton);
    
    splitter->addWidget(outputGroup);
    splitter->setSizes({400, 300});
}

void MainWindow::setupSezioneA(QWidget* tab) {
    QHBoxLayout* mainLayout = new QHBoxLayout(tab);
    
    // --- Aggiungi Junior ---
    QGroupBox* juniorGroup = new QGroupBox("Aggiungi Junior");
    QFormLayout* juniorForm = new QFormLayout(juniorGroup);
    
    juniorMatricola = new QLineEdit();
    juniorNome = new QLineEdit();
    juniorCognome = new QLineEdit();
    juniorStipendio = new QLineEdit();
    juniorSkills = new QLineEdit();
    juniorSkills->setPlaceholderText("skill1,skill2,skill3");
    juniorStagista = new QLineEdit();
    juniorStagista->setPlaceholderText("matricola (opzionale)");
    
    juniorForm->addRow("Matricola:", juniorMatricola);
    juniorForm->addRow("Nome:", juniorNome);
    juniorForm->addRow("Cognome:", juniorCognome);
    juniorForm->addRow("Stipendio:", juniorStipendio);
    juniorForm->addRow("Skills:", juniorSkills);
    juniorForm->addRow("Stagista:", juniorStagista);
    
    QPushButton* addJuniorBtn = new QPushButton("Aggiungi Junior");
    connect(addJuniorBtn, &QPushButton::clicked, this, &MainWindow::aggiungiJunior);
    juniorForm->addRow(addJuniorBtn);
    
    // --- Aggiungi Senior ---
    QGroupBox* seniorGroup = new QGroupBox("Aggiungi Senior");
    QFormLayout* seniorForm = new QFormLayout(seniorGroup);
    
    seniorMatricola = new QLineEdit();
    seniorNome = new QLineEdit();
    seniorCognome = new QLineEdit();
    seniorStipendio = new QLineEdit();
    seniorReperibilita = new QLineEdit();
    seniorReperibilita->setPlaceholderText("lun,mar,mer,gio,ven,sab,dom");
    seniorSubordinati = new QLineEdit();
    seniorSubordinati->setPlaceholderText("matr1,matr2 (opzionale)");
    
    seniorForm->addRow("Matricola:", seniorMatricola);
    seniorForm->addRow("Nome:", seniorNome);
    seniorForm->addRow("Cognome:", seniorCognome);
    seniorForm->addRow("Stipendio:", seniorStipendio);
    seniorForm->addRow("Reperibilità:", seniorReperibilita);
    seniorForm->addRow("Subordinati:", seniorSubordinati);
    
    QPushButton* addSeniorBtn = new QPushButton("Aggiungi Senior");
    connect(addSeniorBtn, &QPushButton::clicked, this, &MainWindow::aggiungiSenior);
    seniorForm->addRow(addSeniorBtn);
    
    // --- Aggiungi Progetto ---
    QGroupBox* progettoGroup = new QGroupBox("Aggiungi Progetto");
    QFormLayout* progettoForm = new QFormLayout(progettoGroup);
    
    progettoNome = new QLineEdit();
    progettoData = new QLineEdit();
    progettoData->setPlaceholderText("YYYY/MM/DD");
    progettoDurata = new QLineEdit();
    progettoBudget = new QLineEdit();
    progettoResponsabile = new QLineEdit();
    progettoResponsabile->setPlaceholderText("matricola senior");
    
    progettoForm->addRow("Nome:", progettoNome);
    progettoForm->addRow("Data Inizio:", progettoData);
    progettoForm->addRow("Durata (mesi):", progettoDurata);
    progettoForm->addRow("Budget:", progettoBudget);
    progettoForm->addRow("Responsabile:", progettoResponsabile);
    
    QPushButton* addProgettoBtn = new QPushButton("Aggiungi Progetto");
    connect(addProgettoBtn, &QPushButton::clicked, this, &MainWindow::aggiungiProgetto);
    progettoForm->addRow(addProgettoBtn);
    
    // --- Visualizza ---
    QGroupBox* viewGroup = new QGroupBox("Visualizza");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    
    QPushButton* viewDipBtn = new QPushButton("A4: Tutti i Dipendenti");
    QPushButton* viewProjBtn = new QPushButton("A5: Tutti i Progetti");
    QPushButton* loadFileBtn = new QPushButton("A6: Carica da File...");
    
    connect(viewDipBtn, &QPushButton::clicked, this, &MainWindow::visualizzaDipendenti);
    connect(viewProjBtn, &QPushButton::clicked, this, &MainWindow::visualizzaProgetti);
    connect(loadFileBtn, &QPushButton::clicked, this, &MainWindow::caricaDaFile);
    
    viewLayout->addWidget(viewDipBtn);
    viewLayout->addWidget(viewProjBtn);
    viewLayout->addWidget(loadFileBtn);
    viewLayout->addStretch();
    
    // Layout
    mainLayout->addWidget(juniorGroup);
    mainLayout->addWidget(seniorGroup);
    mainLayout->addWidget(progettoGroup);
    mainLayout->addWidget(viewGroup);
}

void MainWindow::setupSezioneB(QWidget* tab) {
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);
    
    // Row 1: Query con parametro matricola
    QGroupBox* queryGroup = new QGroupBox("Query per Matricola");
    QGridLayout* queryLayout = new QGridLayout(queryGroup);
    
    QPushButton* b1Btn = new QPushButton("B1: Progetti di un Senior");
    QPushButton* b2Btn = new QPushButton("B2: Progetti di un Junior");
    QPushButton* b7Btn = new QPushButton("B7: Budget minimo (Senior)");
    QPushButton* b8Btn = new QPushButton("B8: Budget massimo (Senior)");
    QPushButton* b9Btn = new QPushButton("B9: Media budget (Senior)");
    
    connect(b1Btn, &QPushButton::clicked, this, &MainWindow::eseguiB1);
    connect(b2Btn, &QPushButton::clicked, this, &MainWindow::eseguiB2);
    connect(b7Btn, &QPushButton::clicked, this, &MainWindow::eseguiB7);
    connect(b8Btn, &QPushButton::clicked, this, &MainWindow::eseguiB8);
    connect(b9Btn, &QPushButton::clicked, this, &MainWindow::eseguiB9);
    
    queryLayout->addWidget(b1Btn, 0, 0);
    queryLayout->addWidget(b2Btn, 0, 1);
    queryLayout->addWidget(b7Btn, 1, 0);
    queryLayout->addWidget(b8Btn, 1, 1);
    queryLayout->addWidget(b9Btn, 1, 2);
    
    // Row 2: Query per progetto
    QGroupBox* projQueryGroup = new QGroupBox("Query per Progetto");
    QHBoxLayout* projQueryLayout = new QHBoxLayout(projQueryGroup);
    
    QPushButton* b3Btn = new QPushButton("B3: Skills di un Progetto");
    connect(b3Btn, &QPushButton::clicked, this, &MainWindow::eseguiB3);
    projQueryLayout->addWidget(b3Btn);
    
    // Row 3: Query globali skills
    QGroupBox* skillGroup = new QGroupBox("Query Skills");
    QHBoxLayout* skillLayout = new QHBoxLayout(skillGroup);
    
    QPushButton* b4Btn = new QPushButton("B4: Skills comuni a tutti");
    QPushButton* b5Btn = new QPushButton("B5: Top 5 skills");
    QPushButton* b6Btn = new QPushButton("B6: Progetti senza skills comuni");
    
    connect(b4Btn, &QPushButton::clicked, this, &MainWindow::eseguiB4);
    connect(b5Btn, &QPushButton::clicked, this, &MainWindow::eseguiB5);
    connect(b6Btn, &QPushButton::clicked, this, &MainWindow::eseguiB6);
    
    skillLayout->addWidget(b4Btn);
    skillLayout->addWidget(b5Btn);
    skillLayout->addWidget(b6Btn);
    
    // Row 4: Ordinamenti
    QGroupBox* sortGroup = new QGroupBox("Ordinamenti Progetti");
    QGridLayout* sortLayout = new QGridLayout(sortGroup);
    
    QPushButton* b10Btn = new QPushButton("B10: Budget crescente");
    QPushButton* b11Btn = new QPushButton("B11: Budget decrescente");
    QPushButton* b12Btn = new QPushButton("B12: Data crescente");
    QPushButton* b13Btn = new QPushButton("B13: Data decrescente");
    QPushButton* b14Btn = new QPushButton("B14: Durata/Budget/Nome");
    
    connect(b10Btn, &QPushButton::clicked, this, &MainWindow::eseguiB10);
    connect(b11Btn, &QPushButton::clicked, this, &MainWindow::eseguiB11);
    connect(b12Btn, &QPushButton::clicked, this, &MainWindow::eseguiB12);
    connect(b13Btn, &QPushButton::clicked, this, &MainWindow::eseguiB13);
    connect(b14Btn, &QPushButton::clicked, this, &MainWindow::eseguiB14);
    
    sortLayout->addWidget(b10Btn, 0, 0);
    sortLayout->addWidget(b11Btn, 0, 1);
    sortLayout->addWidget(b12Btn, 1, 0);
    sortLayout->addWidget(b13Btn, 1, 1);
    sortLayout->addWidget(b14Btn, 2, 0, 1, 2);
    
    mainLayout->addWidget(queryGroup);
    mainLayout->addWidget(projQueryGroup);
    mainLayout->addWidget(skillGroup);
    mainLayout->addWidget(sortGroup);
    mainLayout->addStretch();
}

void MainWindow::setupSezioneC(QWidget* tab) {
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);
    
    QGroupBox* advGroup = new QGroupBox("Operazioni Avanzate");
    QVBoxLayout* advLayout = new QVBoxLayout(advGroup);
    
    QPushButton* c1Btn = new QPushButton("C1: Skills con guadagno massimo");
    QPushButton* c2Btn = new QPushButton("C2: Senior indispensabili");
    QPushButton* c3Btn = new QPushButton("C3: Junior influenzati da un Senior");
    QPushButton* c4Btn = new QPushButton("C4: Progetti simili");
    QPushButton* c5Btn = new QPushButton("C5: Coppie Senior ottimali");
    
    connect(c1Btn, &QPushButton::clicked, this, &MainWindow::eseguiC1);
    connect(c2Btn, &QPushButton::clicked, this, &MainWindow::eseguiC2);
    connect(c3Btn, &QPushButton::clicked, this, &MainWindow::eseguiC3);
    connect(c4Btn, &QPushButton::clicked, this, &MainWindow::eseguiC4);
    connect(c5Btn, &QPushButton::clicked, this, &MainWindow::eseguiC5);
    
    advLayout->addWidget(c1Btn);
    advLayout->addWidget(c2Btn);
    advLayout->addWidget(c3Btn);
    advLayout->addWidget(c4Btn);
    advLayout->addWidget(c5Btn);
    
    mainLayout->addWidget(advGroup);
    mainLayout->addStretch();
}

// ============================================================================
// SEZIONE A - Slots
// ============================================================================

void MainWindow::aggiungiJunior() {
    QString matr = juniorMatricola->text().trimmed();
    QString nome = juniorNome->text().trimmed();
    QString cognome = juniorCognome->text().trimmed();
    QString stipStr = juniorStipendio->text().trimmed();
    QString skillsStr = juniorSkills->text().trimmed();
    QString stagista = juniorStagista->text().trimmed();
    
    if (matr.isEmpty() || nome.isEmpty() || cognome.isEmpty() || 
        stipStr.isEmpty() || skillsStr.isEmpty()) {
        QMessageBox::warning(this, "Errore", "Compilare tutti i campi obbligatori.");
        return;
    }
    
    double stipendio = stipStr.toDouble();
    
    // Parse skills
    list<string> skills;
    QStringList skillList = skillsStr.split(",", Qt::SkipEmptyParts);
    for (const QString& s : skillList) {
        skills.push_back(s.trimmed().toStdString());
    }
    
    gestore.aggiungiDipendenteJunior(
        matr.toStdString(),
        nome.toStdString(),
        cognome.toStdString(),
        stipendio,
        skills,
        stagista.toStdString()
    );
    
    outputArea->append("Aggiunto Junior: " + matr + " - " + nome + " " + cognome);
    
    // Clear fields
    juniorMatricola->clear();
    juniorNome->clear();
    juniorCognome->clear();
    juniorStipendio->clear();
    juniorSkills->clear();
    juniorStagista->clear();
}

void MainWindow::aggiungiSenior() {
    QString matr = seniorMatricola->text().trimmed();
    QString nome = seniorNome->text().trimmed();
    QString cognome = seniorCognome->text().trimmed();
    QString stipStr = seniorStipendio->text().trimmed();
    QString repStr = seniorReperibilita->text().trimmed();
    QString subStr = seniorSubordinati->text().trimmed();
    
    if (matr.isEmpty() || nome.isEmpty() || cognome.isEmpty() || 
        stipStr.isEmpty() || repStr.isEmpty()) {
        QMessageBox::warning(this, "Errore", "Compilare tutti i campi obbligatori.");
        return;
    }
    
    double stipendio = stipStr.toDouble();
    
    // Parse reperibilita
    list<string> reperibilita;
    QStringList repList = repStr.split(",", Qt::SkipEmptyParts);
    for (const QString& r : repList) {
        reperibilita.push_back(r.trimmed().toStdString());
    }
    
    // Parse subordinati
    list<string> subordinati;
    if (!subStr.isEmpty()) {
        QStringList subList = subStr.split(",", Qt::SkipEmptyParts);
        for (const QString& s : subList) {
            subordinati.push_back(s.trimmed().toStdString());
        }
    }
    
    gestore.aggiungiDipendenteSenior(
        matr.toStdString(),
        nome.toStdString(),
        cognome.toStdString(),
        stipendio,
        reperibilita,
        subordinati
    );
    
    outputArea->append("Aggiunto Senior: " + matr + " - " + nome + " " + cognome);
    
    // Clear fields
    seniorMatricola->clear();
    seniorNome->clear();
    seniorCognome->clear();
    seniorStipendio->clear();
    seniorReperibilita->clear();
    seniorSubordinati->clear();
}

void MainWindow::aggiungiProgetto() {
    QString nome = progettoNome->text().trimmed();
    QString data = progettoData->text().trimmed();
    QString durataStr = progettoDurata->text().trimmed();
    QString budgetStr = progettoBudget->text().trimmed();
    QString resp = progettoResponsabile->text().trimmed();
    
    if (nome.isEmpty() || data.isEmpty() || durataStr.isEmpty() || 
        budgetStr.isEmpty() || resp.isEmpty()) {
        QMessageBox::warning(this, "Errore", "Compilare tutti i campi.");
        return;
    }
    
    int durata = durataStr.toInt();
    double budget = budgetStr.toDouble();
    
    gestore.aggiungiProgetto(
        nome.toStdString(),
        data.toStdString(),
        durata,
        budget,
        resp.toStdString()
    );
    
    outputArea->append("Aggiunto Progetto: " + nome);
    
    // Clear fields
    progettoNome->clear();
    progettoData->clear();
    progettoDurata->clear();
    progettoBudget->clear();
    progettoResponsabile->clear();
}

void MainWindow::visualizzaDipendenti() {
    outputArea->append("\n=== TUTTI I DIPENDENTI ===");
    
    vector<Dipendente*> dip = gestore.getDipendenti();
    
    if (dip.empty()) {
        outputArea->append("Nessun dipendente presente.");
        return;
    }
    
    for (Dipendente* d : dip) {
        QString line = QString::fromStdString(d->getTipo()) + ": " +
                       QString::fromStdString(d->getMatricola()) + " - " +
                       QString::fromStdString(d->getNome()) + " " +
                       QString::fromStdString(d->getCognome()) + " - €" +
                       QString::number(d->getStipendio(), 'f', 2);
        outputArea->append(line);
    }
    
    outputArea->append("Totale: " + QString::number(dip.size()) + " dipendenti");
}

void MainWindow::visualizzaProgetti() {
    outputArea->append("\n=== TUTTI I PROGETTI ===");
    
    vector<Progetto*> proj = gestore.getProgetti();
    
    if (proj.empty()) {
        outputArea->append("Nessun progetto presente.");
        return;
    }
    
    for (Progetto* p : proj) {
        QString resp = p->getResponsabile() ? 
                       QString::fromStdString(p->getResponsabile()->getMatricola()) : "N/A";
        QString line = QString::fromStdString(p->getNome()) + " - " +
                       QString::fromStdString(p->getDataInizio()) + " - " +
                       QString::number(p->getDurata()) + " mesi - €" +
                       QString::number(p->getBudget(), 'f', 2) + " - Resp: " + resp;
        outputArea->append(line);
    }
    
    outputArea->append("Totale: " + QString::number(proj.size()) + " progetti");
}

void MainWindow::caricaDaFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Apri File", "", "Text Files (*.txt);;All Files (*)");
    if (filename.isEmpty()) return;
    
    leggiDaFile(filename);
}

void MainWindow::leggiDaFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Errore", "Impossibile aprire il file.");
        return;
    }
    
    QTextStream in(&file);
    int countDJ = 0, countDS = 0, countP = 0;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList parts = line.split(";");
        QString tipo = parts[0];
        
        if (tipo == "DJ" && parts.size() >= 6) {
            string matricola = parts[1].toStdString();
            string nome = parts[2].toStdString();
            string cognome = parts[3].toStdString();
            double stipendio = parts[4].toDouble();
            
            QStringList skillList = parts[5].split(",", Qt::SkipEmptyParts);
            list<string> skills;
            for (const QString& s : skillList) {
                skills.push_back(s.trimmed().toStdString());
            }
            
            string stagista = "";
            if (parts.size() > 6 && !parts[6].isEmpty()) {
                stagista = parts[6].toStdString();
            }
            
            gestore.aggiungiDipendenteJunior(matricola, nome, cognome, stipendio, skills, stagista);
            countDJ++;
        }
        else if (tipo == "DS" && parts.size() >= 6) {
            string matricola = parts[1].toStdString();
            string nome = parts[2].toStdString();
            string cognome = parts[3].toStdString();
            double stipendio = parts[4].toDouble();
            
            QStringList repList = parts[5].split(",", Qt::SkipEmptyParts);
            list<string> reperibilita;
            for (const QString& r : repList) {
                reperibilita.push_back(r.trimmed().toStdString());
            }
            
            list<string> subordinati;
            if (parts.size() > 6 && !parts[6].isEmpty()) {
                QStringList subList = parts[6].split(",", Qt::SkipEmptyParts);
                for (const QString& s : subList) {
                    subordinati.push_back(s.trimmed().toStdString());
                }
            }
            
            gestore.aggiungiDipendenteSenior(matricola, nome, cognome, stipendio, reperibilita, subordinati);
            countDS++;
        }
        else if (tipo == "P" && parts.size() >= 6) {
            string nome = parts[1].toStdString();
            string data = parts[2].toStdString();
            int durata = parts[3].toInt();
            double budget = parts[4].toDouble();
            string responsabile = parts[5].toStdString();
            
            gestore.aggiungiProgetto(nome, data, durata, budget, responsabile);
            countP++;
        }
    }
    
    file.close();
    
    outputArea->append("\n=== FILE CARICATO ===");
    outputArea->append("File: " + filename);
    outputArea->append("Junior caricati: " + QString::number(countDJ));
    outputArea->append("Senior caricati: " + QString::number(countDS));
    outputArea->append("Progetti caricati: " + QString::number(countP));
}

// ============================================================================
// SEZIONE B - Slots
// ============================================================================

void MainWindow::eseguiB1() {
    bool ok;
    QString matr = QInputDialog::getText(this, "B1", "Inserisci matricola Senior:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || matr.isEmpty()) return;
    
    outputArea->append("\n=== B1: Progetti di " + matr + " ===");
    
    vector<Progetto*> result = gestore.b1(matr.toStdString());
    
    if (result.empty()) {
        outputArea->append("Nessun progetto trovato.");
        return;
    }
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

void MainWindow::eseguiB2() {
    bool ok;
    QString matr = QInputDialog::getText(this, "B2", "Inserisci matricola Junior:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || matr.isEmpty()) return;
    
    outputArea->append("\n=== B2: Progetti con partecipazione di " + matr + " ===");
    
    vector<Progetto*> result = gestore.b2(matr.toStdString());
    
    if (result.empty()) {
        outputArea->append("Nessun progetto trovato.");
        return;
    }
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

void MainWindow::eseguiB3() {
    bool ok;
    QString nome = QInputDialog::getText(this, "B3", "Inserisci nome Progetto:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || nome.isEmpty()) return;
    
    outputArea->append("\n=== B3: Skills del progetto " + nome + " ===");
    
    vector<string> result = gestore.b3(nome.toStdString());
    
    if (result.empty()) {
        outputArea->append("Nessuna skill trovata.");
        return;
    }
    
    QString skills;
    for (const string& s : result) {
        skills += QString::fromStdString(s) + ", ";
    }
    skills.chop(2);
    outputArea->append(skills);
}

void MainWindow::eseguiB4() {
    outputArea->append("\n=== B4: Skills presenti in TUTTI i dipendenti ===");
    
    vector<string> result = gestore.b4();
    
    if (result.empty()) {
        outputArea->append("Nessuna skill comune a tutti.");
        return;
    }
    
    QString skills;
    for (const string& s : result) {
        skills += QString::fromStdString(s) + ", ";
    }
    skills.chop(2);
    outputArea->append(skills);
}

void MainWindow::eseguiB5() {
    outputArea->append("\n=== B5: Top 5 skills più diffuse ===");
    
    vector<string> result = gestore.b5();
    
    if (result.empty()) {
        outputArea->append("Nessuna skill trovata.");
        return;
    }
    
    int i = 1;
    for (const string& s : result) {
        outputArea->append(QString::number(i++) + ". " + QString::fromStdString(s));
    }
}

void MainWindow::eseguiB6() {
    outputArea->append("\n=== B6: Progetti senza skills in comune ===");
    
    vector<Progetto*> result = gestore.b6();
    
    if (result.empty()) {
        outputArea->append("Nessun progetto trovato.");
        return;
    }
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()));
    }
}

void MainWindow::eseguiB7() {
    bool ok;
    QString matr = QInputDialog::getText(this, "B7", "Inserisci matricola Senior:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || matr.isEmpty()) return;
    
    outputArea->append("\n=== B7: Progetti budget minimo di " + matr + " ===");
    
    vector<Progetto*> result = gestore.b7(matr.toStdString());
    
    if (result.empty()) {
        outputArea->append("Nessun progetto trovato.");
        return;
    }
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

void MainWindow::eseguiB8() {
    bool ok;
    QString matr = QInputDialog::getText(this, "B8", "Inserisci matricola Senior:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || matr.isEmpty()) return;
    
    outputArea->append("\n=== B8: Progetti budget massimo di " + matr + " ===");
    
    vector<Progetto*> result = gestore.b8(matr.toStdString());
    
    if (result.empty()) {
        outputArea->append("Nessun progetto trovato.");
        return;
    }
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

void MainWindow::eseguiB9() {
    bool ok;
    QString matr = QInputDialog::getText(this, "B9", "Inserisci matricola Senior:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || matr.isEmpty()) return;
    
    double result = gestore.b9(matr.toStdString());
    
    outputArea->append("\n=== B9: Media budget progetti di " + matr + " ===");
    outputArea->append("Media: €" + QString::number(result, 'f', 2));
}

void MainWindow::eseguiB10() {
    outputArea->append("\n=== B10: Progetti per budget crescente ===");
    
    vector<Progetto*> result = gestore.b10();
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

void MainWindow::eseguiB11() {
    outputArea->append("\n=== B11: Progetti per budget decrescente ===");
    
    vector<Progetto*> result = gestore.b11();
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

void MainWindow::eseguiB12() {
    outputArea->append("\n=== B12: Progetti per data crescente ===");
    
    vector<Progetto*> result = gestore.b12();
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - " + 
                          QString::fromStdString(p->getDataInizio()));
    }
}

void MainWindow::eseguiB13() {
    outputArea->append("\n=== B13: Progetti per data decrescente ===");
    
    vector<Progetto*> result = gestore.b13();
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - " + 
                          QString::fromStdString(p->getDataInizio()));
    }
}

void MainWindow::eseguiB14() {
    outputArea->append("\n=== B14: Progetti ordinati (durata desc, budget asc, nome) ===");
    
    vector<Progetto*> result = gestore.b14();
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - " +
                          QString::number(p->getDurata()) + " mesi - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

// ============================================================================
// SEZIONE C - Slots
// ============================================================================

void MainWindow::eseguiC1() {
    outputArea->append("\n=== C1: Skills con guadagno massimo ===");
    
    vector<string> result = gestore.c1();
    
    if (result.empty()) {
        outputArea->append("Nessuna skill trovata.");
        return;
    }
    
    for (const string& s : result) {
        outputArea->append(QString::fromStdString(s));
    }
}

void MainWindow::eseguiC2() {
    outputArea->append("\n=== C2: Senior indispensabili ===");
    
    vector<Dipendente*> result = gestore.c2();
    
    if (result.empty()) {
        outputArea->append("Nessun senior indispensabile trovato.");
        return;
    }
    
    for (Dipendente* d : result) {
        outputArea->append(QString::fromStdString(d->getMatricola()) + " - " +
                          QString::fromStdString(d->getNome()) + " " +
                          QString::fromStdString(d->getCognome()));
    }
    
    outputArea->append("Totale: " + QString::number(result.size()));
}

void MainWindow::eseguiC3() {
    bool ok;
    QString matr = QInputDialog::getText(this, "C3", "Inserisci matricola Senior:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || matr.isEmpty()) return;
    
    outputArea->append("\n=== C3: Junior influenzati da " + matr + " ===");
    
    vector<Dipendente*> result = gestore.c3(matr.toStdString());
    
    if (result.empty()) {
        outputArea->append("Nessun junior influenzato.");
        return;
    }
    
    for (Dipendente* d : result) {
        outputArea->append(QString::fromStdString(d->getMatricola()) + " - " +
                          QString::fromStdString(d->getNome()) + " " +
                          QString::fromStdString(d->getCognome()));
    }
    
    outputArea->append("Totale: " + QString::number(result.size()));
}

void MainWindow::eseguiC4() {
    bool ok;
    QString nome = QInputDialog::getText(this, "C4", "Inserisci nome Progetto:", 
                                         QLineEdit::Normal, "", &ok);
    if (!ok || nome.isEmpty()) return;
    
    outputArea->append("\n=== C4: Progetti simili a " + nome + " ===");
    
    vector<Progetto*> result = gestore.c4(nome.toStdString());
    
    if (result.empty()) {
        outputArea->append("Nessun progetto simile trovato.");
        return;
    }
    
    for (Progetto* p : result) {
        outputArea->append(QString::fromStdString(p->getNome()) + " - €" + 
                          QString::number(p->getBudget(), 'f', 2));
    }
}

void MainWindow::eseguiC5() {
    outputArea->append("\n=== C5: Coppie Senior ottimali ===");
    
    vector<pair<Dipendente*, Dipendente*>> result = gestore.c5();
    
    if (result.empty()) {
        outputArea->append("Nessuna coppia ottimale trovata.");
        return;
    }
    
    for (const auto& coppia : result) {
        outputArea->append(QString::fromStdString(coppia.first->getMatricola()) + " + " +
                          QString::fromStdString(coppia.second->getMatricola()));
    }
    
    outputArea->append("Totale coppie: " + QString::number(result.size()));
}
