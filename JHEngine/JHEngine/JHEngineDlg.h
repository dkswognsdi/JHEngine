
// JHEngineDlg.h : ��� ����
//

#pragma once
#include "afxext.h"
#include "object_manager\object_manager.hpp"
#include "afxwin.h"
#include "afxbutton.h"
#include "afxcmn.h"

// CJHEngineDlg ��ȭ ����
class CJHEngineDlg : public CDialogEx
{
private:
	std::shared_ptr<ObjectManager> object_manager_;
// �����Դϴ�.
public:
	CJHEngineDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JHENGINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//CBitmapButton bitmapbtn1_;
	CStatic process_text_;
	CMFCButton open_process_btn_;
	afx_msg void OnBnClickedOpenprocessbtn();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedButton1();
	CListCtrl scan_result_list_;
	afx_msg void GetDistInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
};
