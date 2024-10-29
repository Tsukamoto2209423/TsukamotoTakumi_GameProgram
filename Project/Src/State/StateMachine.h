#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "State.h"

//状態管理用クラス
class StateMachine
{
private:
    //状態一覧のハッシュマップ
    std::unordered_map<std::string, std::shared_ptr<State>> stateMap_;
    std::shared_ptr<State> nowState_;

public:
    StateMachine() : nowState_() { }

    void Step(void)
    {
        nowState_->Step();

        if (nowState_->CanGoToNextState())
        {
            nowState_->Init();
        }
    }

    //状態を新しく登録する
    void Register(const std::string& name, const std::shared_ptr<State> state)
    {
        stateMap_.insert(std::make_pair(name, state));
    }

    //最初から始める状態を設定
    void SetStartState(const std::string& registerName)
    {
        const auto& it = stateMap_.find(registerName);

        if (it == stateMap_.end())
        {
            return;
        }

        nowState_ = it->second;
        nowState_->Init();

    }

    //状態を変更する
    void ChangeState(void)
    {
       const auto& it = stateMap_.find(nowState_->GetNextState());

        if (it == stateMap_.end())
        {
            return;
        }

        nowState_ = it->second;
    }

    //登録したものを削除する
    void Deregistration(const std::string& registerName)
    {
        const auto& it = stateMap_.find(registerName);

        if (it == stateMap_.end())
        {
            return;
        }

        stateMap_.erase(it);
    }

    //すべての登録を削除する
    void AllDeregistration(void)
    {
        stateMap_.clear();
    }

};
