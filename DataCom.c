
// ��񑗐M�uRX210 �� CM3�v
// �ėp���C�u����
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
// RX210�Ǝ����C�u����
#include "RX210.h"
#include "typedefine.h"
#include "iodefine.h"
// �I���W�i�����C�u����
#include "MyDefine.h"
#include "DataCom.h"
#include "RTC.h"
#include "common.h"
#include "InSig.h"//��
#include "OutSig.h"
#include "LockUnit.h"	// ۯ��Ư�
#include "InternalUnit.h"
#include "common.h"	// ����ٰ��


//#define DEBUG_DATACOM_ERR

// ��`
/*enum {	DATA_NONE = 0,	DATA_NG,	// ���ʺ����
	DATA_OK_DT,	DATA_NG_DT,	// ���t���̑������
	DATA_OK_O1,	DATA_NG_O1,	// �ėp�o��(�P������)�����
	DATA_OK_O2,	DATA_NG_O2,	// �ėp�o��(���葀��)�����
	DATA_NG_LU,	DATA_SP_LU,	DATA_PL_LU,	DATA_PS_LU,		// ۯ��Ưĺ����
	DATA_OK_LOG,DATA_NG_LOG							// �T�u�v�� ���O�o�̓R�}���h
	};
*/
enum {					// �f�[�^���
	KIND_SYSTEM,		// �V�X�e�����	
	KIND_INPUT,			// ���̓|�[�g���
	KIND_OUTPUT,		// �o�̓|�[�g���
	KIND_UNIT,			// �������j�b�g���
	KIND_LOCK,			// ���b�N���j�b�g���
	KIND_GATE,			// �Q�[�g���
	KIND_LOG = 0xE0,	// �T�u�v�� ���O���
	KIND_DMP,			// �T�u�v�� �ُ탊�Z�b�g���
	KIND_ERR = 0xFF,	// �f�[�^�ُ�(CRC�ُ�)
};
enum {
	CMD_NONE = 0,		// ��M�����A����
	CMD_ERR,			// ��M�R�}���h�ُ�
	CMD_RETRY,			// �R�}���h�đ�
	CMD_SYS_DATE,		// �V�X�e�� �������擾
	CMD_SYS_INFO,		// �V�X�e��	�V�X�e�����擾
	CMD_IN_STATUS,		// ���̓|�[�g ���͏�Ԏ擾
	CMD_IN_SETTING,		// ���̓|�[�g �`���^�����O�z���ݒ�
	CMD_OUT_STATUS,		// �o�̓|�[�g �o�͏�Ԏ擾
	CMD_UNIT,
	CMD_LOCK_NG,		// ���b�N���j�b�g�R�}���hNG
	CMD_LOCK_SP,		// ���b�N���j�b�g���� �T�u�v�����
	CMD_LOCK_PL,		// ���b�N���j�b�g�|�[�����O
	CMD_LOCK_PS,		// ���b�N���j�b�g�p�[�L���O�X�e�[�^�X
	CMD_LOG_DATA,		// ���O���擾
	CMD_DMP_DATA,		// �ُ탊�Z�b�g���擾
};

// �\����
struct DataTx
{
	_UBYTE bData;	//�e�X�g�p
};

// �ϐ�
struct DataTx DataTx;
volatile struct DataComIr DataComIr;
struct TxLogType TxLog;
struct LogBfType LogBfTx;
char chLogWork[LOG_LENGTH * LOG_CNT];
WORD wHubAutoScan = 0;

// �v���g�^�C�v�錾
char ChkDataCom(void);

void DataComCmdMake(char chCmd);
//char *SetExSw(char *chp);
char *SetMatrixInInfo(char *chp);
char *SetMatrixInSettingInfo(char *chp);
char *SetGPInSettingInfo(char *chp);
//char *SetExIn(char *chp);
char *SetGPInInfo(char *chp);
char *SetVoltageInfo(char *chp,float flVoltage);
void StartDataComTx(void);
char *SetUserSens(char *chp);

