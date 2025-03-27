// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../../Headers/Engine/Component.h"

namespace Engine
{
	Component::Component()
		: m_isActive(false)
		, m_isSelected(false)
	{
	}

	Component::~Component()
	{
	}

	bool Component::isSelected() const
	{
		return m_isSelected;
	}

	void Component::select()
	{
		m_isSelected = true;
	}

	void Component::deselect()
	{
		m_isSelected = false;
	}

	bool Component::isActive() const
	{
		return m_isActive;
	}

	void Component::activate()
	{
		m_isActive = true;
	}

	void Component::deactivate()
	{
		m_isActive = false;
	}
}
