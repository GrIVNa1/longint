#include <bits/stdc++.h>
#include "integer.h"
#include "natural.h"
#include "rational_struct.h"
using namespace std;


rational RED_Q_Q (const rational &r) { //Q1
    rational q = r;
    vector <int> gcf = GCF_NN_N(TRANS_Z_N(r.numerator), r.denominator);
    q.numerator = DIV_ZZ_Z(q.numerator, TRANS_N_Z(gcf));
    // cout << 1 << endl;
    q.denominator = DIV_NN_N(q.denominator, gcf);
    // cout << 1 << endl;
    return q;
}

bool INT_Q_B(const rational &r) { //Q2
    rational q = RED_Q_Q(r);
    if (q.denominator.size() == 2 && q.denominator[1] == 1) return true;
    return false;
}

rational TRANS_Z_Q (const vector <int> &a) { //Q3
    rational r;
    r.numerator = a;
    r.denominator = {1};
    return r;
}

vector <int> TRANS_Q_Z (const rational &a) { //Q4
    return RED_Q_Q(a).denominator;
}

rational ADD_QQ_Q (const rational &a, const rational &b) { //Q5
    rational c;
    c.denominator = LCM_NN_N(a.denominator, b.denominator);
    c.numerator = ADD_ZZ_Z(MUL_ZZ_Z(a.numerator, TRANS_N_Z(DIV_NN_N(c.denominator, a.denominator))),MUL_ZZ_Z(b.numerator, TRANS_N_Z(DIV_NN_N(c.denominator, b.denominator))));
    return RED_Q_Q(c);
}

rational SUB_QQ_Q (const rational &a, const rational &b) { //Q6
    rational c;
    c.denominator = LCM_NN_N(a.denominator, b.denominator);
    c.numerator = SUB_ZZ_Z(MUL_ZZ_Z(a.numerator, TRANS_N_Z(DIV_NN_N(c.denominator, a.denominator))),MUL_ZZ_Z(b.numerator, TRANS_N_Z(DIV_NN_N(c.denominator, b.denominator))));
    return RED_Q_Q(c);
}

rational MUL_QQ_Q(const rational &a, const rational &b) { //Q7
    rational c;
    c.numerator = MUL_ZZ_Z(a.numerator, b.numerator);
    c.denominator = MUL_NN_N(a.denominator, b.denominator);
    return RED_Q_Q(c);
}

rational DIV_QQ_Q(const rational &a, const rational &b) { //Q8
    rational c;
    c.numerator = MUL_ZZ_Z(a.numerator, TRANS_N_Z(b.denominator));
    c.denominator = MUL_NN_N(c.denominator, TRANS_Z_N(b.numerator));
    return RED_Q_Q(c);
}