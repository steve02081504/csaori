#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif

#include "csaori.h"

bool EncodeDic(string_t file);
bool DecodeDic(string_t file);

/*---------------------------------------------------------
	èâä˙âª
---------------------------------------------------------*/
bool CSAORI::load()
{
	return true;
}

/*---------------------------------------------------------
	âï˙
---------------------------------------------------------*/
bool CSAORI::unload()
{
	return true;
}

/*---------------------------------------------------------
	é¿çs
---------------------------------------------------------*/
void CSAORI::exec(const CSAORIInput& in,CSAORIOutput& out)
{
	const string_t& cmd = in.args[0];
	if (_wcsnicmp(cmd.c_str(), L"Encode", 6) == 0) {
		if (EncodeDic(in.args[1])) {
			out.result_code = SAORIRESULT_OK;
		}else
			out.result_code = SAORIRESULT_BAD_REQUEST;
		return;
	} else if (_wcsnicmp(cmd.c_str(), L"Decode", 6) == 0) {
		if (DecodeDic(in.args[1])) {
			out.result_code = SAORIRESULT_OK;
		}else
			out.result_code = SAORIRESULT_BAD_REQUEST;
		return;
	}
	out.result_code = SAORIRESULT_BAD_REQUEST;
}
