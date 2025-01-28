#pragma once

//3D���f���n���h���ۑ��p�ϐ�
class Model
{
private:
	int handle_;

public:
	Model(void);
	explicit constexpr Model(int handle) : handle_(handle) {}
	constexpr Model(const Model& model) noexcept : handle_(model.handle_) {}

	~Model(void);

	//�摜�ǂݍ��ݏ���
	void Load(const char* name);

	//�摜�ǂݍ��ݏ���
	void Load(const int handleNum);

	//�n���h���擾
	inline int GetHandle(void) const noexcept { return handle_; }

	int operator()() const noexcept { return handle_; }
	void operator()(const char* name) { Load(name); }
};
