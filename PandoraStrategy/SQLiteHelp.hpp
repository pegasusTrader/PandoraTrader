#include <iostream>
#include "sqlite3.h"

// �������ݿ�����
sqlite3* OpenDatabase(const char* dbFilePath)
{
    sqlite3* db;

    // �����ݿ�
    if (sqlite3_open(dbFilePath, &db) != SQLITE_OK) {
        std::cerr << "Error opening database." << std::endl;
        return nullptr;
    }

    return db;
}


// �ر����ݿ�����
void CloseDatabase(sqlite3* db) {
    sqlite3_close(db);
}

// ������
void CreateTable(sqlite3* db) {
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Age INTEGER);";

    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cerr << "Error creating table." << std::endl;
    }
    else {
        std::cout << "Table created or already exists." << std::endl;
    }
}

// ��������
void InsertData(sqlite3* db, const char* name, int age) {
    const char* insertDataSQL = "INSERT INTO Users (Name, Age) VALUES (?, ?);";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, insertDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // �󶨲���
        sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 2, age);

        // ִ�����
        if (sqlite3_step(statement) != SQLITE_DONE) {
            std::cerr << "Error inserting data." << std::endl;
        }
        else {
            std::cout << "Data inserted." << std::endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}

// ��ѯ����
void QueryData(sqlite3* db, const char* queryDataSQL) {
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, queryDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        std::cout << "Id\tName\tAge" << std::endl;

        // ���������
        while (sqlite3_step(statement) == SQLITE_ROW) {
            std::cout << sqlite3_column_int(statement, 0) << "\t"
                << sqlite3_column_text(statement, 1) << "\t"
                << sqlite3_column_int(statement, 2) << std::endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}

// ��������
void UpdateData(sqlite3* db, int id, const char* name, int age) {
    const char* updateDataSQL = "UPDATE Users SET Name=?, Age=? WHERE Id=?;";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, updateDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // �󶨲���
        sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_int(statement, 2, age);
        sqlite3_bind_int(statement, 3, id);

        // ִ�����
        if (sqlite3_step(statement) != SQLITE_DONE) {
            std::cerr << "Error updating data." << std::endl;
        }
        else {
            std::cout << "Data updated." << std::endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}

// ɾ������
void DeleteData(sqlite3* db, int id) {
    const char* deleteDataSQL = "DELETE FROM Users WHERE Id=?;";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, deleteDataSQL, -1, &statement, nullptr) == SQLITE_OK) {
        // �󶨲���
        sqlite3_bind_int(statement, 1, id);

        // ִ�����
        if (sqlite3_step(statement) != SQLITE_DONE) {
            std::cerr << "Error deleting data." << std::endl;
        }
        else {
            std::cout << "Data deleted." << std::endl;
        }

        // �ͷ���Դ
        sqlite3_finalize(statement);
    }
}