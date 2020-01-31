#include "Client.h"

Client::Client(int id)
{
	//m_colorID = 0;
	//m_name = "N/A";
	m_disconnecting = false;
	m_isConnected = false;
	m_isInThread = false;
	m_received = false;
	m_socket = 0;
}

Client::~Client()
{
}

bool Client::ClientConnected() const
{
	return m_isConnected;
}

bool Client::InThread() const
{
	return m_isInThread;
}

bool Client::IsDisconnecting() const
{
	return m_disconnecting;
}

const TCPsocket Client::GetSocket() const
{
	return m_socket;
}

void Client::CloseSocket()
{
	SDLNet_TCP_Close(m_socket);
	m_disconnecting = true;
}

void Client::ListenForClient(const TCPsocket& listenSocket)
{
	//std::cout << "Listening for client\n";
	if (listenSocket != nullptr)
	{
		m_socket = SDLNet_TCP_Accept(listenSocket);
	}
}

void Client::ReceiveText(String& message)
{
	m_received = false;

	char response[2048] = { '\0' };

	if (SDLNet_TCP_Recv(m_socket, response, 2048) <= 0)
	{
		std::cout << "Error recieving message" << std::endl;
		m_disconnecting = true;
		//system("pause");
	}
	else
	{
		std::cout << response << std::endl;

		message = response;
		m_received = true;

		if (message == "exit") m_disconnecting = true;
	}
}

void Client::SendText(const String& message)
{
	String full = message;
	int length = message.Length() + 1;

	if (full == "exit")
	{
		m_disconnecting = true;
	}

	if (SDLNet_TCP_Send(m_socket, full.GetString(), length) < length)
	{
		if (!m_disconnecting)
		{
			std::cout << "Error sending message to client ID: ";
			std::cout << m_id << std::endl;
			m_disconnecting = true;
			//system("pause");
		}
	}
}

void Client::SetInThread(const bool flag)
{
	m_isInThread = flag;
}

void Client::SetConnected(const bool flag)
{
	m_isConnected = flag;
}

String Client::GetInfo() const
{
	return m_info;
}

void Client::UpdateInfo()
{
	// string syntax
	// x-pos$y-pos$score$isTagged

	ReceiveText(m_info);
}