#ifndef LONGINT_POLYNOMIAL_H
#define LONGINT_POLYNOMIAL_H

#include <bits/stdc++.h>
#include "rational_struct.h"

using namespace std;

vector<rational> ADD_PP_P(const vector<rational>& g, const vector<rational>& f);
vector<rational> SUB_PP_P(const vector<rational>& g, const vector<rational>& f);
vector<rational> MUL_PQ_P(const vector<rational>& g, const rational& f);
vector<rational> MUL_Pxk_P(const vector<rational>& g, unsigned long long k);
rational LED_P_Q(const vector<rational>& g);
int DEG_P_N(const vector<rational>& g);
rational FAC_P_Q(const vector<rational>& g);
vector<rational> DIV_PP_P(const vector<rational>& g, const vector<rational>& f);
vector<rational> MOD_PP_P(const vector<rational>& g, const vector<rational>& f);
vector<rational> GCF_PP_P(const vector<rational>& g, const vector<rational>& f);
vector<rational> DER_P_P(const vector<rational>& g);
vector<rational> NMR_P_P(const vector<rational>& p);
vector<rational> MUL_PP_P(const vector<rational>& g, const vector<rational>& f);

#endif