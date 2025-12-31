#include "Form.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <mscorlib.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Globalization;
using namespace System::Threading;
using namespace System::Reflection;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^Args) {
	Application::EnableVisualStyles();

	String^ savedLanguage = AppSettings::LoadLanguage();

	CultureInfo^ culture = gcnew CultureInfo(savedLanguage);
	Thread::CurrentThread->CurrentCulture = culture;
	Thread::CurrentThread->CurrentUICulture = culture;

	RoboCopyForm^ RC = gcnew RoboCopyForm;
	Application::Run(RC);
	return 0;
}