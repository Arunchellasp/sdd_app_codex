/* date = February 8th 2026 6:59 pm */

#ifndef APP_H
#define APP_H

#include "..//base//base_types.h"

typedef struct Window Window;


typedef struct App_State App_State;
struct App_State
{
    Arena *arena;
    Window *window;
    
    
};


global_variable App_State *app = {0};
global_variable Arena *thread_arena[2] = {0};

#endif //APP_H
