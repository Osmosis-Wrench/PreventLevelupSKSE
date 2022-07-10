#include "extend.h"

namespace extend
{
	void StatsMenuEx::AcceptEx(RE::FxDelegateHandler::CallbackProcessor* a_processor)
	{
		originalAcceptFunction(this, a_processor); // like everything this is basically just stolen from Qudix. seriously one day I'll try and do something that he hasn't already done and i'll be so totall lost.
		if (const auto input = RE::BSInputDeviceManager::GetSingleton()) {
			if (!input->GetGamepad()->IsPressed(InputMap::GamepadMaskToKeycode(0x0100))) {
				fxDelegate->callbacks.Remove("SetFadedIn");
				a_processor->Process("SetFadedIn", [](const RE::FxDelegateArgs&) {
					//nop
				});
			}
		}
		//SKSE::InputMap
		//!input->GetKeyboard()->IsPressed(42) || 
	}

	void StatsMenuEx::Install()
	{
		logger::info("Starting Install");
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_StatsMenu[0]);
		originalAcceptFunction = vtbl.write_vfunc(0x1, &AcceptEx);
		logger::info("Installed!");
	}
}
