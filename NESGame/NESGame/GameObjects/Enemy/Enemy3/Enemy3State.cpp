#include "Enemy3State.h"



Enemy3State::Enemy3State()
{
}

Enemy3State::Enemy3State(Enemy3Data *enemyData)
{
	this->mData = enemyData;
}

Enemy3State::~Enemy3State()
{
}



void Enemy3State::Update()
{

}
void Enemy3State::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

