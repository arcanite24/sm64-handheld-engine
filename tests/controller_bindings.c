#include <assert.h>

#define CAPI_SDL2
#define CONTROLLER_BINDINGS_TEST
#include "../src/pc/controller/controller_sdl2.c"

int main(void) {
    const u32 gamepad[MAX_BINDS] = {VK_BASE_SDL_GAMEPAD, VK_BASE_SDL_GAMEPAD + 1, VK_BASE_SDL_GAMEPAD + 2};
    for (int i = 0; i < 20; i++) controller_add_binds(A_BUTTON, gamepad);
    assert(num_joy_binds == MAX_JOYBINDS && num_mouse_binds == 0);

    const u32 mouse[MAX_BINDS] = {VK_BASE_SDL_MOUSE + 1, VK_BASE_SDL_MOUSE + 2, VK_BASE_SDL_MOUSE + 3};
    for (int i = 0; i < 20; i++) controller_add_binds(B_BUTTON, mouse);
    assert(num_mouse_binds == MAX_JOYBINDS && num_joy_binds == MAX_JOYBINDS);

    const u32 invalid[MAX_BINDS] = {VK_BASE_SDL_GAMEPAD + MAX_JOYBUTTONS,
                                    VK_BASE_SDL_MOUSE, VK_BASE_SDL_MOUSE + MAX_MOUSEBUTTONS + 1};
    num_joy_binds = num_mouse_binds = 0;
    controller_add_binds(A_BUTTON, invalid);
    assert(num_joy_binds == 0 && num_mouse_binds == 0);
    return 0;
}
