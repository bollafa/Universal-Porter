#pragma once
#include <fstream>
#include <memory>

namespace UniversalPorter
{
	
	class M2Policy;
	//class M2SequencePolicy;
	//class M2BonePolicy;
	
	class DataObjectBase
	{
	private:

	protected:
		uint32_t RelPos = 0;
	public:
		virtual size_t size() { return 0; }
		virtual const void write(std::ofstream& stream) {}
		virtual const uint32_t & GetRelPos() { return RelPos; }
	};
	std::ofstream& operator<<(std::ofstream& stream, DataObjectBase& objectBase);
	template< typename DataPolicy >
	class DataObject : public DataPolicy, public DataObjectBase
	{
	private:
		
	public:
		DataObject(const DataPolicy& _in) : DataPolicy(_in) {}
		DataObject() {}
		const uint32_t & GetRelPos() { return RelPos; }
		void SetRelPos(unsigned int _Pos) { RelPos = _Pos; }
		size_t size() override { return DataPolicy::GetSize(); }
		const void write(std::ofstream& stream) override 
		{
			RelPos = (uint32_t)stream.tellp(); 
			DataPolicy::write(stream); 
		}
	};

	class RelArrayPolicy
	{
	private:
		struct InternalData
		{
			
			unsigned int mSize = 0;
			unsigned int mOffset = 0;
			InternalData(uint32_t _Size,uint32_t _Offset)  : mSize(_Size), mOffset(_Offset) {}
			InternalData() {}
		}mInternalData;
	protected:
		 size_t GetSize() { return sizeof(InternalData); }
		 const void write(std::ofstream& stream);
		 friend M2Policy;
	public:
		void SetInternalData(unsigned int _Size, unsigned int _Off) { mInternalData = InternalData{ _Size,_Off }; }
		void SetInternalSize(const unsigned int& _Size) { mInternalData.mSize = _Size; }
		void SetInternalOffset(const unsigned int& _Off) { mInternalData.mOffset = _Off; }
		RelArrayPolicy() {}
		RelArrayPolicy(unsigned int _Size, unsigned int _Off) : mInternalData{ _Size,_Off } {}
	};

	using M2Array = UniversalPorter::RelArrayPolicy;
	template <typename Type>
	class BasicDataObject // Basic Abstraction for common types like int or user-defined ones like C3Vector without special interactions
	{
	private:
		Type mValue;
	protected:
		size_t GetSize() { return sizeof(Type); } // Not used! It 'isnt' really used anywhere else ( or it shouldn't) now that we know stream.tellp()
		const void write(std::ofstream& stream) { stream.write((char*)&mValue, sizeof(mValue)); };
	public:
		BasicDataObject(Type _val) : mValue(_val) {}
	};
	template <>
	class BasicDataObject<std::string> // Basic Abstraction for common types like int or user-defined ones like C3Vector without special interactions
	{
	private:
		std::string mValue;
	protected:
		size_t GetSize() { return mValue.length(); } // Not used! It 'isnt' really used anywhere else ( or it shouldn't) now that we know stream.tellp()
		const void write(std::ofstream& stream) { stream << mValue.c_str() << '\0'; };
	public:
		BasicDataObject(std::string _val) : mValue(_val) {}
	};
	// Forward Declaration
	template <typename Type>
	class DataChunk 
	{
	private:
		DataObject<M2Array> mM2Array; // Points to where the objects are
		std::vector<DataObject<Type>> mValues;
		bool bTestMode = true; // bad practice delete when better approach is invented states: True: only print subAblock, false print subAblock and THE VALUES
		void WriteArrays(std::ofstream& stream);
		void WriteValues(std::ofstream& stream);
	protected:
		size_t GetSize() { return 0; } // Not used
		const void write(std::ofstream& stream)
		{
			/*mM2Array.SetInternalSize(mValues.size());
			stream << mM2Array; // Gets written!
			// We? Suppose there's correct offset data
			// We save current stream pos
			
			if(!bTestMode)
			if (mValues.size() != 0)
			{
				uint32_t mOldPos = stream.tellp();
				stream.seekp(mValues[0]->GetRelPos(), std::ios_base::beg); // We move the cursor to the values position!
				// Now we write the values and return to were we left!
				for (auto it = mValues.begin(); it != mValues.end(); ++it)
				{
					stream << ((**it));
				}
				stream.seekp(mOldPos, std::ios_base::beg);
			}
			*/ // Unsupported for now
			if (bTestMode)
			{
				WriteArrays(stream);
			}
			else
			{
				WriteValues(stream);
			}
		};
	public:
		/*
			Add initialize function which will set values to mM2Array ( just a dumb initializer )
		*/
		void AddValue( DataObject<Type> _in) { mValues.push_back(_in); }
		void SetM2ArrayPointer(const uint32_t& _rel) { mM2Array.SetInternalOffset(_rel ); }
		void SetTestMode(const bool& _mode) { bTestMode = _mode; } // Bad practice , delete when better approach exists
	
		const M2Array& GetRelArray() { return mM2Array; }
		DataChunk() {}
	};
	




	template<typename Type>
	inline void DataChunk<Type>::WriteArrays(std::ofstream & stream)
	{
		mM2Array.SetInternalOffset(mValues.size() == 0 ? 0 : mValues[0].GetRelPos());
			mM2Array.SetInternalSize(mValues.size());
			stream << mM2Array;
		

		// WOHOOOOOOOOOOOOOOOOOOOOOOOOO :D
	
	}
	template<>
	inline void DataChunk<BasicDataObject<std::string>>::WriteArrays(std::ofstream & stream)
	{
		mM2Array.SetInternalOffset(mValues.size() == 0 ? 0 : mValues[0].GetRelPos());
		mM2Array.SetInternalSize(mValues.size() == 0 ? 0 : mValues[0].size());
		stream << mM2Array;


		// WOHOOOOOOOOOOOOOOOOOOOOOOOOO :D

	}
	template<typename Type>
	inline void DataChunk<Type>::WriteValues(std::ofstream & stream)
	{
			//uint32_t mOldPos = stream.tellp();
			//uint32_t PosTest = mValues[0]->size();
			//stream.seekp(mValues[0]->GetRelPos(), std::ios_base::beg); // We move the cursor to the values position!
			// Now we write the values and return to were we left!


			for (auto it = mValues.begin(); it != mValues.end(); ++it)
			{
				stream << ((*it));
			}
			//stream.seekp(mOldPos, std::ios_base::beg);
		
	}

}