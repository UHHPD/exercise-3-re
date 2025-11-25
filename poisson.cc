#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    double P_zaehler = std::exp(-mu) * std::pow(mu, k);
    double P_nenner = std::tgamma(k + 1);
    return P_zaehler / P_nenner;
}

int main() {
    using namespace std;

    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;
    }
    for (unsigned int k = 0; k < zaehler.size() ; ++k) {
    std::cout << k << " : " << zaehler[k] << std::endl;
    }
    fin.close();

    ofstream output("hist.txt");
    for (int i = 0; i < (int)zaehler.size(); ++i) {
        output << i << " " << zaehler[i] << endl;
    }
    output.close();

    ofstream output2("histpoi.txt");
    double Poisson;
    for (int i = 0; i < (int)zaehler.size(); ++i) {
        Poisson = poisson(3.11538, i) * 234;
        output2 << i << " " << zaehler[i] << " " << Poisson << endl;
    }
    output2.close();
    return 0;
}