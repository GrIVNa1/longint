#include <bits/stdc++.h>
#include "natural.h"
#include "integer.h"
#include "polynomial.h"
#include "rational.h"

using namespace std;

vector<int> INPUT_N() {
    vector<int> input = {};
    char t;
    t = (char)getchar();
    while (t != '\n') {
        input.push_back(t - '0');
        t = (char)getchar();
    }
    return input;
}

vector<int> INPUT_Z() {
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
        t = (char)getchar();
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
        t = (char)getchar();
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

vector<rational> INPUT_P() {
    string line;
    getline(cin, line);
    if (line.empty()) return {};

    auto str_to_natural = [](const string& s) -> vector<int> {
        vector<int> res;
        for (char c : s) {
            if (!isdigit(c)) break;
            res.push_back(c - '0');
        }
        if (res.empty()) res = {0};
        while (res.size() > 1 && res[0] == 0) res.erase(res.begin());
        return res;
    };

    auto str_to_integer = [&](const string& s) -> vector<int> {
        if (s.empty()) return {0, 0};
        int sign = 1;
        string num_str = s;
        if (num_str[0] == '-') {
            sign = -1;
            num_str = num_str.substr(1);
        } else if (num_str[0] == '+') {
            num_str = num_str.substr(1);
        }
        vector<int> digits = str_to_natural(num_str);
        if (digits.size() == 1 && digits[0] == 0) return {0, 0};
        vector<int> res;
        res.push_back(sign);
        res.insert(res.end(), digits.begin(), digits.end());
        return res;
    };

    auto str_to_rational = [&](const string& s) -> rational {
        size_t slash = s.find('/');
        if (slash == string::npos) {
            rational r;
            r.numerator = str_to_integer(s);
            r.denominator = {1};
            return r;
        } else {
            string num_part = s.substr(0, slash);
            string den_part = s.substr(slash + 1);
            rational r;
            r.numerator = str_to_integer(num_part);
            r.denominator = str_to_natural(den_part);
            if (r.denominator.empty()) r.denominator = {1};
            return r;
        }
    };

    auto parse_term = [&](const string& term) -> pair<rational, int> {
        if (term.empty()) return {rational{{0,0},{1}}, 0};
        size_t xpos = term.find('x');
        if (xpos == string::npos) {
            return {str_to_rational(term), 0};
        }
        string coeff_str = term.substr(0, xpos);
        rational coeff;
        if (coeff_str.empty() || coeff_str == "+" || coeff_str == "-") {
            int sign = 1;
            if (coeff_str == "-") sign = -1;
            vector<int> num = (sign == 1) ? vector<int>{1,1} : vector<int>{-1,1};
            coeff.numerator = num;
            coeff.denominator = {1};
        } else {
            coeff = str_to_rational(coeff_str);
        }
        int deg = 1;
        if (xpos + 1 < term.size() && term[xpos+1] == '^') {
            size_t start = xpos+2;
            size_t end = start;
            while (end < term.size() && isdigit(term[end])) ++end;
            string deg_str = term.substr(start, end-start);
            deg = stoi(deg_str);
        }
        return {coeff, deg};
    };

    vector<string> terms;
    int len = line.size();
    if (len == 0) return {};
    string processed = line;
    if (processed[0] != '+' && processed[0] != '-') {
        processed = "+" + processed;
    }
    int start = 0;
    for (size_t j = 1; j < processed.size(); ++j) {
        if (processed[j] == '+' || processed[j] == '-') {
            terms.push_back(processed.substr(start, j - start));
            start = j;
        }
    }
    terms.push_back(processed.substr(start));

    vector<pair<rational, int>> parsed_terms;
    int max_deg = 0;
    for (const string& t : terms) {
        auto [coeff, deg] = parse_term(t);
        parsed_terms.push_back({coeff, deg});
        if (deg > max_deg) max_deg = deg;
    }

    rational zero;
    zero.numerator = {0, 0};
    zero.denominator = {1};
    vector<rational> poly(max_deg + 1, zero);

    for (auto& [coeff, deg] : parsed_terms) {
        int idx = max_deg - deg;
        poly[idx] = coeff;
    }

    while (poly.size() > 1 && poly[0].numerator[0] == 0) {
        poly.erase(poly.begin());
    }
    return poly;
}

void PRINT_N(const vector<int>& a) {
    for (auto i : a) {
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

void PRINT_Q(const rational& t) {
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

static string nat_to_compact(const vector<int>& num) {
    if (num.empty()) return "0";
    if (num.size() == 1 && num[0] == 0) return "0";

    bool is_power_like = true;
    for (size_t i = 1; i < num.size(); ++i) {
        if (num[i] != 0) {
            is_power_like = false;
            break;
        }
    }

    if (is_power_like) {
        int k = num.size() - 1;
        if (k == 0) return to_string(num[0]);
        if (num[0] == 1) return "10^{" + to_string(k) + "}";
        return to_string(num[0]) + "*10^{" + to_string(k) + "}";
    }

    string s;
    for (int d : num) s += to_string(d);
    return s;
}

void PRINT_P(const vector<rational>& a) {
    bool first = true;
    int n = a.size();

    for (int i = 0; i < n; ++i) {
        if (a[i].numerator[0] == 0) continue;
        int sign = a[i].numerator[0];
        if (sign == 1) {
            if (!first) cout << "+";
        } else {
            cout << "-";
        }
        first = false;

        vector<int> num_digits(a[i].numerator.begin() + 1, a[i].numerator.end());
        cout << nat_to_compact(num_digits);

        bool den_is_one = (a[i].denominator.size() == 1 && a[i].denominator[0] == 1);
        if (!den_is_one) {
            cout << "/" << nat_to_compact(a[i].denominator);
        }

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
        case 'H': {
            cout << "N - Natural" << endl;
            cout << "Z - Integer" << endl;
            cout << "Q - Rational" << endl;
            cout << "P - Polynomial" << endl;
            break;
        }
        case 'N': {
            char h;
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
                    cout << "input number of function" << endl;
                    cout << "1 - COM_NN_D" << endl;
                    cout << "2 - NZER_N_B" << endl;
                    cout << "3 - ADD_1N_N" << endl;
                    cout << "4 - ADD_NN_N" << endl;
                    cout << "5 - SUB_NN_N" << endl;
                    cout << "6 - MUL_ND_N" << endl;
                    cout << "7 - MUL_Nk_N" << endl;
                    cout << "8 - MUL_NN_N" << endl;
                    cout << "9 - SUB_NDN_N" << endl;
                    cout << "10 - DIV_NN_Dk" << endl;
                    cout << "11 - DIV_NN_N" << endl;
                    cout << "12 - MOD_NN_N" << endl;
                    cout << "13 - GCF_NN_N" << endl;
                    cout << "14 - LCM_NN_N" << endl;
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
                    cout << "input number of function" << endl;
                    cout << "1 - ABS_Z_Z" << endl;
                    cout << "2 - POZ_Z_D" << endl;
                    cout << "3 - MUL_ZM_Z" << endl;
                    cout << "4 - TRANS_N_Z" << endl;
                    cout << "5 - TRANS_Z_N" << endl;
                    cout << "6 - ADD_ZZ_Z" << endl;
                    cout << "7 - SUB_ZZ_Z" << endl;
                    cout << "8 - MUL_ZZ_Z" << endl;
                    cout << "9 - DIV_ZZ_Z" << endl;
                    cout << "10 - MOD_ZZ_Z" << endl;
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
                    PRINT_Q(ADD_QQ_Q(a, b));
                    break;
                }
                case 6: {
                    rational a = INPUT_Q();
                    rational b = INPUT_Q();
                    PRINT_Q(SUB_QQ_Q(a, b));
                    break;
                }
                case 7: {
                    rational a = INPUT_Q();
                    rational b = INPUT_Q();
                    PRINT_Q(MUL_QQ_Q(a, b));
                    break;
                }
                case 8: {
                    rational a = INPUT_Q();
                    rational b = INPUT_Q();
                    PRINT_Q(DIV_QQ_Q(a, b));
                    break;
                }
                default:
                    cout << "input number of function" << endl;
                    cout << "1 - RED_Q_Q" << endl;
                    cout << "2 - INT_Q_B" << endl;
                    cout << "3 - TRANS_Z_Q" << endl;
                    cout << "4 - TRANS_Q_Z" << endl;
                    cout << "5 - ADD_QQ_Q" << endl;
                    cout << "6 - SUB_QQ_Q" << endl;
                    cout << "7 - MUL_QQ_Q" << endl;
                    cout << "8 - DIV_QQ_Q" << endl;
                    return 0;
            }
            break;
        }
        case 'P': {
            int h;
            cin >> h;
            cin.ignore();
            switch (h) {
                case 1: {
                    cout << "first term:";
                    vector<rational> a = INPUT_P();
                    cout << "second term:";
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
                    PRINT_P(MUL_PP_P(a, b));
                    break;
                }
                case 9: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(DIV_PP_P(a, b));
                    break;
                }
                case 10: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(MOD_PP_P(a, b));
                    break;
                }
                case 11: {
                    vector<rational> a = INPUT_P();
                    vector<rational> b = INPUT_P();
                    PRINT_P(GCF_PP_P(a, b));
                    break;
                }
                case 12: {
                    vector<rational> a = INPUT_P();
                    PRINT_P(DER_P_P(a));
                    break;
                }
                case 13: {
                    vector<rational> a = INPUT_P();
                    PRINT_P(NMR_P_P(a));
                    break;
                }
                default:
                    cout << "input number of function" << endl;
                    cout << "1 - ADD_PP_P" << endl;
                    cout << "2 - SUB_PP_P" << endl;
                    cout << "3 - MUL_PQ_P" << endl;
                    cout << "4 - MUL_Pxk_P" << endl;
                    cout << "5 - LED_P_Q" << endl;
                    cout << "6 - DEG_P_N" << endl;
                    cout << "7 - FAC_P_Q" << endl;
                    cout << "8 - MUL_PP_P" << endl;
                    cout << "9 - DIV_PP_P" << endl;
                    cout << "10 - MOD_PP_P" << endl;
                    cout << "11 - GCF_PP_P" << endl;
                    cout << "12 - DER_P_P" << endl;
                    cout << "13 - NMR_P_P" << endl;
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