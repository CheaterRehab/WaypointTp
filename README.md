# WaypointTp
Here Pasters

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
            if (Name.find("AthenaPlayerMarker") != std::string::npos)
            {
              auto Rootcomp = Readtard<uint64_t>(Acotr + 0x130);
              auto Pos = Readtard<Vector3>(Rootcomp + 0x11C);
            }
      }
}