// �֐�
void InitDataCom(void)
{		// ������
	memset(&DataTx, 0, sizeof(DataTx));
	memset((struct DataComIr *)&DataComIr, 0, sizeof(DataComIr));
	memset(&TxLog,0,sizeof(TxLog));
	memset(&LogBfTx,0,sizeof(LogBfTx));
	DataComIr.chProc = RX_BUSY;
	RE_SCI5();	// ��M�����݋���
}

void MainDataCom(void)
{		// �ް����MҲݏ���
	char ch = CMD_NONE;	// �Y�����Ȃ��ꍇ��"CMD_NONE"
	
	ClrWDT();	// �����ޯ����϶����ر
	
	switch (DataComIr.chProc)
	{
		case RX_OK:	// ��M�ς�
			ch = ChkDataCom();	// ��M�ް��̉��
			if(DataComIr.chCmd == CMD_LOG_DATA && ch != CMD_LOG_DATA){
				memset(&LogBfTx,0,sizeof(LogBfTx));
			}
			switch (ch)
			{
/*				case DATA_OK_DT:	// ���t���̑�OK
				case DATA_NG_DT:	// ���t���̑�NG
				case DATA_OK_O1:	// �ėp�o��(�P������)OK
				case DATA_NG_O1:	// �ėp�o��(�P������)NG
				case DATA_OK_O2:	// �ėp�o��(���蓮��)OK
				case DATA_NG_O2:	// �ėp�o��(���蓮��)NG
				case DATA_NG_LU:	// ۯ��Ư�NG
				case DATA_SP_LU:	// ۯ��ƯĻ�����
				case DATA_PL_LU:	// ۯ��Ư��߰�ݸ
				case DATA_PS_LU:	// ۯ��Ư�PS
				case DATA_OK_LOG:	// ���O�₢���킹
				//case DATA_NG_LOG:
*/
				case CMD_SYS_DATE:				// �V�X�e���������
				case CMD_SYS_INFO:				// �V�X�e�����
				case CMD_IN_STATUS:				// ���̓|�[�g���
				case CMD_IN_SETTING:			// ���̓|�[�g�ݒ�(�`���^�����O�z������)
				case CMD_OUT_STATUS:			// �o�̓|�[�g���
				case CMD_UNIT:					// �������j�b�g���
				case CMD_LOCK_SP:				// ���b�N���j�b�g����T�u�v�����
				case CMD_LOCK_PL:				// ���b�N���j�b�g�|�[�����O
				case CMD_LOCK_PS:				// ���b�N���j�b�gPS
				case CMD_LOG_DATA:				// �T�u�v�� ���O���
				case CMD_DMP_DATA:				// �T�u�v�� �R�A�_���v���(�Ӑ}���Ȃ����Z�b�g���)
					DataComIr.chProc = TX_STANDBY;
					DataComIr.chCmd = ch;
					break;
				case CMD_RETRY:					// �O��R�}���h�đ�
					DataComIr.chProc = TX_STANDBY;
					break;
				case CMD_ERR:					// ��M�R�}���h�ُ�
					DataComIr.chProc = TX_STANDBY;
					DataComIr.chCmd = CMD_ERR;
					break;
				case CMD_NONE:
				default: 
					DataComIr.chProc = RX_BUSY;
					break;
			} // end switch
			memset((char *)&DataComIr.chRx[0],0,sizeof(DataComIr.chRx));
			break;
		
		case TX_STANDBY:	// ���M�҂�
			ch = DataComIr.chCmd;
			
			if (ch != CMD_NONE)
			{
				DataComCmdMake(ch);
				StartDataComTx();
			} // end if
			
			break;
		
		default:
			break;
	} // end switch
}

