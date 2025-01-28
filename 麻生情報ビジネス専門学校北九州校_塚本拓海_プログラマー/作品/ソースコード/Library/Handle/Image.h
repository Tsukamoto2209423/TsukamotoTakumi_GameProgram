#pragma once

//�摜�n���h���ۑ��p�ϐ�
class Image
{
private:
	int handle_;

public:
	Image(void);
	explicit constexpr Image(int handle) : handle_(handle) {}
	constexpr Image(const Image& image) noexcept : handle_(image.handle_) {}
	
	~Image(void);

	//�摜�ǂݍ��ݏ���
	void Load(const char* name);

	//�n���h���擾
	inline int GetHandle(void) const noexcept { return handle_; }
	int operator()(void) const noexcept { return handle_; }

	void operator()(const char* name) { Load(name); }
};