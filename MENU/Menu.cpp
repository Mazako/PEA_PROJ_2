#include "Menu.h"
#include "PeaUtils.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void Menu::init() {
    bool program = true;
    std::string option;
    while (program) {
        cout << "1) Wczytaj macierz z pliku" << endl;
        cout << "2) Ustaw parametry SA" << endl;
        cout << "3) Ustaw parametry TS" << endl;
        cout << "4) Ustawienia globalne" << endl;
        cout << "5) Pokaz wszystkie ustawienia" << endl;
        cout << "6) Wykonaj tabu search" << endl;
        cout << "7) Wykonaj simulated annealing" << endl;
        cout << "0) Zakoncz program" << endl;
        cout << "Wybierz opcje: ";
        std::getline(std::cin, option);
        if (option == "1") {

        } else if (option == "2") {

        } else if (option == "3") {

        } else if (option == "4") {

        } else if (option == "5") {

        } else if (option == "6") {

        } else if (option == "7") {

        } else if (option == "0") {
            program = false;
        } else {
            cout << "Nie ma takiej opcji" << endl;
        }
    }
}

void Menu::readMatrixFromFile() {
    std::string path;
    cout << "Uwaga! Plik musi miec format .atsp, lub .xml" << endl;
    cout << "Podaj sciezke do pliku: ";
    std::getline(std::cin, path);
    try {
        auto matrix = PeaUtils::readMatrixFromAtspFile(path);
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
        cout << "1) Wyswietlaj informacje o przebiegu algorytmu = " << verbose << endl;
        cout << "2) Maksymalny czas wykonywania algorytmu w minutach = " << timeLimitInMinutes << endl;
        cout << "3) Zaczynaj algorytm od rozwiazania zachlannego = " << useGreedyStart << endl;
        cout << "0) Powrot" << endl;
        cout << "Wybierz opcje aby zmienic parametr: ";
        std::getline(std::cin, option);
        if (option == "1") {
            verbose = !verbose;
        } else if (option == "2") {
            cout << "Podaj wartosc: ";
            cin >> timeLimitInMinutes;
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
    cout << "Wyswietlaj informacje o przebiegu algorytmu = " << verbose << endl;
    cout << "Maksymalny czas wykonywania algorytmu w minutach = " << timeLimitInMinutes << endl;
    cout << "Zaczynaj algorytm od rozwiazania zachlannego = " << useGreedyStart << endl;
    cout << "Wspolczynnik tau (SA) = " << tau << endl;
    cout << "Wspolczynnik wewnetrznej petli (SA) = " << innerLoopFactor << endl;
    cout << "Wspolczynnik wyzarzania (SA) = " << coolingFactor << endl;
    cout << "Ilosc petli bez ulepszenia (TS) = " << unsatisfiedIterationsBeforeReset << endl;
}

void Menu::performTabuSearch() {

}

void Menu::performSimulatedAnnealing() {

}
