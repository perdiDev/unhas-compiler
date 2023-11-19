#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// enum class TokenType {
//     println,
//     int_lit,
//     semi
// };

struct Token {
    // TokenType tipe;
    string tipe;
    string value;
};

vector<Token> tokenize(const string& str) {
    vector<Token> tokens;

    string buf;
    for(int i=0; i<str.length(); i++) {
        char c = str.at(i);

        if(isalpha(c)) {
            buf.push_back(c);
            i++;
            while(isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            if(buf == "cetak") {
                tokens.push_back({.tipe = "println"});
                buf.clear();
                continue;
            } else {
                cerr << "You messed up!" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(isdigit(c)) {
            buf.push_back(c);
            i++;
            while(isdigit(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.tipe = "int_lit", .value=buf});
            buf.clear();
        }
        else if(c == ';') {
            tokens.push_back({.tipe = "semi"});
        }
        else if(isspace(c)) {
            continue;
        } else {
            cerr << "You messed up!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

string token_to_c(const vector<Token>& tokens) {
    stringstream output;
    output << "#include <stdio.h>\nint main() {\n";

    // for(int i=0; i<tokens.size(); i++) {
    //     const Token& token = tokens.at(i);
    //     // cout << token.tipe << " : " << token.value << endl;
    //     // if()
    // }
    output << "printf(\"" << tokens.at(1).value << "\");\n";

    output << "return 0;\n}\n";
    return output.str();
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cerr << "Incorrect: ..." << endl;
        cerr << "hydro <input.hy>" << endl;
        return EXIT_FAILURE;
    }

    string contents;
    {
        stringstream contents_stream;
        fstream input(argv[1], ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    vector<Token> tokens = tokenize(contents);
    
    {
        fstream file("../out/compile.c", ios::out);
        file << token_to_c(tokens);
    }
    
    system("gcc ../out/compile.c -o ../out/unhas");
    system("..\\out\\unhas");

    return EXIT_SUCCESS;
}