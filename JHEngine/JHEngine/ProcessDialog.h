#pragma once


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
};
