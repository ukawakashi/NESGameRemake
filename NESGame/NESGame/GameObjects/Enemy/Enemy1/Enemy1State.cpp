#include "Enemy1State.h"



Enemy1State::Enemy1State()
{
}


Enemy1State::~Enemy1State()
{
}
void Enemy1State::Update()
{

}
void Enemy1State::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

Enemy1State::Enemy1State(Enemy1Data *enemyData)
{
	this->mData = enemyData;
}