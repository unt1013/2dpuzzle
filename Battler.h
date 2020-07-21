#pragma once

class Skill;

class Battler
{
protected:
	float m_fHp = 0;
	float m_fAtk = 0;
	TYPE_COLOR m_eNeed = TYPE_COLOR::NONE;
	TYPE_COLOR m_eEfct = TYPE_COLOR::NONE;
	image* m_cImg = NULL;
	Skill* m_cSkill = NULL;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	void Action();
	
	Battler();
	~Battler();
};