char ChkDataCom(void)
{		// ��M�ް��̉��
	char chRes = CMD_NONE;	// �Y�����Ȃ��ꍇ��"DATA_NONE"
	WORD wKind = 0;	// ���
	WORD wLen  = 0;	// �ް���
	WORD wParam = 0xFFFF;
	WORD wCmd  = 0;	// �����
	WORD wCrc,wRxCrc;
	char ch = 0;	// �ėp�ϐ�(char)
	long l  = 0;	// �ėp�ϐ�(long)
	char *chp = (char *)&DataComIr.chRx[5];
	
	ch = DataComIr.chRx[0];	// �擪�������o
	
	if (ch != ETX && ch != STX)
	{
//		chRes = DATA_NG;	// ����M�Ŗ����J�n�����ł��Ȃ��ꍇ
		chRes = CMD_NONE;	// �擪�f�[�^�����܂��̓S�~�f�[�^�͖���
	}
	else
	{
		l = CheckCrc((char *)&DataComIr.chRx, 1, (long)sizeof(DataComIr.chRx));	// CRC����
		
		if (l >= 0)	// CRC��v
		{
			if (DataComIr.chRx[1] == 'M' && DataComIr.chRx[2] == '1' && DataComIr.chRx[3] == '2' && DataComIr.chRx[4] == '2')
			{	// ��Mͯ�ޕ�OK
				chp = HexAsciiToWord(chp, 2, &wKind);	// ���
				chp = DecAsciiToWord(chp, 3, &wLen);	// �ް���
				l = GetDataLength((char *)&DataComIr.chRx , 10, (long)sizeof(DataComIr.chRx)); // �ް����̎�����Z�o
/*				
				if (wLen == 1)	// �ް�����1�޲Ă̏ꍇ
				{
					switch (*chp)
					{
						case '0':	// ��M����
							switch (DataComIr.chCmd)
							{
								case DATA_PL_LU:	// ���߂��߰�ݸޗv���̏ꍇ
									PostLockUnitRequestPL(DataComIr.wParam);
									break;
								
								default:		// ���̑��͉������Ȃ�
									break;
							} // ens switch
							
							DataComIr.chCmd  = DATA_NONE;	// ����ޏ�����
							DataComIr.wParam = 0;		// ���Ұ�������
							break;
						
						case '1':	// �đ��v��
							chRes = DataComIr.chCmd;	// ��������ނ��ľ��
							break;
							
					} // end switch
					
				}
				else */if (l == (long)wLen) // �f�[�^���`�F�b�N
				{
					switch (wKind)
					{
						case KIND_SYSTEM:		// �V�X�e�����
							chp = DecAsciiToWord(chp, 4, (WORD *)&wParam);	// ��ʃp�����[�^��M
							switch(wParam){
								case 0:		chRes = CMD_SYS_DATE;	break;
								case 1:		chRes = CMD_SYS_INFO;	break;
								default:	chRes = CMD_ERR;		break; 
							}
							break;
						case KIND_INPUT: 		// ���̓|�[�g���
							chp = DecAsciiToWord(chp, 4, (WORD *)&wParam);	// ��ʃp�����[�^��M
							switch(wParam){
								case 0:		chRes = CMD_IN_STATUS;	break;
								case 1:		chRes = CMD_IN_SETTING;	break;
								default:	chRes = CMD_ERR;		break;
							}
							break;
						case KIND_OUTPUT: 		// �o�̓|�[�g���
							chp = DecAsciiToWord(chp, 4, (WORD *)&wParam);	// ��ʃp�����[�^��M
							switch(wParam){
								case 0:		chRes = CMD_OUT_STATUS;	break;
								default:	chRes = CMD_ERR;		break;
							}
							break;
						case KIND_UNIT:			// �������j�b�g���
							chp = DataComRxInternalUnit(chp);
							chRes = CMD_UNIT;
							break;
						case KIND_LOCK: // ۯ��Ư�
							if(wLen == 0)
							{
								switch (DataComIr.chCmd)
								{
									case CMD_LOCK_PL:	// ���߂��߰�ݸޗv���̏ꍇ
										PostLockUnitRequestPL(DataComIr.wParam);
										break;
									
									default:		// ���̑��͉������Ȃ�
										break;
								} // ens switch
								
								DataComIr.chCmd  = CMD_NONE;	// ����ޏ�����
								DataComIr.wParam = 0;		// ���Ұ�������
							}
							else
							{
								chp = DecAsciiToWord(chp, 2, &wCmd);	// �����
								switch (wCmd)
								{
									case 0:	// �����0
										//chRes = DATA_SP_LU;	// �����ۏ�ԗv����M
										chRes = CMD_LOCK_SP;
										break;
									
									case 1:	// �����1
										//chRes = DATA_PL_LU;	// �߰�ݸޗv����M(�Ư���ۯ��ԍ�)
										chRes = CMD_LOCK_PL;
										chp = DecAsciiToWord(chp, 2, (WORD *)&wParam);
										break;
									
									case 2:	// �����2
										//chRes = DATA_PS_LU;	// PS�v����M(�Ưı��ڽ�ԍ�)
										chRes = CMD_LOCK_PS;
										chp = DecAsciiToWord(chp, 3, (WORD *)&wParam);
										break;
									
									default:
										//chRes = DATA_NG_LU;	// �s����ۯ��Ưĺ����
										chRes = CMD_LOCK_NG;
										break;
								} // end switch
							
							}
								
							break;
						case KIND_LOG:	// ���O�擾
							chRes = CMD_LOG_DATA;
							break;
						case KIND_DMP:
							chRes = CMD_DMP_DATA;
						case KIND_ERR:
							chRes = CMD_RETRY;
							break;
						default:
							//chRes = DATA_NG;	// ��ʂ�����Ȃ�
							chRes = CMD_ERR;
#ifdef DEBUG_DATACOM_ERR
	Debug("�f�[�^��ʈُ팟�o\r\n");
#endif
							break;
					} // end switch

					if(chRes != CMD_ERR && chRes != CMD_RETRY){
						DataComIr.wKind = wKind;
						DataComIr.wParam = wParam;
					}

				}
				else	// �ް���������Ȃ�
				{
					/*switch (wKind)
					{
						case 0: // ���t���̑�(��
							chRes = DATA_NG_DT;
							break;
						
						case 1: // �ėp�o��(�P������)
							chRes = DATA_NG_O1;
							break;
						
						case 2: // �ėp�o��(���蓮��)
							chRes = DATA_NG_O2;
							break;
						
						case 3: // ۯ��Ư�
							chRes = DATA_NG_LU;
							break;
						
						default:
							chRes = DATA_NG;	// ��ʂ�����Ȃ�
							break;
					} // end switch	
					*/
					chRes = CMD_ERR;
#ifdef DEBUG_DATACOM_ERR
	Debug("�f�[�^���ُ팟�o\r\n");
#endif				
				} // end if
			}
			else
			{
				//chRes = DATA_NG;	// ͯ�ް������Ȃ�
				chRes = CMD_ERR;
#ifdef DEBUG_DATACOM_ERR
	Debug("�w�b�_�[�ُ팟�o\r\n");
#endif
			} // end if
		}
		else
		{
			//chRes = DATA_NG;	// CRC������Ȃ�
			chRes = CMD_ERR;
#ifdef DEBUG_DATACOM_ERR
	Debug("CRC�ُ팟�o\r\n");
#endif
		} // end if
	} // end if
	
	return chRes;
}

