#ifndef SAXPARSER_H
#define SAXPARSER_H

#include <string>
#include <assert.h>

#include "sax_handler.h"
#include "expat_defs.h"
#include "expat/expat.h"

namespace apex
{
	class SaxParserImpl
	{
	private:
		XML_Parser m_pParser;

		SaxParserHandler& m_handler;

		bool m_bSkipWhitespaces;
	public:
		enum { ChunkSize = 512 };

		SaxParserImpl(SaxParserHandler& handler, const wchar_t* pEncodingName, bool bSkipWhitespaces) : m_pParser(NULL), m_handler(handler), m_bSkipWhitespaces(bSkipWhitespaces)
		{
			m_pParser = XML_ParserCreate(pEncodingName);
			if (m_pParser != NULL)
			{
				XML_SetUserData(m_pParser, this);
				XML_UseParserAsHandlerArg(m_pParser);

				XML_SetElementHandler(m_pParser, onElementStart, onElementEnd);
				XML_SetCharacterDataHandler(m_pParser, onCharacterData);
				XML_SetCommentHandler(m_pParser, onComment);
			}
		}

		~SaxParserImpl()
		{
			if (m_pParser != NULL)
			{
				XML_ParserFree(m_pParser);
			}
		}

	private:
		static void XMLCALL onElementStart(void *pUserData, const wchar_t* pElement, const wchar_t** pAttributes)
		{
			SaxParserImpl* pImpl = getImplFromUserData(pUserData);

			// Fill the collection of attribute key-value pairs.
			std::vector<std::pair<std::wstring, std::wstring>> attributes;
			{
				int index = 0;
				while (pAttributes[index] != NULL)
				{
					attributes.push_back(SaxParserAttributePair(
						std::wstring(pAttributes[index]),
						std::wstring(pAttributes[index + 1])));

					index += 2;
				}
			}

			pImpl->m_handler.onElementStart(pElement, attributes);
		}

		static void XMLCALL onElementEnd(void *pUserData, const wchar_t* pElement)
		{
			SaxParserImpl* pImpl = getImplFromUserData(pUserData);

			pImpl->m_handler.onElementEnd(pElement);
		}

		static void XMLCALL onCharacterData(void *pUserData, const wchar_t* pCharacterData, int length)
		{
			SaxParserImpl* pImpl = getImplFromUserData(pUserData);

			std::wstring characterData(pCharacterData, length);

			if (!(pImpl->m_bSkipWhitespaces && isWhitespaces(characterData)))
			{
				pImpl->m_handler.onCharacterData(characterData);
			}
		}

		static void XMLCALL onComment(void *pUserData, const wchar_t* pComment)
		{
			SaxParserImpl* pImpl = getImplFromUserData(pUserData);

			pImpl->m_handler.onComment(pComment);
		}

		static SaxParserImpl* getImplFromUserData(void* pUserData)
		{
			SaxParserImpl* pImpl = reinterpret_cast<SaxParserImpl*>(XML_GetUserData(reinterpret_cast<XML_Parser*>(pUserData)));
			//assert(pImpl != NULL);

			return pImpl;
		}

		bool parseChunk(const char* pText, int size)
		{
			void* pBuffer = XML_GetBuffer(m_pParser, size);
			//assert(pBuffer != NULL);

			::memcpy_s(pBuffer, size, pText, size);

			if (XML_ParseBuffer(m_pParser, size, false) == XML_STATUS_ERROR)
			{
				return false;
			}

			return true;
		}

		static bool isWhitespaces(const std::wstring& text)
		{
			static wchar_t whitespaces[] = L" \t\r\n\v\f";
			return (text.find_first_not_of(whitespaces) == std::wstring::npos);
		}
	public:

		bool parseXml(const wchar_t* pXmlText, int length)
		{
			int textSize = length * sizeof(wchar_t);
			void* pBuffer = NULL;
			const char* pParsingPosition = reinterpret_cast<const char*>(pXmlText);

			while (textSize > ChunkSize)
			{
				if (!parseChunk(pParsingPosition, ChunkSize))
				{
					return false;
				}

				textSize -= ChunkSize;
				pParsingPosition += ChunkSize;
			}

			if (!parseChunk(pParsingPosition, textSize))
			{
				return false;
			}

			return true;
		}

		XML_Parser getParser() { return m_pParser; }
	};

	class SaxParser
	{
	private:
		SaxParserImpl* m_pImpl;

		SaxParser(const SaxParser&);

		SaxParser& operator=(const SaxParser&);
	public:
		SaxParser(SaxParserHandler& handler);

		SaxParser(SaxParserHandler& handler, const std::wstring& encodingName, bool bSkipWhitespaces = true);

		~SaxParser();

		bool parseXml(const std::wstring& xmlText);

		bool parseFromFile(const std::string& xmlFilePath, bool bUTF8 = true);
	};
}

#endif