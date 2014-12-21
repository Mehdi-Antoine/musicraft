#ifndef InputManager_h
#define InputManager_h

#include <SDL/SDL.h>


class InputManager {

public:

    void updateInput();

    bool* getKey();
    bool getKey(int key);

    bool* getMouse();
    bool getMouse(int mouseButton);

    int* getMousePos();
    int getMousePos(int orientation);

    int* getMouseRel();
    int getMouseRel(int orientation);

    InputManager();

private:


    bool m_key[SDLK_LAST];
    bool m_mouse_button[8];
    bool m_quit;
    int m_mouse_pos[2];
    int m_mouse_pos_rel[2];
    SDL_Event m_event;
};

#endif // InputManager_h
