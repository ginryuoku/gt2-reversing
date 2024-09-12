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

class psxViewLoop : public ScreenViewLoop
{
    int field_0x04;
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
public:
    psxViewLoop();
    virtual ~psxViewLoop();
};

#endif
