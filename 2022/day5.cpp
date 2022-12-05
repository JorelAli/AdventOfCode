#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Instruction {
    int amount;
    int from;
    int to;
};

ostream& operator<<(ostream& os, const std::vector<std::vector<string>>& vectors) {
    for (const auto v : vectors) {
        os << v.back();
    }
    return os;
}

vector<vector<string>> initialVector() {
    return {{"H", "R", "B", "D", "Z", "F", "L", "S"},
            {"T", "B", "M", "Z", "R"},
            {"Z", "L", "C", "H", "N", "S"},
            {"S", "C", "F", "J"},
            {"P", "G", "H", "W", "R", "Z", "B"},
            {"V", "J", "Z", "G", "D", "N", "M", "T"},
            {"G", "L", "N", "W", "F", "S", "P", "Q"},
            {"M", "Z", "R"},
            {"M", "C", "L", "G", "V", "R", "T"}};
}

int main() {
    vector<string> lines;

    {
        ifstream inputFile("day5_input.txt");
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                lines.push_back(line);
            }
            inputFile.close();
        }
    }

    vector<Instruction> instructions;

    // Read the instructions
    for (string s : lines) {
        if (s.starts_with("move")) {
            Instruction instruction;
            size_t next = 0;
            s = s.substr(std::string("move ").length());
            instruction.amount = stoi(s, &next);
            s = s.substr(std::string(" from ").length() + next);
            instruction.from = stoi(s, &next) - 1;
            s = s.substr(std::string(" to ").length() + next);
            instruction.to = stoi(s) - 1;
            instructions.push_back(instruction);
        }
    }

    // Part 1
    vector<vector<string>> vectors = initialVector();
    for (Instruction instruction : instructions) {
        for (int i = 0; i < instruction.amount; i++) {
            vectors[instruction.to].push_back(vectors[instruction.from].back());
            vectors[instruction.from].pop_back();
        }
    }
    cout << "Part 1: " << vectors << "\n";

    // Part 2
    vectors = initialVector();
    for (Instruction instruction : instructions) {
        // Start from the ('from' end - amount), then insert that to the end of the 'to'
        auto it = std::next(vectors[instruction.from].begin(), vectors[instruction.from].size() - instruction.amount);
        vectors[instruction.to].insert(vectors[instruction.to].end(), it, vectors[instruction.from].end());
        for (int i = 0; i < instruction.amount; i++) {
            vectors[instruction.from].pop_back();
        }
    }
    cout << "Part 2: " << vectors << "\n";

    return 0;
}