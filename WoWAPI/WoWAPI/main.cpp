#include <iostream>
//#include "Headers\CoreTypes\CoreTypes.h"
//#include "Headers\MemoryFileMgr\MemoryFileMgr.h"
//#include "Headers\CoreTypes\LesserTypes.h"
//#include "Headers\CoreTypes\HeaderTypes.h"
#include <vector>
#include "stdfax.h"

#include <fstream>
//#define UNNAMED(origin,type,size) origin = Types::M2Array<type>{Types::RelativePointer(sizeof(vTemp.mData)+Extras),size};  Extras+= size * sizeof(type);
//#define __PADDING__(pad) Extras+= pad;
void main()
{
	/*using namespace WoW;*/
	using namespace UniversalPorter;
	RelArrayPolicy hello;
	//Types::DataChunk<Types::M2Sequence> test;
	//std::cout << test.size() << '\n';
	//Types::Header::M2Header empty{};
	////MemoryFile::MemoryFile<Types::TestHeader> vTemp = MemoryFile::WindowsOpenMemoryFile<Types::TestHeader>(L"Test/test.type");
	//MemoryFile::MemoryFile<Types::Header::M2Header> vTemp = MemoryFile::WindowsOpenMemoryFile<Types::Header::M2Header>(L"Test/M2/Ragnaros.m2");
	//
	///* PLAYGROUND BEGIN */
	//std::ofstream fout("Test/data.m2", std::ios::out | std::ios::binary);
	//size_t Extras = 0;
	//
	///*vTemp.mData.name = Types::M2Array<char>{ Types::RelativePointer(sizeof(vTemp.mData)+Extras),4 };
	//Extras += vTemp.mData.name.size();
	//vTemp.mData.sequences = Types::M2Array<Types::M2Sequence>{ Types::RelativePointer(sizeof(vTemp.mData) + Extras),vTemp.mSequences.size() };*/
	//UniversalPorter::DataObject<UniversalPorter::RelArrayPolicy> vData;
	//std::cout << vData.size() << '\n';
	//// Preparing the data with offsets!
	//UNNAMED(vTemp.mData.name, char, 28);
	////__PADDING__(8);
	//UNNAMED(vTemp.mData.global_loops, uint32_t, vTemp.global.size());
	//UNNAMED(vTemp.mData.sequences, Types::M2Sequence, vTemp.mSequences.size());
	//UNNAMED(vTemp.mData.sequence_lookups, uint16_t, vTemp.seq_lookup.size());
	//UNNAMED(vTemp.mData.bones, Types::M2CompBone, vTemp.mBones.size());
	//
	//// Writing the actual data
	//fout.write((char*)&vTemp.mData, sizeof(vTemp.mData));
	//fout.write((char*)"Visit Model-changing.com !\0", vTemp.mData.name.size()); // Encrypt this script later and decrypt it at runtime, so script kiddies wont change this!
	//fout.write((char*)&vTemp.global[0], vTemp.global.size() * sizeof(uint32_t));
	//fout.write((char*)&vTemp.mSequences[0], vTemp.mSequences.size() * sizeof(Types::M2Sequence));
	//fout.write((char*)&vTemp.seq_lookup[0], vTemp.seq_lookup.size() * sizeof(uint16_t));
	//fout.write((char*)&vTemp.mBones[0], vTemp.mBones.size() * sizeof(Types::M2CompBone));
	//fout.write((char*)&vTemp.mTranslation.mTimestampsArr[0], vTemp.mTranslation.mTimestampsArr.size() * sizeof(Types::M2Array<uint32_t>));
	//fout.write((char*)&vTemp.mTranslation.mTimestamps[0], vTemp.mTranslation.mTimestamps.size() * sizeof(uint32_t));
	//fout.write((char*)&vTemp.mTranslation.mValuesArr[0], vTemp.mTranslation.mValuesArr.size() * sizeof(Types::M2Array<Types::C3Vector>));
	//// Let's try bones!
	//fout.close();
	///* PLAYGROUND END */
	//std::cout << vTemp.global.size() << '\n';
	
	
	/*DataObject<M2Policy> M2File;
	std::ofstream TestFile("Test/Testing.m2", std::ios::out | std::ios::binary);
	// Let's see aa
	M2File.SetName("Visit Model-changing.com! Thanks!!!");
	M2File.AddDummyGlobalSeq();
	TestFile << M2File;
	TestFile.close();*/
	std::ofstream TestM2File("Test/Testing.m2", std::ios::out | std::ios::binary);
	std::ofstream TestSkinFile("Test/Testing01.skin", std::ios::out | std::ios::binary);
	UniversalPorterMgr TestPortFile;
	TestPortFile.SetName("Visit Model-changing.com! Thanks!!!");
	TestPortFile.M2File.AddDummyGlobalSeq();
	TestPortFile.WriteM2(TestM2File);

	TestPortFile.mSkinFile.AddDummyCrap();
	TestPortFile.WriteSkin(TestSkinFile);
	TestM2File.close();
	TestSkinFile.close();
}