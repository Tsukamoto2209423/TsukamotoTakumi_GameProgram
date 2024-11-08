#pragma once

#include <vector>
#include <memory>
#include "SubstanceBase.h"
#include "Substance.h"

namespace BOUDAMA
{
	//物質管理クラス
	class SubstanceManager
	{
	private:
		//物質管理
		std::vector<std::shared_ptr<SubstanceBase>> substances_;

	public:
		//コンストラクタ
		SubstanceManager();

		//デストラクタ
		~SubstanceManager();

		//初期化処理関数
		void Init(void);

		//読み込み処理関数
		void Load(void);

		//行動処理関数
		void Step(void);

		//描画処理関数
		void Draw(void);

		//破棄処理関数
		void Fin(void);

		//引数の場所から飛び散りながら出現する処理
		void FlyAppearCalculation(const Vector3D& appearPos);

		//ランダムに物質を抽選して引数の場所から飛び散りながら出現する処理
		void RandomFlyAppearCalculation(const Vector3D& appearPos);

		inline const std::vector<std::shared_ptr<SubstanceBase>>& GetSubstance(void) const { return substances_; }
	};
}
