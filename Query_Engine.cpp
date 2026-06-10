#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 定義資料庫的表結構 (存在記憶體中)
struct Table {
    vector<string> columns;            // 欄位名稱 (例如: id, name, email)
    vector<vector<string>> rows;       // 每一筆資料的內容
};

// 全域變數：模擬資料庫，用來儲存所有載入的 Table
unordered_map<string, Table> database;

// 輔助函式：用來將字串依照指定字元切割 (類似 Python 的 split)
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        // 簡易清除頭尾的空白字元
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);
        tokens.push_back(token);
    }
    return tokens;
}

// 1. 載入 CSV 檔案
void LOAD(const string& table_name) {
    ifstream file(table_name + ".csv"); // 假設檔案名稱為 table_name.csv
    if (!file.is_open()) {
        cout << "Error: No such file " << table_name << ".csv\n";
        return;
    }

    Table new_table;
    string line;
    
    // 讀取第一行作為欄位名稱 (Header)
    if (getline(file, line)) {
        new_table.columns = split(line, ',');
    }

    // 讀取剩餘的資料行
    while (getline(file, line)) {
        if (!line.empty()) {
            new_table.rows.push_back(split(line, ','));
        }
    }

    // 存入 database
    database[table_name] = new_table;
    cout << "Success: Successfully loaded table '" << table_name << "' with " << new_table.rows.size() << " rows.\n";
}

// 2. 執行 SELECT 查詢
void SELECT(const string& query) {
    // 簡易的 Parser 邏輯
    // 假設語法一定是: SELECT [columns] FROM [table_name]
    size_t from_pos = query.find(" FROM ");
    if (from_pos == string::npos) {
        cout << "Syntax Error: Missing FROM keyword.\n";
        return;
    }

    // 萃取欄位字串與表名
    string cols_str = query.substr(7, from_pos - 7); // "SELECT " 長度為 7
    string table_name = query.substr(from_pos + 6);  // " FROM " 長度為 6

    // 清除結尾可能的空白或分號
    table_name.erase(table_name.find_last_not_of(" \t\r\n;") + 1);

    // 檢查表是否存在
    if (database.find(table_name) == database.end()) {
        cout << "Error: Table '" << table_name << "' does not exist. Please LOAD it first.\n";
        return;
    }

    Table& table = database[table_name];
    vector<string> target_cols = split(cols_str, ',');
    vector<int> col_indices;

    // 判斷是 SELECT * 還是特定的欄位
    if (target_cols.size() == 1 && target_cols[0] == "*") {
        for (int i = 0; i < table.columns.size(); ++i) {
            col_indices.push_back(i);
        }
    } else {
        // 尋找目標欄位的 Index
        for (const string& col : target_cols) {
            auto it = find(table.columns.begin(), table.columns.end(), col);
            if (it != table.columns.end()) {
                col_indices.push_back(distance(table.columns.begin(), it));
            } else {
                cout << "Error: Column '" << col << "' not found.\n";
                return;
            }
        }
    }

    // 輸出欄位名稱 (Header)
    for (int idx : col_indices) {
        cout << table.columns[idx] << "\t| ";
    }
    cout << "\n----------------------------------------\n";

    // 輸出資料列
    for (const auto& row : table.rows) {
        for (int idx : col_indices) {
            // 避免 CSV 資料缺漏導致 index out of bounds
            if (idx < row.size()) cout << row[idx] << "\t| ";
            else cout << "NULL\t| ";
        }
        cout << "\n";
    }
}

// 3. 顯示幫助訊息
void HELP() {
    cout << "\n=== Mini Query Engine Command List ===\n";
    cout << "1. LOAD <table_name>                        (Load <table_name>.csv)\n";
    cout << "2. SELECT * FROM <table_name>               (Query all columns)\n";
    cout << "3. SELECT col1, col2, ... FROM <table_name>      (Query specific columns)\n";
    cout << "4. HELP                                     (Display this message)\n";
    cout << "5. EXIT                                     (Exit the program)\n";
    cout << "====================================\n";
}

int main() {
    HELP();
    string input;
    
    cout << "\nSQL> ";
    // 使用 getline 讀取整行字串，包含空白
    while (getline(cin, input)) {
        // 處理空輸入
        if (input.empty()) {
            cout << "SQL> ";
            continue;
        }

        // 簡單的指令路由 (Router)
        if (input == "EXIT") {
            cout << "Bye!\n";
            break;
        } else if (input == "HELP") {
            HELP();
        } else if (input.rfind("LOAD ", 0) == 0) { 
            // 檢查是否以 "LOAD " 開頭
            string table_name = input.substr(5);
            LOAD(table_name);
        } else if (input.rfind("SELECT ", 0) == 0) {
            // 檢查是否以 "SELECT " 開頭
            SELECT(input);
        } else {
            cout << "Syntax Error: Unsupported command. Please input HELP for assistance.\n";
        }
        
        cout << "\nSQL> ";
    }

    return 0;
}