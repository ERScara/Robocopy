#include "Form.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <mscorlib.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^Args) {
	Application::EnableVisualStyles();
	RoboCopyForm^ RC = gcnew RoboCopyForm;
	Application::Run(RC);
	return 0;
}