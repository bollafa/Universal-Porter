#include <iostream>
#include <fstream>
#include <vector>

#include "..\stdfax.h"



#define WriteM2Array(_array) stream.write((char*)&_array, _array.size());
std::ofstream & UniversalPorter::operator<<(std::ofstream & stream,  DataObjectBase & objectBase)
{
	objectBase.write(stream);
	return stream;
}

const void UniversalPorter::HeaderPolicy::write(std::ofstream & stream)
{

	/*stream.write((char*)&mInternalData.magic, sizeof(uint32_t));
	stream.write((char*)&mInternalData.version, sizeof(uint32_t));
	stream.write((char*)&mInternalData.name, mInternalData.name.size());
	stream.write((char*)&mInternalData.Flags, sizeof(uint32_t));
	stream.write((char*)&mInternalData.sequences, mInternalData.sequences.size());
	WriteM2Array(mInternalData.sequence_lookups);
	WriteM2Array(mInternalData.bones);*/
	stream.write((char*)&mInternalData, GetSize());
	
}

const void UniversalPorter::RelArrayPolicy::write(std::ofstream & stream)
{
	stream.write((char*)&mInternalData, GetSize());
}

const void UniversalPorter::M2Policy::write(std::ofstream & stream)
{
	mHeader.mInternalData.name.mInternalData.mOffset = mHeader.GetSize();
	mHeader.mInternalData.name.mInternalData.mSize = mName.length();
	mHeader.mInternalData.global_loops.mInternalData.mOffset = mHeader.mInternalData.name.mInternalData.mOffset + mHeader.mInternalData.name.mInternalData.mSize;
	mHeader.mInternalData.global_loops.mInternalData.mSize = mGlobalSequences.size();
	mHeader.mInternalData.sequences.mInternalData.mOffset = mHeader.mInternalData.global_loops.mInternalData.mOffset + mHeader.mInternalData.global_loops.mInternalData.mSize * sizeof(uint32_t);
	mHeader.mInternalData.sequences.mInternalData.mSize = mSequences.size();
	mHeader.write(stream);
	stream << mName.c_str();
	stream.write((char*)&mGlobalSequences[0], sizeof(uint32_t) * mGlobalSequences.size());
	for each (M2SequencePolicy var in mSequences)
	{
		stream.write((char*)&var, var.GetSize());
	}
	mHeader.mInternalData.bones.mInternalData.mOffset = stream.tellp();
	mHeader.mInternalData.bones.mInternalData.mSize = mBones.size();
	//unsigned int index = 0;
	/*for each (DataObject<M2BonePolicy> var in mBones)
	{
		index++;
		var.mInternalData.scale.timestamps.mInternalData.mOffset = var.GetSize() + index * var.GetSize();
		var.mInternalData.scale.timestamps.mInternalData.mSize = var.mScale.mTimestamps.size();
		//stream.write((char*)&var, var.GetSize());
		//stream << var;
	}*/
	//uint32_t mFfset = stream.tellp();
	//index = 0;
	//bool Once = false;
	/* BONE PARSING */
	for( auto it = mBones.begin(); it != mBones.end(); ++it)
	{
		
		/*var.mInternalData.scale.timestamps.mInternalData.mOffset = mFfset + index * sizeof(M2Array) * var.mScale.mToTimestamps.size();
		var.mInternalData.scale.timestamps.mInternalData.mSize = var.mScale.mToTimestamps.size();
		if(!Once)
			stream.seekp(mHeader.mInternalData.bones.mInternalData.mOffset, std::ios_base::beg);
		Once = true;
		stream.write((char*)&var, var.GetSize());
		index++;*/
		

		
		stream << (*it);
		
	}
	/*for (auto it = mBones.begin(); it != mBones.end(); ++it)
	{
		//stream.write((char*)&var.mScale.mToTimestamps[0], sizeof(M2Array)*var.mScale.mToTimestamps.size());
		for (auto ABlock = it->mScale.mToTimestamps.begin(); ABlock != it->mScale.mToTimestamps.end(); ++ABlock)
		{
			stream << *ABlock;
		}
		for (auto ABlock = it->mScale.mToValues.begin(); ABlock != it->mScale.mToValues.end(); ++ABlock)
		{
			stream << *ABlock;
		}
	}*/


	uint32_t mOld = stream.tellp();
	for (auto it = mBones.begin(); it != mBones.end(); ++it)
	{
		stream << it->mScale;
	} // Write the ABlocks of mScale, now we know the size of the entire thing
	for (auto it = mBones.begin(); it != mBones.end(); ++it)
	{
		it->mScale.SetTestMode(false);
		stream << it->mScale;
	} // Afterwards, we write the values of the ABlocks.
	uint32_t LastValueRel = stream.tellp();
	stream.seekp(mOld, std::ios_base::beg);
	for (auto it = mBones.begin(); it != mBones.end(); ++it)
	{
		it->mScale.SetTestMode(true);
		stream << it->mScale;
	} // Now we rewrite the first thing ( the ABlocks ) so they point to correct data!
	
	// Now we rewrite bones so the point to the correct Arrays!!!
	stream.seekp(mBones[0].GetRelPos(), std::ios_base::beg);
	for each (DataObject<M2BonePolicy> var in mBones)
	{
		/*stream.write((char*)&var.mScale.mToTimestamps[0], sizeof(M2Array)*var.mScale.mToTimestamps.size());*/
		/*var.mInternalData.scale.timestamps.mInternalData.mOffset = var.mScale.mToTimestamps[0].GetRelPos();
		var.mInternalData.scale.timestamps.mInternalData.mSize = var.mScale.mToTimestamps.size();*/
		stream << var;
	}

	/* END BONE PARSING */

	//Now we point the vertices array to the vertices, because now we can print the vertices
	stream.seekp(LastValueRel, std::ios_base::beg);
	/*BoneLookUpTable*/
	mHeader.mInternalData.key_bone_lookup.SetInternalData(mBoneLookup.size(), stream.tellp());
	for (auto it = mBoneLookup.begin(); it != mBoneLookup.end(); ++it)
	{
		stream << *it;
	}
	/* Vertices parsing :*/
	mHeader.mInternalData.vertices.SetInternalData(mVertices.size(), stream.tellp());

	for (auto it = mVertices.begin(); it != mVertices.end(); ++it)
	{
		stream << *it;
	}
	/*TEXTURE PARSING*/
	mHeader.mInternalData.textures.SetInternalData(mTextures.size(), stream.tellp());
	for (auto it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		stream << *it;
	}
	uint32_t mTOld = stream.tellp();
	for (auto it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		stream << it->mFilename;
	}
	for (auto it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		it->mFilename.SetTestMode(false);
		stream << it->mFilename;
	}
	stream.seekp(mTOld, std::ios_base::beg);
	for (auto it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		it->mFilename.SetTestMode(true);
		stream << it->mFilename;
	}
	stream.seekp(mHeader.mInternalData.textures.mInternalData.mOffset, std::ios_base::beg);
	for (auto it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		
		stream << *it;
	}
	/* END TEXTURE PARSING*/
	/*FINAL REWRITE OF HEADER*/
	stream.seekp(0, std::ios_base::beg);
	mHeader.write(stream);
}

