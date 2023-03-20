#include "SqlClient.h"

SqlClient::SqlClient()
{
	Connect();
}

void SqlClient::Connect()
{
	try
	{
		m_Driver = get_driver_instance();
		m_Con = m_Driver->connect(m_Server, m_Username, m_Password);
	}
	catch (sql::SQLException& e)
	{
		std::cout << "Unable to connect to database!" << std::endl;
		std::cout << "[SQL Error] Code:" << e.getErrorCode() << std::endl;
		std::cout << "State: " << e.getSQLState() << std::endl;
		exit(1);
	}

	m_Statement = m_Con->createStatement();	
}

void SqlClient::InsertUser(trans::UserData& ud)
{
	m_Statement->execute("USE chatapp");
	m_PrepStatement = m_Con->prepareStatement("INSERT INTO user(firstname, lastname, email, username, password) VALUES(?, ?, ?, ?, ?)");
	m_PrepStatement->setString(1, ud.firstName);
	m_PrepStatement->setString(2, ud.lastName);
	m_PrepStatement->setString(3, ud.email);
	m_PrepStatement->setString(4, ud.username);
	m_PrepStatement->setString(5, ud.password);
	m_PrepStatement->execute();
}

std::pair<uint32_t, uint32_t> SqlClient::InsertMessage(trans::Name& sender, trans::MessageBody& body, uint32_t chatID, uint32_t chunkID)
{
	m_Statement->execute("USE chatapp");

	uint32_t sid = 0;
	uint32_t rid = 0;

	try
	{
		{
			sql::ResultSet* res = m_Statement->executeQuery("SELECT uid FROM user WHERE username = '" + std::string(sender.name) + "'");
			while (res->next())
			{
				sid = res->getInt(1);
			}
		}
		{
			sql::ResultSet* res = m_Statement->executeQuery("SELECT user1, user2 FROM directchat WHERE cid = '" + std::to_string(chatID) + "'");
			while (res->next())
			{

				rid = res->getInt(1);
				if (rid == sid)
				{
					rid = res->getInt(2);
				}
			}
		}
		m_Statement->execute("INSERT INTO message(sender, time, content, chunk) VALUES(" + std::to_string(sid) + ", now(), '" + std::string(body.body) + "', " + std::to_string(chunkID) + ")");
		m_Statement->execute("INSERT INTO directmessage(cid, mid) VALUES(" + std::to_string(chatID) + ", LAST_INSERT_ID())");
	}
	catch (sql::SQLException& e)
	{
		std::cout << "[SQL Error] Code:" << e.getErrorCode() << std::endl;
		std::cout << "State: " << e.getSQLState() << std::endl;
	}

	return std::make_pair<uint32_t, uint32_t>((uint32_t)sid, (uint32_t)rid);
}

bool SqlClient::CreateDM(const std::string& u1, const std::string& u2)
{
	bool ret = false;

	m_Statement->execute("USE chatapp");

	sql::ResultSet* res = m_Statement->executeQuery("SELECT * FROM directchat WHERE (user1 = (SELECT uid FROM user WHERE username = '" + u1 + "') AND user2 = (SELECT uid FROM user WHERE username = '" + u2 + "')) OR (user1 = (SELECT uid FROM user WHERE username = '" + u2 + "') AND user2 = (SELECT uid FROM user WHERE username = '" + u1 + "'))");

	while (res->next())
	{
		std::cout << "users already have a dm" << std::endl;
		delete res;
		return false;
	}

	m_Statement->execute("INSERT INTO directchat(user1, user2) VALUES ((SELECT uid FROM user WHERE username = '" + u1 + "'), (SELECT uid FROM user WHERE username = '" + u2 + "'))");
	
	delete res;
	return true;
}

bool SqlClient::ValidateUsername(const std::string& username)
{
	m_Statement->execute("USE chatapp");
	sql::ResultSet* res = m_Statement->executeQuery("SELECT username FROM user WHERE username = '" + username + "'");

	while (res->next())
	{
		delete res;
		return false;
	}

	delete res;
	return true;
}

bool SqlClient::ValidateCredentials(const std::string& username, const std::string& password)
{
	m_Statement->execute("USE chatapp");

	sql::ResultSet* res = m_Statement->executeQuery("SELECT username FROM user WHERE username = '" + username + "' AND password = '" + password + "'");

	int count = 0;
	while (res->next())
	{
		count++;
	}

	if (count == 0)
	{
		return false;
	}
	else if (count == 1)
	{
		return true;
	}
	else {
		std::cout << "[Panic] More than one user with identical username!" << std::endl;
		return true;
	}

	return false;
}

