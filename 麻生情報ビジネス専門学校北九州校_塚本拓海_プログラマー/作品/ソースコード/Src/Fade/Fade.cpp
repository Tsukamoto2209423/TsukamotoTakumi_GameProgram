#include "Fade.h"
#include <fstream>
#include <DxLib.h>
#include "Common.h"
#include <Math/MyMath.h>
#include "FileLoader/CSVFileLoader.h"
#include "Input/Input.h"
#include <Input/InputParameter.h>

namespace BOUDAMA
{
	Fade::Fade()
	{
		//状態初期化
		state_ = FADE::NONE;

		//α値
		alphaValue_ = 0;

		posX_ = 0;

		handleIndex_ = 0;

		concentrationLineIndex_ = 0;

		rotAngle_ = 0.0f;

		isEnd_ = false;
	};

	Fade::~Fade()
	{

	};

	//初期化処理関数
	void Fade::Init(void)
	{

		state_ = FADE::NONE;

		//α値
		alphaValue_ = 255;

		posX_ = Common::WINDOW_WIDTH_HALF;

		handleIndex_ = 0;

		rotAngle_ = 0.0f;

		isEnd_ = true;
	}

	//読み込み処理関数
	void Fade::Load(void)
	{
		CSV_LOADER::LoadHandle(FADE::PATH, syobonHandles_);
		CSV_LOADER::LoadHandle(FADE::EFFECT_PATH, lineHandles_);
	}

	//更新処理関数
	void Fade::Step(void)
	{
		//状態無しの場合は何もしない
		if (state_ == FADE::NONE)
		{
			return;
		}

		//フェードインの場合
		if (state_ == FADE::F_IN)
		{
			if (alphaValue_ <= 255)
			{
				alphaValue_ += FADE::ALPHA_SPEED;

				posX_ -= FADE::MOVE_SPEED;
				rotAngle_ -= MyMath::PI_OVER_TWENTY;

				return;
			}

			isEnd_ = (GetASyncLoadNum() == 0);

			return;
		}

		//フェードアウトの場合
		if (state_ == FADE::F_OUT)
		{
			if (alphaValue_ >= 0)
			{
				alphaValue_ -= FADE::ALPHA_SPEED;

				posX_ -= FADE::MOVE_SPEED;
				rotAngle_ -= MyMath::PI_OVER_TWENTY;

				return;
			}

			if (GetASyncLoadNum() == 0)
			{
				//終了フラグを立てる
				isEnd_ = true;

				state_ = FADE::NONE;

				//同期読み込み設定に変更
				SetUseASyncLoadFlag(false);
			}

			return;
		}
	}

	//描画処理関数
	void Fade::Draw(void)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue_);
		DrawBox(0, 0, Common::WINDOW_WIDTH, Common::WINDOW_HEIGHT, GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(posX_, Common::WINDOW_HEIGHT_HALF, 1.0f, rotAngle_, syobonHandles_[handleIndex_], true);
		
		//ネタ画像が表示されているときのみ集中線描画
		if (handleIndex_ == syobonHandles_.size() - 1)
		{
			DrawConcentrationLine();
		}
	}

	//破棄処理関数
	void Fade::Fin(void)
	{
		for (int handle : syobonHandles_)
		{
			if (handle != -1)
			{
				DeleteGraph(handle);
				handle = -1;
			}
		}

		syobonHandles_.clear();
		syobonHandles_.shrink_to_fit();
	}

	//フェードの状態変更
	void Fade::Change(void)
	{
		//状態無しの場合はフェードアウトにする
		if (state_ == FADE::NONE)
		{
			alphaValue_ = 0;
			state_ = FADE::F_IN;

			posX_ = Common::WINDOW_WIDTH + FADE::IMAGE_SIZE;

			//ネタ画像を必ず表示させる
			if (Input::IsKeyDown(GAME_INPUT::DEBUG))
			{
				handleIndex_ = static_cast<int>(syobonHandles_.size() - 1);
			}
			else
			{
				handleIndex_ = GetRand(static_cast<int>(syobonHandles_.size() - 1));
			}

			//フェード終了フラグ初期化
			isEnd_ = false;

			//非同期読み込み設定に変更
			SetUseASyncLoadFlag(true);

			return;
		}

		//フェードインの場合
		if (state_ == FADE::F_IN)
		{
			alphaValue_ = 255;
			state_ = FADE::F_OUT;

			//フェード終了フラグ初期化
			isEnd_ = false;

			return;
		}

		//フェードアウトの場合
		if (state_ == FADE::F_OUT)
		{
			alphaValue_ = 0;
			state_ = FADE::NONE;

			//同期読み込み設定に変更
			SetUseASyncLoadFlag(false);

			isEnd_ = true;

			return;
		}
	}

	//フェードインかフェードアウトが終わったか判定
	bool Fade::IsEnd(void) const noexcept
	{
		return isEnd_;
	}

	//集中線描画
	void Fade::DrawConcentrationLine(void)
	{
		//集中線描画
		DrawGraph(0, 0, lineHandles_[concentrationLineIndex_], true);

		//集中線の繰り返し処理
		concentrationLineIndex_ >= FADE::CONCENTRATION_LINE_END ?
			concentrationLineIndex_ = FADE::CONCENTRATION_LINE_1 : ++concentrationLineIndex_;
	}
}
