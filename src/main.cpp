#include <iostream>
#include <bitset>
#include <vector>

std::bitset<32> generateBinary(int seconds) {
    std::bitset<16> binary = std::bitset<16>(seconds).flip();
    binary <<= 2;
    binary = std::bitset<16>(binary.to_ulong() + 1);


    std::bitset<16> set1 = binary;
    std::bitset<16> set2 = binary;

    set1 >>= 1;
    set2 = set2.flip();

    std::bitset<32> finalBitset(set1.to_string() + set2.to_string());

    return finalBitset;
}

int loopThroughObjectives(std::bitset<32> bits) {
    std::string bitString = bits.to_string();

    std::vector<std::vector<std::string>> objectives;

    int i = 0;
    for (char c : bitString) {
        i++;

        if (c == '1') {
            switch (i)
            {
                case 1:
                    objectives.push_back({"Firewall"});
                    break;

                case 2:
                    objectives.push_back({"Chrome"});
                    break;
                
                default:
                    break;
            }
        } else {
            switch (i)
            {   
                default:
                    break;
            }
        }

        
    }

    for (std::vector<std::string> args: objectives) {
        std::cout << "{";

        for (std::string arg: args) {
            std::cout << arg << ",";
        }

        std::cout << "}" << std::endl;
    }

    return 0;
}


int main() {
    loopThroughObjectives(generateBinary(37729));
    return 0;
}