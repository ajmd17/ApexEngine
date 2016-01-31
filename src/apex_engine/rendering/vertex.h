#ifndef VERTEX_H
#define VERTEX_H

#include "../math/vector2f.h"
#include "../math/vector3f.h"

class Vertex
{
private:
	const static int	MAX_BONE_WEIGHTS = 4,
						MAX_BONE_INDICES = 4;

	int count_bone_indices,
		count_bone_weights;

	Vector3f position,
	   	 	 normal,
	 		 tangent,
			 bitangent;

	Vector2f texCoord0,
			 texCoord1;

	float boneWeights[4];
	unsigned int boneIndices[4];

public:
	Vertex() {}
	
	Vertex(Vector3f pos)
	{
		this->position = pos;
	}

	Vertex(Vector3f pos, Vector2f texCoord0)
	{
		this->position = pos;
		this->texCoord0 = texCoord0;
	}

	Vertex(Vector3f pos, Vector2f texCoord0, Vector3f normal)
	{
		this->position = pos;
		this->texCoord0 = texCoord0;
		this->normal = normal;
	}

	Vertex(const Vertex &other)
	{
		this->position = other.position;
		this->normal = other.normal;
		this->texCoord0 = other.texCoord0;
		this->texCoord1 = other.texCoord1;
		this->tangent = other.tangent;
		this->bitangent = other.tangent;
		for (int i = 0; i < 4; i++)
		{
			this->boneWeights[i] = other.boneWeights[i];
			this->boneIndices[i] = other.boneIndices[i];
		}
	}

	~Vertex()
	{
	}

	void setPosition(Vector3f &pos)
	{
		this->position = pos;
	}

	Vector3f &getPosition()
	{
		return this->position;
	}

	void setNormal(Vector3f &norm)
	{
		this->normal = norm;
	}

	Vector3f &getNormal()
	{
		return this->normal;
	}

	void setTexCoord0(Vector2f &tc0)
	{
		this->texCoord0 = tc0;
	}

	Vector2f &getTexCoord0()
	{
		return this->texCoord0;
	}

	void setTexCoord1(Vector2f &tc1)
	{
		this->texCoord1 = tc1;
	}

	Vector2f &getTexCoord1()
	{
		return this->texCoord1;
	}
	
	void setTangent(Vector3f &tan)
	{
		this->tangent = tan;
	}

	Vector3f &getTangent()
	{
		return this->tangent;
	}

	void setBitangent(Vector3f &bitan)
	{
		this->bitangent = bitan;
	}

	Vector3f &getBitangent()
	{
		return this->bitangent;
	}

	void setBoneWeight(int i, float &val)
	{
		boneWeights[i] = val;
	}

	float &getBoneWeight(int i)
	{
		return boneWeights[i];
	}

	void setBoneIndex(int i, int &val)
	{
		boneIndices[i] = val;
	}

	unsigned int &getBoneIndex(int i)
	{
		return boneIndices[i];
	}

	void addBoneWeight(float &weight)
	{
		if (count_bone_weights < MAX_BONE_WEIGHTS)
		{
			boneWeights[count_bone_weights++] = weight;
		}
	}

	void addBoneIndex(unsigned int &index)
	{
		if (count_bone_indices < MAX_BONE_INDICES)
		{
			boneIndices[count_bone_weights++] = index;
		}
	}

};

#endif
