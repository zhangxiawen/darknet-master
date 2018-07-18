#include "windows.h"
#include "string"
#include "iostream"
#include "speak_sth.h"
#pragma warning(disable: 4996)
#include <sphelper.h>//语音头文件
#include <stdio.h>//C头文件，用来提示错误信息"
#include <fstream>

void speak_sth(std::string context) {
	/*::CoInitialize(NULL);//初始化语音环境
	ISpVoice * pSpVoice = NULL;//初始化语音变量
	if (FAILED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void **)&pSpVoice)))
		//给语音变量创建环境，相当于创建语音变量，FAILED是个宏定义，就是来判断CoCreateInstance这个函数又没有成功创建语音变量，下面是不成功的提示信息。
	{
		printf("Failed to create instance of ISpVoice!\n");
		return;
	}
	std::cout << context + "\n";
	size_t size = context.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, context.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;
	pSpVoice->Speak(buffer, SPF_DEFAULT, NULL);//执行语音变量的Speek函数，这个函数用来读文字。
	pSpVoice->Release(); //释放语音变量
	::CoUninitialize();//释放语音环境*/
	std::cout << context + "\n";
	std::ofstream file;
	file.open("voice.vbs");
	if (!file) printf("fail");
	else {
	file << "CreateObject(\"SAPI.SpVoice\").Speak \"";
	file << context;
	file << "\"";
	file.close();
		 }
	system("voice.vbs");
}