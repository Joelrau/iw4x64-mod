#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	/***************************************************************
	 * Functions
	 **************************************************************/

	WEAK symbol<void(errorParm code, const char* message, ...)> Com_Error{ 0x1401F8FD0 };

	WEAK symbol<void()> Com_Quit_f{ 0x1401FB240 };

	WEAK symbol<dvar_t*(const char* name, bool value, unsigned int flags, const char* desc)> Dvar_RegisterBool { 0x140287CE0 };
	WEAK symbol<dvar_t*(const char* name, float value, float min, float max, unsigned int flags, const char* desc)> Dvar_RegisterFloat { 0x1402880C0 };
	WEAK symbol<dvar_t*(const char* name, int value, int min, int max, unsigned int flags, const char* desc)> Dvar_RegisterInt { 0x1402881F0 };
	WEAK symbol<dvar_t*(const char* name, const char* value, unsigned int flags, const char* desc)> Dvar_RegisterString { 0x140288590 };
	WEAK symbol<dvar_t*(const char* name, const char** valueList, int defaultIndex, unsigned int flags, const char* desc)> Dvar_RegisterEnum { 0x140287FC0 };
	WEAK symbol<dvar_t*(const char* name)> Dvar_FindVar { 0x140287170 };

	WEAK symbol<bool()> CL_IsCgameInitialized { 0x1400F1620 };
	WEAK symbol<void(int, const char*, int)> LiveStorage_PlayerDataSetIntByName { 0x1401FE290 };
	WEAK symbol<void(const char *const *navStrings, int navStringCount, const char *value, void *buffer, char *modifiedFlags)> LiveStorage_DataSetInternalString { 0x1401FCB80 };
	WEAK symbol<void(int)> LiveStorage_WriteStats { 0x140200060 };
	WEAK symbol<char*(int localClientNum)> LiveStorage_GetBufferData { 0x1401FD1C0 };

	WEAK symbol<XAssetHeader(XAssetType type, const char* name)> DB_FindXAssetHeader { 0x140129220 };

	WEAK symbol<Font_s*(const char* font)> R_RegisterFont { 0x1400F9D20 };
	WEAK symbol<void*(const char* material, int type)> Material_RegisterHandle { 0x140019470 };

	WEAK symbol<ScreenPlacement*()> ScrPlace_GetViewPlacement{ 0x1400EF3A0 };

	WEAK symbol<void(float x, float y, float width, float height, float s0, float t0, float s1,
		float t1, float* color, void* material)> R_AddCmdDrawStretchPic{0x14001ACE0};

	WEAK symbol<void(const char *text, int maxChars, Font_s *font, float x, float y, float xScale,
		float yScale, float rotation, const float *color, int style)> R_AddCmdDrawText { 0x14001B260 };

	WEAK symbol<void(const char *text, int maxChars, Font_s *font, float x, float y, float xScale,
		float yScale, float rotation, const float *color, int style, int cursor, char type)> AddBaseDrawTextCmd { 0x14001B0B0 };

	WEAK symbol<int(const char* text, int maxLength, Font_s* font)> R_TextWidth { 0x140019870 };

	WEAK symbol<const char*(dvar_t* dvar, dvar_value value)> Dvar_ValueToString{ 0x14028A690 };

	WEAK symbol<void*()> Com_Frame_Try_Block_Function { 0x1401F9930 };
	WEAK symbol<void()> G_Glass_Update { 0x14016D930 };
	WEAK symbol<bool()> Sys_IsDatabaseReady2 { 0x14020D9A0 };
	WEAK symbol<void(int localClientNum, const char* cmd)> Cbuf_AddText { 0x1401EC4A0 };

	WEAK symbol<void(const char* cmdName, void (), cmd_function_s* allocedCmd)> Cmd_AddCommandInternal { 0x1401EC990 };
	WEAK symbol<void(int localClientNum, int controllerIndex, const char* text)> Cmd_ExecuteSingleCommand { 0x1401ECD60 };
	WEAK symbol<void(const char* text_in)> Com_TokenizeString{0x1401ED560 };
	WEAK symbol<void()> Com_EndTokenizeString{0x1401ECC10 };
	WEAK symbol<const char*(int index)> Cmd_Argv{0x140035D60 };
	WEAK symbol<void(const char* dvarName, const char* buffer)> Dvar_SetCommand { 0x1402892A0 };
	
	/***************************************************************
	 * Variables
	 **************************************************************/
	
	WEAK symbol<int> KeyCatchers { 0x140719AF0 };
	WEAK symbol<PlayerKeyState> playerKeys { 0x14070DB4C };
	WEAK symbol<int> dvarCount { 0x1466D3268 };
	WEAK symbol<dvar_t*> sortedDvars { 0x1466D3270 };
	WEAK symbol<cmd_function_s*> cmd_functions { 0x141C17968 };
	WEAK symbol<CmdArgs> cmd_args{0x141C17810};
	WEAK symbol<CmdArgs> sv_cmd_args{0x141C178C0};

	WEAK symbol<XAssetEntry> EntryPool { 0x141567FD0 };
	WEAK symbol<unsigned short> db_hashTable { 0x141551E90 };
}
