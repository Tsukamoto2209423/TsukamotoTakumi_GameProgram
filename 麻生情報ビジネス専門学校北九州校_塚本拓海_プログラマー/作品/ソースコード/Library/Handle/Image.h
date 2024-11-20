#pragma once

//画像ハンドル保存用変数
class Image
{
private:
	int handle_;

public:
	Image(void);
	explicit constexpr Image(int handle) : handle_(handle) {}
	constexpr Image(const Image& image) noexcept : handle_(image.handle_) {}
	
	~Image(void);

	//画像読み込み処理
	void Load(const char* name);

	//ハンドル取得
	inline int GetHandle(void) const noexcept { return handle_; }

	int operator()() const noexcept { return handle_; }
	void operator()(const char* name) { Load(name); }
};