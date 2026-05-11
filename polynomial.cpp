#include <bits/stdc++.h>

#include "integer.h"
#include "rational_struct.h"
#include "rational.h"
#include "natural.h"
using namespace std;
vector<rational> ADD_PP_P(const vector<rational>& g, const vector<rational>& f) { //P1
    vector<rational> a = g, b = f;
    if (a.size() < b.size()) swap(a, b);
    vector<rational> c = a;
    int shift = a.size() - b.size();
    for (int i = 0; i < b.size(); ++i)
        c[shift + i] = ADD_QQ_Q(c[shift + i], b[i]);
    while (c.size() > 1 && c[0].numerator[0] == 0)
        c.erase(c.begin());
    return c;
}

vector<rational> SUB_PP_P(const vector<rational>& g, const vector<rational>& f) {//P2
    vector<rational> a = g, b = f;
    if (a.size() < b.size()) swap(a, b);
    vector<rational> c = a;
    int shift = a.size() - b.size();
    for (int i = 0; i < b.size(); ++i)
        c[shift + i] = SUB_QQ_Q(c[shift + i], b[i]);
    while (c.size() > 1 && c[0].numerator[0] == 0)
        c.erase(c.begin());
    return c;
}

vector<rational> MUL_PQ_P(const vector<rational>& g, const rational& f) { //P3
    vector<rational> a = g;
    rational q = f;
    for (int i = 0; i < a.size(); ++i) {
        a[i] = MUL_QQ_Q(a[i], q);
    }
    return a;
}

vector<rational> MUL_Pxk_P(const vector<rational> &g, unsigned long long k) { // p4
    vector<rational> a = g;
    rational zero;
    zero.numerator = {0, 0};
    zero.denominator = {1};
    for (unsigned long long i = 0; i < k; ++i)
        a.push_back(zero);
    return a;
}

rational LED_P_Q (const vector<rational> &g) { //P5
    return g[0];
}

int DEG_P_N(const vector<rational> &g) { //P6
    return g.size()-1;
}



rational FAC_P_Q(const vector<rational>& g) { //P7
    vector<int> l = {1}, n;
    for (auto& c : g) l = LCM_NN_N(l, c.denominator);
    for (auto& c : g) if (c.numerator[0]) {
        auto t = MUL_ZZ_Z(c.numerator, TRANS_N_Z(DIV_NN_N(l, c.denominator)));
        auto a = TRANS_Z_N(ABS_Z_Z(t));
        n = n.empty() ? a : GCF_NN_N(n, a);
    }
    return RED_Q_Q({{TRANS_N_Z(n)}, l});
}

vector<rational> MUL_PP_P(const vector<rational>& g, const vector<rational>& f) { // P8
    vector<rational> res = { rational{{0,0}, {1}} };
    for (size_t i = 0; i < g.size(); ++i) {
        int k = g.size() - 1 - i;
        vector<rational> term = MUL_PQ_P(f, g[i]);
        term = MUL_Pxk_P(term, k);
        res = ADD_PP_P(res, term);
    }
    return res;
}

vector<rational> DIV_PP_P(const vector<rational>& g, const vector<rational>& f) { //P9
    vector<rational> a = g, b = f, q;
    while (a.size() >= b.size() && a[0].numerator[0] != 0) {
        unsigned long long k = a.size() - b.size();
        rational c = DIV_QQ_Q(a[0], b[0]);
        vector<rational> m = MUL_Pxk_P(vector<rational>{c}, k);
        a = SUB_PP_P(a, MUL_Pxk_P(MUL_PQ_P(b, c), k));
        q = ADD_PP_P(q, m);
        while (a.size() > 0 && a[0].numerator[0] == 0)
            a.erase(a.begin());
    }
    if (q.empty())
        return vector<rational>{rational{{0},{1}}};
    return q;
}


vector<rational> MOD_PP_P(const vector<rational>& g, const vector<rational>& f) { // P10
    vector<rational> a = g, b = f;
    while (a.size() >= b.size() && a[0].numerator[0] != 0) {
        unsigned long long k = a.size() - b.size();
        rational c = DIV_QQ_Q(a[0], b[0]);
        a = SUB_PP_P(a, MUL_Pxk_P(MUL_PQ_P(b, c), k));
        while (a.size() > 0 && a[0].numerator[0] == 0)
            a.erase(a.begin());
    }
    return a;
}

vector<rational> GCF_PP_P(const vector<rational>& g, const vector<rational>& f) { //P11
    vector<rational> a = g, b = f;
    int iter = 0;
    while (!(b.size() == 1 && b[0].numerator[0] == 0 && b[0].numerator[1] == 0)) {
        vector<rational> r = MOD_PP_P(a, b);
        a = b;
        b = r;
        if (b.empty()) break;
    }
    if (a.empty() || (a.size() == 1 && a[0].numerator[0] == 0 && a[0].numerator[1] == 0))
        return { rational{{0,0}, {1}} };
    rational lead = a[0];
    vector<rational> res;
    for (size_t i = 0; i < a.size(); ++i) {
        res.push_back(DIV_QQ_Q(a[i], lead));
    }
    return res;
}

vector<rational> DER_P_P(const vector<rational>& g) { // P12
    int n = g.size();
    if (n <= 1) return { rational{{0,0}, {1}} };
    vector<rational> res;
    for (int i = 0; i < n - 1; ++i) {
        int k = n - 1 - i;
        vector<int> k_na;
        int tmp = k;
        while (tmp > 0) {
            k_na.insert(k_na.begin(), tmp % 10);
            tmp /= 10;
        }
        rational t;
        t.numerator = MUL_ZZ_Z(g[i].numerator, TRANS_N_Z(k_na));
        t.denominator = g[i].denominator;
        res.push_back(RED_Q_Q(t));
    }
    return res;
}

vector<rational> NMR_P_P(const vector<rational>& p) { //P13
    vector<rational> d = DER_P_P(p);
    vector<rational> g = GCF_PP_P(p, d);
    return DIV_PP_P(p, g);
}