#include "windows.h"
#include "string"
#include "iostream"
#include "speak_sth.h"
#pragma warning(disable: 4996)
#include <sphelper.h>//����ͷ�ļ�
#include <stdio.h>//Cͷ�ļ���������ʾ������Ϣ"
#include <fstream>

void speak_sth(std::string context) {
	/*::CoInitialize(NULL);//��ʼ����������
	ISpVoice * pSpVoice = NULL;//��ʼ����������
	if (FAILED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void **)&pSpVoice)))
		//���������������������൱�ڴ�������������FAILED�Ǹ��궨�壬�������ж�CoCreateInstance���������û�гɹ��������������������ǲ��ɹ�����ʾ��Ϣ��
	{
		printf("Failed to create instance of ISpVoice!\n");
		return;
	}
	std::cout << context + "\n";
	size_t size = context.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, context.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;
	pSpVoice->Speak(buffer, SPF_DEFAULT, NULL);//ִ������������Speek����������������������֡�
	pSpVoice->Release(); //�ͷ���������
	::CoUninitialize();//�ͷ���������*/
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