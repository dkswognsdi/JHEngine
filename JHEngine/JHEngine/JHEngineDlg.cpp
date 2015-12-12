
// JHEngineDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "JHEngine.h"
#include "JHEngineDlg.h"
#include "afxdialogex.h"
#include "ProcessDialog.h"

#include "utils\jhengine_utils.hpp"
#include "thread_manager\thread_manager.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CJHEngineDlg 대화 상자



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
}

BEGIN_MESSAGE_MAP(CJHEngineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENPROCESSBTN, &CJHEngineDlg::OnBnClickedOpenprocessbtn)
	ON_BN_CLICKED(IDC_CHECK2, &CJHEngineDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK8, &CJHEngineDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_BUTTON1, &CJHEngineDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CJHEngineDlg 메시지 처리기

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

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CJHEngineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJHEngineDlg::OnBnClickedCheck8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJHEngineDlg::OnBnClickedButton1()
{
	MemoryScanStructure mem_scan_structure;
	ScanBufferMgr scan_buffer(new ScanBuffer[9]);

	scan_buffer.get()[0].scan_check = TRUE;
	scan_buffer.get()[0].scan_code = 0x12;
	scan_buffer.get()[1].scan_check = TRUE;
	scan_buffer.get()[1].scan_code = 0x34;
	scan_buffer.get()[2].scan_check = FALSE;
	scan_buffer.get()[3].scan_check = FALSE;
	scan_buffer.get()[4].scan_check = FALSE;
	scan_buffer.get()[5].scan_check = FALSE;
	scan_buffer.get()[6].scan_check = FALSE;
	scan_buffer.get()[7].scan_check = FALSE;
	scan_buffer.get()[8].scan_check = TRUE;
	scan_buffer.get()[8].scan_code = 00;


	std::vector<DWORD> scan_result_vec;

	mem_scan_structure.readonly_scan_check = TRUE;
	mem_scan_structure.readonly_x_scan_check = TRUE;
	mem_scan_structure.readwrite_scan_check = TRUE;
	mem_scan_structure.readwrite_x_scan_check = TRUE;
	mem_scan_structure.scan_end_address = 0x7FFE0000;
	mem_scan_structure.scan_start_address = 0;
	mem_scan_structure.writecopy_scan_check = TRUE;
	mem_scan_structure.writecopy_x_scan_check = TRUE;

	MemoryScanner *mem_scan_instance = object_manager_->GetMemoryScannerInstance();
	std::function<BOOL(ProcessManager *, MemoryScanStructure &, ScanBufferPtr, unsigned long)> thread_proc
		(
		std::bind(&MemoryScanner::FirstScan, mem_scan_instance
		, std::placeholders::_1
		, std::placeholders::_2
		, std::placeholders::_3
		, std::placeholders::_4
		)
		);

	ThreadManager<std::function<BOOL(ProcessManager *, MemoryScanStructure &, ScanBufferPtr, unsigned long)>
		, ProcessManager *, MemoryScanStructure &, ScanBufferPtr, unsigned long>
		thread_mgr(thread_proc,
		object_manager_->GetProcessManagerInstance(),
		mem_scan_structure,
		scan_buffer.get(),
		9);

	for (DWORD i = 0; i < scan_result_vec.size(); i++)
	{
		wchar_t str_buffer[MAX_PATH]; 
		StringCbPrintfW(str_buffer, sizeof(str_buffer), L"%08X", scan_result_vec[i]);
		scan_result_list_.InsertItem(i, str_buffer);
	}
}
