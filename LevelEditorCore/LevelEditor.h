#pragma once
#include "../Array/Array.h"
#include "../Stack/Stack.h

//////////////////////////////////////////////////////////////////////////
///////////////////////TYPEDEFS///////////////////////////////////////////
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

typedef size_t memory_index;

typedef float real32;
typedef double real64;

typedef int8 s8;
typedef int8 s08;
typedef int16 s16;
typedef int32 s32;
typedef int64 s64;
typedef bool32 b32;

typedef uint8 u8;
typedef uint8 u08;
typedef uint16 u16;
typedef uint32 u32;
typedef uint64 u64;

typedef real32 r32;
typedef real64 r64;

typedef uint8* MemoryAdress;

///////////////////////////////////////////////////////////////////////////
/////////////////////Pre-Processor Macros//////////////////////////////////

#define PointerToU32(Pointer) ((u32)(memory_index)(Pointer))

#define Bytes(Value)     (Value)
#define Kilobytes(Value) (Bytes(Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)


#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define AlignPow2(Value, Alignment) ((Value + ((Alignment) - 1)) & ~((Alignment) - 1))
#define Align4(Value) ((Value + 3) & ~3)
#define Align8(Value) ((Value + 7) & ~7)
#define Align16(Value) ((Value + 15) & ~15)

#ifndef DEBUG
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}
#else
#define Assert(Expression) if(!(Expression)) \
         {std::cerr<<"Error: "<<__FILE__<<"->"<<__LINE__<<" "<<"\n";}
#endif

//
typedef struct COORDINATES {

	int x, y;

} Point,Vector2D;
