#pragma once

namespace game
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];
	
	enum errorParm
	{
		ERR_FATAL = 0x0,
		ERR_DROP = 0x1,
		ERR_SERVERDISCONNECT = 0x2,
		ERR_DISCONNECT = 0x3,
		ERR_SCRIPT = 0x4,
		ERR_SCRIPT_DROP = 0x5,
		ERR_LOCALIZATION = 0x6,
		ERR_MAPLOADERRORSUMMARY = 0x7,
	};

	enum DvarSetSource : std::uint32_t
	{
		DVAR_SOURCE_INTERNAL = 0x0,
		DVAR_SOURCE_EXTERNAL = 0x1,
		DVAR_SOURCE_SCRIPT = 0x2,
		DVAR_SOURCE_UISCRIPT = 0x3,
		DVAR_SOURCE_SERVERCMD = 0x4,
		DVAR_SOURCE_NUM = 0x5,
	};

	enum DvarFlags : std::uint32_t
	{
		DVAR_NONE = 0,	// No flags
		DVAR_ARCHIVE = 1 << 0,	// Set to cause it to be saved to config_mp.cfg of the client
		DVAR_LATCH = 1 << 1,	// Will only change when C code next does a Dvar_Get(), so it can't be changed
		// without proper initialization. Modified will be set, even though the value hasn't changed yet
		DVAR_CHEAT = 1 << 2,	// Can not be changed if cheats are disabled
		DVAR_CODINFO = 1 << 3,	// On change, this is sent to all clients (if you are host)
		DVAR_SCRIPTINFO = 1 << 4,
		DVAR_TEMP = 1 << 5, // Best educated guess
		DVAR_SAVED = 1 << 6,
		DVAR_INTERNAL = 1 << 7, // Best educated guess
		DVAR_EXTERNAL = 1 << 8,	// Created by a set command
		DVAR_USERINFO = 1 << 9,	// Sent to server on connect or change
		DVAR_SERVERINFO = 1 << 10, // Sent in response to front end requests
		DVAR_INIT = 1 << 11, // Don't allow change from console at all
		DVAR_SYSTEMINFO = 1 << 12, // Will be duplicated on all clients
		DVAR_ROM = 1 << 13, // Display only, cannot be set by user at all
		DVAR_CHANGEABLE_RESET = 1 << 14,
		DVAR_AUTOEXEC = 1 << 15, // isLoadingAutoExecGlobalFlag is always false so it should be never set by the game
	};

	enum dvar_type : std::int8_t
	{
		boolean = 0,
		value = 1,
		vec2 = 2,
		vec3 = 3,
		vec4 = 4,
		integer = 5,
		enumeration = 6,
		string = 7,
		color = 8,
		rgb = 9 // Color without alpha
	};

	union dvar_value
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		char color[4];
	};

	struct $A37BA207B3DDD6345C554D4661813EDD
	{
		int stringCount;
		const char* const* strings;
	};

	struct $9CA192F9DB66A3CB7E01DE78A0DEA53D
	{
		int min;
		int max;
	};

	struct $251C2428A496074035CACA7AAF3D55BD
	{
		float min;
		float max;
	};

	union dvar_limits
	{
		$A37BA207B3DDD6345C554D4661813EDD enumeration;
		$9CA192F9DB66A3CB7E01DE78A0DEA53D integer;
		$251C2428A496074035CACA7AAF3D55BD value;
		$251C2428A496074035CACA7AAF3D55BD vector;
	};

	struct dvar_t
	{
		const char* name;
		unsigned int flags;
		dvar_type type;
		bool modified;
		dvar_value current;
		dvar_value latched;
		dvar_value reset;
		dvar_limits domain;
	};

	struct Glyph
	{
		unsigned short letter;
		char x0;
		char y0;
		char dx;
		char pixelWidth;
		char pixelHeight;
		float s0;
		float t0;
		float s1;
		float t1;
	};
	
	struct Font_s
	{
		const char* fontName;
		int pixelHeight;
		int glyphCount;
		void* material;
		void* glowMaterial;
		Glyph* glyphs;
	};

	struct ScreenPlacement
	{
		vec2_t scaleVirtualToReal;
		vec2_t scaleVirtualToFull;
		vec2_t scaleRealToVirtual;
		vec2_t realViewportPosition;
		vec2_t realViewportSize;
		vec2_t virtualViewableMin;
		vec2_t virtualViewableMax;
		vec2_t realViewableMin;
		vec2_t realViewableMax;
		vec2_t virtualAdjustableMin;
		vec2_t virtualAdjustableMax;
		vec2_t realAdjustableMin;
		vec2_t realAdjustableMax;
		vec2_t subScreenLeft;
	};

	enum keyNum_t
	{
		K_NONE = 0x0,
		K_FIRSTGAMEPADBUTTON_RANGE_1 = 0x1,
		K_BUTTON_A = 0x1,
		K_BUTTON_B = 0x2,
		K_BUTTON_X = 0x3,
		K_BUTTON_Y = 0x4,
		K_BUTTON_LSHLDR = 0x5,
		K_BUTTON_RSHLDR = 0x6,
		K_LASTGAMEPADBUTTON_RANGE_1 = 0x6,
		K_BS = 0x8,
		K_TAB = 0x9,
		K_ENTER = 0xD,
		K_FIRSTGAMEPADBUTTON_RANGE_2 = 0xE,
		K_BUTTON_START = 0xE,
		K_BUTTON_BACK = 0xF,
		K_BUTTON_LSTICK = 0x10,
		K_BUTTON_RSTICK = 0x11,
		K_BUTTON_LTRIG = 0x12,
		K_BUTTON_RTRIG = 0x13,
		K_DPAD_UP = 0x14,
		K_FIRSTDPAD = 0x14,
		K_DPAD_DOWN = 0x15,
		K_DPAD_LEFT = 0x16,
		K_DPAD_RIGHT = 0x17,
		K_BUTTON_LSTICK_ALTIMAGE2 = 0x10,
		K_BUTTON_RSTICK_ALTIMAGE2 = 0x11,
		K_BUTTON_LSTICK_ALTIMAGE = 0xBC,
		K_BUTTON_RSTICK_ALTIMAGE = 0xBD,
		K_LASTDPAD = 0x17,
		K_LASTGAMEPADBUTTON_RANGE_2 = 0x17,
		K_ESCAPE = 0x1B,
		K_FIRSTGAMEPADBUTTON_RANGE_3 = 0x1C,
		K_APAD_UP = 0x1C,
		K_FIRSTAPAD = 0x1C,
		K_APAD_DOWN = 0x1D,
		K_APAD_LEFT = 0x1E,
		K_APAD_RIGHT = 0x1F,
		K_LASTAPAD = 0x1F,
		K_LASTGAMEPADBUTTON_RANGE_3 = 0x1F,
		K_SPACE = 0x20,
		K_GRAVE = 0x60,
		K_TILDE = 0x7E,
		K_BACKSPACE = 0x7F,
		K_ASCII_FIRST = 0x80,
		K_ASCII_181 = 0x80,
		K_ASCII_191 = 0x81,
		K_ASCII_223 = 0x82,
		K_ASCII_224 = 0x83,
		K_ASCII_225 = 0x84,
		K_ASCII_228 = 0x85,
		K_ASCII_229 = 0x86,
		K_ASCII_230 = 0x87,
		K_ASCII_231 = 0x88,
		K_ASCII_232 = 0x89,
		K_ASCII_233 = 0x8A,
		K_ASCII_236 = 0x8B,
		K_ASCII_241 = 0x8C,
		K_ASCII_242 = 0x8D,
		K_ASCII_243 = 0x8E,
		K_ASCII_246 = 0x8F,
		K_ASCII_248 = 0x90,
		K_ASCII_249 = 0x91,
		K_ASCII_250 = 0x92,
		K_ASCII_252 = 0x93,
		K_END_ASCII_CHARS = 0x94,
		K_COMMAND = 0x96,
		K_CAPSLOCK = 0x97,
		K_POWER = 0x98,
		K_PAUSE = 0x99,
		K_UPARROW = 0x9A,
		K_DOWNARROW = 0x9B,
		K_LEFTARROW = 0x9C,
		K_RIGHTARROW = 0x9D,
		K_ALT = 0x9E,
		K_CTRL = 0x9F,
		K_SHIFT = 0xA0,
		K_INS = 0xA1,
		K_DEL = 0xA2,
		K_PGDN = 0xA3,
		K_PGUP = 0xA4,
		K_HOME = 0xA5,
		K_END = 0xA6,
		K_F1 = 0xA7,
		K_F2 = 0xA8,
		K_F3 = 0xA9,
		K_F4 = 0xAA,
		K_F5 = 0xAB,
		K_F6 = 0xAC,
		K_F7 = 0xAD,
		K_F8 = 0xAE,
		K_F9 = 0xAF,
		K_F10 = 0xB0,
		K_F11 = 0xB1,
		K_F12 = 0xB2,
		K_F13 = 0xB3,
		K_F14 = 0xB4,
		K_F15 = 0xB5,
		K_KP_HOME = 0xB6,
		K_KP_UPARROW = 0xB7,
		K_KP_PGUP = 0xB8,
		K_KP_LEFTARROW = 0xB9,
		K_KP_5 = 0xBA,
		K_KP_RIGHTARROW = 0xBB,
		K_KP_END = 0xBC,
		K_KP_DOWNARROW = 0xBD,
		K_KP_PGDN = 0xBE,
		K_KP_ENTER = 0xBF,
		K_KP_INS = 0xC0,
		K_KP_DEL = 0xC1,
		K_KP_SLASH = 0xC2,
		K_KP_MINUS = 0xC3,
		K_KP_PLUS = 0xC4,
		K_KP_NUMLOCK = 0xC5,
		K_KP_STAR = 0xC6,
		K_KP_EQUALS = 0xC7,
		K_MOUSE1 = 0xC8,
		K_MOUSE2 = 0xC9,
		K_MOUSE3 = 0xCA,
		K_MOUSE4 = 0xCB,
		K_MOUSE5 = 0xCC,
		K_MWHEELDOWN = 0xCD,
		K_MWHEELUP = 0xCE,
		K_AUX1 = 0xCF,
		K_AUX2 = 0xD0,
		K_AUX3 = 0xD1,
		K_AUX4 = 0xD2,
		K_AUX5 = 0xD3,
		K_AUX6 = 0xD4,
		K_AUX7 = 0xD5,
		K_AUX8 = 0xD6,
		K_AUX9 = 0xD7,
		K_AUX10 = 0xD8,
		K_AUX11 = 0xD9,
		K_AUX12 = 0xDA,
		K_AUX13 = 0xDB,
		K_AUX14 = 0xDC,
		K_AUX15 = 0xDD,
		K_AUX16 = 0xDE,
		K_LAST_KEY = 0xDF
	};

	struct KeyState
	{
		int down;
		int repeats;
		int binding;
	};
	
	struct PlayerKeyState
	{
		int overstrikeMode;
		int anyKeyDown;
		KeyState keys[256];
	};

	struct cmd_function_s
	{
		cmd_function_s* next;
		const char* name;
		void (__cdecl* function)();
	};

	struct CmdArgs
	{
		int nesting;
		int localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
	};

	enum XAssetType
	{
		ASSET_TYPE_PHYSPRESET = 0x0,
		ASSET_TYPE_PHYSCOLLMAP = 0x1,
		ASSET_TYPE_XANIMPARTS = 0x2,
		ASSET_TYPE_XMODEL_SURFS = 0x3,
		ASSET_TYPE_XMODEL = 0x4,
		ASSET_TYPE_MATERIAL = 0x5,
		ASSET_TYPE_PIXELSHADER = 0x6,
		ASSET_TYPE_VERTEXSHADER = 0x7,
		ASSET_TYPE_VERTEXDECL = 0x8,
		ASSET_TYPE_TECHNIQUE_SET = 0x9,
		ASSET_TYPE_IMAGE = 0xA,
		ASSET_TYPE_SOUND = 0xB,
		ASSET_TYPE_SOUND_CURVE = 0xC,
		ASSET_TYPE_LOADED_SOUND = 0xD,
		ASSET_TYPE_CLIPMAP_SP = 0xE,
		ASSET_TYPE_CLIPMAP_MP = 0xF,
		ASSET_TYPE_COMWORLD = 0x10,
		ASSET_TYPE_GAMEWORLD_SP = 0x11,
		ASSET_TYPE_GAMEWORLD_MP = 0x12,
		ASSET_TYPE_MAP_ENTS = 0x13,
		ASSET_TYPE_FXWORLD = 0x14,
		ASSET_TYPE_GFXWORLD = 0x15,
		ASSET_TYPE_LIGHT_DEF = 0x16,
		ASSET_TYPE_UI_MAP = 0x17,
		ASSET_TYPE_FONT = 0x18,
		ASSET_TYPE_MENULIST = 0x19,
		ASSET_TYPE_MENU = 0x1A,
		ASSET_TYPE_LOCALIZE_ENTRY = 0x1B,
		ASSET_TYPE_WEAPON = 0x1C,
		ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1D,
		ASSET_TYPE_FX = 0x1E,
		ASSET_TYPE_IMPACT_FX = 0x1F,
		ASSET_TYPE_AITYPE = 0x20,
		ASSET_TYPE_MPTYPE = 0x21,
		ASSET_TYPE_CHARACTER = 0x22,
		ASSET_TYPE_XMODELALIAS = 0x23,
		ASSET_TYPE_RAWFILE = 0x24,
		ASSET_TYPE_STRINGTABLE = 0x25,
		ASSET_TYPE_LEADERBOARD = 0x26,
		ASSET_TYPE_STRUCTURED_DATA_DEF = 0x27,
		ASSET_TYPE_TRACER = 0x28,
		ASSET_TYPE_VEHICLE = 0x29,
		ASSET_TYPE_ADDON_MAP_ENTS = 0x2A,
		ASSET_TYPE_COUNT = 0x2B,
		ASSET_TYPE_STRING = 0x2B,
		ASSET_TYPE_ASSETLIST = 0x2C,
		ASSET_TYPE_INVALID = -1,
	};

	struct Material 
	{
		const char *name;
	};

	struct StringTableCell
	{
		const char* string;
		int hash;
	};
	
	struct StringTable
	{
		const char* name;
		int columnCount;
		int rowCount;
		StringTableCell* values;
	};

	struct RawFile
	{
		const char* name;
		int compressedLen;
		int len;
		const char* buffer;
	};
	
	union XAssetHeader
	{
		void* data;
		Material* material;
		Font_s* font;
		StringTable* stringTable;
		RawFile* rawFile;
	};
	
	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};
	
	struct XAssetEntry
	{
		XAsset asset;
		char zoneIndex;
		volatile char inuseMask;
		bool printedMissingAsset;
		unsigned short nextHash;
		unsigned short nextOverride;
	};

	enum FsListBehavior_e
	{
		FS_LIST_PURE_ONLY = 0x0,
		FS_LIST_ALL = 0x1,
	};

	enum fsMode_t
	{
		FS_READ = 0x0,
		FS_WRITE = 0x1,
		FS_APPEND = 0x2,
		FS_APPEND_SYNC = 0x3,
	};

	struct scr_entref_t
	{
		unsigned __int16 entnum;
		unsigned __int16 classnum;
	};
	
	typedef void(*BuiltinFunction)();
	typedef void(*BuiltinMethod)(scr_entref_t);

	struct ScriptFunction
	{
		BuiltinFunction actionFunc;
		bool type;
		std::vector<std::string> aliases;
	};

	struct ScriptMethod
	{
		game::BuiltinMethod actionFunc;
		bool type;
		std::vector<std::string> aliases;
	};

	enum
	{
		VAR_UNDEFINED = 0x0,
		VAR_BEGIN_REF = 0x1,
		VAR_POINTER = 0x1,
		VAR_STRING = 0x2,
		VAR_ISTRING = 0x3,
		VAR_VECTOR = 0x4,
		VAR_END_REF = 0x5,
		VAR_FLOAT = 0x5,
		VAR_INTEGER = 0x6,
		VAR_CODEPOS = 0x7,
		VAR_PRECODEPOS = 0x8,
		VAR_FUNCTION = 0x9,
		VAR_BUILTIN_FUNCTION = 0xA,
		VAR_BUILTIN_METHOD = 0xB,
		VAR_STACK = 0xC,
		VAR_ANIMATION = 0xD,
		VAR_DEVELOPER_CODEPOS = 0xE,
		VAR_PRE_ANIMATION = 0xF,
		VAR_THREAD = 0x10,
		VAR_NOTIFY_THREAD = 0x11,
		VAR_TIME_THREAD = 0x12,
		VAR_CHILD_THREAD = 0x13,
		VAR_OBJECT = 0x14,
		VAR_DEAD_ENTITY = 0x15,
		VAR_ENTITY = 0x16,
		VAR_ARRAY = 0x17,
		VAR_DEAD_THREAD = 0x18,
		VAR_COUNT = 0x19,
		VAR_THREAD_LIST = 0x1A,
		VAR_ENDON_LIST = 0x1B,
	};

	struct clientLinkInfo_t
	{
		__int16 parentId;
		char tagName;
		char flags;
	};

	enum trType_t
	{
		TR_STATIONARY = 0x0,
		TR_INTERPOLATE = 0x1,
		TR_LINEAR = 0x2,
		TR_LINEAR_STOP = 0x3,
		TR_SINE = 0x4,
		TR_GRAVITY = 0x5,
		TR_LOW_GRAVITY = 0x6,
		TR_ACCELERATE = 0x7,
		TR_DECELERATE = 0x8,
		TR_PHYSICS = 0x9,
		TR_FIRST_RAGDOLL = 0xA,
		TR_RAGDOLL = 0xA,
		TR_RAGDOLL_GRAVITY = 0xB,
		TR_RAGDOLL_INTERPOLATE = 0xC,
		TR_LAST_RAGDOLL = 0xC,
		NUM_TRTYPES = 0xD,
	};

	struct trajectory_t
	{
		trType_t trType;
		int trTime;
		int trDuration;
		float trBase[3];
		float trDelta[3];
	};

	struct LerpEntityState
	{
		int eFlags;
		trajectory_t pos;
		trajectory_t apos;
		char pad0[0x24];
	};

	struct Bounds
	{
		float midPoint[3];
		float halfSize[3];
	};

	struct entityState_s
	{
		int number;
		int eType;
		LerpEntityState lerp;
		int time2;
		int otherEntityNum;
		int attackerEntityNum;
		int groundEntityNum;
		int loopSound;
		int surfType;
		union
		{
			int brushModel;
			int triggerModel;
			int item;
			int xmodel;
			int primaryLight;
		} index;
		int clientNum;
		int iHeadIcon;
		int iHeadIconTeam;
		int solid;
		unsigned int eventParm;
		int eventSequence;
		int events[4];
		unsigned int eventParms[4];
		unsigned __int16 weapon;
		int legsAnim;
		int torsoAnim;
		union
		{
			int eventParm2;
			int hintString;
			int fxId;
			int helicopterStage;
		} un1;
		union
		{
			int hintType;
			struct
			{
				unsigned __int16 vehicleXModel;
				char weaponModel;
			} __s1;
			int actorFlags;
		} un2;
		clientLinkInfo_t clientLinkInfo;
		unsigned int partBits[6];
		int clientMask[1];
	};

	struct EntHandle
	{
		unsigned __int16 number;
		unsigned __int16 infoIndex;
	};

	struct entityShared_t
	{
		char isLinked;
		char modelType;
		char svFlags;
		char isInUse;
		Bounds box;
		int contents;
		Bounds absBox;
		float currentOrigin[3];
		float currentAngles[3];
		EntHandle ownerNum;
		int eventTime;
	};

	enum hintType_t
	{
		HINT_NONE = 0x0,
		HINT_NOICON = 0x1,
		HINT_ACTIVATE = 0x2,
		HINT_HEALTH = 0x3,
		HINT_FRIENDLY = 0x4,
		FIRST_WEAPON_HINT = 0x5,
		LAST_WEAPON_HINT = 0x57C,
		HINT_NUM_HINTS = 0x57D,
	};

	enum team_t
	{
		TEAM_FREE = 0x0,
		TEAM_AXIS = 0x1,
		TEAM_ALLIES = 0x2,
		TEAM_SPECTATOR = 0x3,
		TEAM_NUM_TEAMS = 0x4,
	};

	struct clientState_s
	{
		int clientIndex;
		team_t team;
		int modelindex;
		int dualWielding;
		int riotShieldNext;
		int attachModelIndex[6];
		int attachTagIndex[6];
		char name[16];
		float maxSprintTimeMultiplier;
		int rank;
		int prestige;
		unsigned int perks[2];
		int diveState;
		int voiceConnectivityBits;
		unsigned int playerCardIcon;
		unsigned int playerCardTitle;
		unsigned int playerCardNameplate;
	};

	struct playerTeamState_t
	{
		int location;
	};

	enum usercmdButtonBits
	{
		CMD_BUTTON_ATTACK = 1 << 0,
		CMD_BUTTON_SPRINT = 1 << 1,
		CMD_BUTTON_MELEE = 1 << 2,
		CMD_BUTTON_ACTIVATE = 1 << 3,
		CMD_BUTTON_RELOAD = 1 << 4,
		CMD_BUTTON_USE_RELOAD = 1 << 5,
		CMD_BUTTON_LEAN_LEFT = 1 << 6,
		CMD_BUTTON_LEAN_RIGHT = 1 << 7,
		CMD_BUTTON_PRONE = 1 << 8,
		CMD_BUTTON_CROUCH = 1 << 9,
		CMD_BUTTON_UP = 1 << 10,
		CMD_BUTTON_ADS = 1 << 11,
		CMD_BUTTON_DOWN = 1 << 12,
		CMD_BUTTON_BREATH = 1 << 13,
		CMD_BUTTON_FRAG = 1 << 14,
		CMD_BUTTON_OFFHAND_SECONDARY = 1 << 15,
		CMD_BUTTON_THROW = 1 << 19,
	};

	struct usercmd_s
	{
		int serverTime;
		int buttons;
		int angles[3];
		unsigned __int16 weapon;
		unsigned __int16 primaryWeaponForAltMode;
		unsigned __int16 offHandIndex;
		char forwardmove;
		char rightmove;
		float meleeChargeYaw;
		char meleeChargeDist;
		char selectedLoc[2];
		char selectedLocAngle;
		char remoteControlAngles[2];
	};

	static_assert(sizeof(usercmd_s) == 0x28);

	enum clientConnected_t
	{
		CON_DISCONNECTED = 0x0,
		CON_CONNECTING = 0x1,
		CON_CONNECTED = 0x2
	};

	enum sessionState_t
	{
		SESS_STATE_PLAYING = 0x0,
		SESS_STATE_DEAD = 0x1,
		SESS_STATE_SPECTATOR = 0x2,
		SESS_STATE_INTERMISSION = 0x3
	};
	
	struct clientSession_t
	{
		sessionState_t sessionState;
		int forceSpectatorClient;
		int killCamEntity;
		int killCamLookAtEntity;
		int status_icon;
		int archiveTime;
		int score;
		int deaths;
		int kills;
		int assists;
		unsigned __int16 scriptPersId;
		clientConnected_t connected;
		usercmd_s cmd;
		usercmd_s oldcmd;
		int localClient;
		int predictItemPickup;
		char newnetname[16];
		int maxHealth;
		int enterTime;
		playerTeamState_t teamState;
		int voteCount;
		int teamVoteCount;
		float moveSpeedScaleMultiplier;
		int viewmodelIndex;
		int noSpectate;
		int teamInfo;
		clientState_s cs;
		int psOffsetTime;
		int hasRadar;
		int isRadarBlocked;
		int radarMode;
		int weaponHudIconOverrides[6];
		unsigned int unusableEntFlags[64];
		float spectateDefaultPos[3];
		float spectateDefaultAngles[3];
	};

	enum OffhandClass
	{
		OFFHAND_CLASS_NONE = 0x0,
		OFFHAND_CLASS_FRAG_GRENADE = 0x1,
		OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
		OFFHAND_CLASS_FLASH_GRENADE = 0x3,
		OFFHAND_CLASS_THROWINGKNIFE = 0x4,
		OFFHAND_CLASS_OTHER = 0x5,
		OFFHAND_CLASS_COUNT = 0x6,
	};

	enum ViewLockTypes
	{
		PLAYERVIEWLOCK_NONE = 0x0,
		PLAYERVIEWLOCK_FULL = 0x1,
		PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
		PLAYERVIEWLOCKCOUNT = 0x3,
	};

	struct SprintState
	{
		int sprintButtonUpRequired;
		int sprintDelay;
		int lastSprintStart;
		int lastSprintEnd;
		int sprintStartMaxLength;
	};

	struct MantleState
	{
		float yaw;
		int timer;
		int transIndex;
		int flags;
	};

	struct PlayerActiveWeaponState
	{
		int weapAnim;
		int weaponTime;
		int weaponDelay;
		int weaponRestrictKickTime;
		int weaponState;
		int weapHandFlags;
		unsigned int weaponShotCount;
	};

	struct PlayerEquippedWeaponState
	{
		bool usedBefore;
		bool dualWielding;
		char weaponModel;
		bool needsRechamber[2];
	};

	struct GlobalAmmo
	{
		int ammoType;
		int ammoCount;
	};

	struct ClipAmmo
	{
		int clipIndex;
		int ammoCount[2];
	};

	enum PlayerHandIndex
	{
		WEAPON_HAND_RIGHT = 0x0,
		WEAPON_HAND_LEFT = 0x1,
		NUM_WEAPON_HANDS = 0x2,
		WEAPON_HAND_DEFAULT = 0x0,
	};
	
	struct PlayerWeaponCommonState
	{
		int offHandIndex;
		OffhandClass offhandPrimary;
		OffhandClass offhandSecondary;
		unsigned int weapon;
		unsigned int primaryWeaponForAltMode;
		int weapFlags;
		float fWeaponPosFrac;
		float aimSpreadScale;
		int adsDelayTime;
		int spreadOverride;
		int spreadOverrideState;
		PlayerHandIndex lastWeaponHand;
		GlobalAmmo ammoNotInClip[15];
		ClipAmmo ammoInClip[15];
		int weapLockFlags;
		int weapLockedEntnum;
		float weapLockedPos[3];
		int weaponIdleTime;
	};

	enum ActionSlotType
	{
		ACTIONSLOTTYPE_DONOTHING = 0x0,
		ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
		ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
		ACTIONSLOTTYPE_NIGHTVISION = 0x3,
		ACTIONSLOTTYPECOUNT = 0x4,
	};

	struct ActionSlotParam_SpecifyWeapon
	{
		unsigned int index;
	};

	struct ActionSlotParam
	{
		ActionSlotParam_SpecifyWeapon specifyWeapon;
	};

	enum objectiveState_t
	{
		OBJST_EMPTY = 0x0,
		OBJST_ACTIVE = 0x1,
		OBJST_INVISIBLE = 0x2,
		OBJST_DONE = 0x3,
		OBJST_CURRENT = 0x4,
		OBJST_FAILED = 0x5,
		OBJST_NUMSTATES = 0x6,
	};

	struct objective_t
	{
		objectiveState_t state;
		float origin[3];
		int entNum;
		int teamNum;
		int icon;
	};

	enum he_type_t
	{
		HE_TYPE_FREE = 0x0,
		HE_TYPE_TEXT = 0x1,
		HE_TYPE_VALUE = 0x2,
		HE_TYPE_PLAYERNAME = 0x3,
		HE_TYPE_MAPNAME = 0x4,
		HE_TYPE_GAMETYPE = 0x5,
		HE_TYPE_MATERIAL = 0x6,
		HE_TYPE_TIMER_DOWN = 0x7,
		HE_TYPE_TIMER_UP = 0x8,
		HE_TYPE_TIMER_STATIC = 0x9,
		HE_TYPE_TENTHS_TIMER_DOWN = 0xA,
		HE_TYPE_TENTHS_TIMER_UP = 0xB,
		HE_TYPE_TENTHS_TIMER_STATIC = 0xC,
		HE_TYPE_CLOCK_DOWN = 0xD,
		HE_TYPE_CLOCK_UP = 0xE,
		HE_TYPE_WAYPOINT = 0xF,
		HE_TYPE_COUNT = 0x10,
	};

	struct hud_color
	{
		char r;
		char g;
		char b;
		char a;
	};

	union hudelem_color_t
	{
		hud_color __s0;
		int rgba;
	};

	struct hudelem_s
	{
		he_type_t type;
		float x;
		float y;
		float z;
		int targetEntNum;
		float fontScale;
		float fromFontScale;
		int fontScaleStartTime;
		int fontScaleTime;
		int font;
		int alignOrg;
		int alignScreen;
		hudelem_color_t color;
		hudelem_color_t fromColor;
		int fadeStartTime;
		int fadeTime;
		int label;
		int width;
		int height;
		int materialIndex;
		int fromWidth;
		int fromHeight;
		int scaleStartTime;
		int scaleTime;
		float fromX;
		float fromY;
		int fromAlignOrg;
		int fromAlignScreen;
		int moveStartTime;
		int moveTime;
		int time;
		int duration;
		float value;
		int text;
		float sort;
		hudelem_color_t glowColor;
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int soundID;
		int flags;
	};

	struct game_hudelem_s
	{
		hudelem_s elem;
		int clientNum;
		int team;
		int archived;
	};

	enum
	{
		PMF_PRONE = 1 << 0,
		PMF_DUCKED = 1 << 1,
		PMF_MANTLE = 1 << 2,
		PMF_LADDER = 1 << 3,
		PMF_SIGHT_AIMING = 1 << 4,
		PMF_BACKWARDS_RUN = 1 << 5,
		PMF_WALKING = 1 << 6,
		PMF_TIME_HARDLANDING = 1 << 7,
		PMF_TIME_KNOCKBACK = 1 << 8,
		PMF_PRONEMOVE_OVERRIDDEN = 1 << 9,
		PMF_RESPAWNED = 1 << 10,
		PMF_FROZEN = 1 << 11,
		PMF_LADDER_FALL = 1 << 12,
		PMF_JUMPING = 1 << 13,
		PMF_SPRINTING = 1 << 14,
		PMF_SHELLSHOCKED = 1 << 15,
		PMF_MELEE_CHARGE = 1 << 16,
		PMF_NO_SPRINT = 1 << 17,
		PMF_NO_JUMP = 1 << 18,
		PMF_REMOTE_CONTROLLING = 1 << 19,
		PMF_ANIM_SCRIPTED = 1 << 20,
		PMF_UNK1 = 1 << 21,
		PMF_DIVING = 1 << 22,
	};

	enum
	{
		POF_INVULNERABLE = 1 << 0,
		POF_REMOTE_EYES = 1 << 1,
		POF_LASER_ALTVIEW = 1 << 2,
		POF_THERMAL_VISION = 1 << 3,
		POF_THERMAL_VISION_OVERLAY_FOF = 1 << 4,
		POF_REMOTE_CAMERA_SOUNDS = 1 << 5,
		POF_ALT_SCENE_REAR_VIEW = 1 << 6,
		POF_ALT_SCENE_TAG_VIEW = 1 << 7,
		POF_SHIELD_ATTACHED_TO_WORLD_MODEL = 1 << 8,
		POF_DONT_LERP_VIEWANGLES = 1 << 9,
		POF_EMP_JAMMED = 1 << 10,
		POF_FOLLOW = 1 << 11,
		POF_PLAYER = 1 << 12,
		POF_SPEC_ALLOW_CYCLE = 1 << 13,
		POF_SPEC_ALLOW_FREELOOK = 1 << 14,
		POF_AC130 = 1 << 15,
		POF_COMPASS_PING = 1 << 16,
		POF_ADS_THIRD_PERSON_TOGGLE = 1 << 17,
	};

	enum pmtype_t
	{
		PM_NORMAL = 0x0,
		PM_NORMAL_LINKED = 0x1,
		PM_NOCLIP = 0x2,
		PM_UFO = 0x3,
		PM_MPVIEWER = 0x4,
		PM_SPECTATOR = 0x5,
		PM_INTERMISSION = 0x6,
		PM_LASTSTAND = 0x7,
		PM_DEAD = 0x8,
		PM_DEAD_LINKED = 0x9,
	};

	enum
	{
		EF_NONSOLID_BMODEL = 1 << 0,
		EF_TELEPORT_BIT = 1 << 1,
		EF_CROUCHING = 1 << 2,
		EF_PRONE = 1 << 3,
		EF_UNK1 = 1 << 4,
		EF_NODRAW = 1 << 5,
		EF_TIMED_OBJECT = 1 << 6,
		EF_VOTED = 1 << 7,
		EF_TALK = 1 << 8,
		EF_FIRING = 1 << 9,
		EF_TURRET_ACTIVE_PRONE = 1 << 10,
		EF_TURRET_ACTIVE_DUCK = 1 << 11,
		EF_LOCK_LIGHT_VIS = 1 << 12,
		EF_AIM_ASSIST = 1 << 13,
		EF_LOOP_RUMBLE = 1 << 14,
		EF_LASER_SIGHT = 1 << 15,
		EF_MANTLE = 1 << 16,
		EF_DEAD = 1 << 17,
		EF_ADS = 1 << 18,
		EF_NEW = 1 << 19,
		EF_VEHICLE_ACTIVE = 1 << 20,
		EF_JAMMING = 1 << 21,
		EF_COMPASS_PING = 1 << 22,
		EF_SOFT = 1 << 23,
	};

	enum
	{
		PLF_ANGLES_LOCKED = 1 << 0,
		PLF_USES_OFFSET = 1 << 1,
		PLF_WEAPONVIEW_ONLY = 1 << 2,
	};

	enum
	{
		PWF_USE_RELOAD = 1 << 0,
		PWF_USING_OFFHAND = 1 << 1,
		PWF_HOLDING_BREATH = 1 << 2,
		PWF_FRIENDLY_FIRE = 1 << 3,
		PWF_ENEMY_FIRE = 1 << 4,
		PWF_NO_ADS = 1 << 5,
		PWF_USING_NIGHTVISION = 1 << 6,
		PWF_DISABLE_WEAPONS = 1 << 7,
		PWF_TRIGGER_LEFT_FIRE = 1 << 8,
		PWF_TRIGGER_DOUBLE_FIRE = 1 << 9,
		PWF_USING_RECOILSCALE = 1 << 10,
		PWF_DISABLE_WEAPON_SWAPPING = 1 << 11,
		PWF_DISABLE_OFFHAND_WEAPONS = 1 << 12,
		PWF_SWITCHING_TO_RIOTSHIELD = 1 << 13,
		// IW5 flags backported
		PWF_DISABLE_WEAPON_PICKUP = 1 << 16
	};

	struct playerState_s
	{
		int commandTime;
		int pm_type;
		int pm_time;
		int pm_flags;
		int otherFlags;
		int linkFlags;
		int bobCycle;
		float origin[3];
		float velocity[3];
		int grenadeTimeLeft;
		int throwbackGrenadeOwner;
		int throwbackGrenadeTimeLeft;
		unsigned int throwbackWeaponIndex;
		int remoteEyesEnt;
		int remoteEyesTagname;
		int remoteControlEnt;
		int foliageSoundTime;
		int gravity;
		float leanf;
		int speed;
		float delta_angles[3];
		int groundEntityNum;
		float vLadderVec[3];
		int jumpTime;
		float jumpOriginZ;
		int legsTimer;
		int legsAnim;
		int torsoTimer;
		int torsoAnim;
		int legsAnimDuration;
		int torsoAnimDuration;
		int damageTimer;
		int damageDuration;
		int flinchYawAnim;
		int corpseIndex;
		int movementDir;
		int eFlags;
		int eventSequence;
		int events[4];
		unsigned int eventParms[4];
		int oldEventSequence;
		int unpredictableEventSequence;
		int unpredictableEventSequenceOld;
		int unpredictableEvents[4];
		unsigned int unpredictableEventParms[4];
		int clientNum; // 260
		int viewmodelIndex;
		float viewangles[3];
		int viewHeightTarget;
		float viewHeightCurrent;
		int viewHeightLerpTime;
		int viewHeightLerpTarget;
		int viewHeightLerpDown;
		float viewAngleClampBase[2];
		float viewAngleClampRange[2];
		int damageEvent;
		int damageYaw;
		int damagePitch;
		int damageCount;
		int damageFlags;
		int stats[4];
		float proneDirection;
		float proneDirectionPitch;
		float proneTorsoPitch;
		ViewLockTypes viewlocked;
		int viewlocked_entNum;
		float linkAngles[3];
		float linkWeaponAngles[3];
		int linkWeaponEnt;
		int loopSound;
		int cursorHint;
		int cursorHintString;
		int cursorHintEntIndex;
		int cursorHintDualWield;
		int iCompassPlayerInfo;
		int radarEnabled;
		int radarBlocked;
		int radarMode;
		int locationSelectionInfo;
		SprintState sprintState;
		float holdBreathScale;
		int holdBreathTimer;
		float moveSpeedScaleMultiplier;
		MantleState mantleState;
		PlayerActiveWeaponState weapState[2];
		unsigned int weaponsEquipped[15];
		PlayerEquippedWeaponState weapEquippedData[15];
		PlayerWeaponCommonState weapCommon;
		float meleeChargeYaw;
		int meleeChargeDist;
		int meleeChargeTime;
		unsigned int perks[2];
		unsigned int perkSlots[8];
		ActionSlotType actionSlotType[4];
		ActionSlotParam actionSlotParam[4];
		int weaponHudIconOverrides[6];
		int animScriptedType;
		int shellshockIndex;
		int shellshockTime;
		int shellshockDuration;
		float dofNearStart;
		float dofNearEnd;
		float dofFarStart;
		float dofFarEnd;
		float dofNearBlur;
		float dofFarBlur;
		float dofViewmodelStart;
		float dofViewmodelEnd;
		objective_t objective[32];
		int deltaTime;
		int killCamEntity;
		int killCamLookAtEntity;
		int killCamClientNum;
		struct
		{
			hudelem_s current[31];
			hudelem_s archival[31];
		} hud;
		unsigned int partBits[6];
		int recoilScale;
		int diveDirection;
		int stunTime;
	};

	static_assert(sizeof(playerState_s) == 0x311C);
	
	struct gclient_s
	{
		playerState_s ps;
		clientSession_t sess;
		int flags; // 13204
		int spectatorClient;
		int lastCmdTime;
		int buttons;
		int oldbuttons; // 13220
		int latched_buttons; // 13224
		int buttonsSinceLastFrame; // 13228
		unsigned char __pad3[324]; // 13232
		int visionDuration[5];
		char visionName[5][64];
		int lastStand;
		int lastStandTime;
		int hudElemLastAssignedSoundID;
		float lockedTargetOffset[3];
		unsigned __int16 attachShieldTagName;
		hintType_t hintForcedType;
		int hintForcedString;
	};
	
	struct gentity_s
	{
		entityState_s s;
		entityShared_t r;
		gclient_s* client;
	};
}
