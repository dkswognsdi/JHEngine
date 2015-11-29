// ProcessDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JHEngine.h"
#include "ProcessDialog.h"
#include "afxdialogex.h"

#include "object_manager\object_manager.hpp"

// CProcessDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CProcessDialog, CDialogEx)

CProcessDialog::CProcessDialog(ObjectManager *object_manager, CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessDialog::IDD, pParent)
{
	object_manager_ = object_manager;
	CProcessList *process_list = object_manager_->GetProcessListInstance();
	if (process_list->GetProcessList() == ERROR_SUCCESS)
	{
		ProcessListStructure *process_list_structure = process_list->GetStructure();
		int process_num = process_list->GetSize();
	}
}

CProcessDialog::~CProcessDialog()
{
}

void CProcessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProcessDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProcessDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CProcessDialog �޽��� ó�����Դϴ�.


void CProcessDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
