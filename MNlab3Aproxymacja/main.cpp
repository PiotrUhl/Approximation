#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

//funkcja dla kt�rej dokonujemy aproksymacji
double function(double x) {
    return sin(x)*sin(x)*cos(2 * x);
}

//klasa aproksymuj�ca
class AproxGram {
    double(*fun)(double); //funkcja aproksymowana
    double a, b; //granice aproksymowanego przedzia�u
    int n; //ilo�� punkt�w funkcji aproksymowanej
    int m; //stopie� wielomianu
    double dis; //odleg�o�� mi�dzy punktami
    double* X; //wektor wsp�rz�dnych x [n+1]
    double* Y; //wektor wsp�rz�dnych y [n+1]
    double* A; //wektor wsp�czynnik�w [m]
    double S; //warto�� b��du
public:
    //konstruktor
    AproxGram(double(*_f)(double), double _a, double _b, int _n, int _m) : fun(_f), a(_a), b(_b), n(_n), m(_m) {
        dyskretyzacja();
        aproksymacja();
        blad();
    }
    //destruktor
    ~AproxGram() {
        delete[] X;
        delete[] Y;
        delete[] A;
    }
    //zwraca warto�� funkcji aproksymowanej w punkcie numer i
    double f(int i) {
        return fun(X[i]);
    }
    //zwraca warto�� funkcji aproksymuj�cej w punkcie numer i
    double Q(int i) {
        double sum = 0;
        for (int j = 0; j < m; j++) {
            sum += A[j] * Pk(j, n, (X[i] - X[0]) / dis);
        }
        return sum;
    }
    //wypisuje wyniki aproksymacji do strumienia ostr
    void out(ostream& ostr) {
        //parametry (# dla gnuplota)
        ostr << "# Parametry aproksymacji: \n";
        ostr << "# <" << a << ", " << b << ">\n# n = " << n << "\n# m = " << m << "\n";
        //b��d (# dla gnuplota)
        ostr << "# Blad aproksymacji:\n# " << S << '\n';
        //wsp�czynniki (# dla gnuplota)
        ostr << "# Wspolczynniki: \n";
        for (int i = 0; i < m; i++)
            ostr << "# a[" << i << "] = " << A[i] << "\n";
        ostr << "# Wartosci: \n";
        ostr << "# x\tQ(x)\n";
        //tablica warto�ci
        for (int i = 0; i < n; i++) {
            ostr << X[i] << '\t' << Q(i) << '\n';
        }
    }
private:
    //dokonuje dyskretyzacji funkcji f w przedziale <a, b>, dziel�c funkcj� na n punkt�w
    void dyskretyzacja() {
        X = new double[n+1];
        Y = new double[n+1];
        dis = (abs(a) + abs(b)) / static_cast<double>(n);
        for (int i = 0; i <= n; i++) {
            X[i] = i * dis + a;
            Y[i] = fun(X[i]);
        }
    }
    //dokonuje aproksymacji funkcji f z u�yciem wielomian�w ortogonalnych
    void aproksymacja() {
        A = new double[m];
        for (int j = 0; j < m; j++) {
            double c = 0;
            for (int q = 0; q <= n; q++) {
                c += Y[q] * Pk(j, n, q);
            }
            double s = 0;
            for (int q = 0; q <= n; q++) {
                s += pow(Pk(j, n, q), 2);
            }
            A[j] = c / s;
        }
    }
    //oblicza b��d aproksymacji
    void blad() {
        double sum = 0;
        for (int i = 0; i <= n; i++) {
            sum += pow(Q(i) - Y[i], 2);
        }
        S = sqrt(sum / (n + 1));
    }
    //dwumian Newtona
    double dwumianNewtona(double k, int s) {
        double ret = 1;
        for (int i = 1; i <= s; i++) {
            ret *= (k - i + 1) / i;
        }
        return ret;
    }
    //symbol r^[s]
    double symbolrs(double r, int s) {
        double res = 1;
        for (int i = 1; i <= s; i++) {
            res *= (r - i + 1);
        }
        return res;
    }
    //wielomian Grama Pk^(n)(q)
    double Pk(int k, int n, double q) {
        double sum = 0;
        for (int s = 0; s <= k; s++) {
            sum += pow(-1, s) * dwumianNewtona(k, s) * dwumianNewtona(k + s, s) * (symbolrs(q, s) / symbolrs(n, s));
        }
        return sum;
    }
};

int main(int argc, char** argv) {
    AproxGram aprox(function, atof(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]));
    ofstream ofile(argv[5]);
    aprox.out(ofile);
    ofile.close();
    return 0;
}