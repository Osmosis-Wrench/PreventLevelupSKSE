#pragma once
#include "RE/G/GRefCountBase.h"
#include "RE/G/GStats.h"
#include "RE/G/GString.h"
#include "RE/F/FxDelegateHandler.h"

namespace extend
{
	class CallbackProcessorEx : public RE::FxDelegateHandler::CallbackProcessor
	{
	class FxDelegateArgs;
	class GString;

	public:
		static void Install();

	public:
		virtual void ProcessEx(CallbackProcessor*, const RE::GString& a_methodName, RE::FxDelegateHandler::CallbackFn* a_method);

	private:
		using ProcessFn = decltype(&RE::FxDelegateHandler::CallbackProcessor::Process);

		inline static REL::Relocation<ProcessFn> _ProcessFn;
	};

	class StatsMenuEx : public RE::StatsMenu
	{
	public:
		static void Install();

	public:
		void AcceptEx(StatsMenu*, CallbackProcessor* a_processor);

	private:
		using AcceptFn = decltype(&RE::StatsMenu::Accept);

		inline static REL::Relocation<AcceptFn> originalAcceptFunction;
	};
}
