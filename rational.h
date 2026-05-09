#ifndef LONGINT_RATIONAL_H
#define LONGINT_RATIONAL_H

#include "rational_struct.h"

rational RED_Q_Q(const rational &r);
bool INT_Q_B(const rational &r);
rational TRANS_Z_Q(const vector<int> &a);
vector<int> TRANS_Q_Z(const rational &a);
rational ADD_QQ_Q(const rational &a, const rational &b);
rational SUB_QQ_Q(const rational &a, const rational &b);
rational MUL_QQ_Q(const rational &a, const rational &b);
rational DIV_QQ_Q(const rational &a, const rational &b);

#endif