#include "RoboCatClientPCH.hpp"

State::State()
{
}

State::~State()
{
}


void State::RequestStackPush(EState state_id)
{
	StateStack::sInstance->PushState(state_id);
}

void State::RequestStackPop()
{
	StateStack::sInstance->PopState();
}

void State::RequestStackClear()
{
	StateStack::sInstance->ClearStates();
}

void State::OnActivate()
{

}

void State::OnDestroy()
{

}
