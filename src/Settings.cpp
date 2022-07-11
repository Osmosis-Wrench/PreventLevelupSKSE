#include "Settings.h"

bool Settings::LoadSettings()
{
	constexpr auto path = L"Data/SKSE/Plugins/PreventLevelupSKSE.ini";

	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(path);

	const auto get_value = [&]<class T>(T& a_value, const char* a_section, const char* a_key, const char* a_comment) {
		a_value = string::lexical_cast<T>(ini.GetValue(a_section, a_key, std::to_string(a_value).c_str()));
		ini.SetValue(a_section, a_key, std::to_string(a_value).c_str(), a_comment);
	};

	get_value(hotKey, "Settings", "Activation Hotkey", ";Hold hotkey while opening the Skills Menu to trigger Levelup. Default is Left Shift\n;Keyboard scan codes : https://wiki.nexusmods.com/index.php/DirectX_Scancodes_And_How_To_Use_Them\n;Gamepad scan codes : https://geckwiki.com/index.php?title=DisableButton#XBox_Controller_Button_Codes");
	get_value(inverted, "Settings", "Default action", ";With this enabled, default functionality will be inverted. Holding hotkey while menu opening will prevent levelup.");
	(void)ini.SaveFile(path);

	return true;
}

Key Settings::GetHotkey() const
{
	return hotKey;
}

bool Settings::GetInverted() const
{
	return inverted;
}
