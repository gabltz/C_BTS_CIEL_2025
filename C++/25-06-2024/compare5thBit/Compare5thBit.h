// Compare5thBit.h

#ifndef COMPARE5THBIT_H
#define COMPARE5THBIT_H

#include <iostream>
#include <string>

class Compare5thBit {
public:
    Compare5thBit(unsigned int conf, unsigned int mask);
    void comparer5eBit();
    void printBits(unsigned int value, unsigned int bitConf, unsigned int bitMask);

private:
    unsigned int conf;
    unsigned int mask;
};

#endif // COMPARE5THBIT_H
