#include <bits/stdc++.h>

using namespace std;

vector<int> NORM_N_N(const vector<int> &g) {
    vector<int> a = g;
    for (int i = a.size() - 1; i >= 1; --i) {
        if (a[i] >= 10) {
            a[i-1] += a[i] / 10;
            a[i] %= 10;
        }
    }
    while (a[0] >= 10) {
        a.insert(a.begin(), a[0] / 10);
        a[1] %= 10;
    }
    for (int i = a.size() - 1; i >= 1; --i) {
        if (a[i] < 0) {
            a[i] += 10;
            a[i-1] -= 1;
        }
    }
    while (a.size() > 1 && a[0] == 0) {
        a.erase(a.begin());
    }
    return a;
}

int COM_NN_D(const vector<int> &a, const vector<int> &b) { //N1
    // cout << 1 << endl;
    if (a.size() > b.size()) return 2;
    if (a.size() < b.size()) return 1;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] > b[i]) return 2;
        if (a[i] < b[i]) return 1;
    }
    return 0;
}

bool NZER_N_B (const vector<int> &a) { //N2
    // cout << 2 << endl;
    if (a.size() == 1 && a[0] == 0) return false;
    return true;
}

vector<int> ADD_1N_N (const vector<int> &a) { //N3
    // cout << 3 << endl;
    vector<int> g = a;
    g[g.size() - 1] += 1;
    return NORM_N_N(g);
}

vector<int> ADD_NN_N (const vector<int> &g, const vector<int> &f) { //N4
    // cout << 4 << endl;
    vector<int> a = g;
    vector<int> b = f;
    if (COM_NN_D(a,b) == 1) {
        swap(a,b);
    }
    for (int i = b.size()-1; i >= 0; i--) {
        int j = a.size() - (b.size()-i);
        a[j] += b[i];
    }
    return NORM_N_N(a);
}

vector<int> SUB_NN_N (const vector<int> &g, const vector<int> &f) {//N5
    // cout << 5 << endl;
    vector<int> a = g;
    vector<int> b = f;
    if (COM_NN_D(a,b) == 1) {
        swap(a,b);
    }
    for (int i = b.size()-1; i >= 0; i--) {
        int j = a.size() - (b.size()-i);
        a[j] -= b[i];
    }
    return NORM_N_N(a);
}

vector<int> MUL_ND_N(const vector<int> &g, int d) { //N6
    // cout << 6 << endl;
    vector<int> a = g;
    for (int i = 0; i < a.size(); i++) {
        a[i]*=d;
    }
    return NORM_N_N(a);
}

vector<int> MUL_Nk_N (const vector<int> &g, int k) { //N7
    // cout << 7 << endl;
    vector<int> a = g;
    for (int i = 0; i < k; i++) {
        a.push_back(0);
    }
    return NORM_N_N(a);
}

vector<int> MUL_NN_N (const vector<int> &g, const vector<int> &f) { //N8
    // cout << 8 << endl;
    vector<int> a = g;
    vector<int> b = f;
    vector<int> s = {0};
    for (int i = b.size()-1; i >= 0; i--) {
        int k = b.size()-i-1;
        vector<int> x = MUL_ND_N(a, b[i]);
        vector<int> y = MUL_Nk_N(x, k);
        s = ADD_NN_N(s, y);
    }
    return NORM_N_N(s);
}

vector<int> SUB_NDN_N (const vector<int> &g, int d, const vector<int> &f) { //N9
    // cout << 9 << endl;
    return NORM_N_N(SUB_NN_N(g, MUL_ND_N(f, d)));
}

vector<int> DIV_NN_Dk (const vector<int> &g, const vector<int> &f) { //N10
    // cout << 10 << endl;
    vector<int> a = g;
    vector<int> b = f;
    if (COM_NN_D(a, b) == 1) return {0};

    int k = 0;
    while (COM_NN_D(a, MUL_Nk_N(b, k+1)) != 1) k++;

    int i = 1;
    while (i < 9 && COM_NN_D(a, MUL_ND_N(MUL_Nk_N(b, k), i+1)) != 1) i++;

    return NORM_N_N(MUL_Nk_N({i},k));
}

vector<int> DIV_NN_N (const vector<int> &g, const vector<int> &f) { //N11
    // cout << 11 << endl;
    vector<int> a = g;
    vector<int> b = f;
    vector<int> res = {0};
    while (COM_NN_D(a, b) != 1) {
        vector<int> x = DIV_NN_Dk(a, b);
        res = ADD_NN_N(res, x);
        // cout << "()" << res[0] << endl;
        a = SUB_NN_N(a, MUL_NN_N(b, x));
    }

    return NORM_N_N(res);
}

vector<int> MOD_NN_N (const vector<int> &g, const vector<int> &f) {//N12
    return NORM_N_N(SUB_NN_N(g, MUL_NN_N(DIV_NN_N(g, f), f)));
}

vector<int> GCF_NN_N(const vector<int> &g, const vector<int> &f) {
    vector<int> a = g, b = f;
    while (NZER_N_B(b)) {
        vector<int> r = MOD_NN_N(a, b);
        a = b;
        b = r;
    }
    return a;
}

vector<int> LCM_NN_N (const vector<int> &g, const vector<int> &f) { // N14
    return NORM_N_N(DIV_NN_N(MUL_NN_N(g,f), GCF_NN_N(g,f)));
}