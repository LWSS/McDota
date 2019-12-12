#pragma once

#include "../SDK/panorama/IUIPanel.h"

namespace UI
{
	/* Dota Panels */
	inline panorama::IUIPanel* dashRoot = nullptr;
	inline panorama::IUIPanel* hudRoot = nullptr;

	/* Custom Panels */
	inline panorama::IUIPanel* mcDota = nullptr;

	void ToggleUI();
}