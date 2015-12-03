// ProcessDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "JHEngine.h"
#include "ProcessDialog.h"
#include "afxdialogex.h"

#include "object_manager\object_manager.hpp"
#include "utils\jhengine_utils.hpp"

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
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CProcessDialog::OnLvnItemchangedList1)
//	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CProcessDialog::OnClickList1)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CProcessDialog::OnDblclkList1)
END_MESSAGE_MAP()


// CProcessDialog �޽��� ó�����Դϴ�.


void CProcessDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	POSITION pos;
	
	pos = process_list_listctrl.GetFirstSelectedItemPosition();
	if (!pos)
	{
		MessageBoxW(L"no process selected");
		return;
	}

	while (pos)
	{
		int list_num = process_list_listctrl.GetNextSelectedItem(pos);
		ProcessListStructure &pls = object_manager_->GetProcessListInstance()->GetStructure()[list_num];
		object_manager_->GetProcessManagerInstance()->Open(&pls);
		break;
	}
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

void CProcessDialog::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{	
		ProcessListStructure &pls = object_manager_->GetProcessListInstance()->GetStructure()[pNMItemActivate->iItem];
		object_manager_->GetProcessManagerInstance()->Open(&pls);
	}
	*pResult = 0;
	this->EndDialog(0);
}
