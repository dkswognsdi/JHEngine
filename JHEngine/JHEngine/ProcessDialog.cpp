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


// CProcessDialog �޽��� ó�����Դϴ�.


void CProcessDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void CProcessDialog::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CProcessDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CProcessList *process_list = object_manager_->GetProcessListInstance();

	process_list->ProcessListPrint(image_list_, process_list_listctrl, process_list);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
