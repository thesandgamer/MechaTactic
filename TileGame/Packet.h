#pragma once
#include <SDL_stdinc.h>
//#include "GameObject.h"

enum class PacketType
{
	INIT_MATCH,
	PLAYER_1_POSITION,
	PLAYER_2_POSITION,
	BALL_POSITION,
	MISC
};
class Packet
{
public:
	Packet() = default;
	Packet(PacketType type);
	PacketType packetType{ PacketType::MISC };
	Uint16 id{ 0 };


	/*
	Packet(GameObject* gameObject);
	Vector2<float> position{ 0.0f, 0.0f };
	Vector2<float> direction{ 0.0f, 0.0f };*/
};