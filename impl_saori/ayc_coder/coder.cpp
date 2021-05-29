#include "csaori.h"
static int decodecipher(const int c)
{
	return (((c & 0x7) << 5) | ((c & 0xf8) >> 3)) ^ 0x5a;
}
static int encodecipher(const int c)
{
	return (((c ^ 0x5a) << 3) & 0xF8) | (((c ^ 0x5a) >> 5) & 0x7);
}

void runcode(int(*method)(const int),FILE*from,FILE*to){
	int c;
	while((c=fgetc(from))!=EOF){
		fputc(method(c),to);
	}
}
bool RuncodeFor(string_t file,string_t to_file,int(*method)(const int)){
	auto fp=_wfopen(file.c_str(),L"rb");
	if(!fp)return 0;
	auto fp2=_wfopen(to_file.c_str(),L"wb");
	if(!fp2){
		fclose(fp);
		return 0;
	}
	runcode(method,fp,fp2);
	fclose(fp);
	fclose(fp2);
	return 1;
}
#undef max//fucking windows
auto ChangeSuffix(string_t name,string_t newSuffix){
	auto point = name.rfind(L".",std::max(name.rfind(L"\\"),name.rfind(L"/")));
	if (point != string_t::npos)
		name.erase(point);
	return name + L"." + newSuffix;
}
bool EncodeDic(string_t file){
	return RuncodeFor(file,ChangeSuffix(file,L"ayc"),encodecipher);
}
bool DecodeDic(string_t file){
	return RuncodeFor(file,ChangeSuffix(file,L"dic"),decodecipher);
}
