#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cctype>
#include <bits/stdc++.h>

using namespace std;

/* To distinguish between terminal and non-terminal, underscore(_) is used 
   at the starting index of each non-terminal statements */

// Function to check if a string is a non-terminal
bool isNonTerminal(const string &s) {
    if (s[0] == '_') return 1;
    return 0;
}

// Function to perform and print BFS traversal of the parse tree graph
void bfsOfGraph(int V, vector<int> adj[], unordered_map<int, string> &NTV) {
    vector<vector<string>> ans(V + 1);
    vector<bool> visited(V + 1, false);
    queue<pair<int, int>> q;

    q.push({0, 0});
    visited[0] = true;

    while (!q.empty()) {
        int node = q.front().first;
        int curr_level = q.front().second;
        q.pop();

        ans[curr_level].push_back(NTV[node]);

        for (auto x : adj[node]) {
            if (!visited[x]) {
                q.push({x, curr_level + 1});
                visited[x] = true;
            }
        }
    }

    // Reverse the order of nodes at each level
    for (int i = 0; i <= V; ++i) {
        reverse(ans[i].begin(), ans[i].end());
    }

    // Print the BFS traversal
    for (int i = 0; i <= V; ++i) {
        if (ans[i].empty()) continue;
        for (const auto &it : ans[i]) {
            cout << it << " ";
        }
        cout << endl;
    }
}

// Function to tokenize the input string
vector<string> lexer(const string &input, int n) {
    vector<string> ans;
    int i = 0;

    while (i < n) {
        int k = i;  // Used to prevent infinite loops

        // Handles the keyword "if"
        if (i + 1 < n && input.substr(i, 2) == "if") {
            ans.push_back("if");
            i += 2;
        } 
        
        // Handles the keyword "else"
        if (i + 3 < n && input.substr(i, 4) == "else") {
            ans.push_back("else");
            i += 4;
        }
        
        // Handles relational operators of length 2
        if (i + 1 < n) {
            string temp = input.substr(i, 2);
            if (temp == "<=" || temp == ">=" || temp == "==" || temp == "!=") {
                ans.push_back(temp);
                i += 2;
            }
        } 
        
        // Handles single character tokens like "(", ")", "{", "}", "<", ">"
        if (i < n) {
            string temp = input.substr(i, 1);
            if (temp == "{" || temp == "}" || temp == "(" || temp == ")" || temp == "<" || temp == ">") {
                ans.push_back(temp);
                i += 1;
            }
        } 
        
        // Handles alphanumeric strings (variables, numbers)
        if (i < n && isalnum(input[i])) {
            string temp;
            while (i < n && isalnum(input[i])) {
                temp.push_back(input[i]);
                i++;
            }
            ans.push_back(temp);
        }

        if (k == i) {  // If no progress, return failure
            return {"-1"};
        }
    }

    return ans;
}

