#include "Enemy5State.h"



Enemy5State::Enemy5State()
{
}

Enemy5State::Enemy5State(Enemy5Data *enemyData)
{
	this->mData = enemyData;
}

Enemy5State::~Enemy5State()
{
}



void Enemy5State::Update()
{

}
void Enemy5State::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

