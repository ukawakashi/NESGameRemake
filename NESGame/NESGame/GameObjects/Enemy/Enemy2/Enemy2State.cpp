#include "Enemy2State.h"



Enemy2State::Enemy2State()
{
}

Enemy2State::Enemy2State(Enemy2Data *enemyData)
{
	this->mData = enemyData;
}

Enemy2State::~Enemy2State()
{
}



void Enemy2State::Update()
{

}
void Enemy2State::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

