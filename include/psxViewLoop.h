#include "ScreenViewLoop.h"
#ifndef PSX_VIEW_LOOP_H
#define PSX_VIEW_LOOP_H

typedef struct
{
    int field_0x00;
    int field_0x04;
    void* callback;
    void* args;
} psxViewLoopCallbackParams;

typedef struct
{
    char field_0x00;
    char field_0x01;
    char field_0x02;
    char field_0x03;
    char field_0x04;
    char field_0x05;
    char field_0x06;
    char field_0x07;
    char field_0x08;
} D_801F0C70_struct_sub;

typedef struct
{
    char pad[0x4A];
    D_801F0C70_struct_sub struct_0x4A;
} D_801F0C70_struct;

typedef struct
{
    u16 field_0x00;
    u16 field_0x02;
    u16 field_0x04;
    u16 field_0x06;
} psxViewLoopStruct0x26;

typedef struct
{
    int field_0x00;
    int field_0x04;
    int field_0x08;
    int field_0x0C;
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1C;
} psxViewLoopStruct0x38;

typedef struct
{
    int field_0x00;
    int field_0x04;
    int field_0x08;
} psxViewLoopStruct0x58;

class psxViewLoop : public ScreenViewLoop
{
	psxViewLoop* previousLoop;
	psxViewLoopCallbackParams callbackParams;
	int field_0x18;
    char field_0x1C;
    char field_0x1D;
	char field_0x1E;
    char field_0x1F;
	char field_0x20;
	char field_0x21;
	char field_0x22;
	char field_0x23;
	char field_0x24;
    char field_0x25;
    psxViewLoopStruct0x26 field_0x26;
    u16 field_0x2E;
    u16 field_0x30;
    u16 field_0x32;
    u16 field_0x34;
    u16 field_0x36;
    psxViewLoopStruct0x38 field_0x38;
    psxViewLoopStruct0x58 field_0x58;
    int field_0x64;
    int field_0x68;
public:
    psxViewLoop();
    virtual ~psxViewLoop();

	virtual void loop();
    virtual void begin();
    virtual int is_active();
    virtual void update();
    virtual void end();
    virtual void method_0x20();
    virtual int method_0x24();
    virtual void method_0x28();
    virtual void method_0x2C();
    virtual void method_0x30();
    virtual void method_0x34();
    virtual void method_0x38();
    virtual void method_0x3C();
    virtual void method_0x40();
};

#endif
