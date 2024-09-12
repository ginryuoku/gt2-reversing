// thanks to Nenkai for the solve!
#include "common.h"
#include "psxViewLoop.h"

extern int* gt2_main_task071000;

psxViewLoop::psxViewLoop()
{
    psxViewLoopCallbackParams* params = &this->callbackParams;
	params->callback = &gt2_main_task071000; // callback;
    params->args = 0;
    
	this->field_0x18 = 1;
	this->field_0x1C = 3;
    this->field_0x1D = 0;
	this->field_0x1E = 1;
	this->field_0x21 = 0;
	this->field_0x22 = 0;
	this->field_0x24 = 0;
};