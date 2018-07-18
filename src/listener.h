#pragma once
#include <sapi.h> //导入语音头文件
#pragma comment(lib,"sapi.lib") //导入语音头文件库
#include <sphelper.h>//语音识别头文件
#include <atlstr.h>//要用到CString

#pragma once
inline HRESULT BlockForResult(ISpRecoContext * pRecoCtxt, ISpRecoResult ** ppResult);
const WCHAR * KeyWord(int i);
const WCHAR * StopWord();
void listener(int &flag);