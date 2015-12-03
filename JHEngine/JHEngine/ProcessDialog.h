#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CProcessDialog ��ȭ �����Դϴ�.

class CProcessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessDialog)
private:
	ObjectManager *object_manager_;

public:
	CProcessDialog(ObjectManager *object_manager, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CProcessDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ProcessDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	CListCtrl process_list_listctrl;
	CImageList image_list_;
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
