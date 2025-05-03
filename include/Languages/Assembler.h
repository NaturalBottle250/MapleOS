//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-05-02.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <cstdint>
#include <string>
#include <vector>

struct TokenList;
using namespace std;





enum class OperandType { REG, IMM8, IMM16, REG_VAL };

struct InstructionDescription
{
    uint8_t operationCode;
    vector<OperandType> operands;
};
class Assembler
{


public:
    static vector<uint8_t> AssembleTokens(const TokenList &tokens);

private:

};



#endif //ASSEMBLER_H
