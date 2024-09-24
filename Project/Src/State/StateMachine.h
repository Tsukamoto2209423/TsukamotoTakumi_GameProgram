#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "State.h"

//ó‘ÔŠÇ——pƒNƒ‰ƒX
class StateMachine
{
public:
    StateMachine() :
        nowState_()
    {

    }

    void Step(void)
    {
        nowState_->Step();

        if (nowState_->CanGoToNextState())
        {
           
            nowState_->Init();
        }
    }

    //ó‘Ô‚ğV‚µ‚­“o˜^‚·‚é
    void Register(const std::string& name, const std::shared_ptr<State> state)
    {
        stateMap_.insert(std::make_pair(name, state));
    }

    //Å‰‚©‚çn‚ß‚éó‘Ô‚ğİ’è
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

    //ó‘Ô‚ğ•ÏX‚·‚é
    void ChangeState(void)
    {
       const auto& it = stateMap_.find(nowState_->GetNextState());

        if (it == stateMap_.end())
        {
            return;
        }

        nowState_ = it->second;
    }

    //“o˜^‚µ‚½‚à‚Ì‚ğíœ‚·‚é
    void Deregistration(const std::string& registerName)
    {
        auto it = stateMap_.find(registerName);
        if (it == stateMap_.end())
        {
            return;
        }

        stateMap_.erase(it);
    }

    //‚·‚×‚Ä‚Ì“o˜^‚ğíœ‚·‚é
    void AllDeregistration(void)
    {
        stateMap_.clear();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<State>> stateMap_;
    std::shared_ptr<State> nowState_;
};
