#pragma once
#include <sapi.h> //��������ͷ�ļ�
#pragma comment(lib,"sapi.lib") //��������ͷ�ļ���
#include <sphelper.h>//����ʶ��ͷ�ļ�
#include <atlstr.h>//Ҫ�õ�CString

#pragma once
inline HRESULT BlockForResult(ISpRecoContext * pRecoCtxt, ISpRecoResult ** ppResult);
const WCHAR * KeyWord(int i);
const WCHAR * StopWord();
void listener(int &flag);