#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include "Gestore.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Sezione A
    void aggiungiSenior();
    void aggiungiJunior();
    void aggiungiProgetto();
    void visualizzaDipendenti();
    void visualizzaProgetti();
    void caricaDaFile();
    
    // Sezione B
    void eseguiB1();
    void eseguiB2();
    void eseguiB3();
    void eseguiB4();
    void eseguiB5();
    void eseguiB6();
    void eseguiB7();
    void eseguiB8();
    void eseguiB9();
    void eseguiB10();
    void eseguiB11();
    void eseguiB12();
    void eseguiB13();
    void eseguiB14();
    
    // Sezione C
    void eseguiC1();
    void eseguiC2();
    void eseguiC3();
    void eseguiC4();
    void eseguiC5();

private:
    void setupUI();
    void setupSezioneA(QWidget* tab);
    void setupSezioneB(QWidget* tab);
    void setupSezioneC(QWidget* tab);
    
    // Helper per leggere da file
    void leggiDaFile(const QString& filename);
    
    // Gestore principale
    Gestore gestore;
    
    // Output area
    QTextEdit* outputArea;
    
    // Input fields per Sezione A
    // Junior
    QLineEdit* juniorMatricola;
    QLineEdit* juniorNome;
    QLineEdit* juniorCognome;
    QLineEdit* juniorStipendio;
    QLineEdit* juniorSkills;
    QLineEdit* juniorStagista;
    
    // Senior
    QLineEdit* seniorMatricola;
    QLineEdit* seniorNome;
    QLineEdit* seniorCognome;
    QLineEdit* seniorStipendio;
    QLineEdit* seniorReperibilita;
    QLineEdit* seniorSubordinati;
    
    // Progetto
    QLineEdit* progettoNome;
    QLineEdit* progettoData;
    QLineEdit* progettoDurata;
    QLineEdit* progettoBudget;
    QLineEdit* progettoResponsabile;
};

#endif // MAINWINDOW_H
