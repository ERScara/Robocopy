#include "Form.h"
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System::Drawing;
using namespace System::IO;
using namespace System::Threading::Tasks;
using namespace System::Diagnostics;

RoboCopyForm::RoboCopyForm()
{
	InitForm();
}

void RoboCopyForm::InitForm()
{
	this->Text = "Robocopy";
	this->Size = System::Drawing::Size(640, 480);
	this->StartPosition = FormStartPosition::CenterScreen;
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
	this->MaximizeBox = false;

	TabControl^ tabCtrl = gcnew TabControl();
	tabCtrl->Cursor = Cursors::Default;
	tabCtrl->Location = Point(5, 5);
	tabCtrl->Size = Drawing::Size(620, 450);

	tstart = gcnew TabPage("Start");
	lblExpl = gcnew Label();
	lblExpl->Text = "This application offers an accessible way to manage file and folder copying with Robocopy.";
	lblExpl->Width = 260;
	lblExpl->Font = gcnew System::Drawing::Font("Verdana", 9.5, FontStyle::Italic);
	lblExpl->AutoSize = true;
	lblExpl->Location = Point(10, 40);
	tstart->Controls->Add(lblExpl);

	Expl = gcnew Label();
	Expl->Text = "/MIR: Mirrors the complete tree: copy and delete files so the destiny equals the origin.\n/COPY:DATSO: Enables you to copy data, attributes,TimeStamps,Security and Owner.\n/E: Copies subdirectories but not the empty ones.\n/S: Copies subdirectories except empty ones.\n/R:3: Numbrer of retries (3).\nW:5: Latency time between retries (5).";
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
	btnClose->Location = Point(500, 380);
	tstart->Controls->Add(btnClose);

	lblOr = gcnew Label();
	lblOr->Text = "Origin path: ";
	lblOr->Width = 260;
	lblOr->Font = gcnew System::Drawing::Font("Times", 10, FontStyle::Regular);
	lblOr->AutoSize = true;
	lblOr->Location = Point(66, 100);
	tstart->Controls->Add(lblOr);

	lblDest = gcnew Label();
	lblDest->Text = "Destiny path: ";
	lblDest->Width = 260;
	lblDest->Font = gcnew System::Drawing::Font("Times", 10, FontStyle::Regular);
	lblDest->AutoSize = true;
	lblDest->Location = Point(60, 140);
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
	richTextBox->Location = Point(20, 20);
	richTextBox->Size = Drawing::Size(550, 380);
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


