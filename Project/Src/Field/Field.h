#pragma once

namespace BOUDAMA
{
	//場クラス
	class Field
	{
	private:
		//ハンドル
		int handle_;

	public:
		//コンストラクタ
		Field();

		//デストラクタ
		~Field();

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
	};
}
