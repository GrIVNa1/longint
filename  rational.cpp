#include <bits/stdc++.h>
#include "integer.h"
#include "natural.h"
#include "rational_struct.h"
using namespace std;
rational fix_rational(const rational& r) {
    rational res = r;
    if (res.numerator.empty()) {
        res.numerator = {0, 0};
    } else if (res.numerator.size() == 1) {
        int sign = res.numerator[0];
        res.numerator = {sign, 0};
    }
    // Знаменатель
    if (res.denominator.empty()) {
        res.denominator = {1};
    } else if (res.denominator.size() == 1 && res.denominator[0] == 0) {
        res.denominator = {1};
    }
    return res;
}

rational RED_Q_Q(const rational &r) { //Q1
    rational q = r;
    vector<int> gcf = GCF_NN_N(TRANS_Z_N(ABS_Z_Z(r.numerator)), r.denominator);
    q.numerator = DIV_ZZ_Z(q.numerator, TRANS_N_Z(gcf));
    q.denominator = DIV_NN_N(q.denominator, gcf);
    return fix_rational(q);
}

bool INT_Q_B(const rational &r) {
    rational q = RED_Q_Q(r);
    return (q.denominator.size() == 1 && q.denominator[0] == 1);
}

rational TRANS_Z_Q (const vector <int> &a) { //Q3
    rational r;
    r.numerator = a;
    r.denominator = {1};
    return r;
}

vector <int> TRANS_Q_Z (const rational &a) { //Q4
    return RED_Q_Q(a).numerator;
}

rational ADD_QQ_Q(const rational &a, const rational &b) {
    rational x = fix_rational(a);
    rational y = fix_rational(b);
    rational res;
    res.numerator = ADD_ZZ_Z(
        MUL_ZZ_Z(x.numerator, TRANS_N_Z(y.denominator)),
        MUL_ZZ_Z(y.numerator, TRANS_N_Z(x.denominator))
    );
    res.denominator = MUL_NN_N(x.denominator, y.denominator);
    return RED_Q_Q(res);
}

rational SUB_QQ_Q(const rational &a, const rational &b) {
    rational x = fix_rational(a);
    rational y = fix_rational(b);
    rational res;
    res.numerator = SUB_ZZ_Z(
        MUL_ZZ_Z(x.numerator, TRANS_N_Z(y.denominator)),
        MUL_ZZ_Z(y.numerator, TRANS_N_Z(x.denominator))
    );
    res.denominator = MUL_NN_N(x.denominator, y.denominator);
    return RED_Q_Q(res);
}

rational MUL_QQ_Q(const rational &a, const rational &b) {
    rational x = fix_rational(a);
    rational y = fix_rational(b);
    rational res;
    res.numerator = MUL_ZZ_Z(x.numerator, y.numerator);
    res.denominator = MUL_NN_N(x.denominator, y.denominator);
    return RED_Q_Q(res);
}

rational DIV_QQ_Q(const rational &a, const rational &b) {
    rational x = fix_rational(a);
    rational y = fix_rational(b);
    rational res;
    res.numerator = MUL_ZZ_Z(x.numerator, TRANS_N_Z(y.denominator));
    res.denominator = MUL_NN_N(x.denominator, TRANS_Z_N(y.numerator));
    return RED_Q_Q(res);
}