std::vector<std::pair<trans::Name, uint32_t>> SqlClient::ListAllDMsOf(const std::string& username)
{
	std::vector<std::pair<trans::Name, uint32_t>> hasChatsWith;	// name, cid

	std::cout << "Pulling dms of " << username << std::endl;

	{
		try
		{
			sql::ResultSet* res = m_Statement->executeQuery("SELECT username, cid FROM directchat JOIN user ON directchat.user1 = user.uid WHERE directchat.user2 = (SELECT uid FROM user WHERE username = '" + username + "')");

			trans::Name n{};
			std::string s;
			uint32_t id;

			while (res->next())
			{
				s = res->getString(1).asStdString();

				s.resize(64);
				memcpy(n.name, s.data(), s.size());
				id = res->getInt(2);
				hasChatsWith.push_back(std::make_pair<trans::Name, uint32_t>((trans::Name)n, (uint32_t)id));
				n = {};
			}
			delete res;
		}
		catch (sql::SQLException& e)
		{
			std::cout << "[SQL Error] Code:" << e.getErrorCode() << std::endl;
			std::cout << "State: " << e.getSQLState() << std::endl;
		}
	} 

	{
		try
		{
			sql::ResultSet* res = m_Statement->executeQuery("SELECT username, cid FROM directchat JOIN user ON directchat.user2 = user.uid WHERE directchat.user1 = (SELECT uid FROM user WHERE username = '" + username + "')");

			trans::Name n{};
			std::string s;
			uint32_t id;

			while (res->next())
			{
				s = res->getString(1).asStdString();

				memcpy(n.name, s.data(), s.size());
				id = res->getInt(2);
				hasChatsWith.push_back(std::make_pair<trans::Name, uint32_t>((trans::Name)n, (uint32_t)id));
				n = {};
			}
			delete res;
		}
		catch (sql::SQLException& e)
		{
			std::cout << "[SQL Error] Code:" << e.getErrorCode() << std::endl;
			std::cout << "State: " << e.getSQLState() << std::endl;
		}
	}

	std::cout << "Has chats with" << std::endl;

	for (auto i : hasChatsWith)
	{
		std::cout << i.first.name << " " << i.second << std::endl;
	}

	return hasChatsWith;
}

std::vector<trans::Message> SqlClient::GetDirectChatChunk(uint32_t chatID, int32_t chunkID)
{
	std::vector<trans::Message> msgs;
	try {
		sql::ResultSet* res = m_Statement->executeQuery("SELECT message.time, message.content, user.username FROM((message INNER JOIN directmessage ON message.mid = directmessage.mid) INNER JOIN directchat ON directmessage.cid = directchat.cid) INNER JOIN user ON message.sender = user.uid WHERE directchat.cid = " + std::to_string(chatID) + " AND message.chunk = " + std::to_string(chunkID) + " ORDER BY message.time DESC");

		std::string s = "";
		trans::Name n{};
		trans::Date d{};
		trans::MessageBody b{};

		while (res->next())
		{
			s = res->getString("username").asStdString();
			memcpy(n.name, s.data(), s.size());

			s = res->getString("time").asStdString();
			memcpy(d.date, s.data(), s.size());
			d.date[19] = '\0';

			s = res->getString("content").asStdString();
			memcpy(b.body, s.data(), s.size());

			msgs.push_back({ n , d, b });

			n = {};
			d = {};
			b = {};
		}

		std::cout << "Query finished!" << std::endl;

		delete res;
	}
	catch (sql::SQLException& e)
	{
		std::cout << "[SQL Error] Code:" << e.getErrorCode() << std::endl;
		std::cout << "State: " << e.getSQLState() << std::endl;
	}

	return msgs;
}

uint32_t SqlClient::GetUidFromName(trans::Name& name)
{
	uint32_t ret = 0;

	try
	{
		sql::ResultSet* res = m_Statement->executeQuery("SELECT uid FROM user WHERE username = '" + std::string(name.name) + "'");

		while (res->next())
		{
			ret = res->getInt(1);
		}

		delete res;
	}
	catch (sql::SQLException& e)
	{
		std::cout << "[SQL Error] Code:" << e.getErrorCode() << std::endl;
		std::cout << "State: " << e.getSQLState() << std::endl;
	}

	return ret;
}

uint32_t SqlClient::GetNewestDirChatChunk(uint32_t chatID)
{
	uint32_t latestChunk = -1;
	try {
		sql::ResultSet* res = m_Statement->executeQuery("SELECT message.chunk FROM(message INNER JOIN directmessage ON message.mid = directmessage.mid) INNER JOIN directchat ON directmessage.cid = directchat.cid WHERE directchat.cid = " + std::to_string(chatID) + " ORDER BY message.chunk DESC LIMIT 1");
		while (res->next())
		{
			latestChunk = res->getInt(1);
			std::cout << "latest chunk id is " << latestChunk << std::endl;
		}
	}
	catch (sql::SQLException& e)
	{
		std::cout << "[SQL Error] Code:" << e.getErrorCode() << std::endl;
		std::cout << "State: " << e.getSQLState() << std::endl;
	}

	return latestChunk;
}

SqlClient::~SqlClient()
{
	delete m_Con;
	delete m_Statement;
}