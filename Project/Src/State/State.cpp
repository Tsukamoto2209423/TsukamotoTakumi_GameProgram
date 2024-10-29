#include "State.h"

//初期化処理関数
void State::Init()
{
	state_->Init();
}

//行動処理関数
void State::Step()
{
	state_->Step();
}

//次状態移行判断用関数
bool State::CanGoToNextState()
{
	return false;
}

//状態を変更するときに使う関数
void State::ChangeState(void)
{

}

//次の状態取得
std::string State::GetNextState(void) const noexcept
{
	return nextStateName_;
}
