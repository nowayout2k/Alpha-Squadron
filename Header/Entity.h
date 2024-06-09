//
// Created by Johnnie on 5/29/2024.
//

#ifndef ALPHA_SQUADRON_HEADER_ENTITY_H_
#define ALPHA_SQUADRON_HEADER_ENTITY_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector3.hpp>

class Entity
{
 public:
    virtual void update(float deltaTime) { if(!m_isActive) return; };
	bool isActive() const { return m_isActive; };
	bool isDestroyPending() { return m_isDestroyPending; }
protected:
	virtual void destroy()
	{
		m_isActive = false;
		m_isDestroyPending = true;
	}
	Entity(){ m_isActive = true; m_isDestroyPending = false; }
 private:;
	bool m_isActive;
	bool m_isDestroyPending;
};

#endif //ALPHA_SQUADRON_HEADER_ENTITY_H_