void DataComCmdMake(char chCmd)
{		// �ް��̑��M
	char ch = 0;	// �ėp�ϐ�(char)
	WORD w  = 0;	// �ėp�ϐ�(WORD)
	char *chp = (char *)DataComIr.chTx;
	struct Time TimeTmp;
	
	memset((void *)DataComIr.chTx,0x00,sizeof(DataComIr.chTx));//sanodebug
	chp += sprintf(chp, "%cS212", STX);	// ͯ�ް
	
	switch (chCmd)
	{
		case CMD_SYS_DATE:			// ����
			chp += sprintf(chp,"%02X",KIND_SYSTEM);		// �f�[�^���(�V�X�e��)
			chp += sprintf(chp,"%03d",18);				// �f�[�^��
			chp += sprintf(chp,"%04d",DataComIr.wParam);// �p�����[�^
			TimeTmp = RtcRead(0);  // RTC�ǂݍ���
			chp += sprintf(chp, "%04d%02d%02d%02d%02d%02d", TimeTmp.shYear,TimeTmp.chMonth,TimeTmp.chDay,TimeTmp.chHour,TimeTmp.chMin,TimeTmp.chSec);
			break;
		case CMD_SYS_INFO:
			chp += sprintf(chp,"%02X",KIND_SYSTEM);		// �f�[�^���(�V�X�e��)
			chp += sprintf(chp,"%03d",68);				// �f�[�^��
			chp += sprintf(chp,"%04d",DataComIr.wParam);// �p�����[�^
			chp += sprintf(chp,"%d",GetShutDownReq());	// �V���b�g�_�E���v��
			chp += sprintf(chp, "%03d%03d%03d%08X", VER, VER_DEC1, VER_DEC2,dwMyCheckSum);		// �\�t�g���
			for (ch = 0 ; ch < 46 ; ch++){				// �\��46�o�C�g '0'����
				*chp = '0';
				chp++;
			}
			break;
		case CMD_IN_STATUS:
			chp += sprintf(chp,"%02X",KIND_INPUT);		// �f�[�^���
			chp += sprintf(chp,"%03d",56);				// �f�[�^��
			chp += sprintf(chp,"%04d",DataComIr.wParam);// �p�����[�^
			chp += sprintf(chp,"%X",GetRotSw());		// ���[�^���X�C�b�`���
			chp += sprintf(chp,"%d",GetShutDownReq());	// �V���b�g�_�E���v��
			for (ch = 0 ; ch < 8 ; ch++){				// �I���{�[�h�@�\�\��8�o�C�g
				*chp = '0';
				chp++;
			}
			chp = SetVoltageInfo(chp,Get24V_Avg());		// 24V�d���d��
			chp = SetVoltageInfo(chp,Get12VBat_Avg());	// 12V�o�b�e���[�d��
			chp = SetMatrixInInfo(chp);					// �}�g���N�X����
			chp = SetGPInInfo(chp);						// �ėp����	

			break;
		case CMD_IN_SETTING:
			chp += sprintf(chp,"%02X",KIND_INPUT);		// �f�[�^���
			chp += sprintf(chp,"%03d",204);				// �f�[�^�� 16�~4 + 
			chp += sprintf(chp,"%04d",DataComIr.wParam);// �p�����[�^
			chp = SetMatrixInSettingInfo(chp);				// �}�g���N�X���̓`���^�����O�z������
			chp = SetGPInSettingInfo(chp);					// �ėp���̓`���^�����O�z������
			break;
		case CMD_OUT_STATUS:
			chp += sprintf(chp,"%02X",KIND_OUTPUT);		// �f�[�^���
			
			if(DataComIr.wParam == 0){					// �S�o�̓|�[�g					
				chp += sprintf(chp,"%03d",48);			// �f�[�^�� 44
				chp += sprintf(chp,"%04d",DataComIr.wParam);
				for(ch = 1 ; ch < 45 ; ch++){
					chp += sprintf(chp,"%X",GetOutputStatus(ch));
				} 
			}else{										// ����o�̓|�[�g
				chp += sprintf(chp,"%03d",1);			// �f�[�^�� 1
				chp += sprintf(chp,"%04d",DataComIr.wParam);
				chp += sprintf(chp,"%X",GetOutputStatus(DataComIr.wParam));
			}
			break;
		case CMD_UNIT:
			chp += sprintf(chp,"%02X",KIND_UNIT);		// �f�[�^���
			chp += sprintf(chp,"%03d",GetDataComUnitTxDataLen());				// �f�[�^�� 0(�������j�b�g�Ȃ�) 
			chp = GetDataComUnitTxData(chp);
			break;
		/*
		case DATA_OK_DT:	// ���t���̑�OK����
			chp += sprintf(chp, "00");	// ���
			
			switch (DataComIr.wParam)
			{
				case 0:	// ����
					chp += sprintf(chp, "%03d", 19); // �f�[�^��
					chp += sprintf(chp, "%d", 0); // ����
					chp += sprintf(chp, "%04d", DataComIr.wParam);
					TimeTmp = RtcRead(0);  // RTC�ǂݍ���
					chp += sprintf(chp, "%04d%02d%02d%02d%02d%02d", TimeTmp.shYear,TimeTmp.chMonth,TimeTmp.chDay,TimeTmp.chHour,TimeTmp.chMin,TimeTmp.chSec);
					break;
				
				case 1: // ���̑�
					chp += sprintf(chp, "0690");	// �ް���(14 + 54)�A����(1) = 69
					chp += sprintf(chp, "%04d", DataComIr.wParam);
					chp += sprintf(chp, "%d", GetShutDownReq());
					chp += sprintf(chp, "%03d%03d%03d", VER, VER_DEC1, VER_DEC2);
					
					for (ch = 0; ch < 54; ch++)
					{
						chp += sprintf(chp, "0");
					} // end for
					
					break;
				
				default:
					break;
			} // end switch
			
			break;
		*/
//		case DATA_SP_LU:	// ۯ��ƯĻ����ۏ�ԉ���
		case CMD_LOCK_SP:
			chp += sprintf(chp, "04006000");	// ��ʁA�ް����A����
			if( LockUnitIr.chMode == 32 && wHubAutoScan > 0)
			{
				// Hub�d�l�̏ꍇ�͎����ڑ������O��fAutoScanPS��OFF�ƂȂ�ׁA�S�Ԏ��`�F�b�N��������܂ł�ON�Ɣ��肷��
				*chp = '1';
			}
			else
			{
				*chp = (char)GetAutoScanPS() + '0';	// �����ڑ����
			}
			chp++;
			*chp = GetCommSts();			// ۯ��ƯĒʐM���
			chp++;
			*chp = (char)GetInitSts() + '0';	// ���������
			chp++;
			break;
			
//		case DATA_PL_LU:	// ۯ��Ư��߰�ݸމ���
		case CMD_LOCK_PL:
			w  = GetPollingNotifyCount(DataComIr.wParam) * 10;	// 1�Ư��ް����޲Đ����|����
			w += 5;	// �Œ��޲Ă𑫂�
			chp += sprintf(chp, "04%03d001", w);	// ��ʁA�ް����A����A�����
			chp += sprintf(chp, "%02d", DataComIr.wParam);	// �Ư���ۯ��ԍ�
			chp  = SetLockUnitRequestPL(chp, DataComIr.wParam);	// �߰�ݸމ���
			break;
		
//		case DATA_PS_LU:	// ۯ��Ư�PS����
		case CMD_LOCK_PS:
			chp += sprintf(chp, "04034002", w);	// ��ʁA�ް����A����A�����
			chp += sprintf(chp, "%03d", DataComIr.wParam);	// �ƯĔԍ�
			chp  = SetLockUnitRequestPS(chp, DataComIr.wParam);	//PS����
			break;
//		case DATA_OK_LOG:
		case CMD_LOG_DATA:
			ch = 1;
			if(LogBfTx.LogTime.shYear == 0 && LogBfTx.LogTime.chMonth == 0 && LogBfTx.LogTime.chDay == 0)
			{//���M�p�̃��O�f�[�^����Ȃ�
				if(TxLog.shCnt > 0)
				{
					LogBfTx = GetTxLog();	// ���O�o�b�t�@����o�͗p�f�[�^���擾
					if(LogBfTx.LogTime.shYear != 0 || LogBfTx.LogTime.chMonth != 0 || LogBfTx.LogTime.chDay != 0)
					{// �擾�f�[�^����Ȃ�
						ch = 1;
						DeleteTxLog();	// ���O�o�b�t�@����o�͗p�f�[�^���폜����
					}else{
						ch = 0;
					}
				}
				else
				{
					ch = 0;
				}
			}

			if(ch == 1)
			{ // ���M���郍�O�f�[�^����
				chp += sprintf(chp,"E0%03d",GetTxLogLength(LogBfTx));
				chp = SetTxLogString(chp,LogBfTx);
			}
			else
			{
				chp += sprintf(chp, "E0000");	// ���(E0h)�A�f�[�^��(0)
			}

			

			break;
		//case DATA_NG_LOG:
		//	break;
		case CMD_DMP_DATA:
			chp += sprintf(chp,"%02X",KIND_DMP);
//		case DATA_NG:		// �s���Ȏ�M
		case CMD_ERR:
		default:
#ifdef DEBUG_DATACOM_ERR
	Debug("�ُ퉞���R�}���h����\r\n");
#endif
			//chp += sprintf(chp, "FF0011");	// ��ʁA�ް����A�ُ�
			chp += sprintf(chp,"%02X",KIND_ERR);
			chp += sprintf(chp,"%03d",0);
			break;
	} // end switch
	
	*chp = ETX;
	chp++;
	chp += sprintf(chp, "%04X", GetCrc((char *)DataComIr.chTx, 1, (long)sizeof(DataComIr.chTx)));	// �Œ�J�n�ʒu��CRC�쐬
	*chp = EOD;
	chp++;
	*chp = '\0';
}

