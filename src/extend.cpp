#include "extend.h"

namespace extend
{
	void CallbackProcessorEx::ProcessEx(CallbackProcessor*, const RE::GString& a_methodName, RE::FxDelegateHandler::CallbackFn* a_method)
	{
		logger::warn("fired!");
		_ProcessFn(this, a_methodName, a_method);
	};

	void CallbackProcessorEx::Install()
	{
		logger::warn("Starting Install1");
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_FxDelegateHandler__CallbackProcessor[0]);
		_ProcessFn = vtbl.write_vfunc(0x1, &ProcessEx);
		logger::warn("Installed!1");
	};

	void StatsMenuEx::AcceptEx(RE::FxDelegateHandler::CallbackProcessor* a_processor)
	{
		originalAcceptFunction(this, a_processor); // like everything this is basically just stolen from Qudix. seriously one day I'll try and do something that he hasn't already done and i'll be so totall lost.
		fxDelegate->callbacks.Remove("SetFadedIn");
		a_processor->Process("SetFadedIn", [](const RE::FxDelegateArgs&) {
			//nop
		});
	}

	void StatsMenuEx::Install()
	{
		logger::warn("Starting Install");
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_StatsMenu[0]);
		originalAcceptFunction = vtbl.write_vfunc(0x1, &AcceptEx);
		logger::warn("Installed!");
	}
}
