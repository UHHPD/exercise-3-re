#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;


double poisson(double mu, int k) {
    return exp(-mu) * pow(mu, k) / tgamma(k + 1);
}

double Likelyhood(const vector<int>& data, double mu) {
    double likelihood = 1.0;
    for (int k : data) {
        likelihood *= poisson(mu, k);
    }
    return likelihood;
}

int main() {
    using namespace std;

    double mu = 3.11538;
    vector<int> data;
    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        data.push_back(n_i);
    }
    fin.close();
// Compute likelihood (a)
    double likelihood = Likelyhood(data, mu);
    cout << "Likelihood: " << likelihood << endl;
// End of (a)

// Likelyhood Scan (b)
    ofstream fL("likelihood.txt");
    for(double mu_scan = 0.0 ; mu_scan <= 6.0 ; mu_scan += 0.1) {
        double L = Likelyhood(data, mu_scan);
        fL << mu_scan << "\t" << L << endl;
    }
    fL.close();
// End of (b)

// NLL Scan (c)
    ofstream fNLL("nll.txt");
    for(double mu_scan = 0.0 ; mu_scan <= 6.0 ; mu_scan += 0.1) {
        double L = Likelyhood(data, mu_scan);
        double NLL = -2*log(L);
        fNLL << mu_scan << "\t" << NLL << endl;
    }
    fNLL.close();
// End of (c)

// deltaNLL (d)
    double L_max = Likelyhood(data, mu);
    double NLL_min = -2*log(L_max);
    ofstream fdeltaNLL("deltanll.txt");
    double mu_lower = -1.0;
    double mu_upper = 1.0;
    for(double mu_scan = 0.0 ; mu_scan <= 6.0 ; mu_scan += 0.001) {
        double L = Likelyhood(data, mu_scan);
        double NLL = -2*log(L);
        double deltaNLL = NLL - NLL_min;
        fdeltaNLL << mu_scan << "\t" << deltaNLL << endl;

        if (deltaNLL < 1.0) {
            if (mu_lower < 0.0) {
                mu_lower = mu_scan;
            }
            mu_upper = mu_scan;
        }
    }
    fdeltaNLL.close();
    cout << "Error Interval: [" << mu_lower << " to " << mu_upper << "]" << endl;
// End of (d)

// Test against satureted model (e)
    double L_saturated = 1.0;
    for (int k : data) {
        L_saturated *= poisson(k, k);
    }
    double Lambda = likelihood / L_saturated;
    double minus2lnLambda = -2 * log(Lambda);

    cout << "L_saturated: " << L_saturated << endl;
    cout << "Lambda: " << Lambda << endl;
    cout << "-2 ln Lambda: " << minus2lnLambda<< endl;

    int ndof = data.size() - 1;
    cout << "Degrees of Freedom: " << ndof << endl;

    double z = (minus2lnLambda - ndof) / sqrt(2 * ndof);
    cout << "Standard Deviations from Saturated Model: " << z << endl;
// End of (e)
    return 0;
}