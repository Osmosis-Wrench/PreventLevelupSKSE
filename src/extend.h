#pragma once
#include "RE/G/GRefCountBase.h"
#include "RE/G/GStats.h"
#include "RE/G/GString.h"
#include "RE/F/FxDelegateHandler.h"

namespace extend
{
	class StatsMenuEx : public RE::StatsMenu
	{
	public:
		static void Install();

	public:
		void AcceptEx(CallbackProcessor* a_processor);

	private:
		using AcceptFn = decltype(&RE::StatsMenu::Accept);

		inline static REL::Relocation<AcceptFn> originalAcceptFunction;
	};
}