//char *SetExSw(char *chp)
char *SetMatrixInInfo(char *chp)
{		// �}�g���N�X���͓d���쐬
	char chScan,chSens;
	BYTE bInfo;
	for (chScan = 0; chScan < 16; chScan++)
	{
		ClrWDT();
		bInfo = 0;
		for (chSens = 3; chSens >= 0; chSens--)
		{
			bInfo = (bInfo << 1) + GetMatrixIn(chScan, chSens);
		}

		chp += sprintf(chp,"%X",(bInfo & 0x0F));
	}
	return chp;
}

//char *SetExIn(char *chp)
char *SetGPInInfo(char *chp)
{		// �ėp���͓d���쐬
	char ch;
	
	for (ch = 0; ch < 18; ch++)
	{
//		*chp = GetExIn(ch) + 0x30;
		*chp = GetGPIn(ch) + 0x30;
		chp++;
	}
	return chp;
}

// �d�����d���쐬
char *SetVoltageInfo(char *chp,float flVoltage)
{
	chp += sprintf(chp,"%02d",(short)flVoltage);		// ������
	chp += sprintf(chp,"%02d",(short)((flVoltage - (short)flVoltage) * 100));	// ������(���2��)
	return chp;
}

// �}�g���N�X���͐ݒ��� �d���쐬
char *SetMatrixInSettingInfo(char *chp)
{
	char chScan,chSens;
	for(chScan = 0 ; chScan < 16 ; chScan++){
		ClrWDT();
		for(chSens = 0 ; chSens < 4; chSens++){
			chp += sprintf(chp,"%02X",(BYTE)GetMatrixInChatTime(chScan,chSens));
		}
	}
	return chp;
}

