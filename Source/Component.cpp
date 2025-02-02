// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Component.h"
GUI::Component::Component() : m_isActive(false), m_isSelected(false)
{

}
GUI::Component::~Component()
{

}
bool GUI::Component::isSelected() const
{
	return m_isSelected;
}
void GUI::Component::select()
{
	m_isSelected = true;
}
void GUI::Component::deselect()
{
	m_isSelected = false;
}
bool GUI::Component::isActive() const
{
	return m_isActive;
}
void GUI::Component::activate()
{
	m_isActive = true;
}
void GUI::Component::deactivate()
{
	m_isActive = false;
}
