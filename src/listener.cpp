#pragma warning(disable: 4996)
#include <windows.h>
#include <sapi.h>
#include <stdio.h>
#include <string.h>
#include <atlbase.h>
#include <string>
#include "sphelper.h"
#include "listener.h"


inline HRESULT BlockForResult(ISpRecoContext * pRecoCtxt, ISpRecoResult ** ppResult)
{
	HRESULT hr = S_OK;
	CSpEvent event;

	while (SUCCEEDED(hr) &&
		SUCCEEDED(hr = event.GetFrom(pRecoCtxt)) &&
		hr == S_FALSE)
	{
		hr = pRecoCtxt->WaitForNotifyEvent(INFINITE);
	}

	*ppResult = event.RecoResult();
	if (*ppResult)
	{
		(*ppResult)->AddRef();
	}

	return hr;
}

const WCHAR * KeyWord(int i)
{
	const WCHAR * pchKey=NULL;

	LANGID LangId = ::SpGetUserDefaultUILanguage();

	switch (LangId)
	{
	case MAKELANGID(LANG_CHINESE, SUBLANG_DEFAULT):
		pchKey= L"\x7d42\x4e86\\\x30b7\x30e5\x30fc\x30ea\x30e7\x30fc/\x3057\x3085\x3046\x308a\x3087\x3046";;
		break;

	default:
		switch (i)
		{
		case 1:
			pchKey = L"我的面前有什么";
			break;
		case 2:
			pchKey = L"测试";
			break;
		}
		break;
	}

	return pchKey;
}

const WCHAR * StopWord()
{
	const WCHAR * pchStop;

	LANGID LangId = ::SpGetUserDefaultUILanguage();

	switch (LangId)
	{
	case MAKELANGID(LANG_CHINESE, SUBLANG_DEFAULT):
		pchStop = L"\x7d42\x4e86\\\x30b7\x30e5\x30fc\x30ea\x30e7\x30fc/\x3057\x3085\x3046\x308a\x3087\x3046";;
		break;

	default:
		pchStop = L"再见";
		break;
	}

	return pchStop;
}

void listener(int &flag)
{
	HRESULT hr = E_FAIL;

									// Process optional arguments
	
	if (SUCCEEDED(hr = ::CoInitialize(NULL)))
	{
		{
			CComPtr<ISpRecoContext> cpRecoCtxt;
			CComPtr<ISpRecoGrammar> cpGrammar;
			CComPtr<ISpVoice> cpVoice;
			hr = cpRecoCtxt.CoCreateInstance(CLSID_SpSharedRecoContext);
			if (SUCCEEDED(hr))
			{
				hr = cpRecoCtxt->GetVoice(&cpVoice);
			}

			if (cpRecoCtxt && cpVoice &&
				SUCCEEDED(hr = cpRecoCtxt->SetNotifyWin32Event()) &&
				SUCCEEDED(hr = cpRecoCtxt->SetInterest(SPFEI(SPEI_RECOGNITION), SPFEI(SPEI_RECOGNITION))) &&
				SUCCEEDED(hr = cpRecoCtxt->SetAudioOptions(SPAO_RETAIN_AUDIO, NULL, NULL)) &&
				SUCCEEDED(hr = cpRecoCtxt->CreateGrammar(0, &cpGrammar)) &&
				SUCCEEDED(hr = cpGrammar->LoadDictation(NULL, SPLO_STATIC)) &&
				SUCCEEDED(hr = cpGrammar->SetDictationState(SPRS_ACTIVE)))
			{
				USES_CONVERSION;

				const WCHAR * const pchKey1 = KeyWord(1);
				const WCHAR * const pchKey2 = KeyWord(2);
				const WCHAR * const pchStop = StopWord();
				CComPtr<ISpRecoResult> cpResult;

				//printf("I will repeat everything you say.\nSay \"%s\" to exit.\n", W2A(pchStop));

				SUCCEEDED(hr = BlockForResult(cpRecoCtxt, &cpResult));
	
					cpGrammar->SetDictationState(SPRS_ACTIVE_WITH_AUTO_PAUSE);

					CSpDynamicString dstrText;

					if (SUCCEEDED(cpResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE,
						TRUE, &dstrText, NULL)))
					{
						printf("I heard:  %s\n", W2A(dstrText));
						if (_wcsicmp(dstrText, pchKey1) == 0) {
							cpResult.Release();
							flag = 1;
						}
						else if (_wcsicmp(dstrText, pchKey2) == 0)
						{
							cpResult.Release();
							flag = 2;
						}
						else if (_wcsicmp(dstrText, pchStop) == 0)
						{
							cpVoice->Speak(L"再见，期待下次为你服务！", SPF_ASYNC, NULL);
							Sleep(5000);
							cpResult.Release();
							flag = 3;
						}
						else 
						{ 
							cpVoice->Speak(L"抱歉，请再说一遍。", SPF_ASYNC, NULL);
							listener(flag);
							cpResult.Release();

						}
						/*printf("I heard:  %s\n", W2A(dstrText));

						if (fUseTTS)
						{
							cpVoice->Speak(L"I heard", SPF_ASYNC, NULL);
							cpVoice->Speak(dstrText, SPF_ASYNC, NULL);
						}

						if (fReplay)
						{
							if (fUseTTS)
								cpVoice->Speak(L"when you said", SPF_ASYNC, NULL);
							else
								printf("\twhen you said...\n");
							cpResult->SpeakAudio(NULL, 0, NULL, NULL);
						}*/

					}

					cpGrammar->SetDictationState(SPRS_INACTIVE);
				
			}
		}
		::CoUninitialize();
	}
	return;
}
