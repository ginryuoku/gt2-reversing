#include "common.h"
#include "ScreenViewLoop.h"

void ScreenViewLoop::loop()
{
    this->begin();

    while (this->is_active())
    {        
        this->update();   
    }

    this->end();
}
