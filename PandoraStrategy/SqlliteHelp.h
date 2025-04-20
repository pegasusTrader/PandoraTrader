#pragma once
#include <iostream>
#include "sqlite3.h"

class SqlliteHelp
{
public:
		static sqlite3* OpenDatabase(const char* dbFilePath);

		// 关闭数据库连接
		static void CloseDatabase(sqlite3* db);

		// 创建表
		void CreateTable(sqlite3* db);

		// 插入数据
		void InsertData(sqlite3* db, const char* name, int age);

		// 查询数据
		void QueryData(sqlite3* db, const char*);

		// 更新数据
		void UpdateData(sqlite3* db, int id, const char* name, int age);

		// 删除数据
		void DeleteData(sqlite3* db, int id);
};

