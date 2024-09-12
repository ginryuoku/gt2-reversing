#ifndef SCREENVIEWLOOP_H
#define SCREENVIEWLOOP_H

class ScreenViewLoop
{
    virtual int pad() = 0; // vtable pad, 4 bytes is just empty?
public:
    ScreenViewLoop() {}
    virtual ~ScreenViewLoop();
    virtual void loop();
    virtual void begin();
    virtual bool is_active() 
    { 
        return true; 
    }

    virtual void update();
    virtual void end();
};

#endif
