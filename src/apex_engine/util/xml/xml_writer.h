#ifndef XML_WRITER_H
#define XML_WRITER_H

#include <fstream>
using std::ofstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

// A simple XML writer class. 
// Created by: Andrew MacDonald (12/02/2016)
namespace apex
{
	class Element
	{
	public:
		Element() {}
		int id;
		int parentid;
		string tag;
		bool is_closed;
		bool contains_data;
	};

	class XmlWriter
	{
	private:
		std::ofstream file;
		vector<Element> elements;
		int eltIdx;
		int indent;
		int c_id;

		void closeLastElement()
		{
			if (elements.size() > 0)
			{
				Element &lastElt = elements[eltIdx];
				if (!lastElt.is_closed)
				{
					file << ">";
					lastElt.is_closed = true;
				}
			}
		}
	public:
		XmlWriter(const char *filepath)
		{
			file.open(filepath);
			if (!file.is_open())
			{
				throw std::runtime_error("Stream error");
			}

			indent = 0;
			eltIdx = -1;
			c_id = 0;
		}

		void beginDocument()
		{
			// header
			file << "<?xml version=\"1.0\"?>\n";
		}

		void close()
		{
			file.close();
		}

		void beginElement(const string tag)
		{
			closeLastElement();

			Element elt;
			elt.tag = tag;
			elt.is_closed = false;
			elt.contains_data = false;
			elt.id = ++c_id;
			elt.parentid = eltIdx;

			elements.push_back(elt);
			eltIdx = elements.size() - 1;

			if (eltIdx > 0)
				file << "\n";
			for (int i = 0; i < indent; i++)
				file << "\t";
			file << "<" << elt.tag;
			indent++;
		}

		void endElement()
		{
			indent--;

			if (elements[eltIdx].id == c_id)
			{
				if (elements[eltIdx].contains_data)
					file << "</" << elements[eltIdx].tag << ">";
				else
					file << "/>";
			}
			else
			{
				closeLastElement();

				file << "\n";
				for (int i = 0; i < indent; i++)
					file << "\t";
				file << "</" << elements[eltIdx].tag << ">";
			}

			eltIdx = elements[eltIdx].parentid;
		}

		void attribute(const string &name, const string &value)
		{
			file << " " << name << "=\"" << value << "\"";
		}

		void characters(const string &data)
		{
			closeLastElement();

			if (elements.size() > 0)
			{
				Element &lastElt = elements[eltIdx];
				lastElt.contains_data = true;
			}
			file << data;
		}

		void comment(const string &comment)
		{
			closeLastElement();

			file << "\n";
			for (int i = 0; i < indent; i++)
				file << "\t";
			file << "<!--" << comment << "-->";
		}
	};
}
#endif