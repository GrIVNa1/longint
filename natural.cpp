#include <bits/stdc++.h>

int COM_NN_D(const std::vector<int> &a, const std::vector<int> &b) { //N1
    // std::cout << 1 << std::endl;
    if (a.size() > b.size()) return 2;
    if (a.size() < b.size()) return 1;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] > b[i]) return 2;
        if (a[i] < b[i]) return 1;
    }
    return 0;
}

bool NZER_N_B (const std::vector<int> &a) { //N2
    // std::cout << 2 << std::endl;
    if (a.size() == 1 && a[0] == 0) return false;
    return true;
}

std::vector<int> NORM_N_N (const std::vector<int> &g) {
    // std::cout << 0;
    std::vector<int> a = g;
    for (int i = g.size() - 1; i >= 1; i--) {
        // std::cout << "_";
        if (a[i] >= 10) {
            a[i-1] += a[i]/10;
            a[i] %= 10;
        }
    }
    while (a[0] >= 10) {
        a.insert(a.begin(), a[0]/10);
        a[1] %= 10;
    }

    for (int i = 1; i < a.size(); i++) {
        // std::cout << "-";
        if (a[i] < 0) {
            a[i] += 10;
            a[i-1] -= 1;
        }
    }
    while (a[0] == 0 && a.size() != 1) {
        a.erase(a.begin());
    }
    // std::cout << std::endl;
    return a;
}

std::vector<int> ADD_1N_N (const std::vector<int> &a) { //N3
    // std::cout << 3 << std::endl;
    std::vector<int> g = a;
    g[g.size() - 1] += 1;
    return NORM_N_N(g);
}

std::vector<int> ADD_NN_N (const std::vector<int> &g, const std::vector<int> &f) { //N4
    // std::cout << 4 << std::endl;
    std::vector<int> a = g;
    std::vector<int> b = f;
    if (COM_NN_D(a,b) == 1) {
        std::swap(a,b);
    }
    for (int i = b.size()-1; i >= 0; i--) {
        int j = a.size() - (b.size()-i);
        a[j] += b[i];
    }
    return NORM_N_N(a);
}

std::vector<int> SUB_NN_N (const std::vector<int> &g, const std::vector<int> &f) {//N5
    // std::cout << 5 << std::endl;
    std::vector<int> a = g;
    std::vector<int> b = f;
    if (COM_NN_D(a,b) == 1) {
        std::swap(a,b);
    }
    for (int i = b.size()-1; i >= 0; i--) {
        int j = a.size() - (b.size()-i);
        a[j] -= b[i];
    }
    return NORM_N_N(a);
}

std::vector<int> MUL_ND_N(const std::vector<int> &g, int d) { //N6
    // std::cout << 6 << std::endl;
    std::vector<int> a = g;
    for (int i = 0; i < a.size(); i++) {
        a[i]*=d;
    }
    return NORM_N_N(a);
}

std::vector<int> MUL_Nk_N (const std::vector<int> &g, int k) { //N7
    // std::cout << 7 << std::endl;
    std::vector<int> a = g;
    for (int i = 0; i < k; i++) {
        a.push_back(0);
    }
    return NORM_N_N(a);
}

std::vector<int> MUL_NN_N (const std::vector<int> &g, const std::vector<int> &f) { //N8
    // std::cout << 8 << std::endl;
    std::vector<int> a = g;
    std::vector<int> b = f;
    std::vector<int> s = {0};
    for (int i = b.size()-1; i >= 0; i--) {
        int k = b.size()-i-1;
        std::vector<int> x = MUL_ND_N(a, b[i]);
        std::vector<int> y = MUL_Nk_N(x, k);
        s = ADD_NN_N(s, y);
    }
    return NORM_N_N(s);
}

std::vector<int> SUB_NDN_N (const std::vector<int> &g, int d, const std::vector<int> &f) { //N9
    // std::cout << 9 << std::endl;
    return NORM_N_N(SUB_NN_N(g, MUL_ND_N(f, d)));
}

std::vector<int> DIV_NN_Dk (const std::vector<int> &g, const std::vector<int> &f) { //N10
    // std::cout << 10 << std::endl;
    std::vector<int> a = g;
    std::vector<int> b = f;
    if (COM_NN_D(a, b) == 1) return {0};

    int k = 0;
    while (COM_NN_D(a, MUL_Nk_N(b, k+1)) != 1) k++;

    int i = 1;
    while (i < 9 && COM_NN_D(a, MUL_ND_N(MUL_Nk_N(b, k), i+1)) != 1) i++;

    return NORM_N_N(MUL_Nk_N({i},k));
}

std::vector<int> DIV_NN_N (const std::vector<int> &g, const std::vector<int> &f) { //N11
    // std::cout << 11 << std::endl;
    std::vector<int> a = g;
    std::vector<int> b = f;
    std::vector<int> res = {0};
    while (COM_NN_D(a, b) != 1) {
        std::vector<int> x = DIV_NN_Dk(a, b);
        res = ADD_NN_N(res, x);
        // std::cout << "()" << res[0] << std::endl;
        a = SUB_NN_N(a, MUL_NN_N(b, x));
    }

    return NORM_N_N(res);
}

std::vector<int> MOD_NN_N (const std::vector<int> &g, const std::vector<int> &f) {//N12
    return NORM_N_N(SUB_NN_N(g, MUL_NN_N(DIV_NN_N(g, f), f)));
}

std::vector<int> GCF_NN_N(const std::vector<int> &g, const std::vector<int> &f) { //N13
    if (!NZER_N_B(g)) return f;
    if (!NZER_N_B(f)) return g;
    std::vector<int> a = g;
    std::vector<int> b = f;
    std::vector<int> r, prev_r;
    if (COM_NN_D(a,b) == 2) r = b;
    else r = a;
    while (NZER_N_B(r)) {
        if (COM_NN_D(a,b) == 1) std::swap(a,b);
        prev_r = r;
        r = MOD_NN_N(a,b);
        a = r;
    }
    return NORM_N_N(prev_r);
}

std::vector<int> LCM_NN_N (const std::vector<int> &g, const std::vector<int> &f) { // N14
    return NORM_N_N(DIV_NN_N(MUL_NN_N(g,f), GCF_NN_N(g,f)));
}