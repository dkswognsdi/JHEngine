#pragma once


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
};