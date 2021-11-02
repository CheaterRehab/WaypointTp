//this is stolen from https://github.com/owsiak1337/fortnite-cheat-internal-season-8/blob/b84d3340c4f1a10fd3bc32b6ffc6a4381f42e51c/dllmain.cpp~RF1160ac5.TMP
//im not sure if this works lol but have fun
bool K2_SetActorLocation(UObject* a, const struct FVector& NewLocation, bool bSweep, bool bTeleport, struct FHitResult* SweepHitResult) 
{
	static UFunction* fn = nullptr;
	if (!fn) fn = FindFunction(E("Function Engine.Actor.K2_SetActorLocation"));

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
			uint64_t Acotr = Readtard<uint64_t>(AActorsLEVE + ai * sizeof(PVOID));
			//Get Name
			if (Name.find("AthenaPlayerMarker") != std::string::npos)
			{
				auto Rootcomp = Readtard<uint64_t>(Acotr + 0x130);
				auto Pos = Readtard<Vector3>(Rootcomp + 0x11C);
				//im not sure if the part works lol but have fun
				FHitResult xxxx;
				Teleport(actor, Pos, false, true, &xxxx);
			}
		}
	}
}
