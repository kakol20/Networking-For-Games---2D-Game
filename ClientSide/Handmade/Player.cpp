#include "Player.h"

#include <cmath>
#include <sstream>

#include "InputManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"


Player::Player()
{
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Player.png", "PlayerSprite");
	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/Formula1-Regular.ttf", 100, "MainFont");

	m_taggedT.SetFont("MainFont");
	m_scoreT.SetFont("MainFont");

	m_sprite.SetTexture("PlayerSprite");
	m_sprite.SetSpriteDimension(30, 30);
	m_sprite.SetTextureDimension(1, 1, 30, 30);

	m_taggedT.SetText("T");
	m_taggedT.SetSize(15, 30);

	m_position.x = TheScreen::Instance()->GetScreenSize().x / 2;
	m_position.y = TheScreen::Instance()->GetScreenSize().y / 2;
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

	if (m_tagged)
	{
		m_score = 0.0f;
	}
	else
	{
		m_score += 0.5f;;
	}

	std::stringstream str;
	char scoreChar[10] = { '\0' };

	str << m_score;
	str >> scoreChar;

	String score = "Score: ";
	score += scoreChar;

	m_scoreT.SetText(score.GetString());
	m_scoreT.SetSize(score.Length() * 15, 30);
}

bool Player::Draw()
{
	m_sprite.Draw(m_position.x - 15, m_position.y - 15);

	if (m_tagged)
	{
		m_taggedT.Draw(m_position.x - 7, m_position.y - 15);
	}

	m_scoreT.Draw();

	return true;
}

bool Player::IsTagged() const
{
	return m_tagged;
}

void Player::SetTagged(const bool flag)
{
	m_tagged = flag;
}

int Player::GetScore() const
{
	return (int)floor(m_score);
}
