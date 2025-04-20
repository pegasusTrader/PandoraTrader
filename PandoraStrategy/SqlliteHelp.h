#pragma once
#include <iostream>
#include "sqlite3.h"

class SqlliteHelp
{
public:
		static sqlite3* OpenDatabase(const char* dbFilePath);

		// �ر����ݿ�����
		static void CloseDatabase(sqlite3* db);

		// ������
		void CreateTable(sqlite3* db);

		// ��������
		void InsertData(sqlite3* db, const char* name, int age);

		// ��ѯ����
		void QueryData(sqlite3* db, const char*);

		// ��������
		void UpdateData(sqlite3* db, int id, const char* name, int age);

		// ɾ������
		void DeleteData(sqlite3* db, int id);
};

