#include "SqlliteHelp.h"
#include <iostream>
#include "sqlite3.h"
using namespace std;

// �������ݿ�����
sqlite3* SqlliteHelp::OpenDatabase(const char* dbFilePath)
{
    sqlite3* db;

    // �����ݿ�
    if (sqlite3_open(dbFilePath, &db) != SQLITE_OK) {
        cerr << "Error opening database." << endl;
        return nullptr;
    }

    return db;
}


// �ر����ݿ�����
void SqlliteHelp::CloseDatabase(sqlite3* db) {
    sqlite3_close(db);
}

// ������
void SqlliteHelp::CreateTable(sqlite3* db) {
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Age INTEGER);";

    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr) != SQLITE_OK) {
        cerr << "Error creating table." << endl;
    }
    else {
        cout << "Table created or already exists." << endl;
    }
}

// ��������
void SqlliteHelp::InsertData(sqlite3* db, const char* name, int age) {
    const char* insertDataSQL = "INSERT INTO Users (Name, Age) VALUES (?, ?);";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, insertDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // �󶨲���
        sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 2, age);

        // ִ�����
        if (sqlite3_step(statement) != SQLITE_DONE) {
            cerr << "Error inserting data." << endl;
        }
        else {
            cout << "Data inserted." << endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}

// ��ѯ����
void SqlliteHelp::QueryData(sqlite3* db, const char* queryDataSQL) {
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, queryDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        cout << "Id\tName\tAge" << endl;

        // ���������
        while (sqlite3_step(statement) == SQLITE_ROW) {
            cout << sqlite3_column_int(statement, 0) << "\t"
                << sqlite3_column_text(statement, 1) << "\t"
                << sqlite3_column_int(statement, 2) << endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}

// ��������
void SqlliteHelp::UpdateData(sqlite3* db, int id, const char* name, int age) {
    const char* updateDataSQL = "UPDATE Users SET Name=?, Age=? WHERE Id=?;";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, updateDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // �󶨲���
        sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 2, age);
        sqlite3_bind_int(statement, 3, id);

        // ִ�����
        if (sqlite3_step(statement) != SQLITE_DONE) {
            cerr << "Error updating data." << endl;
        }
        else {
            cout << "Data updated." << endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}

// ɾ������
void SqlliteHelp::DeleteData(sqlite3* db, int id) {
    const char* deleteDataSQL = "DELETE FROM Users WHERE Id=?;";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, deleteDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // �󶨲���
        sqlite3_bind_int(statement, 1, id);

        // ִ�����
        if (sqlite3_step(statement) != SQLITE_DONE) {
            cerr << "Error deleting data." << endl;
        }
        else {
            cout << "Data deleted." << endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}

