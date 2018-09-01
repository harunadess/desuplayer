#ifndef FILEPATH_H
#define FILEPATH_H

#include <string>
using std::string;
using std::wstring;

class FilePath
{
public:
	FilePath();
	FilePath(wstring wideFilePath, string u8FilePath);
	~FilePath();

	wstring wideFilePath_;
	string u8FilePath_;

	template <class Archive>
	void save(Archive& archive) const
	{
		archive(wideFilePath_, u8FilePath_);
	}

	template <class Archive>
	void load(Archive& archive)
	{
		archive(wideFilePath_, u8FilePath_);
	}

};

#endif // !FILEPATH_H
