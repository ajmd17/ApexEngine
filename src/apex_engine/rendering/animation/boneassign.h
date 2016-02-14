#ifndef BONEASSIGN_H
#define BONEASSIGN_H

namespace apex
{
	class BoneAssign
	{
	private:
		int vertIndex, boneIndex;
		float boneWeight;
	public:
		BoneAssign() {}

		BoneAssign(int vertIndex, float boneWeight, int boneIndex)
		{
			this->vertIndex = vertIndex;
			this->boneWeight = boneWeight;
			this->boneIndex = boneIndex;
		}

		int getVertexIndex() { return this->vertIndex; }

		void setVertexIndex(int i) { this->vertIndex = i; }

		float getBoneWeight() { return this->boneWeight; }

		void setBoneWeight(float weight) { this->boneWeight = weight; }

		int getBoneIndex() { return this->boneIndex; }

		void setBoneIndex(int i) { this->boneIndex = i; }
	};
}

#endif