// �ėp���͐ݒ��� �d���쐬
char *SetGPInSettingInfo(char *chp)
{
	char chNum;
	for(chNum = 0 ; chNum < 18 ; chNum++){
		ClrWDT();
		chp += sprintf(chp,"%04X",GetGPInChatTime(chNum));
		
	}
	return chp;
}

void StartDataComTx(void)
{
	DataComIr.chProc = TX_BUSY;
	DataComIr.shTxPos = 0;
	TE_SCI5(); // ���M�����݋���
}
// ############################################# �O���Ăяo���֐� ##################################################
short GetTxLogCount(void)
{
	return TxLog.shCnt;
}
void SetTxLog(const char *chpFormat,...)
{
	va_list args;
//	char chBf[256];
	struct LogBfType BfTmp;
	struct Time TimeTmp;
	long l,lCnt;
	BYTE bScrHold;
	
	memset(&chLogWork[0],0,sizeof(chLogWork));

	va_start(args, chpFormat);
	lCnt = (long)vsprintf(&chLogWork[0], chpFormat, args);
	va_end(args);

	memset(&BfTmp,0,sizeof(BfTmp));
	TimeTmp = RtcRead(FALSE);
	BfTmp.LogTime.shYear = TimeTmp.shYear;
	BfTmp.LogTime.chMonth = TimeTmp.chMonth;
	BfTmp.LogTime.chDay = TimeTmp.chDay;
	BfTmp.LogTime.chHour = TimeTmp.chHour;
	BfTmp.LogTime.chMin = TimeTmp.chMin;
	BfTmp.LogTime.chSec = TimeTmp.chSec;
	BfTmp.LogTime.sh1ms = Rtc1msRead();
	l = 0;
	if(lCnt > LOG_LENGTH){					// ���O1�����̃f�[�^���𒴂���ꍇ�A�������ɕ���
		
		while(lCnt > LOG_LENGTH){
			memcpy(&BfTmp.chLogBf[0],&chLogWork[l],(size_t)LOG_LENGTH);
			SaveTxLog(BfTmp);
			lCnt -= LOG_LENGTH;
			l += LOG_LENGTH;
		}
		
	}
	memcpy(&BfTmp.chLogBf[0],&chLogWork[l],(size_t)lCnt);
	SaveTxLog(BfTmp);
	
}
struct LogBfType GetTxLog(void)
{
	struct LogBfType LogBf;
	memset(&LogBf,0,sizeof(LogBf));
	
