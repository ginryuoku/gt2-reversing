#ifndef SCREENVIEWLOOP_H
#define SCREENVIEWLOOP_H

class ScreenViewLoop
{
//    virtual int pad() = 0; // vtable pad, 4 bytes is just empty?
public:
    ScreenViewLoop() {}
    void func0();
    virtual ~ScreenViewLoop();
    virtual void loop();
    virtual void begin();
    virtual int is_active() 
    { 
        // should be a bool but creates match failures
        return 1; 
    }

    virtual void update();
    virtual void end();
};

#endif
