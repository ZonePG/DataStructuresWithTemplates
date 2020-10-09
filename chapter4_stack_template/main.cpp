#include "stack.h"
#include <iostream>

#define OPCOUNT 6
#define MAXTOKENS 30
#define BUFFSIZE 133

void processExpr();
uint8_t findNextToken(bool);
uint8_t validateExp();
double evalExp();
double doArith(uint8_t, double, double);
void displayError();

enum Tokens {
    LEFTPAREN, // order in sequence of (, +, -, * and / is required
    PLUS,      // as a proxy for arithmetic precedence
    MINUS,
    MULTIPLY,
    DIVIDE,
    RIGHTPAREN,
    NUM,
    OPERATOR,
    ERRORTOKEN
};

struct keyname {
    char *keyword;
    uint8_t token;
};

const keyname operators[OPCOUNT] = {
    {"+", PLUS},
    {"-", MINUS},
    {"*", MULTIPLY},
    {"/", DIVIDE},
    {"(", LEFTPAREN},
    {")", RIGHTPAREN}};

struct StatItem {
    uint8_t sType;
    union {
        double fVal;
        uint8_t iVal;
    };
};
uint8_t statItemCount, errCode;
StatItem statItems[MAXTOKENS];
char buff[BUFFSIZE];

char *pptr, *nptr;

int main() {
    std::cout << "Enter an expression" << std::endl;
    while (true) {
        std::cin.getline(buff, 132);
        processExpr();
        std::cout << "Another?" << std::endl;
    }
}

void processExpr() {
    if (strlen(buff) == 0) {
        return;
    }
    pptr = nptr = buff;
    statItemCount = 0;
    bool lastWasOp = true;
    uint8_t tkn = findNextToken(lastWasOp);
    while (tkn != ERRORTOKEN && statItemCount <= MAXTOKENS) {
        lastWasOp = false;
        switch (tkn) {
        case NUM:
            statItems[statItemCount].sType = tkn;
            statItems[statItemCount].fVal = tkn;
            break;
        default:
            statItems[statItemCount].sType = OPERATOR;
            statItems[statItemCount].iVal = tkn;
            lastWasOp = true;
            break;
        }
        statItemCount++;
        pptr = nptr;
        tkn = findNextToken(lastWasOp);
    }
    errCode = validateExp();
    if (errCode == 0) {
        double res = evalExp();
        if (errCode == 0) {
            // no evaluation error
            std::cout << "Evaluates to: " << res << '\n';
        }
    }
    if (errCode != 0) {
        displayError();
    }
}

uint8_t findNextToken(bool wasOp) {
    // we are looking for constants and operators
    // ignore whitespace between statement components
    while (isspace(*pptr)) {
        pptr++;
    }
    if (*pptr == 0) {
        return ERRORTOKEN;
    }
    if (isdigit(*pptr) || (*pptr == '-' && wasOp) || *pptr == '.') {
        bool isNum = false;
        int i = (isdigit(*pptr)) ? 0 : 1;
        for (int j = strlen(pptr); i < j; i++) {
            if (isdigit(pptr[i]) || pptr[i] == '.') {
                isNum = true;
                nptr = pptr + i;
            } else {
                break;
            }
        }
        if (isNum) {
            nptr++;
            return NUM;
        }
    }
    for (int k = 0; k < OPCOUNT; k++) {
        if (strncmp(pptr, operators[k].keyword,
                    strlen(operators[k].keyword)) == 0) {
            nptr = pptr + strlen(operators[k].keyword);
            return operators[k].token;
        }
    }
    return ERRORTOKEN;
}

uint8_t validateExp() {
    int pCount = 0;
    int tr = 0;
    bool wasOp = true;
    for (int i = 0; i < statItemCount; i++) {
        int st = statItems[i].sType;
        int tk = statItems[i].iVal;
        if (st == OPERATOR) {
            if (tk == LEFTPAREN) {
                pCount++;
                continue;
            }
            if (tk == RIGHTPAREN) {
                pCount--;
                continue;
            }
            if (wasOp) {
                return 3;
            }
            wasOp = true;
        }
        if (st == NUM) {
            if (!wasOp) {
                return 5;
            }
            wasOp = false;
        }
    }
    if (pCount != 0) {
        return 7;
    }
    if (wasOp) {
        return 6; // op without value
    }
    return 0;
}

double doArith(uint8_t op, double lVal, double rVal) {
    switch (op) {
    case MULTIPLY:
        return lVal * rVal;
    case DIVIDE:
        if (rVal == 0) {
            errCode = 21;
            return 0;
        }
        return lVal / rVal;
    case MINUS:
        return lVal - rVal;
    case PLUS:
        return lVal + rVal;
    default:
        return 0;
    }
}

void displayError() {
    switch (errCode) {
    case 3:
        std::cout << "Operator does not follow a value\n";
        break;
    case 5:
        std::cout << "Expression is missing an operator\n";
        break;
    case 6:
        std::cout << "Incomplete expression\n";
        break;
    case 7:
        std::cout << "Missing parenthesis\n";
        break;
    case 21:
        std::cout << "Divide by zero error\n";
        break;
    default:
        std::cout << "Undefined error\n";
        break;
    }
}