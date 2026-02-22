/* date = February 9th 2026 10:42 am */

#ifndef WINDOW_H
#define WINDOW_H


typedef struct Window Window;
struct Window
{
    u16 width;
    u16 hight;
    char *titel;
    u8 fps;
    
    // Position
    i16 x;
    i16 y;
    
    // State flags
    b8 fullscreen;
    b8 resizable;
    b8 vsync;
    b8 minimized;
    b8 maximized;
    b8 hidden;
    b8 borderless;
    b8 always_on_top;
};

internal void
window_init(Window *window, u16 width, u16 hight, char *titel)
{
    window->width = width;
    window->hight = hight;
    window->titel = titel;
    window->fps = 60;
    
    // Default position (centered)
    window->x = -1;
    window->y = -1;
    
    // Default state
    window->fullscreen = 1;
    window->resizable = 1;
    window->vsync = 1;
    window->minimized = 0;
    window->maximized = 0;
    window->hidden = 0;
    window->borderless = 0;
    window->always_on_top = 0;
    
    // Set window flags before init
    u32 flags = 0;
    if(window->resizable) flags |= FLAG_WINDOW_RESIZABLE;
    if(window->vsync) flags |= FLAG_VSYNC_HINT;
    if(window->borderless) flags |= FLAG_WINDOW_UNDECORATED;
    if(window->always_on_top) flags |= FLAG_WINDOW_TOPMOST;
    if(window->hidden) flags |= FLAG_WINDOW_HIDDEN;
    
    SetConfigFlags(flags);
    InitWindow(window->width, window->hight, window->titel);
    
    // Set position if specified
    if(window->x >= 0 && window->y >= 0)
    {
        SetWindowPosition(window->x, window->y);
    }
    
    SetTargetFPS(window->fps);
}

internal void
window_set_fps(Window *window, u8 fps)
{
    window->fps = fps;
    SetTargetFPS(window->fps);
}

internal void
window_set_position(Window *window, i16 x, i16 y)
{
    window->x = x;
    window->y = y;
    SetWindowPosition(x, y);
}

internal void
window_set_size(Window *window, u16 width, u16 hight)
{
    window->width = width;
    window->hight = hight;
    SetWindowSize(width, hight);
}

internal void
window_toggle_fullscreen(Window *window)
{
    window->fullscreen = !window->fullscreen;
    ToggleFullscreen();
}

internal void
window_set_fullscreen(Window *window, b8 fullscreen)
{
    if(window->fullscreen != fullscreen)
    {
        window->fullscreen = fullscreen;
        ToggleFullscreen();
    }
}

internal void
window_minimize(Window *window)
{
    window->minimized = 1;
    MinimizeWindow();
}

internal void
window_maximize(Window *window)
{
    window->maximized = 1;
    MaximizeWindow();
}

internal void
window_restore(Window *window)
{
    window->minimized = 0;
    window->maximized = 0;
    RestoreWindow();
}

internal void
window_set_title(Window *window, char *titel)
{
    window->titel = titel;
    SetWindowTitle(titel);
}

internal void
window_set_icon(char *icon_path)
{
    Image icon = LoadImage(icon_path);
    SetWindowIcon(icon);
    UnloadImage(icon);
}

internal b8
window_should_close(void)
{
    return WindowShouldClose();
}

internal void
window_update_state(Window *window)
{
    
    
    // Update state based on actual window state
    window->minimized = IsWindowMinimized();
    window->maximized = IsWindowMaximized();
    window->hidden = IsWindowHidden();
    window->fullscreen = IsWindowFullscreen();
    
    // Update size if resized
    if(IsWindowResized())
    {
        window->width = GetScreenWidth();
        window->hight = GetScreenHeight();
    }
}

internal void
window_close(void)
{
    CloseWindow();
}

#endif //WINDOW_H
