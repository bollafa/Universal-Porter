#pragma once
#include "..\stdfax.h"

namespace UniversalPorter
{
	std::ofstream& operator<<(std::ofstream& stream, DataObjectBase& objectBase);
	class HeaderPolicy
	{
	private:

		struct InternalData
		{
			uint32_t magic = _byteswap_ulong('MD20');                                       // "MD20". Legion uses a chunked file format starting with MD21.
			uint32_t version = 264;
			M2Array name;                                   // should be globally unique, used to reload by name in internal clients
			uint32_t Flags = 0;
			M2Array global_loops;						// Timestamps used in global looping animations.
			M2Array sequences;                       // Information about the animations in the model.
			M2Array sequence_lookups;
			/*#if  VERSION <= BC
			M2Array< ? > playable_animation_lookup;
			#endif*/
			M2Array bones;
			M2Array key_bone_lookup;
			M2Array vertices;
			// #if VERSION <= BC
			//
			//#else
			uint32_t NumSkinProfiles = 0;
			//#endif
			M2Array colors; // I'll implement them if they are needed, but honestly i dont know what they do
			M2Array textures;
			/* Let's see : */

			M2Array texture_weights;            // Transparency of textures.
												/*#if  VERSION <= BC
												M2Array< ? > unknown;
												#endif*/
			M2Array texture_transforms;
			M2Array replacable_texture_lookup;
			M2Array materials;                       // Blending modes / render flags.
			M2Array bone_lookup_table;
			M2Array texture_lookup_table;
			M2Array tex_unit_lookup_table;             // >= Cata : unused
			M2Array transparency_lookup_table;
			M2Array texture_transforms_lookup_table;
			// This is a large block - Ok it wasnt so big afterall ... huheuhe


			CAaBox bounding_box;                                 // min/max( [1].z, 2.0277779f ) - 0.16f seems to be the maximum camera height
			float bounding_sphere_radius;                         // detail doodad draw dist = clamp (bounding_sphere_radius * detailDoodadDensityFade * detailDoodadDist, ...)
			CAaBox collision_box;
			float collision_sphere_radius;

			M2Array collision_triangles;
			M2Array collision_vertices;
			M2Array collision_normals;
			M2Array attachments;                   // position of equipped weapons or effects
			M2Array attachment_lookup_table;
			M2Array events;                             // Used for playing sounds when dying and a lot else.
			M2Array lights;                             // Lights are mainly used in loginscreens but in wands and some doodads too.
			M2Array cameras;                           // The cameras are present in most models for having a model in the character tab. 
			M2Array camera_lookup_table;
			M2Array ribbon_emitters;                   // Things swirling around. See the CoT-entrance for light-trails.
			M2Array particle_emitters;
			InternalData() {}
		}mInternalData;
	protected:

		size_t GetSize() { return sizeof(InternalData); }
		const void write(std::ofstream& stream);
		friend M2Policy;
	};
	class SkinPolicy;
	/*Let's start with the SKIN HEADer POLICY :D */
	class SkinHeaderPolicy // skinhead see what i did there , this is the .skin file 'definition' if you want to call it so
	{
		friend SkinPolicy;
	private:
		struct InternalData
		{
//#if VERSION >= Wrath 
			uint32_t magic = _byteswap_ulong('SKIN');                         // 'SKIN'
//#endif
			M2Array vertices;
			M2Array indices;
			M2Array bones;
			M2Array submeshes;
			M2Array batches;
			uint32_t boneCountMax = 0;
		}mInternalData;
	protected:
		const void write(std::ofstream& stream);
		size_t GetSize() { return sizeof(InternalData); }
	public:

	};
	// SKIN LEADER HERE ---------------------------------
	class SkinPolicy // This is the actual .skin orquestrator
	{
	private:
		DataObject<SkinHeaderPolicy> mHeader;
		std::vector<DataObject<BasicDataObject<unsigned short>>> mVerticesLookup; // The vertex in the global vertex list.
		std::vector<DataObject<BasicDataObject<M2Face>>> mFaces; // Three indices which make up a triangle.
		std::vector<DataObject<BasicDataObject<M2VertexProp>>> mBoneProps;
		std::vector<DataObject<M2SubmeshPolicy>> mSubmeshes;
		std::vector<DataObject<M2Batch>> mTexturesBatch;
	protected:
		const void write(std::ofstream& stream);
		size_t GetSize() { return 0xDEAD; } // not really used, come on it is the orquestrator no need for this **** return ; 0xDEADBEEF
	public:
		void AddDummyCrap(); // Just to test it if works :D
	};
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
	// Nice easy lemon squeeze abstracted & cheesy 
	class UniversalPorterMgr // We make EVEN ANOTHER ABSTRACTION so the end user doesnt even need to know shit. It is as fool proof as possible.
	{
		/*
			This class will 'orquestrate' / 'lead' all the program, every instance means another ported file. It could even use assimp. But for now i'll put assimp implementation in
			main.cpp, imagine we wanted to change the library! Then this class wouldnt be so "abstract" and "useful" after all.
			The user will have to consciusly supply 
		*/
	private:
		
		
	protected:

	public:
		/* PUBLIC FOR NOW*/
		DataObject<M2Policy> M2File;
		// We suppose Im just going to support 1 skin. I mean, if I supported more I could just make it a vector and profit,but for now I'd rather just support 1.
		DataObject<SkinPolicy> mSkinFile;
		/* WOW BREAKING ENCAPSULATION GREAT */
		void SetName(const std::string& _Name) { M2File.SetName(_Name); }
		/*Write 2 different writing functions, one for M2 and the other for the skin , make sure that there ARE DIFFERENT STREAMS OTHERWISE WE'RE SCREWED */
		void WriteM2( std::ofstream& _M2Stream) { _M2Stream << M2File; }
		void WriteSkin(std::ofstream& _SkinStream) { _SkinStream << mSkinFile; }
	};
	
}