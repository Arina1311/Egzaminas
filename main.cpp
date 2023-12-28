
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
#include <iterator>
#include "Funkcijos.h"

using namespace std;


bool yraTikSkaitmenys(const string &zodis) {
    for (char c : zodis) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool isPunctuation(char c) {
    return std::ispunct(static_cast<unsigned char>(c));
}

string pasalintiSkyrybiniusZenklus(const string &zodis) {
    string rezultatas;
    remove_copy_if(zodis.begin(), zodis.end(), back_inserter(rezultatas), isPunctuation);
    return rezultatas;
}


int main() {
    ifstream inputFile("tekst.txt");
    if (!inputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo!" << endl;
        return 1;
    }

    map<string, int> zodzioDažnumas;
    string eilute, zodis;

    while (getline(inputFile, eilute)) {
        istringstream iss(eilute);
        while (iss >> zodis) {
            string valytasZodis = pasalintiSkyrybiniusZenklus(zodis);
            if (!valytasZodis.empty() && !yraTikSkaitmenys(valytasZodis)) {
                string mazosiosRaidesZodis = valytasZodis;
                transform(mazosiosRaidesZodis.begin(), mazosiosRaidesZodis.end(), mazosiosRaidesZodis.begin(), ::tolower);
                ++zodzioDažnumas[mazosiosRaidesZodis];
            }
        }
    }

    inputFile.close();

    ofstream outputFile("rezultatas.txt");
    if (!outputFile.is_open()) {
        cerr << "Nepavyko atidaryti rezultato failo!" << endl;
        return 1;
    }

    outputFile <<left<<setw(30)<<"| Zodis"<<setw(80)<<"| Pasikartojimai tekste"<<endl;
    outputFile <<"---------------------------------------------------------------------------------------------------------"<<endl;
    for (const auto &pora : zodzioDažnumas) {
        if (pora.second > 1) {
            outputFile <<left<<setw(30)<< "| "+ pora.first << setw(80)<< "| " + to_string(pora.second) << endl;
        }
    }

    outputFile.close();

    cout << "Rezultatai išsaugoti rezultatas.txt faile." << endl;

    return 0;
}
