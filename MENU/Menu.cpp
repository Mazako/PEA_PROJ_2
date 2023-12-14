#include "Menu.h"
#include "PeaUtils.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void Menu::init() {
    bool program = true;
    std::string option;
    cout << "Pea, zadanie 2" << endl;
    cout << "Autor: Michal Maziarz (263913)" << endl;
    while (program) {
        for (int i = 0; i < 4; i++) {
            cout << endl;
        }
        cout << "Macierz: " << (!currentMatrix ? "BRAK" : currentMatrix->getName()) << endl;
        cout << "1) Wczytaj macierz z pliku" << endl;
        cout << "2) Ustaw parametry SA" << endl;
        cout << "3) Ustaw parametry TS" << endl;
        cout << "4) Ustawienia globalne" << endl;
        cout << "5) Pokaz wszystkie ustawienia" << endl;
        cout << "6) Wykonaj tabu search" << endl;
        cout << "7) Wykonaj simulated annealing" << endl;
        cout << "8) Oblicz koszt drogi z pliku (dla aktualnej macierzy)" << endl;
        cout << "0) Zakoncz program" << endl;
        cout << "Wybierz opcje: ";
        std::getline(std::cin, option);
        if (option == "1") {
            readMatrixFromFile();
        } else if (option == "2") {
            setSaParams();
        } else if (option == "3") {
            setTsParams();
        } else if (option == "4") {
            setGlobalSettings();
        } else if (option == "5") {
            showAllSettings();
        } else if (option == "6") {
            performTabuSearch();
        } else if (option == "7") {
            performSimulatedAnnealing();
        } else if (option == "8") {
            readResultFileAndCalcPath();
        } else if (option == "0") {
            program = false;
        } else {
            cout << "Nie ma takiej opcji" << endl;
        }
    }
}

void Menu::readMatrixFromFile() {
    std::string path;
    std::string option;
    cout << "1) Plik .atsp" << endl;
    cout << "2) Plik .xml" << endl;
    cout << "Wybierz opcje: ";
    std::getline(cin, option);
    if (option != "1" && option != "2") {
        cout << "Nie ma takiej opcji.";
        return;
    }
    cout << "Podaj sciezke do pliku: ";
    std::getline(std::cin, path);
    try {
        TspMatrix* matrix;
        if (option == "1") {
            matrix = PeaUtils::readMatrixFromAtspFile(path);
        } else {
            matrix = PeaUtils::readMatrixFromXmlFile(path);
        }
        delete this->currentMatrix;
        this->currentMatrix = matrix;
    } catch (std::exception& e) {
        cout << "Problem z wczytaniem pliku" << endl;
    }
}

void Menu::setSaParams() {
    bool running = true;
    std::string option;
    while (running) {
        cout << "1) Wspolczynnik tau = " << tau << endl;
        cout << "2) Wspolczynnik wewnetrznej petli = " << innerLoopFactor << endl;
        cout << "3) Wspolczynnik wyzarzania = " << coolingFactor << endl;
        cout << "0) Powrot" << endl;
        cout << "Wybierz opcje aby zmienic parametr: ";
        std::getline(std::cin, option);
        if (option == "1") {
            cout << "Podaj wartosc: ";
            cin >> tau;
            getchar();
        } else if (option == "2") {
            cout << "Podaj wartosc: ";
            cin >> innerLoopFactor;
            getchar();
        } else if (option == "3") {
            cout << "Podaj wartosc: ";
            cin >> coolingFactor;
            getchar();
        } else if (option == "0") {
            running = false;
        } else {
            cout << "Nie ma takiej opcji" << endl;
        }
    }
}

void Menu::setTsParams() {
    bool running = true;
    std::string option;
    while (running) {
        cout << "1) Ilosc petli bez ulepszenia (warunek resetu) = " << unsatisfiedIterationsBeforeReset << endl;
        cout << "0) Powrot" << endl;
        cout << "Wybierz opcje aby zmienic parametr: ";
        std::getline(std::cin, option);
        if (option == "1") {
            cout << "Podaj wartosc: ";
            cin >> unsatisfiedIterationsBeforeReset;
            getchar();
        } else if (option == "0") {
            running = false;
        } else {
            cout << "Nie ma takiej opcji" << endl;
        }
    }
}

void Menu::setGlobalSettings() {
    bool running = true;
    std::string option;
    while (running) {

        cout << "1) Wyswietlaj informacje o przebiegu algorytmu = " << evaluateBool(verbose) << endl;
        cout << "2) Maksymalny czas wykonywania algorytmu w sekundach = " << timeLimitInSeconds << endl;
        cout << "3) Zaczynaj algorytm od rozwiazania zachlannego = " << evaluateBool(useGreedyStart) << endl;
        cout << "0) Powrot" << endl;
        cout << "Wybierz opcje aby zmienic parametr: ";
        std::getline(std::cin, option);
        if (option == "1") {
            verbose = !verbose;
        } else if (option == "2") {
            cout << "Podaj wartosc: ";
            cin >> timeLimitInSeconds;
            getchar();
        } else if (option == "0") {
            running = false;
        } else if (option == "3") {
            useGreedyStart = !useGreedyStart;
        }
        else {
            cout << "Nie ma takiej opcji" << endl;
        }
    }
}

void Menu::showAllSettings() {
    cout << "Wyswietlaj informacje o przebiegu algorytmu = " << evaluateBool(verbose) << endl;
    cout << "Maksymalny czas wykonywania algorytmu w sekundach = " << timeLimitInSeconds << endl;
    cout << "Zaczynaj algorytm od rozwiazania zachlannego = " << evaluateBool(verbose) << endl;
    cout << "Wspolczynnik tau (SA) = " << tau << endl;
    cout << "Wspolczynnik wewnetrznej petli (SA) = " << innerLoopFactor << endl;
    cout << "Wspolczynnik wyzarzania (SA) = " << coolingFactor << endl;
    cout << "Ilosc petli bez ulepszenia (TS) = " << unsatisfiedIterationsBeforeReset << endl;
}

void Menu::performTabuSearch() {
    if (currentMatrix == nullptr) {
        cout << "Wybierz macierz!" << endl;
        return;
    }
    auto results = TabuSearch::solve(currentMatrix, timeLimitInSeconds, unsatisfiedIterationsBeforeReset, verbose, useGreedyStart);
    cout << results->toString() << endl;
    cout << "Zapisano sciezke rozwiazania w pliku: " << results->getFilePath() << endl;
    delete results;
}

void Menu::performSimulatedAnnealing() {
    if (currentMatrix == nullptr) {
        cout << "Wybierz macierz!" << endl;
        return;
    }
    auto results = SimulatedAnnealing::solve(currentMatrix, timeLimitInSeconds, tau, innerLoopFactor, coolingFactor, verbose, useGreedyStart);
    cout << results->toString() << endl;
    cout << "Zapisano sciezke rozwiazania w pliku: " << results->getFilePath() << endl;
    delete results;
}

void Menu::readResultFileAndCalcPath() {
    if (currentMatrix == nullptr) {
        cout << "Wybierz macierz!" << endl;
        return;
    }
    std::string path;
    std::string option;
    cout << "Podaj sciezke do pliku: ";
    std::getline(std::cin, path);
    try {
        auto result = PeaUtils::readPathAndCalculateCost(currentMatrix, path);
        cout << "Wynik: " << result << endl;
    } catch (std::exception& e) {
        cout << "Problem z wczytaniem pliku" << endl;
    }

}

std::string Menu::evaluateBool(bool value) {
    return value ? "Tak" : "Nie";
}

Menu::Menu() = default;
