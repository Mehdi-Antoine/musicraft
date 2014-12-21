#include "InputManager.h"




void InputManager::updateInput() {

    //Récupération des events
    while(SDL_PollEvent(&m_event)) {
        //Quel type d'event
        switch(m_event.type) {

        case SDL_KEYDOWN:

            m_key[m_event.key.keysym.sym] = true;

            //Quelle touche
            switch(m_event.key.keysym.sym) {

            case SDLK_z:
                m_key[SDLK_z] = true;
                break;

            case SDLK_q:
                m_key[SDLK_q] = true;
                break;

            case SDLK_s:
                m_key[SDLK_s] = true;
                break;

            case SDLK_d:
                m_key[SDLK_d] = true;
                break;



            default:
                break;

            }

            break;

        case SDL_KEYUP:

            m_key[m_event.key.keysym.sym] = false;

            //Quelle touche
            switch(m_event.key.keysym.sym) {

            case SDLK_z:
                m_key[SDLK_z] = false;
                break;

            case SDLK_q:
                m_key[SDLK_q] = false;
                break;

            case SDLK_s:
                m_key[SDLK_s] = false;
                break;

            case SDLK_d:
                m_key[SDLK_d] = false;
                break;

            default:
                break;

            }

            break;

        case SDL_MOUSEMOTION:

            m_mouse_pos_rel[0] = m_event.motion.xrel;
            m_mouse_pos_rel[1] = m_event.motion.yrel;

            break;

        case SDL_MOUSEBUTTONDOWN:
            m_mouse_button[m_event.button.button]= true;

            if (m_event.button.button == SDL_BUTTON_LEFT) {
                m_mouse_pos[0] = m_event.button.x;
                m_mouse_pos[1] = m_event.button.y;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            m_mouse_button[m_event.button.button]= false;
            break;

        case SDL_QUIT:
            m_quit = true;
            break;

        default:
            break;
        }

    }

}

bool* InputManager::getKey()
{
    return m_key;
}


bool InputManager::getKey(int key)
{
    return m_key[key];
}

bool* InputManager::getMouse()
{
    return m_mouse_button;
}


bool InputManager::getMouse(int mouseButton)
{
    return m_mouse_button[mouseButton];
}

int* InputManager::getMousePos()
{
    return m_mouse_pos;
}


int InputManager::getMousePos(int orientation)
{
    if(orientation == 0) {
        return m_mouse_pos[0];
    }

    return m_mouse_pos[1];
}

int* InputManager::getMouseRel()
{
    return m_mouse_pos_rel;
}


int InputManager::getMouseRel(int orientation)
{
    if(orientation == 0) {
        return m_mouse_pos_rel[0];
    }

    return m_mouse_pos_rel[1];
}

InputManager::InputManager()
{
}
