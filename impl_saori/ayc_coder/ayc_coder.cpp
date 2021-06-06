#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif

#include "coder.h"

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
	if(in.args[3]!=L"Taromati2"){
		out.result_code = SAORIRESULT_BAD_REQUEST;
	}
	else if(in.args[2]==L"aya") {
		if (cmd==L"Encode") {
			if (Runcoder_t<Aya_Coder_t>::EncodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		} else if (cmd==L"Decode") {
			if (Runcoder_t<Aya_Coder_t>::DecodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		}
	}
	else if(in.args[2]==L"misaka") {
		if (cmd==L"Encode") {
			if (Runcoder_t<Misaka_Coder_t>::EncodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		} else if (cmd==L"Decode") {
			if (Runcoder_t<Misaka_Coder_t>::DecodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		}
	}
	else if(in.args[2]==L"kawari") {
		if (cmd==L"Encode") {
			if (Runcoder_t<Kawari_Coder_t>::EncodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		} else if (cmd==L"Decode") {
			if (Runcoder_t<Kawari_Coder_t>::DecodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		}
	}
	else if(in.args[2]==L"satoriya") {
		if (cmd==L"Encode") {
			if (Runcoder_t<Satoriya_Coder_t>::EncodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		} else if (cmd==L"Decode") {
			if (Runcoder_t<Satoriya_Coder_t>::DecodeDic(in.args[1])) {
				out.result_code = SAORIRESULT_OK;
			}else
				out.result_code = SAORIRESULT_BAD_REQUEST;
		}
	}
	else
		out.result_code = SAORIRESULT_BAD_REQUEST;
	out.result=out.result_code==SAORIRESULT_OK?L"1":L"0";
}
