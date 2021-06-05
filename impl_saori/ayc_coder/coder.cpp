#include "csaori.h"
#undef max//fucking windows
struct Aya_Coder_t{
	struct decoder_t{
		void write_header(FILE*to){}
		static int cipher(const int c)
		{
			return (((c & 0x7) << 5) | ((c & 0xf8) >> 3)) ^ 0x5a;
		}
		void write_ender(FILE*to){}
	};
	struct encoder_t{
		void write_header(FILE*to){}
		static int cipher(const int c)
		{
			return (((c ^ 0x5a) << 3) & 0xF8) | (((c ^ 0x5a) >> 5) & 0x7);
		}
		void write_ender(FILE*to){}
	};
	static constexpr auto codedFileSuffix=L"ayc";
	static constexpr auto NoncodedFileSuffix=L"dic";
};


auto ChangeSuffix(string_t name,string_t newSuffix){
	auto point = name.rfind(L".",std::max(name.rfind(L"\\"),name.rfind(L"/")));
	if (point != string_t::npos)
		name.erase(point);
	return name + L"." + newSuffix;
}
template<class Coder_t>
struct Runcoder_t{
	template<class do_coder_t>
	void runcode(FILE*from,FILE*to){
		do_coder_t::write_header()
		int c;
		while((c=fgetc(from))!=EOF){
			fputc(do_coder_t::cipher(c),to);
		}
		do_coder_t::write_ender()
	}
	template<class do_coder_t>
	bool RuncodeFor(string_t file,string_t to_file){
		auto fp=_wfopen(file.c_str(),L"rb");
		if(!fp)return 0;
		auto fp2=_wfopen(to_file.c_str(),L"wb");
		if(!fp2){
			fclose(fp);
			return 0;
		}
		runcode<do_coder_t>(fp,fp2);
		fclose(fp);
		fclose(fp2);
		return 1;
	}
	bool EncodeDic(string_t file){
		return RuncodeFor<Coder_t::encoder_t>(file,ChangeSuffix(file,Coder_t::codedFileSuffix));
	}
	bool DecodeDic(string_t file){
		return RuncodeFor<Coder_t::decoder_t>(file,ChangeSuffix(file,Coder_t::NoncodedFileSuffix));
	}
};
