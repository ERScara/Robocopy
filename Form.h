#pragma once
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#using <System.dll>

using namespace System;
using namespace System::IO;
using namespace System::Threading::Tasks;
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;

ref class RoboCopyForm :public Form {
public:
	RoboCopyForm();
	void InitForm();
private:
	Button^ btnExOr;
	Button^ btnExDes;
	Button^ btnClose;
	Button^ btnCopy;
	Label^ lblOr;
	Label^ lblDest;
	Label^ Expl;
	GroupBox^ grbox;
	CheckBox^ cbMir;
	CheckBox^ cbE;
	CheckBox^ cbCpyAll;
	CheckBox^ cbS;
	CheckBox^ cbR;
	CheckBox^ cbW;
	Label^ lblExpl;
	ProgressBar^ pb1;
	RichTextBox^ richTextBox;
	TabPage^ tp;
	TabPage^ tstart;
	TextBox^ txtOrigin;
	TextBox^ txtDest;
protected:
	void btnCopy_Click(Object^ pSender, EventArgs^ Args);
	void Close_Click(Object^ pSender, EventArgs^ Args);
	void btnOrigin_Click(Object^ pSender, EventArgs^ Args) {
		FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
		if (fbd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			txtOrigin->Text = fbd->SelectedPath;
		}
	}
	void btnDest_Click(Object^ pSender, EventArgs^ Args) {
		FolderBrowserDialog^ fbd = gcnew FolderBrowserDialog();
		if (fbd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			txtDest->Text = fbd->SelectedPath;
		}
	}
	void txtOrigin_DragEnter(Object^ pSender, DragEventArgs^ Args) {
		if(Args->Data->GetDataPresent(DataFormats::FileDrop)){
			Args->Effect = DragDropEffects::Copy;
		}
	}
	void txtOrigin_DragDrop(Object^ pSender, DragEventArgs^ Args) {
		array<String^>^ files = (array<String^>^)Args->Data->GetData(DataFormats::FileDrop);
		if (files->Length > 0) {
			txtOrigin->Text = files[0];
		}
	}
	void txtDest_DragEnter(Object^ pSender, DragEventArgs^ Args) {
		if (Args->Data->GetDataPresent(DataFormats::FileDrop)) {
			Args->Effect = DragDropEffects::Copy;
		}
	}
	void txtDest_DragDrop(Object^ pSender, DragEventArgs^ Args) {
		array<String^>^ files = (array<String^>^)Args->Data->GetData(DataFormats::FileDrop);
		if (files->Length > 0) {
			txtDest->Text = files[0];
		}
	}
	int CountFiles(String^ path) {
		try {
			array<String^>^ files = Directory::GetFiles(path, "*", SearchOption::AllDirectories);
			return files->Length;
		}
		catch (...) {
			return 0;
		}
	}
	void OnProcessExit(int exitCode);
	void IncrementProgress();
	void DoCopy(String^ origon, String^ destiny, String^ options);
	void AppendLine(String^ s);
	String^ Options() {
		String^ options = "";

		if (cbCpyAll->Checked) options += " /COPY:DATSO";
		if (cbMir->Checked) options += " /MIR";
		if (cbE->Checked) options += " /E";
		if (cbE->Checked) options += " /S";
		if (cbR->Checked) options += " /R:3";
		if (cbW->Checked) options += " /W:5";

		return options;
	}
};