	if(TxLog.shCnt > 0){
		LogBf = TxLog.LogBf[TxLog.shOutPos];
	}

	return LogBf;

}
WORD GetTxLogLength(struct LogBfType LogBf)
{
	WORD w;
	w = 0;
	ClrWDT();
	while(LogBf.chLogBf[w] != 0 && w <LOG_LENGTH){
		w++;
	}

	if(w > 0)	w += 29;	// SetTxLogString�Ő����������������񕪂����Z 

	return w;
}
char *SetTxLogString(char *chpBf,struct LogBfType LogBf)
{
	short sh;

	if(LogBf.LogTime.shYear == 0 && LogBf.LogTime.chMonth == 0 && LogBf.LogTime.chDay == 0)
		return chpBf;

	// ���O���������𕶎���
	chpBf += sprintf(chpBf,"%04d/%02d/%02d %02d:%02d:%02d.%03d,[%02d],",LogBf.LogTime.shYear,		// �N
																		LogBf.LogTime.chMonth,		// ��
																		LogBf.LogTime.chDay,		// ��
																		LogBf.LogTime.chHour,		// ��
																		LogBf.LogTime.chMin,		// ��
																		LogBf.LogTime.chSec,		// �b
																		LogBf.LogTime.sh1ms,		// �^���~���b
																		LogBf.bSerial);				// �ʂ��ԍ�
	
	// ���O�f�[�^
	sh = 0;
	ClrWDT();
	while(LogBf.chLogBf[sh] != 0 && sh <LOG_LENGTH){
		*chpBf = LogBf.chLogBf[sh];
		chpBf++;
		sh++;
	}
	return chpBf;
}

