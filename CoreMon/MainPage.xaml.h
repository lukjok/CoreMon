//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace CoreMon
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		void Check(int CoreNum);
		void StartTimerAndRegisterHandler();
		void OnTick(Object^ sender, Object^ e);
		void Init(int n);
		void InitMaxValues(int max);

	private:
		DWORD CheckCPUCores();
		void SetValues(ULONG* val);
	};
}
