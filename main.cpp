#include <bits/stdc++.h>
#include "natural.h"
#include "integer.h"
#include "polynomial.h"
#include "rational.h"



bool equal_rational(const rational& a, const rational& b) {
    rational ra = RED_Q_Q(a);
    rational rb = RED_Q_Q(b);
    if (ra.numerator.size() != rb.numerator.size()) return false;
    if (ra.denominator.size() != rb.denominator.size()) return false;
    for (size_t i = 0; i < ra.numerator.size(); ++i)
        if (ra.numerator[i] != rb.numerator[i]) return false;
    for (size_t i = 0; i < ra.denominator.size(); ++i)
        if (ra.denominator[i] != rb.denominator[i]) return false;
    return true;
}

vector<rational> normalize_poly(const vector<rational>& p) {
    vector<rational> res = p;
    while (res.size() > 1 && res[0].numerator[0] == 0)
        res.erase(res.begin());
    return res;
}

bool equal_poly(const vector<rational>& a, const vector<rational>& b) {
    vector<rational> na = normalize_poly(a);
    vector<rational> nb = normalize_poly(b);
    if (na.size() != nb.size()) return false;
    for (size_t i = 0; i < na.size(); ++i)
        if (!equal_rational(na[i], nb[i])) return false;
    return true;
}

using namespace std;
vector <int> INPUT_N() {
    vector<int> input = {};
    char t;
    t = (char)getchar();
    while (t != '\n') {
        input.push_back(t - '0');
        t = (char)getchar();
    }
    return input;
}
vector <int> INPUT_Z() {
    vector<int> input;
    char t = (char)getchar();
    int sign = 1;
    if (t == '-') {
        sign = -1;
        t = (char)getchar();
    }
    vector<int> digits;
    while (t != '\n') {
        digits.push_back(t - '0');
        t = (char) getchar();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        sign = 0;
    }
    input.push_back(sign);
    input.insert(input.end(), digits.begin(), digits.end());
    return input;
}
rational INPUT_Q() {
    rational q;
    vector<int> input;
    char t = (char)getchar();
    int sign = 1;
    if (t == '-') {
        sign = -1;
        t = (char)getchar();
    }
    vector<int> digits;
    while (t != '/') {
        digits.push_back(t - '0');
        t = (char) getchar();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        sign = 0;
    }
    input.push_back(sign);
    input.insert(input.end(), digits.begin(), digits.end());
    q.numerator = input;
    q.denominator = INPUT_N();
    return q;
}
vector <rational> INPUT_P() {
    int m;
    cout << "input pow:";
    cin >> m;
    cin.ignore();
    vector <rational> h = {};
    for (int i = 0; i <= m; i++) {
        cout << "x^" << m-i << ":";
        h.push_back(INPUT_Q());
    }
    return h;
}

void PRINT_N(const vector<int>& a) {
    for (auto i: a) {
        cout << i;
    }
    cout << endl;
}
void PRINT_Z(const vector<int>& a) {
    if (a[0] == 0) {
        cout << "0" << endl;
        return;
    }
    if (a[0] == 1) cout << "+";
    else cout << "-";
    for (int i = 1; i < a.size(); i++) {
        cout << a[i];
    }
    cout << endl;
}
void PRINT_Q(const rational &t) {
    vector<int> f = t.numerator;
    if (f[0] == 1) cout << "+";
    if (f[0] == -1) cout << "-";
    for (int i = 1; i < f.size(); i++) {
        cout << f[i];
    }
    cout << "/";
    PRINT_N(t.denominator);
    cout << endl;
}
void PRINT_P(const vector<rational>& a) {
    bool first = true;
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        if (a[i].numerator[0] == 0) continue;
        if (a[i].numerator[0] == 1) {
            if (!first) cout << "+";
        } else {
            cout << "-";
        }
        first = false;
        for (size_t j = 1; j < a[i].numerator.size(); ++j)
            cout << a[i].numerator[j];
        cout << "/";
        for (auto d : a[i].denominator) cout << d;
        int deg = n - 1 - i;
        if (deg > 0) {
            cout << "x";
            if (deg > 1) cout << "^" << deg;
        }
    }
    if (first) cout << "0";
    cout << endl;
}

