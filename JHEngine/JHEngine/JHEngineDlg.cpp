
// JHEngineDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "JHEngine.h"
#include "JHEngineDlg.h"
#include "afxdialogex.h"
#include "ProcessDialog.h"

#include "utils\jhengine_utils.hpp"
#include "JHEngine\thread_manager\worker_manager.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJHEngineDlg ��ȭ ����



CJHEngineDlg::CJHEngineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJHEngineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	object_manager_ = std::make_shared<ObjectManager>();
}

void CJHEngineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDOK, bitmapbtn1_);
	DDX_Control(pDX, IDC_ProcessText, process_text_);
	DDX_Control(pDX, IDC_OPENPROCESSBTN, open_process_btn_);
	DDX_Control(pDX, ScanResultListView, scan_result_list_);
	DDX_Control(pDX, ScanResultCountLabel, scan_result_count_label_);
	DDX_Control(pDX, IDC_EDIT1, scan_find_edit_);
}

BEGIN_MESSAGE_MAP(CJHEngineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENPROCESSBTN, &CJHEngineDlg::OnBnClickedOpenprocessbtn)
	ON_BN_CLICKED(IDC_CHECK2, &CJHEngineDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK8, &CJHEngineDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_BUTTON1, &CJHEngineDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_GETDISPINFO, ScanResultListView, &CJHEngineDlg::GetDistInfo)
	ON_BN_CLICKED(IDC_BUTTON2, &CJHEngineDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CJHEngineDlg �޽��� ó����

BOOL CJHEngineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	open_process_btn_.SetImage(OpenProcessBitmap);
	open_process_btn_.SetWindowTextW(L"");

	LV_COLUMN col;

	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;

	col.pszText = L"Address";
	col.iSubItem = 0;
	col.cx = 90;
	scan_result_list_.InsertColumn(0, &col);
	col.pszText = L"CurVal";
	scan_result_list_.InsertColumn(1, &col);
	col.pszText = L"CurVal2";
	scan_result_list_.InsertColumn(2, &col);
	return TRUE;
}

void CJHEngineDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CJHEngineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CJHEngineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJHEngineDlg::OnBnClickedOpenprocessbtn()
{
	CProcessDialog process_dialog(object_manager_.get());
	process_dialog.DoModal();
	if (!object_manager_->GetProcessManagerInstance()->IsOpened())
	{
		ProcessListStructure *pls = object_manager_->GetProcessManagerInstance()->GetProcessListStructure();
		if (pls)
			JHEngineUtils::ErrorMsg(L"%08X-%ls Open Fail", pls->pid, pls->process_name.c_str());
	}
	else
	{
		ProcessListStructure *pls = object_manager_->GetProcessManagerInstance()->GetProcessListStructure();
		wchar_t proc_msg[MAX_PATH];
		StringCbPrintfW(proc_msg, sizeof(proc_msg), L"%08X-%ls", pls->pid, pls->process_name.c_str());
		process_text_.SetWindowTextW(proc_msg);
	}
}


void CJHEngineDlg::OnBnClickedCheck2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CJHEngineDlg::OnBnClickedCheck8()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CJHEngineDlg::OnBnClickedButton1()
{
	MemoryScanStructure mem_scan_structure;
	int size = 0;
	ScanBufferMgr scan_buffer(new ScanBuffer[size]);

	mem_scan_structure.readonly_scan_check = TRUE;
	mem_scan_structure.readonly_x_scan_check = TRUE;
	mem_scan_structure.readwrite_scan_check = TRUE;
	mem_scan_structure.readwrite_x_scan_check = TRUE;
	mem_scan_structure.scan_end_address = 0x7FFE0000;
	mem_scan_structure.scan_start_address = 0;
	mem_scan_structure.writecopy_scan_check = TRUE;
	mem_scan_structure.writecopy_x_scan_check = TRUE;

	object_manager_->GetMemoryScannerInstance()->FirstScan(object_manager_->GetProcessManagerInstance()
		, mem_scan_structure
		, scan_buffer.get()
		, size
		, scan_result_list_
		, scan_result_count_label_);
}


void CJHEngineDlg::GetDistInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	int nItem = pItem->iItem;

	*pResult = 0;
	MemoryScanner::ScanResultVec scv = object_manager_->GetMemoryScannerInstance()->GetScanResult();


	if (pItem->mask & LVIF_TEXT)
	{
		switch (pItem->iSubItem)
		{
		case 0:
		{
				  boost::wformat addr_format(L"%08X");
				  addr_format % scv[nItem];
				  lstrcpyn(pItem->pszText, addr_format.str().c_str(), pItem->cchTextMax);
				  break;
		}
		case 1:
		{
			boost::wformat addr_format(L"%08d");
			addr_format % nItem;
			lstrcpyn(pItem->pszText, addr_format.str().c_str(), pItem->cchTextMax);
			break;
		}
		}
	}
}


void CJHEngineDlg::OnBnClickedButton2()
{
	object_manager_->GetMemoryScannerInstance()->ScanResultClear(scan_result_list_);
}
