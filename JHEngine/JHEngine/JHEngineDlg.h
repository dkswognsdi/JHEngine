
// JHEngineDlg.h : ��� ����
//

#pragma once
#include "afxext.h"
#include "object_manager\object_manager.hpp"
#include "afxwin.h"

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
};
