#ifndef SAXPARSERHANDLER_H
#define SAXPARSERHANDLER_H

#include <string>
#include <vector>

namespace apex
{
	typedef std::pair<std::wstring, std::wstring> SaxParserAttributePair;

	typedef std::vector<SaxParserAttributePair> SaxParserAttributes;

	class SaxParserHandler
	{
	public:
		virtual void onElementStart(const std::wstring& element, const SaxParserAttributes& attributes) { }

		virtual void onElementEnd(const std::wstring& element) { }

		virtual void onCharacterData(const std::wstring& characterData) { }

		virtual void onComment(const std::wstring& comment) { }
	};
}

#endif