#pragma once
#include "RE/G/GRefCountBase.h"
#include "RE/G/GStats.h"

namespace extend
{
	class CallbackProcessorEx : public RE::FxDelegateHandler::CallbackProcessor
	{
	class FxDelegateArgs;
	class GString;

	public:
		static void Install();

	public:
		virtual void ProcessEx(const GString& a_methodName, RE::FxDelegateHandler::CallbackFn* a_method);

	private:
		using ProcessFn = decltype(&RE::FxDelegateHandler::CallbackProcessor::Process);

		inline static REL::Relocation<ProcessFn> _ProcessFn;
	};
}
