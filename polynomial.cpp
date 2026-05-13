#include <bits/stdc++.h>

#include "integer.h"
#include "rational_struct.h"
#include "rational.h"
#include "natural.h"
using namespace std;

rational fix_Rational(const rational& r) {
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

vector<rational> ADD_PP_P(const vector<rational>& g, const vector<rational>& f) {
    vector<rational> a = g, b = f;
    for (auto& c : a) c = fix_Rational(c);
    for (auto& c : b) c = fix_Rational(c);
    if (a.size() < b.size()) swap(a, b);
    vector<rational> c = a;
    int shift = a.size() - b.size();
    for (int i = 0; i < b.size(); ++i)
        c[shift + i] = ADD_QQ_Q(c[shift + i], b[i]);
    for (auto& x : c) x = fix_Rational(x);
    while (c.size() > 1 && c[0].numerator[0] == 0)
        c.erase(c.begin());
    return c;
}

vector<rational> SUB_PP_P(const vector<rational>& g, const vector<rational>& f) {
    vector<rational> a = g, b = f;
    for (auto& coeff : a) coeff = fix_Rational(coeff);
    for (auto& coeff : b) coeff = fix_Rational(coeff);

    if (a.size() < b.size()) swap(a, b);
    vector<rational> c = a;
    int shift = a.size() - b.size();
    for (int i = 0; i < b.size(); ++i)
        c[shift + i] = SUB_QQ_Q(c[shift + i], b[i]);

    for (auto& coeff : c) coeff = fix_Rational(coeff);

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


struct RawRat {
    std::vector<int> num;
    std::vector<int> den;
};

inline RawRat toRaw(const rational& r) {
    return {r.numerator, r.denominator};
}

inline rational toRational(const RawRat& r) {
    rational res;
    res.numerator = r.num;
    res.denominator = r.den;
    return RED_Q_Q(res);
}

RawRat addRaw(const RawRat& a, const RawRat& b) {
    RawRat res;
    if (a.den.size() == 1 && a.den[0] == 1) {
        res.den = b.den;
        res.num = ADD_ZZ_Z(MUL_ZZ_Z(a.num, TRANS_N_Z(b.den)), b.num);
    } else if (b.den.size() == 1 && b.den[0] == 1) {
        res.den = a.den;
        res.num = ADD_ZZ_Z(a.num, MUL_ZZ_Z(b.num, TRANS_N_Z(a.den)));
    } else {
        res.den = LCM_NN_N(a.den, b.den);
        auto m1 = DIV_NN_N(res.den, a.den);
        auto m2 = DIV_NN_N(res.den, b.den);
        res.num = ADD_ZZ_Z(MUL_ZZ_Z(a.num, TRANS_N_Z(m1)),
                           MUL_ZZ_Z(b.num, TRANS_N_Z(m2)));
    }
    return res;
}

RawRat subRaw(const RawRat& a, const RawRat& b) {
    RawRat res;
    if (a.den.size() == 1 && a.den[0] == 1) {
        res.den = b.den;
        res.num = SUB_ZZ_Z(MUL_ZZ_Z(a.num, TRANS_N_Z(b.den)), b.num);
    } else if (b.den.size() == 1 && b.den[0] == 1) {
        res.den = a.den;
        res.num = SUB_ZZ_Z(a.num, MUL_ZZ_Z(b.num, TRANS_N_Z(a.den)));
    } else {
        res.den = LCM_NN_N(a.den, b.den);
        auto m1 = DIV_NN_N(res.den, a.den);
        auto m2 = DIV_NN_N(res.den, b.den);
        res.num = SUB_ZZ_Z(MUL_ZZ_Z(a.num, TRANS_N_Z(m1)),
                           MUL_ZZ_Z(b.num, TRANS_N_Z(m2)));
    }
    return res;
}

RawRat mulRaw(const RawRat& a, const RawRat& b) {
    RawRat res;
    res.num = MUL_ZZ_Z(a.num, b.num);
    res.den = MUL_NN_N(a.den, b.den);
    return res;
}

RawRat divRaw(const RawRat& a, const RawRat& b) {
    RawRat res;
    // (a.num/a.den) / (b.num/b.den) = (a.num * b.den) / (a.den * b.num)
    res.num = MUL_ZZ_Z(a.num, TRANS_N_Z(b.den));
    res.den = MUL_NN_N(a.den, TRANS_Z_N(b.num));
    return res;
}



vector<rational> DIV_PP_P(const vector<rational>& g, const vector<rational>& f) {

    if (f.size() == 2) {
        if (g.size() <= 1) return {rational{{0, 0},{1}}};

        RawRat a = toRaw(f[0]);
        RawRat b = toRaw(f[1]);
        size_t degQ = g.size() - 1;
        std::vector<RawRat> rawQ(degQ);

        rawQ[0] = divRaw(toRaw(g[0]), a);
        for (size_t i = 1; i < degQ; ++i) {
            RawRat term = mulRaw(b, rawQ[i-1]);
            RawRat diff = subRaw(toRaw(g[i]), term);
            rawQ[i] = divRaw(diff, a);
        }

        vector<rational> q(degQ);
        for (size_t i = 0; i < degQ; ++i)
            q[i] = toRational(rawQ[i]);

        while (q.size() > 1 && q[0].numerator[0] == 0)
            q.erase(q.begin());
        return q;
    }

    vector<rational> a = g, b = f, q;
    while (a.size() >= b.size() && a[0].numerator[0] != 0) {
        unsigned long long k = a.size() - b.size();
        rational c = DIV_QQ_Q(a[0], b[0]);
        vector<rational> m = MUL_Pxk_P({c}, k);
        a = SUB_PP_P(a, MUL_Pxk_P(MUL_PQ_P(b, c), k));
        q = ADD_PP_P(q, m);
        while (a.size() > 0 && a[0].numerator[0] == 0)
            a.erase(a.begin());
    }
    if (q.empty())
        return {rational{{0, 0},{1}}};
    return q;
}


vector<rational> MOD_PP_P(const vector<rational>& g, const vector<rational>& f) {
    if (f.size() == 2) {
        if (g.size() <= 1) return g;

        RawRat a = toRaw(f[0]);
        RawRat b = toRaw(f[1]);

        RawRat cur = divRaw(toRaw(g[0]), a);
        for (size_t i = 1; i < g.size() - 1; ++i) {
            RawRat term = mulRaw(b, cur);
            RawRat diff = subRaw(toRaw(g[i]), term);
            cur = divRaw(diff, a);
        }
        RawRat r = subRaw(toRaw(g.back()), mulRaw(b, cur));
        rational res = toRational(r);

        if (res.numerator[0] == 0)
            return {rational{{0, 0},{1}}};
        return {res};
    }

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