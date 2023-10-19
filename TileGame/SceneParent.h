#pragma once
#include <SDL.h>

#include "Actor.h"
#include <vector>
#include <map>

#include "CameraActor.h"
#include "NetworkServer.h"


enum class SceneMode
{
	SinglePlayer,
	LocalMultiplayer,
	OnlineClient,
	OnlineServer
};
int recvPacketThread(void* data);

/// <summary>
/// Classe parent pour toutes les scènes
/// </summary>
class SceneParent
{
public:
	virtual ~SceneParent() = default;

	virtual void load();
	virtual void start();
	virtual void update();
	virtual void draw();
	virtual void drawUi();
	virtual void close();

	virtual void onUpdate();

	std::map<Uint16, Actor*> gameObjectMap;


	CameraActor* getCamera();


	// Network
	NetworkAgent* networkAgent{ nullptr };
	bool connectionEstablished{ false };
	bool disconnected{ false };
	bool alreadyDestroyed{ false };
	SDL_Thread* thread{ nullptr };
	SDL_sem* sem{ nullptr };
	void setSceneMode(SceneMode sceneMode);
	void destroyNetworkAgent();
	void disconnect();
	bool isOnline() const;
	bool handlePacket(Packet* packet);
	virtual void onDisconnect() {}
	virtual void handleConnectionEstablished() {}


protected:
	SceneMode sceneMode{ SceneMode::SinglePlayer };

	CameraActor cam;

};