int main() {
    
    // Taking input
    string input;
    getline(cin, input);

    // Remove blank spaces from the input string
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    int len = input.size();

    // Get tokens using lexer
    vector<string> tokenized_input = lexer(input, len);
    int len2 = tokenized_input.size();

    // Check for invalid tokens
    if (tokenized_input[0] == "-1" && tokenized_input.size() == 1) {
        cout << "Invalid Token" << endl;
        return 0;
    }

    // Initializing the parsing table
    
    /* In the production, first entry is LHS and everything that follows is RHS
       for eg.: AbcA denotes A -> bcA
    
     Context Free Grammar:
        _stmt->_opst 
        _opst->if(_cond){_opst}else{_opst}/epsil
        _cond->_vari _oper _vari
        _oper->_rela
        _rela-> >,<,<=,>=,==,!=
        _vari-> _lett _nvar
        _lett-> a/b/c.../z/A/B/C.../Y/Z
        _nvar-> _lett _nvar/_nonl _nvar/epsi
        _nonl-> 0/1/2/3/.../9 
        
     *Mapping of non-terminals:
        stmt -> 0     vari -> 5
        opst -> 1     lett -> 6  
        cond -> 2     nvar -> 7 
        oper -> 3     nonl -> 8    
        rela -> 4                       */
        
    unordered_map<string, int> non_T;
    non_T["_stmt"] = 0;
    non_T["_opst"] = 1;
    non_T["_cond"] = 2;
    non_T["_oper"] = 3;
    non_T["_rela"] = 4;
    non_T["_vari"] = 5;
    non_T["_lett"] = 6;
    non_T["_nvar"] = 7;
    non_T["_nonl"] = 8;
    
    /* Mapping of terminals:
        if -> 0
        } -> 1
        ) -> 2   
        <, >, <=, >=, ==, != -> 3 to 8  
        a to z -> 9 to 34
        A to Z -> 35 to 60
        0 to 9 -> 61 to 70
        $ -> 71
        else -> 72 
        ( -> 73
        { -> 74         */
        
    unordered_map<string, int> T;
    T["if"] = 0;
    T["}"] = 1;
    T[")"] = 2;
    T["<"] = 3;
    T[">"] = 4;
    T["<="] = 5;
    T[">="] = 6;
    T["=="] = 7;
    T["!="] = 8;

    // Mapping of terminals for alphabetic and numeric characters
    for (int i = 9; i <= 34; ++i) {
        string str = "";
        char c = 'a' + i - 9;
        str += c;
        T[str] = i;
    }
    
    for (int i = 35; i <= 60; ++i) {
        string str = "";
        char c = 'A' + i - 35;
        str += c;
        T[str] = i;
    }
    
    for (int i = 61; i <= 70; ++i) {
        string str = "";
        char c = '0' + i - 61;
        str += c;
        T[str] = i;
    }

    T["$"] = 71;
    T["else"] = 72;
    T["("] = 73;
    T["{"] = 74;

    // Initialize the parsing table with empty productions
    vector<string> table[9][75];
    vector<string> temp;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 75; ++j) {
            vector<string> tempStr;
            tempStr.push_back("-1");
            table[i][j] = tempStr;
        }
    }

    // Fill in the parsing table
    // Example productions:
    // _stmt -> _opst
    table[0][0] = {"_opst"};
    table[0][1] = {"epsi"};

    // _opst -> if(_cond){_opst}else{_opst}
    table[1][0] = {"if", "(", "_cond", ")", "{", "_opst", "}", "else", "{", "_opst", "}"};
    table[1][1] = {"epsi"};

    // _oper -> _rela
    table[7][2] = {"epsi"};
    for (int i = 3; i <= 8; ++i) {
        table[3][i] = {"_rela"};
        table[7][i] = {"epsi"};
    }

    // _rela -> relational operators
    table[4][3] = {"<"};
    table[4][4] = {">"};
    table[4][5] = {"<="};
    table[4][6] = {">="};
    table[4][7] = {"=="};
    table[4][8] = {"!="};

    // _cond -> _vari _oper _vari
    for (int i = 9; i <= 60; ++i) {
        table[2][i] = {"_vari", "_oper", "_vari"};
        table[5][i] = {"_lett", "_nvar"};
        table[7][i] = {"_lett", "_nvar"};
    }

    // _lett -> alphabetic characters
    for (int i = 9; i <= 34; ++i) {
        char c = 'a' + i - 9;
        string tempStr = "";
        tempStr += c;
        table[6][i] = {tempStr};
    }
    for (int i = 35; i <= 60; ++i) {
        char c = 'a' + i - 9;
        string tempStr = "";
        tempStr += c;
        table[6][i] = {tempStr};
    }

    // _nvar -> numeric characters
    for (int i = 61; i <= 70; ++i) {
        char c = 'a' + i - 9;
        string tempStr = "";
        tempStr += c;
        table[8][i] = {tempStr};
        table[7][i] = {"_nonl", "_nvar"};
    }

    // _stmt and _opst -> epsilon for end symbol $
    table[0][71] = {"epsi"};
    table[1][71] = {"epsi"};

    // Parsing stack
    stack<pair<string, int>> st;
    unordered_map<int, string> NTV;
    
    // stroes parse tree as graph
    vector<int> adjList[10000];

    int flag1 = 0; // checks for any anomaly at some point
    int node = 0;  // stores the count of number of nodes

    st.push({"$", -1});
    
    // start variable
    st.push({"_stmt", 0});
    NTV[0] = "_stmt";

    int input_ptr = 0;  // to traverse through the loop

    // Parsing loop
    while (st.top().second != -1) {
        
        // implies that input is finished but the stack is not empty yet
        if (input_ptr == len2) {
            flag1 = 1;
            break;
        }

        int curr_node = st.top().second;
        string curr_var = st.top().first;
        string curr_input = tokenized_input[input_ptr];
        st.pop();
        
        // if terminal is present at the top of the stack
        if (!isNonTerminal(curr_var)) {
            if (curr_var == "epsi") {
                continue;
            } 
            else if (curr_var == curr_input) {
                input_ptr++;
            } 
            else {
                flag1 = 1;
                break;
            }
        } 
        
        // if non-terminal is present at the top of the stack
        else {
            
            if ((non_T.find(curr_var) != non_T.end()) && (T.find(curr_input) != T.end())) {
                int i = non_T[curr_var];
                int j = T[curr_input];

                if (table[i][j][0] == "-1") {
                    flag1 = 1;
                    break;
                }

                vector<string> tokens = table[i][j];
                int curr_len = tokens.size();
                for(int z = curr_len - 1; z >= 0; z--){
                    node++;
                    st.push({tokens[z],node});
                    NTV[node] = tokens[z];  // maintains mapping
                    adjList[curr_node].push_back(node); // add RHS of production rule to adjList
                }
            }
            else {
                flag1 = 1;
                break;
            }
        }
    }

    // Checking for successful parse
    if (flag1 == 1) {
        cout << "The given input has Invalid Syntax" << endl;
    } 
    else {
        cout << "The given input is valid" << endl << endl;
        cout << "The Parse Tree:" << endl;
        bfsOfGraph(node+1, adjList, NTV);
        
        // To print the adjacency list
        cout << "\nAdjcancy List of the graph is: " << endl;
        for(int i = 0; i < node + 1; ++i){
            if (adjList[i].size() == 0) continue;
            cout << NTV[i] << " -> ";
            // Loop through adjList[i] in reverse order
            for (auto it = adjList[i].rbegin(); it != adjList[i].rend(); ++it) {
                cout << NTV[*it] << " ";
            }
            cout << endl;
        }
    }

    return 0;

}