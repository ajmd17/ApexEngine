#include "sax_parser.h"
#include <fstream>
#include <iostream>

namespace apex
{
	SaxParser::SaxParser(SaxParserHandler& handler) : m_pImpl(NULL)
	{
		m_pImpl = new SaxParserImpl(handler, NULL, true);
		assert(m_pImpl != NULL);
		assert(m_pImpl->GetParser() != NULL);
	}

	SaxParser::SaxParser(SaxParserHandler& handler, const std::wstring& encodingName, bool bSkipWhitespaces)
		: m_pImpl(NULL)
	{
		const wchar_t* pEncodingName = (encodingName.length() > 0) ? encodingName.c_str() : NULL;
		m_pImpl = new SaxParserImpl(handler, pEncodingName, bSkipWhitespaces);
		assert(m_pImpl != NULL);
		assert(m_pImpl->GetParser() != NULL);
	}

	SaxParser::~SaxParser()
	{
		if (m_pImpl != NULL)
		{
			delete m_pImpl;
			m_pImpl = NULL;
		}
	}

	bool SaxParser::parseXml(const std::wstring& xmlText)
	{
		return m_pImpl->parseXml(xmlText.c_str(), static_cast<int>(xmlText.length()));
	}

	bool SaxParser::parseFromFile(const std::string& xmlFilePath, bool bUTF8)
	{
		std::wifstream inputFile(xmlFilePath.c_str());
		if (inputFile.is_open())
		{
			// Skip the BOM bytes.
			if (bUTF8) { inputFile.seekg(3); }

			std::wstring xmlText(
				(std::istreambuf_iterator<wchar_t>(inputFile)),
				std::istreambuf_iterator<wchar_t>());

			return m_pImpl->parseXml(xmlText.c_str(), static_cast<int>(xmlText.length()));
		}

		return false;
	}
}