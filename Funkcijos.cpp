#include "Funkcijos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <set>
#include <map>
#include <sstream>

using namespace std;

void Nuorodos(const string& failoPavadinimas, set<string>  visiURL) {
    ofstream urlFailas(failoPavadinimas);

    try {
        if (!urlFailas.is_open()) {
            throw runtime_error("Nepavyko sukurti failo.");
        }

    urlFailas << "Domenai:"<<endl;
    urlFailas <<"-------------------------------------------"<<endl;
    for (const string& domenas : visiURL) {
        urlFailas << domenas << endl;
    }
    urlFailas.close();
    } 
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    } 
}

void BendrasPasikartojimas (const string& failoPavadinimas, map<string, map<int, int> >& zodziuPasikartojimai) {
    ofstream outputFile(failoPavadinimas);

        try {
        if (!outputFile.is_open()) {
            throw runtime_error("Nepavyko sukurti failo.");
        }
        outputFile <<left<<setw(30)<<"| Zodis"<<setw(80)<<"| Pasikartojimai tekste"<<endl;
        outputFile <<"---------------------------------------------------------------------------------------------------------"<<endl;
        for (const auto &pora : zodziuPasikartojimai) {
        if (pora.second.size() > 1 && !any_of(pora.first.begin(), pora.first.end(), ::isdigit)) {
            outputFile << left << setw(30) << "| " + pora.first << setw(80) << "| " + to_string(pora.second.size()) << endl;
        }
    }
    outputFile.close();
    } 
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    } 
}

void EilutesIrPasikartojimai (const string& failoPavadinimas, map<string, map<int, int> >& zodziuPasikartojimai) {
    ofstream rezultatuFailas(failoPavadinimas);

    try {
        if (!rezultatuFailas.is_open()) {
            throw runtime_error("Nepavyko sukurti failo.");
        }

    rezultatuFailas << left << setw(30) << "| Žodis" << left << setw(80) << "| Eilutes numeris (Pasikartojimai)" << endl;
    rezultatuFailas << left << setfill('-') << left << setw(110) << " " << setfill(' ') << endl;

    for (const auto& irasas : zodziuPasikartojimai) {
        const string& zodis = irasas.first;
        const map<int, int>& pasikartojimai = irasas.second;

        if (pasikartojimai.size() > 1 && !any_of(zodis.begin(), zodis.end(), ::isdigit)) {
            stringstream eiluciuNumeriaiSrautas;                                //Eilučių numerių formavimas:
            for (const auto& eilutesirasas : pasikartojimai) {
                eiluciuNumeriaiSrautas << eilutesirasas.first << " (" << eilutesirasas.second << "); ";
            }

            string eiluciuNumeriai = eiluciuNumeriaiSrautas.str();
            eiluciuNumeriai.pop_back();

            rezultatuFailas << left << setw(30) << "| " + zodis << left << setw(80) << "| " + eiluciuNumeriai << endl;
        }
    }

    rezultatuFailas.close();
    } 
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    } 
}

void TaiFailas(const string& failoVardas, const vector<string>& ZodisSuTai) {
    ofstream out(failoVardas);
    out <<"Zodziai su junginiu - tai: "<<endl;
    out <<"-------------------------------- "<<endl;
    for (const auto& zodis : ZodisSuTai) {
        out << zodis << endl;
    }
    out.close();
}
