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
	image_list_.Create(16, 16, ILC_COLOR32 | ILC_MASK, 1, 1000);
}

CProcessDialog::~CProcessDialog()
{
}

void CProcessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, process_list_listctrl);
}


BEGIN_MESSAGE_MAP(CProcessDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProcessDialog::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &CProcessDialog::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CProcessDialog 메시지 처리기입니다.


void CProcessDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CProcessDialog::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CProcessDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CProcessList *process_list = object_manager_->GetProcessListInstance();

	process_list->ProcessListPrint(image_list_, process_list_listctrl, process_list);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
