#include <bits/stdc++.h>
#include "natural.h"

using namespace std;

vector <int> ABS_Z_Z (const vector <int> &a) { //Z1
    vector <int> abs_a = a;
    if (abs_a[0] != 0) abs_a[0] = 1;
    return abs_a;
}

int SGN_Z_D(const vector <int> &a) { //N2
    return a[0];
}

vector <int> MUL_ZM_Z (const vector <int> &g) { //Z3
    vector <int> a = g;
    a[0] *= -1;
    return a;
}

vector <int> TRANS_N_Z (const vector <int> &g) { //Z4
    vector <int> a = g;
    if (a[0] != 0) a.insert(a.begin(), 1);
    else a.insert(a.begin(), 0);
    return a;
}
vector <int> TRANS_Z_N (const vector <int> &g) { //Z5
    vector <int> a = g;
    a.erase(a.begin());
    return a;
}

vector <int> ADD_ZZ_Z(const vector <int> &g, const vector <int> &f) { //Z6
    if (SGN_Z_D(g) == 0) return f;
    if (SGN_Z_D(f) == 0) return g;

    vector <int> a = TRANS_Z_N(g);
    vector <int> b = TRANS_Z_N(f);

    if (SGN_Z_D(g) == 1 && SGN_Z_D(f) == 1) {
        vector <int> c = ADD_NN_N(a, b);
        c = TRANS_N_Z(c);
        return c;
    }
    if (SGN_Z_D(g) == -1 && SGN_Z_D(f) == -1) {
        vector <int> c = ADD_NN_N(a, b);
        c = TRANS_N_Z(c);
        c = MUL_ZM_Z(c);
        return c;
    }
    vector <int> c = SUB_NN_N(a, b);
    if (COM_NN_D(a, b) == 2 && g[0] == -1 && f[0] == 1) {
        c = TRANS_N_Z(c);
        c = MUL_ZM_Z(c);
    }
    if (COM_NN_D(a, b) == 2 && g[0] == 1 && f[0] == -1)
        c = TRANS_N_Z(c);
    if (COM_NN_D(a, b) == 0)
        c.insert(c.begin(), 0);
    return c;
}

vector <int> SUB_ZZ_Z(const vector <int> &g, const vector <int> &f) { //Z7
    vector <int> a = TRANS_Z_N(g);
    vector <int> b = TRANS_Z_N(f);
    if (SGN_Z_D(g) == 1 && SGN_Z_D(f) == 1) {
        if (COM_NN_D(a,b) == 2)
            return TRANS_N_Z(SUB_NN_N(a,b));
        if (COM_NN_D(a,b) == 1)
            return MUL_ZM_Z(TRANS_N_Z(SUB_NN_N(a,b)));
        return {0, 0};
    }
    if (SGN_Z_D(g) == -1 && SGN_Z_D(f) == -1) {
        if (COM_NN_D(a,b) == 2)
            return MUL_ZM_Z(TRANS_N_Z(SUB_NN_N(a,b)));
        if (COM_NN_D(a,b) == 1)
            return TRANS_N_Z(SUB_NN_N(a,b));
        return {0, 0};
    }
    if (SGN_Z_D(g) == 1 && SGN_Z_D(f) == -1) {
        return TRANS_N_Z(ADD_NN_N(a,b));
    }
    if (SGN_Z_D(g) == -1 && SGN_Z_D(f) == 1) {
        return MUL_ZM_Z(TRANS_N_Z(ADD_NN_N(a,b)));
    }
    if (SGN_Z_D(g) == 0) return MUL_ZM_Z(f);
    if (SGN_Z_D(f) == 0) return g;
}

vector <int> MUL_ZZ_Z(const vector <int> &g, const vector <int> &f) { //Z8
    vector <int> a = TRANS_Z_N(g);
    vector <int> b = TRANS_Z_N(f);
    if ((SGN_Z_D(g) == 1 && SGN_Z_D(f) == 1)|| (SGN_Z_D(g) == -1 && SGN_Z_D(f) == -1))
        return TRANS_N_Z(MUL_NN_N(a,b));
    if ((SGN_Z_D(g) == 1 && SGN_Z_D(f) == -1) || (SGN_Z_D(g) == -1 && SGN_Z_D(f) == 1))
        return MUL_ZM_Z(TRANS_N_Z(MUL_NN_N(a,b)));
    if (SGN_Z_D(g) == 0) return {0, 0};
    if (SGN_Z_D(f) == 0) return {0, 0};
}

vector <int> DIV_ZZ_Z(const vector <int> &g, const vector <int> &f) { //Z9
    vector <int> a = TRANS_Z_N(g);
    vector <int> b = TRANS_Z_N(f);
    if ((SGN_Z_D(g) == 1 && SGN_Z_D(f) == 1)|| (SGN_Z_D(g) == -1 && SGN_Z_D(f) == -1)) {
        vector<int>c = TRANS_N_Z(DIV_NN_N(a,b));
        if (c[1] == 0) c[0] = 0;
        return c;
    }
    if ((SGN_Z_D(g) == 1 && SGN_Z_D(f) == -1) || (SGN_Z_D(g) == -1 && SGN_Z_D(f) == 1)) {
        vector <int> c = MUL_ZM_Z(TRANS_N_Z(DIV_NN_N(a,b)));
        if (c[1] == 0) c[0] = 0;
        return c;
        return c;
    }
    if (SGN_Z_D(g) == 0) return {0, 0};
}

vector<int> MOD_ZZ_Z(const vector<int> &g, const vector<int> &f) { //Z10
    vector<int> q = DIV_ZZ_Z(g, f);
    vector<int> r = SUB_ZZ_Z(g, MUL_ZZ_Z(f, q));
    if (SGN_Z_D(r) == -1) {
        r = ADD_ZZ_Z(r, ABS_Z_Z(f));
    }
    return r;
}