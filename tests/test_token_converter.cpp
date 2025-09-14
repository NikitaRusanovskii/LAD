#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include "../token_converter.h"


using namespace std;


/*

Ввиду отсутствия комментариев, некоторые функции могут тестироваться
на некорректных тест-кейсах, поэтому я рекомендую проверить,
правильные ли наборы данных я выбрал

*/


TEST(TokenConverterTest, IsInstrucionValid) {
    vector<string> data_set = {
        {"sub"}, {"add"}, {"not"},
        {"mul"}, {"div"}, {"xor"},
        {"inc"}, {"and"}, {"or"},
        {"cmp"}, {"jmp"}, {"je"},
        {"jl"}, {"jle"}, {"jg"},
        {"jge"}, {"mv"}, {"ld"},
        {"st"}, {"nop"}, {"fadd"},
        {"fsub"}, {"fmul"}, {"fdiv"}, {"jne"},
    };
    for(auto data: data_set) {
        EXPECT_TRUE(is_instruction(data)) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, IsInstrucionInvalid) {
    vector<string> data_set = {
        {"sub."}, {"add "}, {"nott"},
        {".mul"}, {"~div"}, {"/xor"},
        {"i n c"}, {"and_"}, {"orqwesd"},
        {"c m p"}, {"jmp%"}, {"jqeasd"},
        {"jel"}, {"jlae"}, {"jgspdl"},
        {"jgeee"}, {"mv           "}, {"r2l34d"},
        {"store"}, {"nop  "}, {"fadd1"}, {" "}, {""},
        {"fsub..."}, {"fmul,"}, {"fdiv!!"}, {"   jne"},
    };
    for(auto data: data_set) {
        EXPECT_FALSE(is_instruction(data)) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, IsNumberValid) {
    vector<string> data_set = {
        "1", "3", "132", "9", "0",
        "-1", "-2", "3", "-33", "10"
    };

    for (auto data: data_set) {
        EXPECT_TRUE(is_number(data)) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, IsNumberInvalid) {
    vector<string> data_set = {
        " ", "", "a", "10a", "r12", "ten", "one"
    };

    for (auto data: data_set) {
        EXPECT_FALSE(is_number(data)) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, IsRegisterValid) {
    vector<string> data_set = {
        "r1", "r2", "r0", "r12", "r15", "r16", "r99",
        "f1", "f58"
    };

    for (auto data: data_set) {
        EXPECT_TRUE(is_register(data)) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, IsRegisterInvalid) {
    vector<string> data_set = {
        " r1", "a2", "r-1", " ", "", "r111111111111111111",
        "f1 ", " f1", "f-1", "f 1", "f ", "-"
    };

    for (auto data: data_set) {
        EXPECT_FALSE(is_register(data)) << "fall ont the set: " << data << endl;
    }
}


TEST(TokenConverterTest, IsAddressValid) {
    vector<string> data_set = {
        "[000]", "[004]", "[1004]", "[-10]", "[1020]",
        "[1016]", "[4]"
    };

    for (auto data: data_set) {
        EXPECT_TRUE(is_address(data)) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, IsAddressInvalid) {
    vector<string> data_set = {
        "[]", "[ ]", "[-]", "[-1]", "[3]",
        "[10000000000000000000000]", "[11]",
        "10]", "[", "10", "0", "3", "4", "palka"
    };

    for (auto data: data_set) {
        EXPECT_FALSE(is_address(data)) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, DeleteFirstCharVariousInput) {
    vector<string> data_set = {
        "", " ", "lol", "a", "palka", // пустая строка
        "-1", "10", "13"
    };

    for (auto data: data_set) {
        auto sbstr = data.size() > 1? data.substr(1) : "";
        EXPECT_EQ(delete_first_char(data), sbstr) << "fall ont the set: " << data << endl;
    }
}

TEST(TokenConverterTest, DeleteLastCharVariousInput) {
    vector<string> data_set = {
        "", " ", "lol", "a", "palka", // пустая строка
        "-1", "10", "13"
    };

    for (auto data: data_set) {
        auto sbstr = data.size() > 1? data.substr(0, data.size()-1) : "";
        EXPECT_EQ(delete_last_char(data), sbstr) << "fall ont the set: " << data << endl;
    }
}