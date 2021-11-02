#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <iostream>
class UClass {
public:
	BYTE _padding_0[0x40];
	UClass* SuperClass;
};

class UObject {
public:
	PVOID VTableObject;
	DWORD ObjectFlags;
	DWORD InternalIndex;
	UClass* Class;
	BYTE _padding_0[0x8];
	UObject* Outer;

	inline BOOLEAN IsA(PVOID parentClass) {
		for (auto super = this->Class; super; super = super->SuperClass) {
			if (super == parentClass) {
				return TRUE;
			}
		}

		return FALSE;
	}
};

class FUObjectItem {
public:
	UObject* Object;
	DWORD Flags;
	DWORD ClusterIndex;
	DWORD SerialNumber;
	DWORD SerialNumber2;
};

class TUObjectArray {
public:
	FUObjectItem* Objects[9];
};

class GObjects {
public:
	TUObjectArray* ObjectArray;
	BYTE _padding_0[0xC];
	DWORD ObjectCount;
};

template<class T>
struct TArray {
	friend struct FString;

public:
	inline TArray() {
		Data = nullptr;
		Count = Max = 0;
	};

	inline INT Num() const {
		return Count;
	};

	inline T& operator[](INT i) {
		return Data[i];
	};

	inline BOOLEAN IsValidIndex(INT i) {
		return i < Num();
	}

private:
	T* Data;
	INT Count;
	INT Max;
};

struct FString : private TArray<WCHAR> {
	FString() {
		Data = nullptr;
		Max = Count = 0;
	}

	FString(LPCWSTR other) {
		Max = Count = static_cast<INT>(wcslen(other));

		if (Count) {
			Data = const_cast<PWCHAR>(other);
		}
	};

	inline BOOLEAN IsValid() {
		return Data != nullptr;
	}

	inline PWCHAR c_str() {
		return Data;
	}
};

class FText {
private:
	char _padding_[0x28];
	PWCHAR Name;
	DWORD Length;

public:
	inline PWCHAR c_str() {
		return Name;
	}
};

typedef struct {
	float X, Y, Z;
} FVector;

typedef struct {
	float X, Y;
} FVector2D;

typedef struct {
	float Pitch;
	float Yaw;
	float Roll;
} FRotator;

typedef struct {
	FVector Location;
	FRotator Rotation;
	float FOV;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float OrthoFarClipPlane;
	float AspectRatio;
} FMinimalViewInfo;

typedef struct {
	float M[4][4];
} FMatrix;

typedef struct {
	FVector ViewOrigin;
	char _padding_0[4];
	FMatrix ViewRotationMatrix;
	FMatrix ProjectionMatrix;
} FSceneViewProjectionData;

typedef struct {
	FVector Origin;
	FVector BoxExtent;
	float SphereRadius;
} FBoxSphereBounds;
template<typename T>
static T* FindObject(const std::string& name)
{
	for (int i = 0; i < GetGlobalObjects().Num(); ++i)
	{
		auto object = GetGlobalObjects().GetByIndex(i);

		if (object == nullptr)
		{
			continue;
		}

		if (object->GetFullName() == name)
		{
			return static_cast<T*>(object);
		}
	}
	return nullptr;
}

static UClass* FindClass(const std::string& name)
{
	return FindObject<UClass>(name);
}
class UField : public UObject
{
public:
	class UField* Next;                                                     // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY

	static UClass* StaticClass()
	{
		static UClass* ptr = NULL;
		if (!ptr)
			ptr = FindClass(("Class CoreUObject.Field"));

		return ptr;
	}

};
class UStruct : public UField
{
public:
	char                                               pad_0030[0x10];                                           // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UStruct* SuperField;                                               // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UField* Children;                                                 // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	void* ChildProperties;                                          // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int32_t                                            PropertySize;                                             // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int32_t                                            MinAlignment;                                             // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	char                                               pad_0060[0x50];                                           // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY

	static UClass* StaticClass()
	{
		static UClass* ptr = NULL;
		if (!ptr)
			ptr = FindClass(("Class CoreUObject.Struct"));

		return ptr;
	}

};
class UFunction : public UStruct
{
public:
	int32_t FunctionFlags; //0x0088
	int16_t RepOffset; //0x008C
	int8_t NumParms; //0x008E
	char pad_0x008F[0x1]; //0x008F
	int16_t ParmsSize; //0x0090
	int16_t ReturnValueOffset; //0x0092
	int16_t RPCId; //0x0094
	int16_t RPCResponseId; //0x0096
	class UProperty* FirstPropertyToInit; //0x0098
	UFunction* EventGraphFunction; //0x00A0
	int32_t EventGraphCallOffset; //0x00A8
	char pad_0x00AC[0x4]; //0x00AC
	void* Func; //0x00B0
};

namespace teleport
{
	UFunction* FindFunction(const char* memes)
	{
		return FindObject<UFunction>(memes);
	}
	bool K2_SetActorLocation(UObject* a, const struct FVector& NewLocation, bool bSweep, bool bTeleport, struct FHitResult* SweepHitResult)
	{
		static UFunction* fn = nullptr;
		if (!fn) fn = FindFunction(("Function Engine.Actor.K2_SetActorLocation"));

		// Function Engine.Actor.K2_SetActorLocation
		struct AActor_K2_SetActorLocation_Params
		{
			struct FVector                                     NewLocation;                                              // (Parm, IsPlainOldData)
			bool                                               bSweep;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
			struct FHitResult                                  SweepHitResult;                                           // (Parm, OutParm, IsPlainOldData)
			bool                                               bTeleport;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};

		AActor_K2_SetActorLocation_Params params;

		params.NewLocation = NewLocation;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;

		auto flags = fn->FunctionFlags;

		ProcessEvent(a, fn, &params);

		fn->FunctionFlags = flags;

		if (SweepHitResult != nullptr)
			*SweepHitResult = params.SweepHitResult;

		return params.ReturnValue;
	}
	void TeleportToMarker()
	{
		for (int li = 0; li < Readtard<DWORD>(Uworld + 0x140 + sizeof(PVOID)); ++li) {
			DWORD_PTR levels = Readtard<uintptr_t>(Uworld + 0x140);
			if (!levels) break;

			DWORD_PTR level = Readtard<uintptr_t>(levels + li * sizeof(PVOID));

			if (!level) std::cout << "Failed LEVEL\n";

			auto lc = Readtard<DWORD>(level + offset_aactors + sizeof(PVOID));

			DWORD_PTR AActorsLEVE = Readtard<uintptr_t>(level + offset_aactors);

			for (int ai = 0; ai < lc; ++ai)
			{
				UObject* Acotr = Readtard<UObject*>(AActorsLEVE + ai * sizeof(PVOID));
				//Get Name
				if (Name.find("AthenaPlayerMarker") != std::string::npos)
				{
					auto Rootcomp = Readtard<uint64_t>(Acotr + 0x130);
					auto Pos = Readtard<Vector3>(Rootcomp + 0x11C);
					//im not sure if the part works lol but have fun
					FHitResult xxxx;
					K2_SetActorLocation(Acotr, Pos, false, true, &xxxx);
				}
			}
		}
	}

}