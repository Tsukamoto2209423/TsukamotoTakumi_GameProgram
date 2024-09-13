#pragma once

#include <memory>
#include "Object/Object.h"
#include <Player/PlayerParameter.h>

//物質基底クラス
class SubstanceBase : public Object
{
protected:
	//くっついたときの所有者
	std::weak_ptr<Object> owner_;

	//くっついたときにスコアに加算する値
	int addScoreNum;

public:
	//コンストラクタ
	SubstanceBase();

	//デストラクタ
	virtual ~SubstanceBase();

	//初期化処理関数
	virtual void Init(void);

	//読み込み処理関数
	virtual void Load(int originalHandle);

	//行動処理関数
	virtual void Step(void);

	//破棄処理関数
	virtual void Fin(void);

	//くっつく関数

	/// <summary>
	/// くっつく処理を行う関数
	/// </summary>
	/// <param name="attachObject">くっつくオブジェクト</param>
	virtual void AttachToObject(const std::shared_ptr<Object>& attachObject);

	//当たり判定処理
	virtual void HitCalculation(void);

	//引数の場所に出現する処理
	virtual void appearCalculation(const Vector3D& appearPos);

	//引数の場所から飛び散りながら出現する処理
	virtual void FlyAppearCalculation(const Vector3D &appearPos);

	//プレイヤーに吸い込まれるように追いかける処理
	virtual void ChasePosCalculation(const Vector3D& chasePos);

	/// <summary>
	/// くっついていないか
	/// </summary>
	/// <returns>
	/// true : くっついていない
	/// false : くっついている
	/// </returns>
	inline bool IsOwnerExpired(void) const noexcept { return owner_.expired(); }

	//くっつけている人(所有者)取得
	inline std::shared_ptr<Object> GetOwner(void) const noexcept { return owner_.lock(); }

	//所有者設定
	inline void SetOwner(const std::shared_ptr<Object>& owner) { owner_ = owner; }

	//所有者初期化
	inline void ResetOwner(void) { owner_.reset(); }

	//くっついたときにスコアに加算する値を取得
	inline int GetAddScoreNum(void) const { return addScoreNum; }

	/// <summary>
	/// 所有者はダメージを与えられる状態か
	/// </summary>
	/// <returns>
	/// true : ダメージを与えられる
	/// false : ダメージを与えられない
	/// </returns>
	bool IsOwnerNotInvincible(void) const;

};