void SaveTxLog(struct LogBfType BfTmp)
{
	struct LogBfTye *pLogBf;
	
	ClrWDT();	// �����ޯ����϶����ر
	
	if(TxLog.shCnt >= LOG_CNT){
		DeleteTxLog();
	}
	BfTmp.bSerial = TxLog.bSerial;
	TxLog.LogBf[TxLog.shInPos] = BfTmp;
	
	TxLog.shCnt++;
	TxLog.shInPos++;
	if(TxLog.shInPos >= LOG_CNT){
		TxLog.shInPos = 0;
	}
	TxLog.bSerial++;
	if(TxLog.bSerial >= 100){
		TxLog.bSerial = 0;
	}
}

void DeleteTxLog(void)
{
	memset(&TxLog.LogBf[TxLog.shOutPos],0,sizeof(TxLog.LogBf[TxLog.shOutPos]));
	TxLog.shOutPos++;
	if(TxLog.shOutPos >= LOG_CNT){
		TxLog.shOutPos = 0;
	}
	if(TxLog.shCnt > 0){
		TxLog.shCnt--;
	}
}

char *SetUserSens(char *chp)
{    // �l���m�Z���T���͗p�d���쐬
    char ch;

    //*chp = GetUserSens() + 0x30;
    *chp = GetGPIn(IN_BF_USER_SENS) + 0x30;
    chp++;

    //Debug("USER_SENS:%c\n",GetUserSens() + 0x30);

    return chp;
}

/*void Debug(const char *chpFormat,...)
{		// ���ޯ�ޗp�o��
	va_list args;
	char chBf[256];
	long lCnt;
	
	va_start(args, chpFormat);
	lCnt = (long)vsprintf(&chBf[0], chpFormat, args);
	va_end(args);
	
	memcpy((char *)DataComIr.chTx, (char *)chBf, (size_t)lCnt);
	DataComIr.chTx[lCnt] = 0;
	
	DataComIr.chProc = TX_BUSY;
	DataComIr.shTxPos = 0;
	TE_SCI1();
}*/

// ############################################# �����ݏ��� ##################################################
void Ir1msDataCom(void)
{
	if (DataComIr.wRxTmOut > 0)
	{
		DataComIr.wRxTmOut--;
		if (DataComIr.wRxTmOut == 0 && DataComIr.chProc == RX_BUSY)
		{
			DataComIr.chProc = RX_OK;
			DataComIr.chRx[DataComIr.shRxPos] = EOD;
			DataComIr.shRxPos = 0;
		}
	}
}

