#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif

#include "csaori.h"
#include "Getip.hpp"

/*---------------------------------------------------------
	������
---------------------------------------------------------*/
bool CSAORI::load()
{
	return true;
}

/*---------------------------------------------------------
	���
---------------------------------------------------------*/
bool CSAORI::unload()
{
	return true;
}

/*---------------------------------------------------------
	���s
---------------------------------------------------------*/
void CSAORI::exec(const CSAORIInput& in,CSAORIOutput& out)
{
	const string_t& cmd = in.args[0];
	if (_wcsnicmp(cmd.c_str(), L"GetLocalIP", 10) == 0) {
		if (GetLocalIP(out.result)) {
			out.result_code = SAORIRESULT_OK;
		}else
			out.result_code = SAORIRESULT_INTERNAL_SERVER_ERROR;
		return;
	} else if (_wcsnicmp(cmd.c_str(), L"GetInternetIP", 13) == 0) {
		if (GetInternetIP(out.result)) {
			out.result_code = SAORIRESULT_OK;
		}else
			out.result_code = SAORIRESULT_INTERNAL_SERVER_ERROR;
		return;
	} else if (_wcsnicmp(cmd.c_str(), L"GetLocalHostname", 16) == 0) {
		if (GetLocalHostname(out.result)) {
			out.result_code = SAORIRESULT_OK;
		} else
			out.result_code = SAORIRESULT_INTERNAL_SERVER_ERROR;
		return;
	}
	out.result_code = SAORIRESULT_BAD_REQUEST;
}
