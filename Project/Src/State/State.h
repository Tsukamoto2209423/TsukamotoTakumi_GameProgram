#pragma once

#include <memory>
#include <string>
#include "StateBase.h"

//ステートマシンで使う状態切り替え用クラス
class State final
{
private:
    //状態実行用変数
    std::shared_ptr<StateBase> state_;

    //次に行く状態の名前
    std::string nextStateName_;

public:
    State() = default;
    State(const std::shared_ptr<StateBase> state, const std::string& nextStateName) noexcept :
        state_(state), nextStateName_(nextStateName)  {}

    ~State() = default;

    //初期化処理関数
    void Init(void);

    //行動処理関数
    void Step(void);

    //次状態移行判断用関数
    bool CanGoToNextState(void);

    //状態を変更するときに使う関数
    void ChangeState(void);

    //次の状態取得
    std::string GetNextState(void) const noexcept;
};
