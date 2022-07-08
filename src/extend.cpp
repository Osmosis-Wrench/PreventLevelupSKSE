#include "extend.h"

namespace extend
{
	void StatsMenuEx::AcceptEx(RE::FxDelegateHandler::CallbackProcessor* a_processor)
	{
		originalAcceptFunction(this, a_processor); // like everything this is basically just stolen from Qudix. seriously one day I'll try and do something that he hasn't already done and i'll be so totall lost.
		fxDelegate->callbacks.Remove("SetFadedIn");
		a_processor->Process("SetFadedIn", [](const RE::FxDelegateArgs&) {
			//nop
		});

		if (const auto input = RE::BSInputDeviceManager::GetSingleton()) {
			if (input->GetKeyboard()->IsPressed(42)) {
				
			}
		}
	}

	void StatsMenuEx::Install()
	{
		logger::info("Starting Install");
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_StatsMenu[0]);
		originalAcceptFunction = vtbl.write_vfunc(0x1, &AcceptEx);
		logger::info("Installed!");
	}

	KeyInputEventHandler* KeyInputEventHandler::GetSingleton()
	{
		static KeyInputEventHandler singleton;
		return std::addressof(singleton);
	}

	void KeyInputEventHandler::Register()
	{
		//static RE::BSWin32GamepadDevice test;
		//static RE::BSInputDeviceManager inputManager;
		//inputManager.GetSingleton();
		if (const auto input = RE::BSInputDeviceManager::GetSingleton()) {
			if (input->GetKeyboard()->IsPressed(26)) {
				RE::DebugMessageBox("Test1");
			}
			if (input->GetKeyboard()->IsPressed(0x1A)) {
				RE::DebugMessageBox("Test2");
			}
		}
	}

	RE::BSEventNotifyControl KeyInputEventHandler::ProcessEvent(RE::InputEvent* const* a_evn, RE::BSTEventSource<RE::InputEvent*>*)
	{
		return RE::BSEventNotifyControl::kContinue;
	}
}
