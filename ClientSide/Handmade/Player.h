#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Update();
	virtual bool Draw();

	bool IsTagged();
	void SetTagged(bool flag);
	

private:

	bool m_tagged;
	Sprite m_sprite;
	Text m_taggedT;
};

#endif // !PLAYER_H