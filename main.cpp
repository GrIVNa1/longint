#include <bits/stdc++.h>
#include "natural.h"
#include "integer.h"
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
    } else if (t == '+') {
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

void PRINT_ARRAY(const vector<int>& a) {
    for (auto i : a) {
        cout << i;
    }
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
                    PRINT_ARRAY(ADD_1N_N(a));
                    break;
                }
                case 4: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(ADD_NN_N(a, b));
                    break;
                }
                case 5: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(SUB_NN_N(a, b));
                    break;
                }
                case 6: {
                    vector<int> a = INPUT_N();
                    int n;
                    cin >> n;
                    PRINT_ARRAY(MUL_ND_N(a, n));
                    break;
                }
                case 7: {
                    vector<int> a = INPUT_N();
                    int k;
                    cin >> k;
                    PRINT_ARRAY(MUL_Nk_N(a, k));
                    break;
                }
                case 8: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(MUL_NN_N(a, b));
                    break;
                }
                case 9: {
                    vector<int> a = INPUT_N();
                    int n;
                    cin >> n;
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(SUB_NDN_N(a, n, b));
                    break;
                }
                case 10: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(DIV_NN_Dk(a, b));
                    break;
                }
                case 11: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(DIV_NN_N(a, b));
                    break;
                }
                case 12: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(MOD_NN_N(a, b));
                    break;
                }
                case 13: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(GCF_NN_N(a, b));
                    break;
                }
                case 14: {
                    vector<int> a = INPUT_N();
                    vector<int> b = INPUT_N();
                    PRINT_ARRAY(LCM_NN_N(a, b));
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
                    PRINT_ARRAY(ABS_Z_Z(a));
                    break;
                }
                case 2: {
                    vector<int> a = INPUT_Z();
                    cout << SGN_Z_D(a) << endl;
                    break;
                }
                case 3: {
                    vector<int> a = INPUT_Z();
                    PRINT_ARRAY(MUL_ZM_Z(a));
                    break;
                }
                case 4: {
                    vector<int> a = INPUT_N();
                    PRINT_ARRAY(TRANS_N_Z(a));
                    break;
                }
                case 5: {
                    vector<int> a = INPUT_Z();
                    PRINT_ARRAY(TRANS_Z_N(a));
                    break;
                }
                case 6: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_ARRAY(ADD_ZZ_Z(a, b));
                    break;
                }
                case 7: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_ARRAY(SUB_ZZ_Z(a, b));
                    break;
                }
                case 8: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_ARRAY(MUL_ZZ_Z(a, b));
                    break;
                }
                case 9: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_ARRAY(DIV_ZZ_Z(a, b));
                    break;
                }
                case 10: {
                    vector<int> a = INPUT_Z();
                    vector<int> b = INPUT_Z();
                    PRINT_ARRAY(MOD_ZZ_Z(a, b));
                    break;
                }
                default:
                    cout << "incorrect input" << endl;
                    return 0;
            }
            break;
        }
        default:
            cout << "incorrect input" << endl;
            return 0;
    }
    return 0;
}