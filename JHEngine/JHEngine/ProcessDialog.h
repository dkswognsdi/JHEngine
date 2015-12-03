#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CProcessDialog 대화 상자입니다.

class CProcessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessDialog)
private:
	ObjectManager *object_manager_;

public:
	CProcessDialog(ObjectManager *object_manager, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CProcessDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ProcessDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
