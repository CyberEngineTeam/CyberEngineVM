#include <iostream>
#include <bitset>

int generateListOfObjectives(int seconds) {
    std::bitset<16> binary = std::bitset<16>(seconds).flip();
    binary <<= 2;
    binary = std::bitset<16>(binary.to_ulong() + 1);


    std::bitset<16> set1 = binary;
    std::bitset<16> set2 = binary;

    set1 >>= 1;
    set2 = set2.flip();

    std::bitset<32> finalBitset = set1;

    std::cout << binary.to_string() << std::endl;

    return 0;
}

int main() {
    generateListOfObjectives(37729);
    return 0;
}