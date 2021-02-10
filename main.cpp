#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

const double eps = 1e-5;

bool do_or_not = true;
size_t n, m, k;
const vector<string> rim_numbers = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X"};

class Rational {
 private:
    int a = 0, b = 1;

 public:
    Rational(int _a = 0, int _b = 1) : a(_a), b(_b) {
        if (b < 0) {
            a = -a;
            b = -b;
        }
        int gcd = std::__gcd(std::abs(a), b);
        a /= gcd;
        b /= gcd;
    }
    static void MakeGood(int& x, int &y) {
        if (y < 0) {
            x = -x;
            y = -y;
        }
        int gcd = std::__gcd(std::abs(x), y);
        x /= gcd;
        y /= gcd;
    }
    int numerator() const {
        int gcd = std::__gcd(std::abs(a), b);
        return a / gcd;
    }
    int denominator() const {
        int gcd = std::__gcd(std::abs(a), b);
        return b / gcd;
    }
    Rational operator+(Rational other) const {
        int lcm = (b * other.b) / std::__gcd(b, other.b);
        return Rational(a * (lcm / b) + other.a * (lcm / other.b), lcm);
    }
    Rational operator-(Rational other) const {
        int lcm = (b * other.b) / std::__gcd(b, other.b);
        return Rational(a * (lcm / b) - other.a * (lcm / other.b), lcm);
    }
    Rational operator*(Rational other) const {
        return Rational(a * other.a, b * other.b);
    }
    Rational operator/(Rational other) const {
        return Rational(a * other.b, b * other.a);
    }
    Rational& operator+=(Rational other) {
        int lcm = (b * other.b) / std::__gcd(b, other.b);
        a = a * (lcm / b) + other.a * (lcm / other.b);
        b = lcm;
        MakeGood(a, b);
        return *this;
    }
    Rational& operator-=(Rational other) {
        int lcm = (b * other.b) / std::__gcd(b, other.b);
        a = a * (lcm / b) - other.a * (lcm / other.b);
        b = lcm;
        MakeGood(a, b);
        return *this;
    }
    Rational& operator*=(Rational other) {
        a *= other.a;
        b *= other.b;
        MakeGood(a, b);
        return *this;
    }
    Rational& operator/=(Rational other) {
        a *= other.b;
        b *= other.a;
        MakeGood(a, b);
        return *this;
    }
    Rational operator+() const {
        return Rational(a, b);
    }
    Rational operator-() const {
        return Rational(-a, b);
    }
    bool operator==(Rational other) const {
        return a * other.b == b * other.a;
    }
    bool operator!=(Rational other) const {
        return a * other.b != b * other.a;
    }
    Rational& operator++() {
        return *this += 1;
    }
    Rational& operator--() {
        return *this -= 1;
    }
    const Rational operator++(int) {
        Rational now = *this;
        ++*this;
        return now;
    }
    const Rational operator--(int) {
        Rational now = *this;
        --*this;
        return now;
    }
};

Rational operator+(int x, Rational c) {
    return Rational(x) + c;
}

Rational operator-(int x, Rational c) {
    return Rational(x) - c;
}

Rational operator*(int x, Rational c) {
    return Rational(x) * c;
}

Rational operator/(int x, Rational c) {
    return Rational(x) / c;
}

std::ostream& operator<<(std::ostream& out, Rational x) {
    if (x.denominator() != 1) {
        out << x.numerator() << "/" << x.denominator();
    } else {
        out << x.numerator() ;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Rational& number) {
    int x;
    in >> x;
    number = Rational(x);
    return in;
}

Rational mat[100][100];

void devide(size_t i, Rational x) {
    if (x == 0) {
        return;
    }
    for (size_t j = 0; j < m + k; ++j) {
        mat[i][j] /= x;
    }
    cout << rim_numbers[i] + " = " + rim_numbers[i] << " : " << x << endl;
    do_or_not = true;
}

void subtract(size_t i, size_t i2, Rational x) {
    for (size_t j = 0; j < m + k; ++j) {
        mat[i][j] -= x * mat[i2][j];
    }
    if (x.numerator() < 0) {
        cout << rim_numbers[i]+ " = " + rim_numbers[i] << " + " << -x << " * " << rim_numbers[i2] << endl;
    } else {
        cout << rim_numbers[i]+ " = " + rim_numbers[i] << " - " << x << " * " << rim_numbers[i2] << endl;
    }
    do_or_not = true;
}


void swap_rows(size_t i, size_t i2) {
    if (i != i2) {
        cout << rim_numbers[i] << " <=> " << rim_numbers[i2] << endl;
    }
    for (size_t j = 0; j < m + k; ++j) {
        swap(mat[i][j], mat[i2][j]);
    }
    do_or_not = true;
}

bool do_good(size_t i) {
    for (size_t j = i; j < n; ++j) {
        if (mat[j][i] != 0) {
            swap_rows(i, j);
            return true;
        }
    }
    return false;
}

void check() {
    for (size_t i = 0; i < n; ++i) {
        bool have = 0;
        for (size_t j = 0; j < m; ++j) {
            if (mat[i][j] != 0) have = 1;
        }
        if (!have) {
            for (size_t j = m; j < m + k; ++j) {
                if (mat[i][j] != 0) {
                    cout << "No solution";
                    exit(0);
                }
            }
        }
    }
}

void out() {
    do_or_not = false;
    cout << endl;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            cout << mat[i][j] << ' ';
        }
        cout << " | ";
        for (size_t j = m; j < m + k; ++j) {
            cout << mat[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void out_answer() {
    cout << "Answer:" << endl << endl;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < k; ++j) {
            if(mat[i][i] == 0) {
                cout << "x" << i + 1 << j + 1 << "\t";
                continue;
            }
            if (mat[i][j+m] == 0)  cout << "0";
            else cout << mat[i][j+m];
            for (size_t j2 = i + 1; j2 < m; ++j2) {
                if (mat[i][j2] == 0) continue;
                if (mat[i][j2].numerator() < 0) cout << '+';
                cout << -mat[i][j2] << "*x" << j2+1 << j+1;
            }
            cout << "\t";
        }
        cout << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> k; m = n;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            cin >> mat[i][j];
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = m; j < m + k; ++j) {
            cin >> mat[i][j];
        }
    }
    out();
    check();
    for (size_t j = 0; j < m; ++j) {
        if(!do_good(j)) {
            continue;
        }
        if (mat[j][j] != 1) {
            devide(j, mat[j][j]);
        }
        for (size_t i = j + 1; i < n; ++i) {
            if (mat[i][j] != 0) {
                subtract(i, j, mat[i][j]);
            }
        }
        if (do_or_not) {
            out();
            check();
        }
    }
    cout << "--------------------" << endl << endl;
    for (int j = m - 1; j >= 0; --j) {
        if (mat[j][j] == eps) {
            continue;
        }
        for (int i = j - 1; i >= 0; --i) {
            if (mat[i][j] != 0) {
                subtract(i, j, mat[i][j]);
            }
        }
        if (do_or_not) {
            out();
            check();
        }
    }
    out_answer();
}
