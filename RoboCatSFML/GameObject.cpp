#include "RoboCatPCH.hpp"

GameObject::GameObject() :
	mIndexInWorld(-1),
	mDoesWantToDie(false),
	mRotation(0.f),
	mNetworkId(0),
	mColor(Colors::White),
	mScale(1.0f),
	mPriority(0)
{
}

void GameObject::Update()
{
	//object don't do anything by default...	
}


sf::FloatRect GameObject::GetBounds()
{
	return sf::FloatRect(mPosition.mX - mSize.mX / 2.f * mScale, mPosition.mY - mSize.mY / 2.f * mScale, mSize.mX * mScale, mSize.mY * mScale);
}

Vector3 GameObject::GetForwardVector()	const
{
	//should we cache this when you turn?
	//SDL appears to use radians while SFML uses degrees - make sure to convert to radians
	//before using!
	return Vector3(sinf(RoboMath::ToRadians(mRotation)), -cosf(RoboMath::ToRadians(mRotation)), 0.f);
}

void GameObject::SetNetworkId(int inNetworkId)
{
	//this doesn't put you in the map or remove you from it
	mNetworkId = inNetworkId;

}

void GameObject::SetRotation(float inRotation)
{
	//should we normalize using fmodf?
	mRotation = inRotation;
}