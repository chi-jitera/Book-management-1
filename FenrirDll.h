// FenrirDll.h : FenrirDll.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��



struct cResultFile {
	int		m_num;
	string	m_data;

	cResultFile( const int &num, const string &data ) {
		m_num	= num;
		m_data	= data;
	}
	cResultFile( const cResultFile &obj ) {
		m_num	= obj.m_num;
		m_data	= obj.m_data;
	}
	cResultFile& operator=( const cResultFile &obj ) {
		if( this == &obj ) return *this;

		m_num	= obj.m_num;
		m_data	= obj.m_data;

		return *this;
	}

      bool operator<( const cResultFile &obj ) { return m_num < obj.m_num; }
};



// FenrirDll
// ���̃N���X�̎����Ɋւ��Ă� CConvGDS.cpp ���Q�Ƃ��Ă��������B
//

class FenrirDll : public CWinApp {

	public :
		FenrirDll();
		~FenrirDll();

		cResultPrm	*m_rPrm; 
		cMeasurePrm *m_mPrm;
		cContourPrm	*m_cPrm;

		CadInfomation	*m_cInfo;
		cLSCalibration	*m_LScal;
		cToolMatching	*m_lineTMat;
		cToolMatching	*m_spaceTMat;
		cCalibration	*m_cal;

		cMilImage	*mil_img;

		vector< int > m_filterPrm;
		vector< string > m_filterName;



		// VB����
		string	*vpTable;
		string	*vpDetails;
		string	*vpContour;

		cImage		*img;
		cImage		*tmpImg;
		cImage		*cad;

		vector< f_vec > m_corner;

		vector< cResultFile > resultFile;


	// �I�[�o�[���C�h
	public :
		virtual BOOL InitInstance();
		int ExitInstance();

		DECLARE_MESSAGE_MAP()
};
