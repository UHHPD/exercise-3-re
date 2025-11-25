#include <iostream>
#include <fstream>
#include <vector>


double poisson(double mu, int k) {
    return 0;
}

int main() {
    using namespace std;

    vector<int> zaehler(11);

    ifstream input("datensumme.txt");
    int val;
    for(int i = 0 ; i < 234 ; ++i) {
        input >> val;
        zaehler[val] += 1;
    }
    for ( unsigned int k = 0 ; k < zaehler . size () ; ++ k ) {
    std :: cout << k << " : " << zaehler [ k ] << std :: endl ;
    }
    input.close();
}