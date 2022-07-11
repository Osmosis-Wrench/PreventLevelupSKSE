#pragma once

class Settings
{
public:
	[[nodiscard]] static Settings* GetSingleton()
	{
		static Settings singleton;
		return std::addressof(singleton);
	}

	bool LoadSettings();

	[[nodiscard]] Key GetHotkey() const;
	[[nodiscard]] bool GetInverted() const;

private:
	Key hotKey{ Key::kLeftShift };
	bool inverted{ false };
};
