#pragma once

//3Dモデルハンドル保存用変数
class Model
{
private:
	int handle_;

public:
	Model(void);
	explicit constexpr Model(int handle) : handle_(handle) {}
	constexpr Model(const Model& model) noexcept : handle_(model.handle_) {}

	~Model(void);

	//画像読み込み処理
	void Load(const char* name);

	//画像読み込み処理
	void Load(const int handleNum);

	//ハンドル取得
	inline int GetHandle(void) const noexcept { return handle_; }

	int operator()() const noexcept { return handle_; }
	void operator()(const char* name) { Load(name); }
};
