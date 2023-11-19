#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Token {
    string type;
    string value;
};

vector<Token> tokenize(const string& str) {
    vector<Token> tokens;
    
    int current = 0;
    while(current < str.size()) {
        char c = str.at(current);

        if(isalpha(c)) {
            string tempValue;
            while(isalpha(c)) {
                tempValue += c;
                c = str.at(++current);
            }
            tokens.push_back({"expr", tempValue});
            continue;
        }
        if(isspace(c)) {
            current++;
            continue;
        }
        if(c == ';') {
            tokens.push_back({"EOF", ";"});
            current++;
            continue;
        }
        if(isdigit(c)) {
            string tempValue;
            while(isdigit(c)) {
                tempValue += c;
                c = str.at(++current);
            }
            tokens.push_back({"number", tempValue});
            continue;
        }
        cerr << "Error: Unknown char \'" << c << "\'\n";
        exit(EXIT_FAILURE);
    }
    return tokens;
}

struct ASTNode {
    string typeAST;
    string valueAST;
    vector<string> params;
};

vector<ASTNode> parser(vector<Token>& tokens) {
    vector<ASTNode> par;
    int current = 0;
    while(current<tokens.size()) {
        Token token = tokens.at(current);

        if(token.type == "expr") {
            par.push_back({"CallExpression", token.value});
            
            current++;
            while(tokens.at(current).type == "number") {
                par.at(par.size()-1).params.push_back(tokens.at(current).value);
                current++;
                if(current>=tokens.size()) {
                    break;
                }
            }
        } else {
            int errToken = current-1; 
            cerr << "Error token \'" << tokens.at(errToken).type << "\' at '" << tokens.at(errToken).value << "\'\n";
            exit(EXIT_FAILURE);
        }
        current++;
    }
    return par;
}

string generateCode(vector<ASTNode>& pars) {
    stringstream cCode;
    cCode << "#include <stdio.h>\nint main() {\n";
    cCode << "\tint tambah, kurang, kali, bagi;\n\n";

    int current = 0;
    while(current < pars.size()) {
        ASTNode par = pars.at(current++);

        if(par.typeAST == "CallExpression") {
            string v = par.valueAST;
            if(v == "tambah" || v == "kurang" || v == "kali" || v=="bagi") {
                cCode << "\t" << v << " = ";

                vector<string> param = par.params;
                if(param.size() < 2) {
                    cerr << "Error syntax at...";
                    exit(EXIT_FAILURE);
                }

                char opr;
                if(v=="tambah") opr = '+'; 
                else if(v=="kurang") opr = '-'; 
                else if(v=="kali") opr = '*'; 
                else opr = '/'; 

                for(int i=0; i<param.size()-1; i++) {
                    cCode << param.at(i) << " " << opr << " ";
                }

                cCode << param.at(param.size()-1) << ";\n";
                cCode << "\tprintf(\"%d\\n\", " << v << ");\n\n";
            } else {
                cerr << "Error: not valid expression";
                exit(EXIT_FAILURE);
            }
        }
    }

    cCode << "\treturn 0;\n}\n";

    return cCode.str();
}

string compiler(string str) {
    vector<Token> tokenz = tokenize(str);
    // for(Token t : tokenz) {
    //     cout << "{\n\ttype: " << t.type << ",\n\tvalue: " << t.value << "\n},\n";
    // }

    vector<ASTNode> par = parser(tokenz);
    // for(ASTNode p: par) {
    //     cout << "{\n\ttype: " << p.typeAST << "\n\tvalue: " << p.valueAST << "\n\tparams: [ ";
    //     for(string t: p.params) {
    //         cout << t << " ";
    //     }
    //     cout << "]\n}\n";
    // }

    string codeCompile = generateCode(par);
    // cout << codeCompile << endl;

    return codeCompile;
}

int main(int argc, char* argv[]) {
    
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

    string output = compiler(contents);
    
    {
        fstream file("../out/compile.c", ios::out);
        file << output;
    }
    
    system("gcc ../out/compile.c -o ../out/unhas");
    system("..\\out\\unhas");

    return EXIT_SUCCESS;
}