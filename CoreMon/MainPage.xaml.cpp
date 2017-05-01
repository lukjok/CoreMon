

#include "pch.h"
#include "MainPage.xaml.h"

using namespace CoreMon;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
	InitializeComponent();
	const int CPUCores = CheckCPUCores();
	Init(CPUCores);
	StartTimerAndRegisterHandler();
}

void CoreMon::MainPage::Check(int CoreNum)
{
	ULONG *mhz = new ULONG[CoreNum];
	const int size = CoreNum * sizeof(PROCESSOR_POWER_INFORMATION);
	LPBYTE pBuffer = new BYTE[size];

	NTSTATUS status;
	status = ::CallNtPowerInformation(ProcessorInformation, NULL, 0, pBuffer, size);
	if (status == ERROR_SUCCESS)
	{
		PPROCESSOR_POWER_INFORMATION ppi = (PPROCESSOR_POWER_INFORMATION)pBuffer;
		InitMaxValues(ppi->MaxMhz);
		for (DWORD nIndex = 0; nIndex < CheckCPUCores(); nIndex++)
		{
			mhz[nIndex] = ppi->CurrentMhz;
			ppi++;
		}
		SetValues(mhz);
	}
	else
	{
		OutputDebugString(L"CallNtPowerInformation failed.");
	}
	delete[]pBuffer;
	delete[]mhz;
}


void CoreMon::MainPage::StartTimerAndRegisterHandler()
{
	auto timer = ref new Windows::UI::Xaml::DispatcherTimer();
	TimeSpan ts;
	ts.Duration = 5000000;
	timer->Interval = ts;
	timer->Start();
	auto registrationtoken = timer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTick);
}

void CoreMon::MainPage::OnTick(Object ^ sender, Object ^ e)
{

	Check(CheckCPUCores());
}

DWORD CoreMon::MainPage::CheckCPUCores()
{
	SYSTEM_INFO si = { 0 };
	::GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
}

void CoreMon::MainPage::Init(int n)
{
	switch (n)
	{
	case 2:
		cpb5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb7->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb8->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c7->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c8->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc4->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc3->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc7->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc8->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	case 4:
		cpb5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb7->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb8->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c7->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c8->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc7->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc8->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	case 6:
		cpb5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cpb6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		c6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc5->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		cc6->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	default:
		break;
	}
	
}

void CoreMon::MainPage::InitMaxValues(int max)
{
	cpb1->Maximum = max;
	cpb2->Maximum = max;
	cpb3->Maximum = max;
	cpb4->Maximum = max;
	cpb5->Maximum = max;
	cpb6->Maximum = max;
	cpb7->Maximum = max;
	cpb8->Maximum = max;
}

void CoreMon::MainPage::SetValues(ULONG*  val)
{
	cc1->Text = val[0].ToString() + " MHz";
	cpb1->Value = val[0];
	cc2->Text = val[1].ToString() + " MHz";
	cpb2->Value = val[1];
	cc3->Text = val[2].ToString() + " MHz";
	cpb3->Value = val[2];
	cc4->Text = val[3].ToString() + " MHz";
	cpb4->Value = val[3];
	if (CheckCPUCores() > 4)
	{
		cc5->Text = val[4].ToString() + " MHz";
		cpb5->Value = val[4];
		cc6->Text = val[5].ToString() + " MHz";
		cpb6->Value = val[5];
		cc7->Text = val[6].ToString() + " MHz";
		cpb7->Value = val[6];
		cc8->Text = val[7].ToString() + " MHz";
		cpb8->Value = val[7];
	}
}


