#include "Form.h"
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System::Drawing;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Resources;
using namespace System::Diagnostics;

RoboCopyForm::RoboCopyForm()
{
	InitForm();
	Setup_Menu();
}

void RoboCopyForm::InitForm()
{
	this->Text = "Robocopy";
	this->Size = System::Drawing::Size(715, 500);
	this->StartPosition = FormStartPosition::CenterScreen;
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	this->MaximizeBox = false;

	TabControl^ tabCtrl = gcnew TabControl();
	tabCtrl->Cursor = Cursors::Default;
	tabCtrl->Location = Point(3, 5);
	tabCtrl->Size = Drawing::Size(690, 430);

	tstart = gcnew TabPage("Start");
	lblExpl = gcnew Label();
	lblExpl->Text = "This application offers an accessible way to manage file and folder copying with Robocopy.";
	lblExpl->Width = 260;
	lblExpl->Font = gcnew System::Drawing::Font("Verdana", 9.5, FontStyle::Italic);
	lblExpl->AutoSize = true;
	lblExpl->Location = Point(6, 40);
	tstart->Controls->Add(lblExpl);

	Expl = gcnew Label();
	Expl->Text = "/MIR: Mirrors the complete tree: copy and delete files so the destiny equals the origin.\n/COPY:DATSO: Enables you to copy data, attributes, timestamps, security and owner.\n/E: Copies subdirectories, including empty ones.\n/S: Copies subdirectories, except empty ones.\n/R:3: Numbrer of retries (3).\n/W:5: Latency time between retries (5).";
	Expl->Location = Point(20, 190);
	Expl->Size = Drawing::Size(200, 150);
	tstart->Controls->Add(Expl);

	btnExOr = gcnew Button();
	btnExOr->Size = Drawing::Size(100, 20);
	btnExOr->Click += gcnew EventHandler(this, &RoboCopyForm::btnOrigin_Click);
	btnExOr->Cursor = Cursors::Hand;
	btnExOr->Text = "Browse...";
	btnExOr->Location = Point(450, 100);
	tstart->Controls->Add(btnExOr);

	btnExDes = gcnew Button();
	btnExDes->Size = Drawing::Size(100, 20);
	btnExDes->Click += gcnew EventHandler(this, &RoboCopyForm::btnDest_Click);
	btnExDes->Cursor = Cursors::Hand;
	btnExDes->Text = "Browse...";
	btnExDes->Location = Point(450, 140);
	tstart->Controls->Add(btnExDes);

	btnCopy = gcnew Button();
	btnCopy->Size = Drawing::Size(70, 20);
	btnCopy->Cursor = Cursors::Hand;
	btnCopy->Click += gcnew EventHandler(this, &RoboCopyForm::btnCopy_Click);
	btnCopy->Text = "Copy";
	btnCopy->Location = Point(500, 270);
	tstart->Controls->Add(btnCopy);

	btnClose = gcnew Button();
	btnClose->Size = Drawing::Size(70, 20);
	btnClose->Cursor = Cursors::Hand;
	btnClose->Click += gcnew EventHandler(this, &RoboCopyForm::Close_Click);
	btnClose->Text = "Close";
	btnClose->Location = Point(590, 360);
	tstart->Controls->Add(btnClose);

	lblOr = gcnew Label();
	lblOr->Text = "Origin Path: ";
	lblOr->Width = 260;
	lblOr->Font = gcnew System::Drawing::Font("Times", 10, FontStyle::Regular);
	lblOr->AutoSize = true;
	lblOr->Location = Point(46, 100);
	tstart->Controls->Add(lblOr);

	lblDest = gcnew Label();
	lblDest->Text = "Destiny Path: ";
	lblDest->Width = 260;
	lblDest->Font = gcnew System::Drawing::Font("Times", 10, FontStyle::Regular);
	lblDest->AutoSize = true;
	lblDest->Location = Point(40, 140);
	tstart->Controls->Add(lblDest);

	txtOrigin = gcnew TextBox();
	txtOrigin->Location = Point(150, 100);
	txtOrigin->DragEnter += gcnew DragEventHandler(this, &RoboCopyForm::txtOrigin_DragEnter);
	txtOrigin->DragDrop += gcnew DragEventHandler(this, &RoboCopyForm::txtOrigin_DragDrop);
	txtOrigin->AllowDrop = true;
	txtOrigin->Width = 260;
	tstart->Controls->Add(txtOrigin);

	txtDest = gcnew TextBox();
	txtDest->Location = Point(150, 140);
	txtDest->DragEnter += gcnew DragEventHandler(this, &RoboCopyForm::txtDest_DragEnter);
	txtDest->DragDrop += gcnew DragEventHandler(this, &RoboCopyForm::txtDest_DragDrop);
	txtDest->AllowDrop = true;
	txtDest->Width = 260;
	tstart->Controls->Add(txtDest);

	grbox = gcnew GroupBox();
	grbox->Text = "Options";
	grbox->Size = Drawing::Size(195, 100);
	grbox->BackColor = System::Drawing::Color::Transparent;
	grbox->Location = Point(280, 210);
	tstart->Controls->Add(grbox);

	cbCpyAll = gcnew CheckBox();
	cbCpyAll->Text = "/COPY:DATSO";
	cbCpyAll->Cursor = Cursors::Hand;
	cbCpyAll->BringToFront();
	cbCpyAll->Checked = false;
	cbCpyAll->Location = Point(95, 20);
	this->grbox->Controls->Add(cbCpyAll);

	cbMir = gcnew CheckBox();
	cbMir->Text = "/MIR";
	cbMir->Cursor = Cursors::Hand;
	cbMir->BringToFront();
	cbMir->Checked = false;
	cbMir->Location = Point(20, 20);
	this->grbox->Controls->Add(cbMir);

	cbE = gcnew CheckBox();
	cbE->Text = "/E";
	cbE->Cursor = Cursors::Hand;
	cbE->BringToFront();
	cbE->Checked = false;
	cbE->Location = Point(95, 60);
	this->grbox->Controls->Add(cbE);

	cbR = gcnew CheckBox();
	cbR->Text = "/R:3";
	cbR->Cursor = Cursors::Hand;
	cbR->BringToFront();
	cbR->Checked = false;
	cbR->Location = Point(20, 60);
	this->grbox->Controls->Add(cbR);

	cbS = gcnew CheckBox();
	cbS->Text = "/S";
	cbS->Cursor = Cursors::Hand;
	cbS->BringToFront();
	cbS->Checked = false;
	cbS->Location = Point(95, 40);
	this->grbox->Controls->Add(cbS);

	cbW = gcnew CheckBox();
	cbW->Text = "/W:5";
	cbW->Cursor = Cursors::Hand;
	cbW->BringToFront();
	cbW->Checked = false;
	cbW->Location = Point(20, 40);
	this->grbox->Controls->Add(cbW);

	pb1 = gcnew ProgressBar();
	pb1->Visible = true;
	btnCopy->Enabled = true;

	pb1->Location = Point(50, 360);
	pb1->Cursor = Cursors::Default;
	pb1->Size = Drawing::Size(200, 20);
	tstart->Controls->Add(pb1);

	tp = gcnew TabPage("Log");
	richTextBox = gcnew RichTextBox();
	richTextBox->Location = Point(50, 15);
	richTextBox->Size = Drawing::Size(570, 380);
	richTextBox->ReadOnly = true;
	richTextBox->ScrollBars = RichTextBoxScrollBars::Vertical;
	

	this->tp->Controls->Add(richTextBox);
	tabCtrl->Controls->Add(tstart);
	tabCtrl->Controls->Add(tp);
	
	this->Controls->Add(tabCtrl);
}

