// ProcessDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JHEngine.h"
#include "ProcessDialog.h"
#include "afxdialogex.h"

#include "object_manager\object_manager.hpp"

// CProcessDialog 대화 상자입니다.

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


// CProcessDialog 메시지 처리기입니다.


void CProcessDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
