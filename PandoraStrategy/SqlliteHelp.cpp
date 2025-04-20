#include "SqlliteHelp.h"
#include <iostream>
#include "sqlite3.h"
using namespace std;

// 创建数据库连接
sqlite3* SqlliteHelp::OpenDatabase(const char* dbFilePath)
{
    sqlite3* db;

    // 打开数据库
    if (sqlite3_open(dbFilePath, &db) != SQLITE_OK) {
        cerr << "Error opening database." << endl;
        return nullptr;
    }

    return db;
}


// 关闭数据库连接
void SqlliteHelp::CloseDatabase(sqlite3* db) {
    sqlite3_close(db);
}

// 创建表
void SqlliteHelp::CreateTable(sqlite3* db) {
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Age INTEGER);";

    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr) != SQLITE_OK) {
        cerr << "Error creating table." << endl;
    }
    else {
        cout << "Table created or already exists." << endl;
    }
}

// 插入数据
void SqlliteHelp::InsertData(sqlite3* db, const char* name, int age) {
    const char* insertDataSQL = "INSERT INTO Users (Name, Age) VALUES (?, ?);";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, insertDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // 绑定参数
        sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 2, age);

        // 执行语句
        if (sqlite3_step(statement) != SQLITE_DONE) {
            cerr << "Error inserting data." << endl;
        }
        else {
            cout << "Data inserted." << endl;
        }

        // 释放资源
        sqlite3_finalize(statement);
    }
}

// 查询数据
void SqlliteHelp::QueryData(sqlite3* db, const char* queryDataSQL) {
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, queryDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        cout << "Id\tName\tAge" << endl;

        // 遍历结果集
        while (sqlite3_step(statement) == SQLITE_ROW) {
            cout << sqlite3_column_int(statement, 0) << "\t"
                << sqlite3_column_text(statement, 1) << "\t"
                << sqlite3_column_int(statement, 2) << endl;
        }

        // 释放资源
        sqlite3_finalize(statement);
    }
}

// 更新数据
void SqlliteHelp::UpdateData(sqlite3* db, int id, const char* name, int age) {
    const char* updateDataSQL = "UPDATE Users SET Name=?, Age=? WHERE Id=?;";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, updateDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // 绑定参数
        sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 2, age);
        sqlite3_bind_int(statement, 3, id);

        // 执行语句
        if (sqlite3_step(statement) != SQLITE_DONE) {
            cerr << "Error updating data." << endl;
        }
        else {
            cout << "Data updated." << endl;
        }

        // 释放资源
        sqlite3_finalize(statement);
    }
}

// 删除数据
void SqlliteHelp::DeleteData(sqlite3* db, int id) {
    const char* deleteDataSQL = "DELETE FROM Users WHERE Id=?;";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, deleteDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // 绑定参数
        sqlite3_bind_int(statement, 1, id);

        // 执行语句
        if (sqlite3_step(statement) != SQLITE_DONE) {
            cerr << "Error deleting data." << endl;
        }
        else {
            cout << "Data deleted." << endl;
        }

        // 释放资源
        sqlite3_finalize(statement);
    }
}