void RoboCopyForm::btnCopy_Click(Object^ pSender, EventArgs^ Args)
{
	String^ origin = txtOrigin->Text;
	String^ destiny = txtDest->Text;
	String^ options = Options();

	if (String::IsNullOrEmpty(origin) || String::IsNullOrEmpty(destiny)) {
		MessageBox::Show("Must select Origin and Destiny\nPlease fill the fileds with Origin and Destiny", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	int totalFiles = CountFiles(origin);
	if (totalFiles == 0) {
		pb1->Style = ProgressBarStyle::Marquee;
		pb1->MarqueeAnimationSpeed = 30;
	}
	else {
		pb1->Style = ProgressBarStyle::Continuous;
		pb1->Maximum = totalFiles;
		pb1->Value = 0;
	}

	btnCopy->Enabled = false;

	DoCopy(origin, destiny, options);
}

void RoboCopyForm::AppendLine(String^ s) {
	richTextBox->AppendText(s + Environment::NewLine);
}

void RoboCopyForm::IncrementProgress() {
	if (pb1->Style == ProgressBarStyle::Continuous && pb1->Value < pb1->Maximum) {
		pb1->Value += 1;
	}
}

void RoboCopyForm::OnProcessExit(int exitCode) {
	btnCopy->Enabled = true;
	pb1->Style = ProgressBarStyle::Continuous;
	pb1->Value = pb1->Maximum;
	richTextBox->AppendText("Exit Code: " + exitCode.ToString() + Environment::NewLine);
}

void RoboCopyForm::Close_Click(Object^ pSender, EventArgs^ Args) {
	this->Close();
}

void RoboCopyForm::DoCopy(String^ origin, String^ destiny, String^ options) {
	Process^ proc = gcnew Diagnostics::Process();
	proc->StartInfo->FileName = Environment::SystemDirectory + "\\robocopy.exe";
	proc->StartInfo->Arguments = "\"" + txtOrigin->Text + "\" \"" + txtDest->Text + "\" " + options;
	proc->StartInfo->UseShellExecute = false;
	proc->StartInfo->RedirectStandardOutput = true;
	proc->StartInfo->RedirectStandardError = true;
	proc->StartInfo->CreateNoWindow = true;

	try {
		proc->Start();

		while (!proc->StandardOutput->EndOfStream) {
			String^ line = proc->StandardOutput->ReadLine();
			if (!String::IsNullOrEmpty(line)) {
				if (line->Contains("New File") || line->Contains("Copied")) {
					this->BeginInvoke(gcnew MethodInvoker(this, &RoboCopyForm::IncrementProgress));
				}
				this->BeginInvoke(gcnew Action<String^>(this, &RoboCopyForm::AppendLine), line);
			}
		}

		proc->WaitForExit();
		int exitCode = proc->ExitCode;

		this->BeginInvoke(gcnew Action<int>(this, &RoboCopyForm::OnProcessExit), exitCode);

	}
	catch (Exception^ ex) {
		String^ msg = "Error running robocopy: " + ex->Message;
		this->BeginInvoke(gcnew Action<String^>(this, &RoboCopyForm::AppendLine), msg);

		this->BeginInvoke(gcnew MethodInvoker(this, &RoboCopyForm::IncrementProgress));
	}
}

void RoboCopyForm::Setup_Menu(void)
{
	menuBar = gcnew MainMenu();
	fileMenu = gcnew MenuItem("&File");
	this->menuBar->MenuItems->Add(fileMenu);
	Item1 = gcnew MenuItem("&About...");
	Item1->Click += gcnew EventHandler(this, &RoboCopyForm::MenuItem_About_Click);
	fileMenu->MenuItems->Add(Item1);
	Item2 = gcnew MenuItem("&Exit");
	Item2->Click += gcnew EventHandler(this, &RoboCopyForm::MenuItem_Exit_Click);
	fileMenu->MenuItems->Add(Item2);
	settingsMenu = gcnew MenuItem("&Settings");
	this->menuBar->MenuItems->Add(settingsMenu);
	submenu1 = gcnew MenuItem("&Language");
	settingsMenu->MenuItems->Add(submenu1);
	Item1_1 = gcnew MenuItem("&English");
	Item1_1->Click += gcnew EventHandler(this, &RoboCopyForm::MenuItem_English_Click);
	Item1_1->Checked = true;
	Item1_2 = gcnew MenuItem("&Spanish");
	Item1_2->Checked = false;
	Item1_2->Click += gcnew EventHandler(this, &RoboCopyForm::MenuItem_Spanish_Click);

	submenu1->MenuItems->Add(Item1_1);
	submenu1->MenuItems->Add(Item1_2);

	this->Menu = menuBar;
}

void RoboCopyForm::MenuItem_About_Click(Object^ pSender, EventArgs^ Args)
{
	Form^ aboutForm = gcnew Form();
	aboutForm->Text = L"About Robocopy";
	aboutForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	aboutForm->Size = System::Drawing::Size(370, 160);
	aboutForm->BackColor = System::Drawing::Color::LightGray;
	aboutForm->MaximizeBox = false;
	aboutForm->MinimizeBox = false;
	aboutForm->StartPosition = FormStartPosition::CenterScreen;

	Label^ label1 = gcnew Label();
	label1->Text = L"Made by Esteban Rodolfo Scaramuzza, 2025.";
	label1->Size = System::Drawing::Size(label1->PreferredWidth, label1->PreferredHeight);
	label1->Location = Point(90, 30);

	Label^ label2 = gcnew Label();
	Bitmap^ iconBitmap = gcnew Bitmap("RCGUI2.bmp");
	label2->Image = iconBitmap;
	label2->Size = System::Drawing::Size(48, 48);
	label2->Location = Point(15, 20);
	label2->AutoSize = false;
	label2->ImageAlign = ContentAlignment::MiddleLeft;

	aboutForm->Controls->Add(label1);
	aboutForm->Controls->Add(label2);

	OKButton = gcnew Button();
	OKButton->Text = L"OK";
	OKButton->Size = System::Drawing::Size(40, 25);
	OKButton->BackColor = System::Drawing::Color::White;
	OKButton->Cursor = Cursors::Hand;
	OKButton->Location = Point(290, 85);

	OKButton->Click += gcnew EventHandler(this, &RoboCopyForm::OKButton_Cliked);
	aboutForm->Controls->Add(OKButton);
	aboutForm->ShowDialog();
}

void RoboCopyForm::OKButton_Cliked(Object^ pSender, EventArgs^ Args)
{
	Button^ clickedButton = dynamic_cast<Button^>(pSender);
	Form^ parentForm = clickedButton->FindForm();

	parentForm->Close();
}

void RoboCopyForm::MenuItem_Exit_Click(Object^ pSender, EventArgs^ Args)
{
	this->Close();
}


void RoboCopyForm::MenuItem_English_Click(Object^ pSender, EventArgs^ Args) {
	Item1_1->Checked = true;
	Item1_2->Checked = false;

	CultureInfo^ englishCulture = gcnew CultureInfo("en-GB");

	Thread::CurrentThread->CurrentCulture = englishCulture;
	Thread::CurrentThread->CurrentUICulture = englishCulture;
	AppSettings^ settings = gcnew AppSettings();
	settings->InitializeMenu();
	if (resManager == nullptr) {
		resManager = gcnew ResourceManager("Robocopy.English", Assembly::GetExecutingAssembly());
	}
	this->Text = resManager->GetString("Form.Text", englishCulture);

	fileMenu->Text = resManager->GetString("MainMenu.Text", englishCulture);
	Item1->Text = resManager->GetString("Item1.Text", englishCulture);
	Item2->Text = resManager->GetString("Item2.Text", englishCulture);
	settingsMenu->Text = resManager->GetString("Settings.Text", englishCulture);
	submenu1->Text = resManager->GetString("SMenu.Text", englishCulture);
	Item1_1->Text = resManager->GetString("I1.Text", englishCulture);
	Item1_2->Text = resManager->GetString("I2.Text", englishCulture);
	lblExpl->Text = resManager->GetString("lblExpl.Text", englishCulture);
	Expl->Text = resManager->GetString("Expl.Text", englishCulture);
	btnClose->Text = resManager->GetString("BtnClose.Text", englishCulture);
	grbox->Text = resManager->GetString("GrpBox.Text", englishCulture);
	lblOr->Text = resManager->GetString("LblOr.Text", englishCulture);
	lblDest->Text = resManager->GetString("LblDest.Text", englishCulture);
	btnCopy->Text = resManager->GetString("btnCopy.Text", englishCulture);
	btnExOr->Text = resManager->GetString("btnExOr.Text", englishCulture);
	btnExDes->Text = resManager->GetString("btnExDes.Text", englishCulture);
	tstart->Text = resManager->GetString("tstart.Text", englishCulture);
	tp->Text = resManager->GetString("tp.Text", englishCulture);

	AppSettings::SaveLanguage("en-GB");
}

void RoboCopyForm::MenuItem_Spanish_Click(Object^ pSender, EventArgs^ Args) {
	Item1_1->Checked = false;
	Item1_2->Checked = true;

	CultureInfo^ spanishCulture = gcnew CultureInfo("es-ES");

	Thread::CurrentThread->CurrentCulture = spanishCulture;
	Thread::CurrentThread->CurrentUICulture = spanishCulture;
	AppSettings^ settings = gcnew AppSettings();
	settings->InitializeMenu();
	if (resManager == nullptr) {
		resManager = gcnew ResourceManager("Robocopy.Español", Assembly::GetExecutingAssembly());
	}
	this->Text = resManager->GetString("Form.Text", spanishCulture);

	fileMenu->Text = resManager->GetString("MainMenu.Text", spanishCulture);
	Item1->Text = resManager->GetString("Item1.Text", spanishCulture);
	Item2->Text = resManager->GetString("Item2.Text", spanishCulture);
	settingsMenu->Text = resManager->GetString("Settings.Text", spanishCulture);
	submenu1->Text = resManager->GetString("SMenu.Text", spanishCulture);
	Item1_1->Text = resManager->GetString("I1.Text", spanishCulture);
	Item1_2->Text = resManager->GetString("I2.Text", spanishCulture);
	lblExpl->Text = resManager->GetString("lblExpl.Text", spanishCulture);
	Expl->Text = resManager->GetString("Expl.Text", spanishCulture);
	btnClose->Text = resManager->GetString("BtnClose.Text", spanishCulture);
	grbox->Text = resManager->GetString("GrpBox.Text", spanishCulture);
	lblOr->Text = resManager->GetString("LblOr.Text", spanishCulture);
	lblDest->Text = resManager->GetString("LblDest.Text", spanishCulture);
	btnCopy->Text = resManager->GetString("btnCopy.Text", spanishCulture);
	btnExOr->Text = resManager->GetString("btnExOr.Text", spanishCulture);
	btnExDes->Text = resManager->GetString("btnExDes.Text", spanishCulture);
	tstart->Text = resManager->GetString("tstart.Text", spanishCulture);
	tp->Text = resManager->GetString("tp.Text", spanishCulture);

	AppSettings::SaveLanguage("es-ES");
}