void UniversalPorter::M2Policy::AddDummyGlobalSeq() // Add dummy stuff function, for unit test purposes. :D
{
	for (unsigned int i = 0; i < 50; i++)
		mGlobalSequences.push_back(i);
	for (unsigned int j = 0; j < 50; j++)
		mSequences.push_back(M2SequencePolicy());
	for (unsigned int i = 0; i < 50; i++)
	{
		DataObject<M2BonePolicy> tempBone{};
		if (!(i % 2))
		{

			/*DataObject<M2Array> timestTemp{ M2Array{ 1,i } };
			DataObject<M2Array> timesttTemp{ M2Array{ 2,i } };
			tempBone.mScale.mToTimestamps.push_back(timestTemp);
			tempBone.mScale.mToTimestamps.push_back(timesttTemp);
			tempBone.mScale.mToValues.push_back(timestTemp);*/
		DataObject<DataChunk<BasicDataObject<uint32_t>>> BasicTemp;
	
		BasicTemp.AddValue(DataObject<BasicDataObject<uint32_t>>({1337}));
		BasicTemp.AddValue(DataObject<BasicDataObject<uint32_t>>({ i }));
		//BasicTemp.AddValue((DataObjectBase*)&DataObject<BasicDataObject<uint32_t>>(BasicDataObject<uint32_t>{ { 1337 }}));
		//BasicTemp.AddValue((DataObjectBase*)&DataObject<BasicDataObject<std::string>>(BasicDataObject<std::string>{  std::string("HelloTHERE") }));
			//BasicTemp.AddValue((DataObjectBase*)&DataObject<BasicDataObject<C3Vector>>(BasicDataObject<C3Vector>{ { 0, 0, 0 }}));
			tempBone.mScale.AddTimeStamp(BasicTemp);
			//tempBone.mScale.AddValue(BasicTemp);
			DataObject<M2VertexPolicy> vTempVertex;
			mVertices.push_back(vTempVertex);
			mVertices.push_back(vTempVertex);
			BasicDataObject<uint16_t> bonelookup = 1337;
			mBoneLookup.push_back(bonelookup);
			mBoneLookup.push_back(bonelookup);

		}
			
		mBones.push_back(tempBone);

	}
		
	DataObject<M2TexturePolicy> vTempTexture;
	DataObject<DataChunk<BasicDataObject<std::string>>> vTempFileName;
	vTempFileName.AddValue(DataObject<BasicDataObject<std::string>>(BasicDataObject<std::string>("Hello")));
	vTempTexture.SetFileName(vTempFileName);

	DataObject<M2TexturePolicy> vSTempTexture;
	DataObject<DataChunk<BasicDataObject<std::string>>> vSTempFileName;
	vSTempFileName.AddValue(DataObject<BasicDataObject<std::string>>(BasicDataObject<std::string>("L33T")));
	vSTempTexture.SetFileName(vSTempFileName);

	mTextures.push_back(vTempTexture);
	mTextures.push_back(vSTempTexture);
}


