#pragma once
#include "..\stdfax.h"

namespace UniversalPorter
{
	class M2Policy
	{
	private:
		DataObject<HeaderPolicy> mHeader;
		std::string mName;
		std::vector<uint32_t> mGlobalSequences;
		std::vector<M2SequencePolicy> mSequences;
		std::vector<DataObject<M2BonePolicy>> mBones;
		std::vector<DataObject<BasicDataObject<uint16_t>>> mBoneLookup;
		std::vector<DataObject<M2VertexPolicy>> mVertices;
		std::vector<DataObject<M2TexturePolicy>> mTextures;
	protected:
		const void write(std::ofstream& stream);
		size_t GetSize() { return sizeof(M2Policy); }
	public:
		void SetName(const std::string& _Name) { mName = _Name; }
		void AddDummyGlobalSeq(); // Just to test it if works :D
	};
	std::ofstream& operator<<(std::ofstream& stream, DataObjectBase& objectBase);
}