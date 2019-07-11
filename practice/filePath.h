#ifndef FILEPATH_H
#define FILEPATH_H

#include <string>

class FilePath
{
public:
	FilePath();
	FilePath(std::wstring wideFilePath, std::string u8FilePath);
	~FilePath();

	template <class Archive>
	void save(Archive& archive) const
	{
		archive(wideFilePath, u8FilePath);
	}

	template <class Archive>
	void load(Archive& archive)
	{
		archive(wideFilePath, u8FilePath);
	}

	std::wstring wideFilePath;
	std::string u8FilePath;

};

#endif // !FILEPATH_H
