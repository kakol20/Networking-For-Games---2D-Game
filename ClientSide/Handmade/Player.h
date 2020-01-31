#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Sprite.h"
#include "String.h"
#include "Text.h"


class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Update();
	virtual bool Draw();

	bool IsTagged() const;
	void SetTagged(const bool flag);

	int GetScore() const;

private:

	bool m_tagged;
	float m_score;
	Sprite m_sprite;
	Text m_scoreT;
	Text m_taggedT;
};

#endif // !PLAYER_H