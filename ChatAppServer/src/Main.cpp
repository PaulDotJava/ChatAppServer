#include <iostream>
#include <unordered_map>

#include <cstdint>

#define OLC_PGEX_NETWORK
#include "olcPGEX_Network.h"

#include "SqlClient.h"


#include "shared/MessageType.h"

class ChatServer : public olc::net::server_interface<AppMsg>
{
public:
	ChatServer(uint16_t nPort) : olc::net::server_interface<AppMsg>(nPort)
	{
		m_SqlClient = std::make_unique<SqlClient>();
	}

	//std::unordered_map<uint32_t, sPlayerDescription> m_mapPlayerRoster;
	//std::vector<uint32_t> m_vGarbageIDs;

protected:
	bool OnClientConnect(std::shared_ptr<olc::net::connection<AppMsg>> client) override
	{
		// For now we will allow all 
		return true;
	}

	void OnClientValidated(std::shared_ptr<olc::net::connection<AppMsg>> client) override
	{
		// Client passed validation check, so send them a message informing
		// them they can continue to communicate
		olc::net::message<AppMsg> msg;
		msg.header.id = AppMsg::Client_Accepted;
		client->Send(msg);
	}

	void OnClientDisconnect(std::shared_ptr<olc::net::connection<AppMsg>> client) override
	{
		if (client)
		{
			
		}

	}

	void OnMessage(std::shared_ptr<olc::net::connection<AppMsg>> client, olc::net::message<AppMsg>& msg) override
	{
		switch (msg.header.id)
		{
		case AppMsg::Server_Login:
		{
			std::cout << msg << std::endl;
			char username[64];
			char password[64];

			msg >> password >> username;
			std::cout << "Username: " << username << ", Password: " << password << std::endl;

			bool s = m_SqlClient->ValidateCredentials(username, password);

			trans::Name n{};

			memcpy(n.name, username, 64);

			uint32_t uid = m_SqlClient->GetUidFromName(n);

			for (const auto& i : m_ActiveClients)
			{
				if (i.first == uid)
				{
					s = false;
				}
			}

			if (s)
			{
				m_ActiveClients.push_back(std::make_pair<uint32_t, olc::net::connection<AppMsg>*>((uint32_t)uid, client.get()));
			}

			olc::net::message<AppMsg> resp;
			resp.header.id = AppMsg::Client_LoginResp;
			resp << s;
			client->Send(resp);

			break;
		}
		case AppMsg::Server_Register:
		{
			std::cout << msg << std::endl;
			trans::UserData ud;
			msg >> ud;
			std::cout << ud.firstName << std::endl;

			olc::net::message<AppMsg> resp;
			resp.header.id = AppMsg::Client_RegisterResp;
			if (m_SqlClient->ValidateUsername(ud.username))
			{
				std::cout << "name valid" << std::endl;
				m_SqlClient->InsertUser(ud);
				resp << true;
			}
			else {
				std::cout << "name not valid" << std::endl;
				resp << false;
			}
			client->Send(resp);

			break;
		}
		case AppMsg::Server_CreateDM:
		{
			std::cout << msg << std::endl;

			char u1[64], u2[64];
			msg >> u1 >> u2;
			std::cout << u1 << std::endl;
			std::cout << u2 << std::endl;	// ->request

			bool s = m_SqlClient->CreateDM(u1, u2);
			std::cout << "Create dm success: " << s << std::endl;
			olc::net::message<AppMsg> resp;
			resp.header.id = AppMsg::Client_CreateDMResp;
			resp << s;
			client->Send(resp);

			trans::Name n{};
			memcpy(n.name, u1, 64);
			uint32_t u1id = m_SqlClient->GetUidFromName(n);

			SendDMs(u2, client.get());

			for (auto& i : m_ActiveClients)
			{
				if (i.first == u1id)
				{
					SendDMs(u1, i.second);
				}
			}

			break;
		}
		case AppMsg::Server_RequestDMs:
		{
			std::cout << "client requested dms!" << std::endl;
			char name[64];
			msg >> name;
			std::cout << name << std::endl;

			SendDMs(name, client.get());
			break;
		}
		case AppMsg::Server_RequestDMChunk:
		{
			std::cout << "client requested dir chat chunk" << std::endl;
			std::cout << msg << std::endl;
			int32_t chunkID;
			uint32_t chatID;
			msg >> chunkID;
			msg >> chatID;

			SendDMChunk(chatID, chunkID, client.get());
			
			break;
		}
		case AppMsg::Server_SendDirectMessage:
		{
			std::cout << "Message recieved: " << msg << std::endl;

			trans::Name sender{};
			trans::MessageBody body{};
			uint32_t chatID;
			uint32_t chunkID;

			msg >> body >> sender >> chatID >> chunkID;

			std::cout << body.body << std::endl;

			std::pair<uint32_t, uint32_t> part = m_SqlClient->InsertMessage(sender, body, chatID, chunkID);

			for (auto& i : m_ActiveClients)
			{
				std::cout << "active client: " << i.first << std::endl;

				if (i.first == part.first || i.first == part.second)
				{
					std::cout << "Sending stuff beck!" << std::endl;
					SendDMChunk(chatID, chunkID, i.second);

					uint32_t bodyLen = 0;
					for (; body.body[bodyLen] != '\0'; bodyLen++)
					{ /* - Silence - */ }

					std::cout << "Pinging " << bodyLen << " bytes long msg back!" << std::endl;

					olc::net::message<AppMsg> recieverPing;
					recieverPing.header.id = AppMsg::Client_MessageRecieved;
					recieverPing << bodyLen;

					i.second->Send(recieverPing);
				}
			}

			break;
		}
		case AppMsg::Server_Disconnect:
		{
			for (int i = 0; i < m_ActiveClients.size(); i++)
			{
				if (m_ActiveClients.at(i).second == client.get())
				{
					m_ActiveClients.erase(m_ActiveClients.begin() + i);
					break;
				}
			}
			break;
		}
		default:
			break;
		}
	}
private:
	void SendDMs(char u[64], olc::net::connection<AppMsg>* client)
	{
		std::vector<std::pair<trans::Name, uint32_t>> l = m_SqlClient->ListAllDMsOf(u);

		std::cout << "Sending dms to " << u << std::endl;

		olc::net::message<AppMsg> msg;
		msg.header.id = AppMsg::Client_SendDMs;
		for (auto i : l)
		{
			//std::cout << sizeof(i.first) + sizeof(i.second) << std::endl;
			msg << i.first << i.second;
		}
		client->Send(msg);
	}

	void SendDMChunk(uint32_t chatID, uint32_t chunkID, olc::net::connection<AppMsg>* client)
	{
		if (chunkID == -1)
		{
			chunkID = m_SqlClient->GetNewestDirChatChunk(chatID);
		}

		std::vector<trans::Message> chunk = m_SqlClient->GetDirectChatChunk(chatID, chunkID);

		if (chunk.size() == 0)
		{
			return;
		}

		olc::net::message<AppMsg> resp;
		resp.header.id = AppMsg::Client_SendDMChunk;

		trans::Message m{};

		for (int i = 0; i < chunk.size(); i++)
		{
			m = chunk.at(i);

			resp << m;

			m = {};
		}

		resp << chatID << chunkID;
		client->Send(resp);
	}
private:
	std::unique_ptr<SqlClient> m_SqlClient;
	std::vector<std::pair<uint32_t, olc::net::connection<AppMsg>*>> m_ActiveClients;		// uid, connection
};



int main()
{
	ChatServer server(60000);
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}
	return 0;
}