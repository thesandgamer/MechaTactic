#pragma once
#include "NetworkAgent.h"
#include <string>
enum class ClientState
{
	Null,
	READ_CONFIG_FILE,
	OPENING_SOCKET,
	SENDING,
	RECEIVING,
	CONNECTION_ESTABLISHED
};
class NetworkClient : public NetworkAgent
{
public:
	NetworkClient();
	ClientState state;
	// Client side
	TCPsocket clientSocket{ nullptr };
	// Server side
	std::string serverIP{ "" };
	Uint16 serverPort{ 0 };
	bool readConfigFile() override;
	bool establishConnection() override;
	bool sendPacket(Packet* packet) override;
	Packet* recvPacket() override;
	void beforeDestroy() override;
	bool openClientSocket();
};