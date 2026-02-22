////////////////////////////////
// NOTE(ARUN): UI Helper Types
////////////////////////////////

typedef struct UI_Button_Result UI_Button_Result;
struct UI_Button_Result
{
    b8 clicked;
    b8 hovered;
    b8 pressed;
};

////////////////////////////////
// NOTE(ARUN): UI Functions
////////////////////////////////

internal UI_Button_Result
ui_button(Rectangle rect, char *label, Color base_color)
{
    UI_Button_Result result = {0};
    
    Vector2 mouse_pos = GetMousePosition();
    result.hovered = CheckCollisionPointRec(mouse_pos, rect);
    result.pressed = result.hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    result.clicked = result.hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    
    // NOTE(ARUN): Color transitions based on state
    Color color = base_color;
    if(result.pressed)
    {
        color = (Color){
            (u8)(base_color.r * 0.7f),
            (u8)(base_color.g * 0.7f),
            (u8)(base_color.b * 0.7f),
            base_color.a
        };
    }
    else if(result.hovered)
    {
        color = (Color){
            (u8)(base_color.r * 0.85f),
            (u8)(base_color.g * 0.85f),
            (u8)(base_color.b * 0.85f),
            base_color.a
        };
    }
    
    // NOTE(ARUN): Draw button
    DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 2, result.hovered ? WHITE : (Color){200, 200, 200, 255});
    
    // NOTE(ARUN): Draw label centered
    i32 text_width = MeasureText(label, 20);
    i32 text_x = (i32)(rect.x + (rect.width - text_width) / 2);
    i32 text_y = (i32)(rect.y + (rect.height - 20) / 2);
    DrawText(label, text_x, text_y, 20, WHITE);
    
    return result;
}

////////////////////////////////
// NOTE(ARUN): App Functions
////////////////////////////////

internal void 
app_init()
{
    
    // NOTE(ARUN):@thread_arena_init
	{
		for(u32 it = 0; it < ArrayCount(thread_arena); it += 1)
		{
			thread_arena[it] = arena_alloc(KB(1));
		}
	}
    
    // NOTE(ARUN): @arena_init
	Arena *arena = arena_alloc(GB(2));
    app = push_array(arena, App_State, 1);
	app->arena = arena;
    
    // NOTE(ARUN): @window_init
    app->window = push_array(arena, Window, 1);
    window_init(app->window, 800, 450, "RAD-Style Window with Button");
    
}

internal void
app_frame()
{
    // NOTE(ARUN): Update window state
    window_update_state(app->window);
    
    // NOTE(ARUN): Begin drawing
    BeginDrawing();
    ClearBackground((Color){30, 30, 35, 255}); // Dark background like RAD Debugger
    
    // NOTE(ARUN): Draw title
    DrawText("RAD Debugger Style UI", 20, 20, 30, (Color){200, 200, 210, 255});
    DrawText("Inspired by Ryan Fleury", 20, 55, 16, (Color){140, 140, 150, 255});
    
    // NOTE(ARUN): Create a button
    Rectangle button_rect = {
        (r32)(app->window->width / 2 - 100),
        (r32)(app->window->hight / 2 - 25),
        200,
        50
    };
    
    UI_Button_Result button = ui_button(button_rect, "Click Me!", (Color){60, 120, 180, 255});
    
    // NOTE(ARUN): Handle button click
    if(button.clicked)
    {
        // Button was clicked - do something!
        // For demonstration, we'll just show a message
    }
    
    // NOTE(ARUN): Show click feedback
    if(button.clicked)
    {
        DrawText("Button Clicked!", 
                 app->window->width / 2 - MeasureText("Button Clicked!", 24) / 2,
                 app->window->hight / 2 + 60,
                 24,
                 (Color){100, 220, 100, 255});
    }
    
    // NOTE(ARUN): Draw status info
    {
        char status[256];
        snprintf(status, sizeof(status), "Button State: %s", 
                button.pressed ? "PRESSED" : 
                button.hovered ? "HOVERED" : 
                "IDLE");
        DrawText(status, 20, app->window->hight - 40, 16, (Color){180, 180, 190, 255});
    }
    
    // NOTE(ARUN): Draw FPS
    DrawFPS(app->window->width - 100, 20);
    
    EndDrawing();
}
