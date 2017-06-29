#pragma once


namespace UniversalPorter
{
	class M2Policy;
	class RelArrayPolicy;
	struct C2Vector
	{
		float x;
		float y;
	};
	struct C3Vector
	{
		float x;
		float y;
		float z;
	};
	struct CAaBox
	{
		C3Vector min;
		C3Vector max;
	};
	struct M2Bounds {
		CAaBox extent;
		float radius;
	};
	struct M2Range
	{
		uint32_t first;
		uint32_t second;
	};

	struct Quat16 {
		__int16 x, y, z, w;
	};
	using M2CompQuat = Quat16;

	struct Quat32 {
		float x, y, z, w;
		Quat32(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	};

	static const Quat32 Quat16ToQuat32(const Quat16 t)
	{
		return Quat32(
			float(t.x < 0 ? t.x + 32768 : t.x - 32767) / 32767.0f,
			float(t.y < 0 ? t.y + 32768 : t.y - 32767) / 32767.0f,
			float(t.z < 0 ? t.z + 32768 : t.z - 32767) / 32767.0f,
			float(t.w < 0 ? t.w + 32768 : t.w - 32767) / 32767.0f);
	}

	/*class M2Policy;*/
	
	//using M2Array = UniversalPorter::RelArrayPolicy;
	class M2SequencePolicy
	{
	private:
		
