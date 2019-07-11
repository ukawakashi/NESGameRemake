#pragma once
class BossState;
class Boss;
class BossBird;
class BossData
{
public:
	BossData();
	~BossData();

	Boss      *boss = nullptr;
	BossState *state = nullptr;
	BossBird  *bossBird = nullptr;
	void Update();
};



