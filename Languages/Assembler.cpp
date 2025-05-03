//
// In the name of the Father, Son, and Holy Spirit, may we all be guided. Amen
//
// Created by Daniel Alzawahra on 2025-05-02.
//
// GitHub: NaturalBottle/ NaturalBottle250
//
//

#include "Languages/Assembler.h"

#include <iostream>
#include <unordered_map>

#include "Utilities/TokenList.h"


static const std::unordered_map<std::string_view,InstructionDescription> instructionsTable =
    {
    { "LOAD",  { 0x1, { OperandType::REG,  OperandType::REG_VAL} } },
    { "ADD",   { 0x2, { OperandType::REG,  OperandType::REG  } } },
    { "ADDI",  { 0x3, { OperandType::REG,  OperandType::IMM8  } } },
    { "STORE", { 0x4, { OperandType::REG_VAL, OperandType::REG } } },
    { "JMP",   { 0x5, { OperandType::IMM16 } } },
    { "LOADI", { 0x6, { OperandType::REG,  OperandType::IMM8  } } },

    { "JZ",    { 0x9, { OperandType::IMM16 } } },
    { "JNZ",   { 0xA, { OperandType::IMM16 } } },
    { "TRAP",  { 0xF, { OperandType::REG  } } },
    };

static const unordered_map<string_view, uint8_t> registersMap =
    {
    {"R0", 0x0},
    {"R1", 0x1},
    {"R2", 0x2},
    {"R3", 0x3},
    {"R4", 0x4},
    {"R5", 0x5},
    {"R6", 0x6},
    {"R7", 0x7},

    };

vector<uint8_t> Assembler::AssembleTokens(const TokenList &tokens)
{

    char* operation = tokens.tokens[0];

    auto operationTuple = instructionsTable.find(operation);
    if (operationTuple == instructionsTable.end())
    {
        //ERROR
    }
    vector<uint8_t> result;
    InstructionDescription instruction = operationTuple->second;

    uint8_t operationByte = instruction.operationCode << 4;

    uint8_t registerNibble = 0, operandByte = 0;

    int index = 0, tokenIndex = 1;

    for (index = 0; index < instruction.operands.size(); index++)
    {
        char* token = tokens.tokens[tokenIndex++];
        OperandType operandType = instruction.operands[index];

        int reg = 0;
        switch (operandType)
        {
            case OperandType::REG:
            {

                reg = token[1] - '0';
                if (index == 0)
                {
                    operandByte |= (static_cast<uint8_t>(reg) & 0x0F) << 4;
                }
                else
                {
                    operandByte |= (static_cast<uint8_t>(reg) & 0x0F);
                }
                break;
            }

            case OperandType::IMM8:
            {
                result.push_back(operationByte);
                result.push_back(operandByte);

                int value = stoi(token);
                result.push_back(static_cast<uint8_t>(value & 0xFF));

                return result;
            }

        }
    }
    result.push_back(operationByte);
    result.push_back(operandByte);
    return result;

    //result.push_back(operationCode << 4 | 0);




}