		struct InternalData
		{
			enum AnimationID : uint16_t
			{
				A_Stand = 0,
				A_Death,
				A_Spell,
				A_Stop,
				A_Walk,
				A_Run,
				A_Dead,
				A_Rise,
				A_StandWound,
				A_CombatWound,
				A_CombatCritical,
				A_ShuffleLeft,
				A_ShuffleRight,
				A_Walkbackwards,
				A_Stun,
				A_HandsClosed,
				A_AttackUnarmed,
				A_Attack1H,
				A_Attack2H,
				A_Attack2HL,
				A_ParryUnarmed,
				A_Parry1H,
				A_Parry2H,
				A_Parry2HL,
				A_ShieldBlock,
				A_ReadyUnarmed,
				A_Ready1H,
				A_Ready2H,
				A_Ready2HL,
				A_ReadyBow,
				A_Dodge,
				A_SpellPrecast,
				A_SpellCast,
				A_SpellCastArea,
				A_NPCWelcome,
				A_NPCGoodbye,
				A_Block,
				A_JumpStart,
				A_Jump,
				A_JumpEnd,
				A_Fall,
				A_SwimIdle,
				A_Swim,
				A_SwimLeft,
				A_SwimRight,
				A_SwimBackwards,
				A_AttackBow,
				A_FireBow,
				A_ReadyRifle,
				A_AttackRifle,
				A_Loot,
				A_ReadySpellDirected,
				A_ReadySpellOmni,
				A_SpellCastDirected,
				A_SpellCastOmni,
				A_BattleRoar,
				A_ReadyAbility,
				A_Special1H,
				A_Special2H,
				A_ShieldBash,
				A_EmoteTalk,
				A_EmoteEat,
				A_EmoteWork,
				A_EmoteUseStanding,
				A_EmoteTalkExclamation,
				A_EmoteTalkQuestion,
				A_EmoteBow,
				A_EmoteWave,
				A_EmoteCheer,
				A_EmoteDance,
				A_EmoteLaugh,
				A_EmoteSleep,
				A_EmoteSitGround,
				A_EmoteRude,
				A_EmoteRoar,
				A_EmoteKneel,
				A_EmoteKiss,
				A_EmoteCry,
				A_EmoteChicken,
				A_EmoteBeg,
				A_EmoteApplaud,
				A_EmoteShout,
				A_EmoteFlex,
				A_EmoteShy,
				A_EmotePoint,
				A_Attack1HPierce,
				A_Attack2HLoosePierce,
				A_AttackOff,
				A_AttackOffPierce,
				A_Sheath,
				A_HipSheath,
				A_Mount,
				A_RunRight,
				A_RunLeft,
				A_MountSpecial,
				A_Kick,
				A_SitGroundDown,
				A_SitGround,
				A_SitGroundUp,
				A_SleepDown,
				A_Sleep,
				A_SleepUp,
				A_SitChairLow,
				A_SitChairMed,
				A_SitChairHigh,
				A_LoadBow,
				A_LoadRifle,
				A_AttackThrown,
				A_ReadyThrown,
				A_HoldBow,
				A_HoldRifle,
				A_HoldThrown,
				A_LoadThrown,
				A_EmoteSalute,
				A_KneelStart,
				A_KneelLoop,
				A_KneelEnd,
				A_AttackUnarmedOff,
				A_SpecialUnarmed,
				A_StealthWalk,
				A_StealthStand,
				A_Knockdown,
				A_EatingLoop,
				A_UseStandingLoop,
				A_ChannelCastDirected,
				A_ChannelCastOmni,
				A_Whirlwind,
				A_Birth,
				A_UseStandingStart,
				A_UseStandingEnd,
				A_CreatureSpecial,
				A_Drown,
				A_Drowned,
				A_FishingCast,
				A_FishingLoop,
				A_Fly,
				A_EmoteWorkNoSheathe,
				A_EmoteStunNoSheathe,
				A_EmoteUseStandingNoSheathe,
				A_SpellSleepDown,
				A_SpellKneelStart,
				A_SpellKneelLoop,
				A_SpellKneelEnd,
				A_Sprint,
				A_InFlight,
				A_Spawn,
				A_Close,
				A_Closed,
				A_Open,
				A_Opened,
				A_Destroy,
				A_Destroyed,
				A_Rebuild,
				A_Custom0,
				A_Custom1,
				A_Custom2,
				A_Custom3,
				A_Despawn,
				A_Hold,
				A_Decay,
				A_BowPull,
				A_BowRelease,
				A_ShipStart,
				A_ShipMoving,
				A_ShipStop,
				A_GroupArrow,
				A_Arrow,
				A_CorpseArrow,
				A_GuideArrow,
				A_Sway,
				A_DruidCatPounce,
				A_DruidCatRip,
				A_DruidCatRake,
				A_DruidCatRavage,
				A_DruidCatClaw,
				A_DruidCatCower,
				A_DruidBearSwipe,
				A_DruidBearBite,
				A_DruidBearMaul,
				A_DruidBearBash,
				A_DragonTail,
				A_DragonStomp,
				A_DragonSpit,
				A_DragonSpitHover,
				A_DragonSpitFly,
				A_EmoteYes,
				A_EmoteNo,
				A_JumpLandRun,
				A_LootHold,
				A_LootUp,
				A_StandHigh,
				A_Impact,
				A_LiftOff,
				A_Hover,
				A_SuccubusEntice,
				A_EmoteTrain,
				A_EmoteDead,
				A_EmoteDanceOnce,
				A_Deflect,
				A_EmoteEatNoSheathe,
				A_Land,
				A_Submerge,
				A_Submerged,
				A_Cannibalize,
				A_ArrowBirth,
				A_GroupArrowBirth,
				A_CorpseArrowBirth,
				A_GuideArrowBirth,
				A_EmoteTalkNoSheathe,
				A_EmotePointNoSheathe,
				A_EmoteSaluteNoSheathe,
				A_EmoteDanceSpecial,
				A_Mutilate,
				A_CustomSpell01,
				A_CustomSpell02,
				A_CustomSpell03,
				A_CustomSpell04,
				A_CustomSpell05,
				A_CustomSpell06,
				A_CustomSpell07,
				A_CustomSpell08,
				A_CustomSpell09,
				A_CustomSpell10,
				A_StealthRun
			};
			AnimationID id = AnimationID(0);                   // Animation id in AnimationData.dbc
			uint16_t variationIndex = 0;       // Sub-animation id: Which number in a row of animations this one is.
										   /*#if  VERSION <= BC
										   uint32_t start_timestamp;
										   uint32_t end_timestamp;
										   #else*/
			uint32_t duration = 100;             // The length (timestamps) of the animation. I believe this actually the length of the animation in milliseconds.
										   //#endif
			float movespeed = 100;               // This is the speed the character moves with in this animation.
			uint32_t flags = 0x32;                // See below.
			int16_t frequency = 0;             // This is used to determine how often the animation is played. For all animations of the same type, this adds up to 0x7FFF (32767).
			uint16_t _padding;
			M2Range replay{ 0,0 };                // May both be 0 to not repeat. Client will pick a random number of repetitions within bounds if given.
			uint32_t blendtime = 0;            // The client blends (lerp) animation states between animations where the end and start values differ. This specifies how long that blending takes. Values: 0, 50, 100, 150, 200, 250, 300, 350, 500.
			M2Bounds bounds{ {{0,0,0},{0,0,0}},0.0 };
			int16_t variationNext = -1;         // id of the following animation of this AnimationID, points to an Index or is -1 if none.
			uint16_t aliasNext = 0;            // id in the list of animations. Used to find actual animation if this sequence is an alias (flags & 0x40
		}mInternalData;
	protected:
		const void write(std::ofstream& stream);
		size_t GetSize() { return sizeof(InternalData); }
		friend UniversalPorter::M2Policy;
		
	};
	struct M2TrackBase
	{
		uint16_t interpolation_type = 0;
		int16_t global_sequence = -1;
/*#if  VERSION < Wrath
		M2Array<pair<uint32_t>> interpolation_ranges;   // no longer required >= Wrath , as implicit by minimum and maximum timestamp per sequence.
		M2Array<uint32_t> timestamps;
#else*/
		M2Array timestamps;
//#endif
	};

	
	struct M2Track : M2TrackBase
	{
/*#if  VERSION < Wrath 
		M2Array<T> values;
#else*/
		M2Array values;
//#endif
	};
	template<typename T>
	class M2TrackPolicy
	{
	private:
		std::vector< DataObject< DataChunk<BasicDataObject<uint32_t>  > > > mTimestamps;
		std::vector< DataObject< DataChunk<BasicDataObject<C3Vector> > > > mValues;
		bool bTestMode = true; // Test mode like Volkgswagen's
	protected:
	size_t GetSize() { return 0; } // Not Used! It is and old function, (deprecated) but keeped in for backward-compatibility
	const void write(std::ofstream& stream)
	{

			for (auto it = mTimestamps.begin(); it != mTimestamps.end(); ++it)
			{
				it->SetTestMode(bTestMode);
				stream << *it;
			}
			for (auto it = mValues.begin(); it != mValues.end(); ++it)
			{
				it->SetTestMode(bTestMode);
				stream << *it;
			}
	
		// Print the values here
	}
	public:
		const M2Array& GetTimestampsRelArrayPosition() { return M2Array{ mTimestamps.size(),mTimestamps.size() == 0 ? 0 : mTimestamps[0].GetRelPos() }; } //Retrieve a m2 array that points to timestamps
		const M2Array& GetValuesRelArrayPosition() { return M2Array{ mValues.size(), mValues.size() == 0 ? 0 : mValues[0].GetRelPos() }; }
		void SetTestMode(const bool& _mode) { bTestMode = _mode; }
		void AddTimeStamp(const DataObject<DataChunk<BasicDataObject<uint32_t>>>& _in) { mTimestamps.push_back(_in); }
		void AddValue(const DataObject<DataChunk<BasicDataObject<uint32_t>>>& _in) { mValues.push_back(_in); }
	};
	class M2BonePolicy
	{
		friend M2Policy;
	private:
		struct InternalData
		{
			int32_t key_bone_id = -1;            // Back-reference to the key bone lookup table. -1 if this is no key bone.
			enum
			{
				spherical_billboard = 0x8,
				cylindrical_billboard_lock_x = 0x10,
				cylindrical_billboard_lock_y = 0x20,
				cylindrical_billboard_lock_z = 0x40,
				transformed = 0x200,
				kinematic_bone = 0x400,       // MoP+: allow physics to influence this bone
				helmet_anim_scaled = 0x1000,  // set blend_modificator to helmetAnimScalingRec.m_amount for this bone
			};
			uint32_t flags = 0;
			int16_t parent_bone = -1;            // Parent bone ID or -1 if there is none.
			uint16_t submesh_id = 0;            // Mesh part ID OR uDistToParent?
			union {                         // only >= BC ?
				struct {
					uint16_t uDistToFurthDesc = 304;
					uint16_t uZRatioOfChain = 0;
				} CompressData;
				uint32_t boneNameCRC = 0;
			};
			M2Track translation;
			/*#if  VERSION <= Vanilla
			M2Track<C4Quaternion> rotation;
			#else*/
			M2Track rotation;   // compressed values, default is (32767,32767,32767,65535) == (0,0,0,1) == identity
											//#endif
			M2Track scale;
			C3Vector pivot{ 0,0,0 };                 // The pivot point of that bone.
			InternalData() {}
		}mInternalData;
	protected:
	
