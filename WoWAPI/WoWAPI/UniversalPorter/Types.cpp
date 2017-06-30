#include <fstream>
#include <cstdint>
#include <vector>
#include "..\stdfax.h"

const void UniversalPorter::M2SequencePolicy::write(std::ofstream & stream)
{
	return void();
}

const void UniversalPorter::M2BonePolicy::write(std::ofstream & stream)
{
	
	/*mInternalData.scale.timestamps.SetInternalData(mScale.mToTimestamps.size(),mScale.mToTimestamps.size() == 0 ? 0 : mScale.mToTimestamps[0].GetRelPos());
	mInternalData.scale.values.SetInternalData(mScale.mToValues.size(), mScale.mToValues.size() == 0 ? 0 : mScale.mToValues[0].GetRelPos());*/
	mInternalData.scale.timestamps = mScale.GetTimestampsRelArrayPosition();
	mInternalData.scale.values = mScale.GetValuesRelArrayPosition();
	stream.write((char*)&mInternalData, GetSize());
}

const void UniversalPorter::M2VertexPolicy::write(std::ofstream & stream)
{
	stream.write((char*)&mInternalData, GetSize());
}

const void UniversalPorter::M2TexturePolicy::write(std::ofstream & stream)
{
	mInternalData.filename = mFilename.GetRelArray();
	stream.write((char*)&mInternalData, GetSize());
}

void UniversalPorter::M2TexturePolicy::SetFileName(const DataObject<DataChunk<BasicDataObject<std::string>>>& mTexturePath)
{
	mFilename = mTexturePath;
}

const void UniversalPorter::M2SubmeshPolicy::write(std::ofstream & stream)
{
	stream.write((char*)&mInternalData, GetSize());
}

const void UniversalPorter::M2Batch::write(std::ofstream & stream)
{
	stream.write((char*)&mInternalData, GetSize());
}
