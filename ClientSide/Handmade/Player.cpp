#include "Player.h"

#include "TextureManager.h"
#include "InputManager.h"

Player::Player()
{
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Player.png", "PlayerSprite");
	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/Formula1-Regular.ttf", 100, "MainFont");

	m_taggedT.SetFont("MainFont");

	m_sprite.SetTexture("PlayerSprite");
	m_sprite.SetSpriteDimension(30, 30);
	m_sprite.SetTextureDimension(1, 1, 30, 30);

	m_taggedT.SetText("T");
	m_taggedT.SetSize(15, 30);

	m_position.x = 0;
	m_position.y = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	KeyState keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_W])
	{
		m_position.y -= 1;
	}

	if (keys[SDL_SCANCODE_S])
	{
		m_position.y += 1;
	}

	if (keys[SDL_SCANCODE_D])
	{
		m_position.x += 1;
	}

	if (keys[SDL_SCANCODE_A])
	{
		m_position.x -= 1;
	}
}

bool Player::Draw()
{
	m_sprite.Draw(m_position.x - 15, m_position.y - 15);
	if (m_tagged)
	{
		m_taggedT.Draw(m_position.x - 7, m_position.y - 15);
	}

	return true;
}

bool Player::IsTagged()
{
	return m_tagged;
}

void Player::SetTagged(bool flag)
{
	m_tagged = flag;
}