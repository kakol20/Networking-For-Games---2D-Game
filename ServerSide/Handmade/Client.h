#ifndef CLIENT_H
#define CLIENT_H

#include <SDL.h>
#include <SDL_net.h>

#include "String.h"

class Client
{
public:
	Client(int id);
	~Client();

	// Network Related Functions
	bool ClientConnected() const;
	bool InThread() const;
	bool IsDisconnecting() const;
	const TCPsocket GetSocket() const;

	void CloseSocket();
	void ListenForClient(const TCPsocket& listenSocket);
	void ReceiveText(String& message);
	void SendText(const String& message);
	void SetInThread(const bool flag);

	// Game Related Functions
	String GetInfo() const;
	void UpdateInfo();

private:
	bool m_disconnecting;
	bool m_isConnected;
	bool m_isInThread;
	bool m_received;
	TCPsocket m_socket = nullptr;
	int m_id;

	// Game Info
	bool m_isTagged;
	String m_info;
};

#endif // !CLIENT_H
