#include <vector>
#include <iostream>
#include <SDL/SDL.h>
#include "include/World.hpp"


//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

Window::Window(){
	
}

Window::Window(int width, int height)
: m_window_width(width), m_window_height(height), m_etat(0){
}

Window::~Window(){
	
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------GETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------


int Window::getWindowWidth() const{
	return m_window_width;
}

int Window::getWindowHeight() const{
	return m_window_height;
}

int Window::getEtat() const{
	return m_etat;
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------SETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void Window::Window::setWindowWidth(int window_width){
	m_window_width = window_width;
}

void Window::setWindowHeight(int window_height){
	m_window_height = window_height;
}

void Window::setEtat(int etat){
	m_etat = etat;
}


//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------FUNCTIONS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------


void Window::updateVideoMode(int mode){

	if(mode == 1){
		if(!SDL_SetVideoMode(0, 0, 32, SDL_RESIZABLE | SDL_FULLSCREEN | SDL_OPENGL)) {
        	std::cerr << SDL_GetError() << std::endl;
        	return;
    	}

	    const SDL_VideoInfo* info = SDL_GetVideoInfo();
		m_window_width = info->current_w;
		m_window_height = info->current_h;
		m_etat = 1; //fullscreen
	}
	else if(mode == 2){
		if(!SDL_SetVideoMode(0, 0, 32, SDL_RESIZABLE | SDL_OPENGL)) {
	    	std::cerr << SDL_GetError() << std::endl;
	    	return;
		}
    	const SDL_VideoInfo* info = SDL_GetVideoInfo();
		m_window_width = info->current_w;
		m_window_height = info->current_h;
		m_etat = 2; //fenetré 
	}
	if(mode == 3){
		if(!SDL_SetVideoMode(1024, 768, 32, SDL_RESIZABLE | SDL_OPENGL)) {
        	std::cerr << SDL_GetError() << std::endl;
        	return;
	    }
    	const SDL_VideoInfo* info = SDL_GetVideoInfo();
		m_window_width = info->current_w;
		m_window_height = info->current_h;
		m_etat = 3; //1024x768 
    }
    
}