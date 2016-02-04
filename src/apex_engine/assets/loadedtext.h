#ifndef LOADEDTEXT_H
#define LOADEDTEXT_H

#include "loadableobject.h"

#include <string>
#include <vector>

class LoadedText : public ILoadableObject 
{
private:
	std::string text;
public:
	LoadedText(std::string text)
	{
		this->text = text;
	}

	std::string getText()
	{
		return text;
	}
};

#endif