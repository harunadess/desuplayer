#include "IOHandler.h"


IOHandler::IOHandler()
{
}


IOHandler::~IOHandler()
{
}

void IOHandler::outputTextInline(const char* output)
{
	cout << output << " " << flush;
}

void IOHandler::outputNewline()
{
	cout << "\n" << flush;
}

void IOHandler::outputText(const char* output)
{
	cout << output << endl;
}

void IOHandler::outputTextWithSpacing(const char* output)
{
	cout << endl << output << endl;
}

void IOHandler::outputHeading(const char* output)
{
	cout << headingLine_ << endl 
		<< "  " << output << endl 
		<< headingLine_ << endl;
}
