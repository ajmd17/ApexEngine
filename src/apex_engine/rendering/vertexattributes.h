#ifndef VERTEXATTRIBUTES_H
#define VERTEXATTRIBUTES_H

#include <iostream>

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace apex
{
	class VertexAttribute
	{
	private:
		const char *attribName;
		unsigned int size, offset;
	public:

		VertexAttribute()
		{

		}

		VertexAttribute(const char *attributeName, unsigned int size)
		{
			this->attribName = attributeName;
			this->size = size;
		}

		const char *getAttributeName()
		{
			return attribName;
		}

		void setAttributeName(const char *name)
		{
			this->attribName = name;
		}

		unsigned int &getSize()
		{
			return size;
		}

		void setSize(unsigned int size)
		{
			this->size = size;
		}

		unsigned int &getOffset()
		{
			return offset;
		}

		void setOffset(unsigned int offset)
		{
			this->offset = offset;
		}
	};

	class VertexAttributes
	{
	private:
		vector<VertexAttribute> attribs;
	public:
		static VertexAttribute POSITIONS, TEXCOORDS0, TEXCOORDS1, NORMALS, TANGENTS, BITANGENTS, BONEINDICES, BONEWEIGHTS;

		VertexAttributes()
		{

		}

		~VertexAttributes()
		{
		}

		size_t getNumAttributes()
		{
			return attribs.size();
		}

		bool hasAttribute(VertexAttribute &attr)
		{
			for (size_t i = 0; i < attribs.size(); i++)
			{
				if (strcmp(attribs[i].getAttributeName(), attr.getAttributeName()) == 0)
				{
					if (attribs[i].getSize() == attr.getSize())
						return true;
				}
			}
			return false;
		}

		void setAttribute(VertexAttribute &val)
		{
			for (size_t i = 0; i < attribs.size(); i++)
			{
				if (strcmp(attribs[i].getAttributeName(), val.getAttributeName()) == 0)
				{
					std::cout << "An attribute with the name '" << val.getAttributeName() << "' already exists!\n";
					return;
				}
			}

			attribs.push_back(val);
		}

		void setAttribute(const char *name, unsigned int size)
		{
			VertexAttribute v_attr(name, size);
			this->setAttribute(v_attr);
		}

		VertexAttribute &getAttribute(int index)
		{
			return attribs[index];
		}

		bool getAttribute(const char *name, VertexAttribute &outAttr)
		{
			for (size_t i = 0; i < attribs.size(); i++)
			{
				if (strcmp(attribs[i].getAttributeName(), name) == 0)
				{
					outAttr = attribs[i];
					return true;
				}
			}
			return false;
		}
	};
}
#endif