#pragma once

namespace game
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	struct cmd_function_t
	{
		cmd_function_t* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void(__cdecl* function)();
		int flags;
	};

	struct CmdArgs
	{
		int nesting;
		int localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
	};

	enum netsrc_t
	{
		NS_CLIENT1 = 0x0,
		NS_CLIENT2 = 0x1,
		NS_CLIENT3 = 0x2,
		NS_CLIENT4 = 0x3,
		NS_MAXCLIENTS = 0x4,
		NS_SERVER = 0x4,
		NS_PACKET = 0x5,
		NS_INVALID_NETSRC = 0x6
	};

	struct msg_t
	{
		int overflowed;
		int readOnly;
		unsigned char* data;
		unsigned char* splitData;
		int maxsize;
		int cursize;
		int splitSize;
		int readcount;
		int bit;
		int lastEntityRef;
		netsrc_t targetLocalNetID;
	};

	static_assert(sizeof(msg_t) == 0x2C);

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};

	struct scr_entref_t
	{
		unsigned __int16 entnum;
		unsigned __int16 classnum;
	};

	typedef void(__cdecl* scr_call_t)(int entref);

	enum MeansOfDeath
	{
		MOD_UNKNOWN = 0,
		MOD_PISTOL_BULLET = 1,
		MOD_RIFLE_BULLET = 2,
		MOD_EXPLOSIVE_BULLET = 3,
		MOD_GRENADE = 4,
		MOD_GRENADE_SPLASH = 5,
		MOD_PROJECTILE = 6,
		MOD_PROJECTILE_SPLASH = 7,
		MOD_MELEE = 8,
		MOD_HEAD_SHOT = 9,
		MOD_CRUSH = 10,
		MOD_FALLING = 11,
		MOD_SUICIDE = 12,
		MOD_TRIGGER_HURT = 13,
		MOD_EXPLOSIVE = 14,
		MOD_IMPACT = 15,
		MOD_NUM = 16
	};

	enum scriptType_e
	{
		SCRIPT_NONE = 0,
		SCRIPT_OBJECT = 1,
		SCRIPT_STRING = 2,
		SCRIPT_ISTRING = 3,
		SCRIPT_VECTOR = 4,
		SCRIPT_FLOAT = 5,
		SCRIPT_INTEGER = 6,
		SCRIPT_END = 8,
		SCRIPT_FUNCTION = 9,
		SCRIPT_STRUCT = 19,
		SCRIPT_ARRAY = 22,
	};

	struct VariableStackBuffer
	{
		const char* pos;
		unsigned __int16 size;
		unsigned __int16 bufLen;
		unsigned __int16 localId;
		char time;
		char buf[1];
	};

	union VariableUnion
	{
		int intValue;
		float floatValue;
		unsigned int stringValue;
		const float* vectorValue;
		const char* codePosValue;
		unsigned int pointerValue;
		VariableStackBuffer* stackValue;
		unsigned int entityId;
		unsigned int uintValue;
	};

	struct VariableValue
	{
		VariableUnion u;
		scriptType_e type;
	};

	struct function_stack_t
	{
		const char* pos;
		unsigned int localId;
		unsigned int localVarCount;
		VariableValue* top;
		VariableValue* startTop;
	};

	struct function_frame_t
	{
		function_stack_t fs;
		int topType;
	};

	struct scrVmPub_t
	{
		unsigned int* localVars;
		VariableValue* maxstack;
		int function_count;
		function_frame_t* function_frame;
		VariableValue* top;
		/*bool debugCode;
		bool abort_on_error;
		bool terminal_error;
		bool block_execution;*/
		unsigned int inparamcount;
		unsigned int outparamcount;
		unsigned int breakpointOutparamcount;
		bool showError;
		function_frame_t function_frame_start[32];
		VariableValue stack[2048];
	};

	struct scr_classStruct_t
	{
		unsigned __int16 id;
		unsigned __int16 entArrayId;
		char charId;
		const char* name;
	};

	struct ObjectVariableChildren
	{
		unsigned __int16 firstChild;
		unsigned __int16 lastChild;
	};

	struct ObjectVariableValue_u_f
	{
		unsigned __int16 prev;
		unsigned __int16 next;
	};

	union ObjectVariableValue_u_o_u
	{
		unsigned __int16 size;
		unsigned __int16 entnum;
		unsigned __int16 nextEntId;
		unsigned __int16 self;
	};

	struct	ObjectVariableValue_u_o
	{
		unsigned __int16 refCount;
		ObjectVariableValue_u_o_u u;
	};

	union ObjectVariableValue_w
	{
		unsigned int type;
		unsigned int classnum;
		unsigned int notifyName;
		unsigned int waitTime;
		unsigned int parentLocalId;
	};

	struct ChildVariableValue_u_f
	{
		unsigned __int16 prev;
		unsigned __int16 next;
	};

	union ChildVariableValue_u
	{
		ChildVariableValue_u_f f;
		VariableUnion u;
	};

	struct ChildBucketMatchKeys_keys
	{
		unsigned __int16 name_hi;
		unsigned __int16 parentId;
	};

	union ChildBucketMatchKeys
	{
		ChildBucketMatchKeys_keys keys;
		unsigned int match;
	};

	struct	ChildVariableValue
	{
		ChildVariableValue_u u;
		unsigned __int16 next;
		char type;
		char name_lo;
		ChildBucketMatchKeys k;
		unsigned __int16 nextSibling;
		unsigned __int16 prevSibling;
	};

	union ObjectVariableValue_u
	{
		ObjectVariableValue_u_f f;
		ObjectVariableValue_u_o o;
	};

	struct ObjectVariableValue
	{
		ObjectVariableValue_u u;
		ObjectVariableValue_w w;
	};

	struct scrVarGlob_t
	{
		ObjectVariableValue objectVariableValue[36864];
		ObjectVariableChildren objectVariableChildren[36864];
		unsigned __int16 childVariableBucket[65536];
		ChildVariableValue childVariableValue[102400];
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		char color[4];
	};

	struct enum_limit
	{
		int stringCount;
		const char** strings;
	};

	struct int_limit
	{
		int min;
		int max;
	};

	struct float_limit
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		enum_limit enumeration;
		int_limit integer;
		float_limit value;
		float_limit vector;
	};

	struct dvar_t
	{
		const char* name;
		unsigned int flags;
		char type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		bool(__cdecl* domainFunc)(dvar_t*, DvarValue);
		dvar_t* hashNext;
	};

	struct playerState_s
	{
		char __pad0[0x4EC];
		unsigned int perks[0x2];
		unsigned int perkSlots[0x9];
		char __pad1[0x2DE8];
	};

	struct gclient_s
	{
		playerState_s ps;
		char __pad0[0x2CC];
		int flags;
	};

	struct gentity_s
	{
		int entnum;
		char __pad0[0x154];
		gclient_s* client;
		char __pad1[0x28];
		int flags;
		char __pad2[0xEC];
	};

	enum netadrtype_t
	{
		NA_BOT = 0x0,
		NA_BAD = 0x1,
		NA_LOOPBACK = 0x2,
		NA_BROADCAST = 0x3,
		NA_IP = 0x4
	};

	struct netadr_s
	{
		netadrtype_t type;
		unsigned char ip[4];
		unsigned __int16 port;
		unsigned char ipx[10];
		unsigned int addrHandleIndex;
	};

	static_assert(sizeof(netadr_s) == 24);

	struct netchan_t
	{
		int outgoingSequence;
		netsrc_t sock;
		int dropped;
		int incomingSequence;
		netadr_s remoteAddress;
		int qport;
		int fragmentSequence;
		int fragmentLength;
		unsigned char* fragmentBuffer;
		int fragmentBufferSize;
		int unsentFragments;
		int unsentFragmentStart;
		int unsentLength;
		unsigned char* unsentBuffer;
		int unsentBufferSize;
		unsigned char __pad0[0x5E0];
	};

	static_assert(sizeof(netchan_t) == 0x630);

	enum clientState_t
	{
		CS_FREE = 0,
		CS_ZOMBIE = 1,
		CS_RECONNECTING = 2,
		CS_CONNECTED = 3,
		CS_CLIENTLOADING = 4,
		CS_ACTIVE = 5
	};

	struct clientHeader_t
	{
		clientState_t state; // 0
		int sendAsActive; // 4
		int deltaMessage; // 8
		int rateDealyed; // 12
		int hasAckedBaselineData; // 16
		int hugeSnapshotSent; // 20
		netchan_t netchan; // 24
		vec3_t predictedOrigin;
		int predictedOriginServerTime;
		int migrationState;
		vec3_t predictedVehicleOrigin;
		int predictedVehicleServerTime;
	};

	static_assert(sizeof(clientHeader_t) == 0x66C);

	struct client_s
	{
		clientHeader_t header;
		const char* dropReason;
		char userinfo[1024];
		char __pad0[0x41242];
		unsigned __int16 scriptId; // 269490
		int bIsTestClient; // 269492
		int serverId; // 269496
		char __pad1[0x369DC];
	};

	static_assert(sizeof(client_s) == 0x78698);
}