		const void write(std::ofstream& stream);
		size_t GetSize() { return sizeof(InternalData); }
		
		DataObject<M2TrackPolicy<C3Vector>> mTranslation;
		DataObject<M2TrackPolicy<M2CompQuat>> mRotation;
		DataObject<M2TrackPolicy<C3Vector>> mScale;

		friend UniversalPorter::M2Policy;
		
	public:
		M2BonePolicy() : mInternalData() {}
	};

	class M2VertexPolicy
	{
	private:
		struct InternalData
		{
			C3Vector pos = { 0,0,0 };
			uint8_t bone_weights[4] = { 0,0,0,0 };
			uint8_t bone_indices[4] = { 0,0,0,0 };
			C3Vector normal = { 0,0,0 };
			C2Vector tex_coords[2] = { {0,0},{0,0} };  // two textures, depending on shader used
		}mInternalData;
	protected:
		const void write(std::ofstream& stream);
		size_t GetSize() { return sizeof(InternalData); }
	public:
		M2VertexPolicy() : mInternalData() {}
	};

	class M2TexturePolicy
	{
		friend M2Policy;
	private:
		struct InternalData
		{
			uint32_t type = 0;          // see below
			uint32_t flags = 0;         // see below
			M2Array filename; // for non-hardcoded textures (type != 0), this still points to a zero-sized string
		}mInternalData;
	protected:
		 DataObject< DataChunk<BasicDataObject<std::string>  > >  mFilename;
		const void write(std::ofstream& stream);
		size_t GetSize() { return sizeof(InternalData); }
	public:
		M2TexturePolicy() {}
		void SetFileName(const DataObject< DataChunk<BasicDataObject<std::string>  > >& mTexturePath);
	};
}