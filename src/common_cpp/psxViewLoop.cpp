// thanks to Nenkai for the solve!
#include "common.h"
#include "psxViewLoop.h"

extern int* gt2_main_task071000;
extern "C" void* gt2_main_task020(void**, psxViewLoopCallbackParams*);
extern "C" void gt2_main_sharedovr_func_14_0();                 /* extern */
extern "C" s32 gt2_main_sharedovr_funcC0();                    /* extern */
extern "C" void gt2_main_sharedovr_funcC1();                      /* extern */
extern "C" void gt2_main_sharedovr_funcC2();                      /* extern */
extern "C" s32 gt2_main_task020_callback_checker(s32);         /* extern */
extern "C" void gt2_main_task0702();                              /* extern */
extern "C" void gt2_main_task07200(s32);    
extern "C" void gt2_main_race_func13_0(void*, psxViewLoopCallbackParams*);  
extern u8 D_800959AC;
extern psxViewLoop* D_800959B0; // gt2_previous_view_loop
extern void* D_801F0688;
extern D_801F0C70_struct D_801F0C70;

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

psxViewLoop::~psxViewLoop() {
}

void psxViewLoop::begin() {
    u8 var_a1;
    psxViewLoop* currentLoop = D_800959B0;
    D_800959B0 = this;
    this->previousLoop = currentLoop;
    var_a1 = D_800959AC < this->field_0x1E ? D_800959AC : 0;
    this->field_0x1C = 3;
    this->field_0x1D = var_a1;
    this->field_0x1F = 0;
    this->field_0x20 = 0;
    gt2_main_task020(&D_801F0688, &this->callbackParams);
    this->field_0x38.field_0x04 = 0;
}

int psxViewLoop::is_active() 
{
    int var_s1 = 0;
    D_801F0C70_struct* temp_v0 = &D_801F0C70;
    D_801F0C70_struct_sub* sub_struct = &temp_v0->struct_0x4A;
    
    if (sub_struct->field_0x00 == 0 && (sub_struct->field_0x02 | (sub_struct->field_0x03 << 8)) == 0xEF79) {
        var_s1 = 1;
    }
    
    gt2_main_sharedovr_func_14_0();
    this->method_0x20();
    this->method_0x28();
    if (!var_s1)
        var_s1 = this->method_0x24();
    
    this->method_0x2C();
    this->method_0x30();
    return var_s1;
}

void psxViewLoop::update() 
{
    this->field_0x64 = gt2_main_sharedovr_funcC0();
    if (this->field_0x21 == 0)
        gt2_main_task0702();
    
    s32 var_v1 = this->field_0x1D + 1;
    if (var_v1 >= this->field_0x1E) {
        var_v1 = 0;
    }

    u8 field_0x18 = this->field_0x18;
    int temp_a0 = this->field_0x1C;
    this->field_0x1D = (u8)var_v1;
    this->field_0x20 = field_0x18;
    
    if (temp_a0 != 0) {
        u8 temp_v0 = temp_a0 - 1;
        this->field_0x1C = temp_v0;
        if ((temp_v0 & 0xFF) == 0) {
            this->field_0x1F = 1;
        }
    }
    
    gt2_main_task07200(this->field_0x18);
    
    if (this->field_0x21 != 0)
        gt2_main_sharedovr_funcC1();
    
    s32 temp_s1 = gt2_main_task020_callback_checker(0);
    if (this->field_0x20 != 0) {
        this->field_0x20 = 0;
        this->method_0x38();
        
        if (this->field_0x1F != 0) {
            this->field_0x1F = 0;
            this->method_0x3C();
        }
    }
    
    gt2_main_task020_callback_checker(temp_s1);
    if (this->field_0x22 != 0)
        gt2_main_sharedovr_funcC2();
    
    this->field_0x68 = gt2_main_sharedovr_funcC0();
}

void psxViewLoop::end() {
    gt2_main_race_func13_0(&D_801F0688, &this->callbackParams);
    gt2_main_task0702();
    D_800959AC = this->field_0x1D;
    D_800959B0 = this->previousLoop;
}

extern "C" void gt2_main_dma_mdec_func0();                        /* extern */
extern "C" void gt2_main_sharedovr_func500(psxViewLoopStruct0x38*);                  /* extern */
extern "C" void gt2_main_sharedovr_func501(psxViewLoopStruct0x38*);                  /* extern */
extern "C" void gt2_main_sharedovr_func502(psxViewLoopStruct0x38*);                  /* extern */
extern "C" void gt2_main_sharedovr_func503(psxViewLoopStruct0x58*);                  /* extern */
extern "C" void gt2_main_sharedovr_func504(psxViewLoopStruct0x38*, psxViewLoopStruct0x26*);             /* extern */

void psxViewLoop::method_0x20(void) {

}


s32 psxViewLoop::method_0x24() {
    return 1;
}

void psxViewLoop::method_0x28() 
{
    psxViewLoopStruct0x38* temp_s0 = &this->field_0x38;
    gt2_main_sharedovr_func500(temp_s0);
    gt2_main_sharedovr_func501(temp_s0);
    gt2_main_sharedovr_func502(temp_s0);
    gt2_main_sharedovr_func503(&this->field_0x58);
    gt2_main_sharedovr_func504(temp_s0, &this->field_0x26);
    gt2_main_dma_mdec_func0();
}

void psxViewLoop::method_0x2C() {
	
}

extern "C" void gt2_main_sharedovr_func10(psxViewLoopStruct0x38*);                   /* extern */

void psxViewLoop::method_0x30() {
    gt2_main_sharedovr_func10(&this->field_0x38);
}

extern "C" void gt2_main_sharedovr_funcB0(s16, s16);              /* extern */
extern "C" void gt2_main_sharedovr_funcB1(s16, s16);              /* extern */
extern "C" void gt2_main_task07201(u8);                           /* extern */
extern "C" void gt2_main_task0c_gpu_reg1_op(u8);                  /* extern */

void psxViewLoop::method_0x34() 
{
    this->method_0x28();
    this->method_0x2C();
    this->method_0x30();
    this->update();
}

void psxViewLoop::method_0x38() 
{
    this->field_0x20 = 0;
}

void psxViewLoop::method_0x3C() 
{
    this->field_0x22 = (s8)((this->field_0x23 >> 2) & 1);
    gt2_main_task07201(this->field_0x23);
    gt2_main_sharedovr_funcB0(this->field_0x2E, this->field_0x32);
    gt2_main_sharedovr_funcB1(this->field_0x30, this->field_0x34);
    gt2_main_task0c_gpu_reg1_op(this->field_0x24);
}

extern s32 D_801F0684;

void psxViewLoop::method_0x40() {

    int current_val = D_801F0684;
    int temp_v1 = this->field_0x20;
    int temp_s1 = this->field_0x1F;
    if ((temp_v1 != 0) && (current_val >= temp_v1))
    {
        this->field_0x20 = 0U;
        this->method_0x38();
        
        if (temp_s1 != 0) {
            this->field_0x1F = 0;
            this->method_0x3C();
        }
    }
}
