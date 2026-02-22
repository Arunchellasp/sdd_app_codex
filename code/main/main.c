#include "..\\project\\app_inc.h"
#include "..\\project\\app_inc.c"


int main(void)
{
    app_init();
    
    // NOTE(ARUN): Main loop - keep running until window is closed
    while(!window_should_close())
    {
        app_frame();
    }
    
    // NOTE(ARUN): Cleanup
    window_close();
    
    return 0;
}
