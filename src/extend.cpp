#include "extend.h"

namespace extend
{
	void CallbackProcessorEx::ProcessEx(const GString& a_methodName, RE::FxDelegateHandler::CallbackFn* a_method)
	{
		logger::info("called");
		return _ProcessFn(this, a_methodName, a_method);
	};

	void CallbackProcessorEx::Install()
	{
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_FxDelegateHandler__CallbackProcessor[0]);
		_ProcessFn = vtbl.write_vfunc(0x1, &ProcessEx);
	};
}
