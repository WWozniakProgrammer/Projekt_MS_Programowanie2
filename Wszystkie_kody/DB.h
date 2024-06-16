#pragma once
#include "sqlite3.h"

class DB
{
	public:
		DB();
		void close();
		bool executeQuery(const char* sql);
		bool selectData(const char* sql);

	private:
		sqlite3* db{};
};

