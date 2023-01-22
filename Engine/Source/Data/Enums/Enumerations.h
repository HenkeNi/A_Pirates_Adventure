#pragma once


enum class ePriority
{
	Low, Moderate, High, NotSpecified
};

enum class eWindowEventType
{
	Resize, LostFocus, GainedFocus, Close
};

enum class eKeyState
{
	Press, Release, Repeat
};

