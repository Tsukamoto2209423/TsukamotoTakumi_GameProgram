#include "Field.h"
#include "DxLib.h"

namespace BOUDAMA
{
	namespace FIELD
	{
		constexpr char PATH[] = "Data/Model/Field/Field_Blue.x";

		constexpr VECTOR SCALE = { 9.0f,9.0f, 9.0f };
	}

	//コンストラクタ
	Field::Field()
	{
		//ハンドル初期化
		handle_ = -1;
	}

	//デストラクタ
	Field::~Field()
	{

	}

	//初期化処理関数
	void Field::Init(void)
	{

	}

	//読み込み処理関数
	void Field::Load(void)
	{
		//未読み込みなら読み込む
		if (handle_ == -1)
		{
			handle_ = MV1LoadModel(FIELD::PATH);
		}

		MV1SetScale(handle_, FIELD::SCALE);

		MV1SetPosition(handle_, { 0.0f,-30.0f,0.0f });
	}

	//行動処理関数
	void Field::Step(void)
	{

	}

	//描画処理関数
	void Field::Draw(void)
	{
		//描画
		MV1DrawModel(handle_);
	}

	//破棄処理関数
	void Field::Fin(void)
	{
		//読み込まれているなら破棄処理
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}
	}
}