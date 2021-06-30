#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif

#include "csaori.h"
#include "csaori_util.h"

/*---------------------------------------------------------
	初期化
---------------------------------------------------------*/
bool CSAORI::load()
{
	return true;
}

/*---------------------------------------------------------
	解放
---------------------------------------------------------*/
bool CSAORI::unload()
{
	return true;
}

/*---------------------------------------------------------
	実行
---------------------------------------------------------*/
string_t ExeCmd(string_t Cmd) {
	// ?建匿名管道,write->read;
	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		return L"";
	// ?置命令行?程??信息(以?藏方式??命令并定位其?出到hWrite
	STARTUPINFO si = { sizeof(STARTUPINFO) }; // Pointer to STARTUPINFO structure;
	GetStartupInfo(&si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE; //?藏窗口；
	si.hStdError = hWrite;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite; //管道的?入端口?接命令行的?出；
	// ??命令行
	PROCESS_INFORMATION pi;// Pointer to PROCESS_INFORMATION structure;
	if (!CreateProcess(NULL,
		(LPWSTR)Cmd.c_str(),
		NULL,
		NULL,
		TRUE, 
		//FALSE,          // Set handle inheritance to FALSE
		NULL,
		//0,              // No creation flags
		NULL,
		NULL,
		&si,
		&pi))
		return L"";
	CloseHandle(hWrite);//??管道的?入端口；
	// ?取命令行返回?
	string_t strRetTmp;
	char buff[1024] = { 0 };
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL))//从管道的?出端?取命令行写入的数据；
	{
		strRetTmp += SAORI_FUNC::MultiByteToUnicode(buff,CP_ACP);
	}
	CloseHandle(hRead);//??管道的?出端口；
	return strRetTmp;
}

void CSAORI::exec(const CSAORIInput& in,CSAORIOutput& out)
{
	out.result_code = SAORIRESULT_OK;
	string_t a=L"cmd.exe /q /u /c";
	for (auto& i : in.args) {
		a += L" " + i;
	}
	a=ExeCmd(a);
	if(a!=L"-1")
		out.result = a;
	else
		out.result_code = SAORIRESULT_BAD_REQUEST;
	return;
}
