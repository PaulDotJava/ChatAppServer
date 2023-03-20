#pragma once

#include <string>
#include <iostream>

#include <mysql_connection.h>
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/prepared_statement.h"

#include "shared/TransmissionTypes.h"

class SqlClient
{
public:
	SqlClient();
	~SqlClient();
public:
	void InsertUser(trans::UserData& ud);
	std::pair<uint32_t, uint32_t> InsertMessage(trans::Name& sender, trans::MessageBody& body, uint32_t chatID, uint32_t chunkID);
	bool ValidateUsername(const std::string& username);
	bool ValidateCredentials(const std::string& username, const std::string& password);
	bool CreateDM(const std::string& u1, const std::string& u2);
	std::vector<std::pair<trans::Name, uint32_t>> ListAllDMsOf(const std::string& username);
	std::vector<trans::Message> GetDirectChatChunk(uint32_t chatID, int32_t chunkID);
	uint32_t GetNewestDirChatChunk(uint32_t chatID);
	uint32_t GetUidFromName(trans::Name& name);
private:
	void Connect();
private:
	const std::string m_Server = "tcp://127.0.0.1::3306";
	const std::string m_Username = "Server";
	const std::string m_Password = "serverpass";
private:
	sql::Driver* m_Driver;
	sql::Connection* m_Con;
	sql::Statement* m_Statement;
	sql::PreparedStatement* m_PrepStatement;
};