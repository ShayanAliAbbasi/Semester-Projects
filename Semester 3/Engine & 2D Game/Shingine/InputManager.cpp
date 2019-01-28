#include "InputManager.h"

namespace Shingine {

InputManager::InputManager() : m_mouseCoords(0, 0)
{
}

InputManager::~InputManager()
{
}

void InputManager::update() {
    // Loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
    for (auto& it : m_keyMap) {
        m_previousKeyMap[it.first] = it.second;
    }
}

void InputManager::pressKey(unsigned int keyID) {
    // if keyID doesn't already exist in keyMap, it will get added
    m_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
     m_keyMap[keyID] = false;
}

void InputManager::setMouseCoords(int x, int y) {
	m_mouseCoords.x = static_cast<float>(x);
	m_mouseCoords.y = static_cast<float>(y);
}

bool InputManager::isKeyDown(unsigned int keyID) {
   
    auto it = m_keyMap.find(keyID);
    if (it != m_keyMap.end()) {
        // Found the key
        return it->second;
    } else {
        // Didn't find the key
        return false;
    }
}

bool InputManager::isKeyPressed(unsigned int keyID) {
    // Check if it is pressed this frame, and wasn't pressed last frame
    if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
        return true;
    }
    return false;
}

bool InputManager::wasKeyDown(unsigned int keyID) {
    
    auto it = m_previousKeyMap.find(keyID);
    if (it != m_previousKeyMap.end()) {
        // Found the key
        return it->second;
    } else {
        // Didn't find the key
        return false;
    }
}

}