int main() {
    char t;
    cin >> t;

    switch (t) {
        case 'N': {
            int h;
            cin >> h;
            cin.ignore();
            switch (h) {
                case 1: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    cout << COM_NN_D(a, b) << endl;
                    break;
                }
                case 2: {
                    vector<int> a = INPUT_N();
                    cout << NZER_N_B(a) << endl;
                    break;
                }
                case 3: {
                    vector<int> a = INPUT_N();
                    PRINT_N(ADD_1N_N(a));
                    break;
                }
                case 4: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(ADD_NN_N(a, b));
                    break;
                }
                case 5: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(SUB_NN_N(a, b));
                    break;
                }
                case 6: {
                    vector<int> a = INPUT_N();
                    int n;
                    cin >> n;
                    PRINT_N(MUL_ND_N(a, n));
                    break;
                }
                case 7: {
                    vector<int> a = INPUT_N();
                    int k;
                    cin >> k;
                    PRINT_N(MUL_Nk_N(a, k));
                    break;
                }
                case 8: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(MUL_NN_N(a, b));
                    break;
                }
                case 9: {
                    vector<int> a = INPUT_N();
                    int n;
                    cin >> n;
                    vector<int> b = INPUT_N();
                    PRINT_N(SUB_NDN_N(a, n, b));
                    break;
                }
                case 10: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(DIV_NN_Dk(a, b));
                    break;
                }
                case 11: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(DIV_NN_N(a, b));
                    break;
                }
                case 12: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(MOD_NN_N(a, b));
                    break;
                }
                case 13: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(GCF_NN_N(a, b));
                    break;
                }
                case 14: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_N(LCM_NN_N(a, b));
                    break;
                }
                default:
                    cout << "incorrect input" << endl;
                    return 0;
            }
            break;
        }
        case 'Z': {
            int h;
            cin >> h;
            cin.ignore();
            switch (h) {
                case 1: {
                    vector<int> a = INPUT_Z();
                    PRINT_Z(ABS_Z_Z(a));
                    break;
                }
                case 2: {
                    vector<int> a = INPUT_Z();
                    cout << SGN_Z_D(a) << endl;
                    break;
                }
                case 3: {
                    vector<int> a = INPUT_Z();
                    PRINT_Z(MUL_ZM_Z(a));
                    break;
                }
                case 4: {
                    vector<int> a = INPUT_N();
                    PRINT_Z(TRANS_N_Z(a));
                    break;
                }
                case 5: {
                    vector<int> a = INPUT_Z();
                    PRINT_Z(TRANS_Z_N(a));
                    break;
                }
                case 6: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_Z(ADD_ZZ_Z(a, b));
                    break;
                }
                case 7: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_Z(SUB_ZZ_Z(a, b));
                    break;
                }
                case 8: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_Z(MUL_ZZ_Z(a, b));
                    break;
                }
                case 9: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_Z(DIV_ZZ_Z(a, b));
                    break;
                }
                case 10: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_Z(MOD_ZZ_Z(a, b));
                    break;
                }
                default:
                    cout << "incorrect input" << endl;
                    return 0;
            }
            break;
        }
        case 'Q': {
            int h;
            cin >> h;
            cin.ignore();
            switch (h) {
                case 1: {
                    rational input = INPUT_Q();
                    // PRINT_N(input.numerator);
                    // PRINT_N(input.denominator);
                    input = RED_Q_Q(input);
                    PRINT_Q(input);
                    break;
                }
                case 2: {
                    rational a = INPUT_Q();
                    cout << INT_Q_B(a) << endl;
                    break;
                }
                case 3: {
                    vector<int> a = INPUT_Z();
                    PRINT_Q(TRANS_Z_Q(a));
                    break;
                }
                case 4: {
                    rational a = INPUT_Q();
                    PRINT_Z(TRANS_Q_Z(a));
                    break;
                }
                case 5: {
                    rational a = INPUT_Q();
                    rational b = INPUT_Q();
                    PRINT_Q(ADD_QQ_Q(a,b));
                    break;
                }
                case 6: {
                    rational a = INPUT_Q();
                    rational b = INPUT_Q();
                    PRINT_Q(SUB_QQ_Q(a,b));
                    break;
                }
                case 7: {
                    rational a = INPUT_Q();
                    rational b = INPUT_Q();
                    PRINT_Q(MUL_QQ_Q(a,b));
                    break;
                }
                case 8: {
                    rational a = INPUT_Q();
                    rational b = INPUT_Q();
                    PRINT_Q(DIV_QQ_Q(a,b));
                }
                default:
                    cout << "Incorrect input" << endl;
            }
            break;
        }
        case 'P': {
            int h;
            cin >> h;
            cin.ignore();
            switch (h) {
                case 1: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(ADD_PP_P(a, b));
                    break;
                }
                case 2: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(SUB_PP_P(a, b));
                    break;
                }
                case 3: {
                    vector<rational> a = INPUT_P();
                    rational b = INPUT_Q();
                    PRINT_P(MUL_PQ_P(a, b));
                    break;
                }
                case 4: {
                    vector<rational> a = INPUT_P();
                    unsigned long long k;
                    cin >> k;
                    PRINT_P(MUL_Pxk_P(a, k));
                    break;
                }
                case 5: {
                    vector<rational> a = INPUT_P();
                    PRINT_Q(LED_P_Q(a));
                    break;
                }
                case 6: {
                    vector<rational> a = INPUT_P();
                    cout << DEG_P_N(a) << endl;
                    break;
                }
                case 7: {
                    vector<rational> a = INPUT_P();
                    PRINT_Q(FAC_P_Q(a));
                    break;
                }
                case 8: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(DIV_PP_P(a, b));
                    break;
                }
                case 9: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(MOD_PP_P(a, b));
                    break;
                }
                case 10: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(GCF_PP_P(a, b));
                    break;
                }
                case 11: {
                    vector<rational> a = INPUT_P();
                    PRINT_P(DER_P_P(a));
                    break;
                }
                case 12: {
                    vector<rational> a = INPUT_P();
                    PRINT_P(NMR_P_P(a));
                    break;
                }
                default:
                    cout << "incorrect input" << endl;
                    return 0;
            }
            break;
        }
        default: {
            cout << "incorrect input" << endl;
        }
        return 0;
    }

    return 0;
}