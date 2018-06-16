#ifndef IO_HANDLER_H
#define IO_HANDLER_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::flush;
using std::end;

class IOHandler
{
public:
	IOHandler();
	~IOHandler();

	void outputTextInline(const char* output);
	void outputNewline();
	void outputText(const char* output);
	void outputTextWithSpacing(const char* output);
	void outputHeading(const char* output);
private:
	const char* headingLine_ = "========================================================";
};

#endif // !IO_HANDLER_H
