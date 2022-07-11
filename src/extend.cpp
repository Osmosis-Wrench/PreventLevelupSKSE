#include "extend.h"
#include "Settings.h"

namespace extend
{
	void StatsMenuEx::AcceptEx(RE::FxDelegateHandler::CallbackProcessor* a_processor)
	{
		originalAcceptFunction(this, a_processor);
		const auto isHotkeyHeld = KeyInputEventHandler::GetSingleton()->IsHotkeyHeld();
		if (Settings::GetSingleton()->GetInverted())
		{
			if (isHotkeyHeld) {
				fxDelegate->callbacks.Remove("SetFadedIn");
				a_processor->Process("SetFadedIn", [](const RE::FxDelegateArgs&) {
					//nop
				});
			}
		} else {
			if (!isHotkeyHeld) {
				fxDelegate->callbacks.Remove("SetFadedIn");
				a_processor->Process("SetFadedIn", [](const RE::FxDelegateArgs&) {
					//nop
				});
			}
		}
	}

	void StatsMenuEx::Install()
	{
		logger::info("Starting Install...");
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_StatsMenu[0]);
		originalAcceptFunction = vtbl.write_vfunc(0x1, &AcceptEx);
		logger::info("Installed!");
	}

	// input event handler

	bool KeyInputEventHandler::IsHotkeyHeld() const
	{
		return hotkeyHeld;
	}

	KeyInputEventHandler* KeyInputEventHandler::GetSingleton()
	{
		static KeyInputEventHandler singleton;
		return std::addressof(singleton);
	}

	void KeyInputEventHandler::Register()
	{
		if (const auto inputHandler = RE::BSInputDeviceManager::GetSingleton()) {
			inputHandler->AddEventSink<RE::InputEvent*>(GetSingleton());
			logger::info("Registered to get input events!");
		}
	}

	RE::BSEventNotifyControl KeyInputEventHandler::ProcessEvent(RE::InputEvent* const* a_evn, RE::BSTEventSource<RE::InputEvent*>*)
	{
		using InputType = RE::INPUT_EVENT_TYPE;

		if (!a_evn){
			return RE::BSEventNotifyControl::kContinue;
		}

		if (auto player = RE::PlayerCharacter::GetSingleton(); !player->Is3DLoaded()) {
			return RE::BSEventNotifyControl::kContinue;
		}
		
		if (const auto UI = RE::UI::GetSingleton(); UI->IsMenuOpen(RE::Console::MENU_NAME)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		const auto hotKey = Settings::GetSingleton()->GetHotkey();

		for (auto event = *a_evn; event; event = event->next) {
			if (const auto button = event->AsButtonEvent(); button) {
				if (const auto key = static_cast<Key>(button->GetIDCode()); key == hotKey) {
					if (hotkeyHeld != button->IsPressed()) {
						hotkeyHeld = button->IsPressed();
					}
				}
			}
		}

		return RE::BSEventNotifyControl::kContinue;
	}
}
