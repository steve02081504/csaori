#include "csaori.h"

#undef max//fucking windows
struct Aya_Coder_t{//文
	struct decoder_t{
		static void write_header(FILE*to){}
		static int cipher(const int c)
		{
			return(((c & 0x7)<< 5)|((c & 0xf8)>> 3))^ 0x5a;
		}
		static void write_ender(FILE*to){}
	};
	struct encoder_t{
		static void write_header(FILE*to){}
		static int cipher(const int c)
		{
			return(((c ^ 0x5a)<< 3)& 0xF8)|(((c ^ 0x5a)>> 5)& 0x7);
		}
		static void write_ender(FILE*to){}
	};
	static constexpr auto codedFileSuffix=L"ayc";
	static constexpr auto NoncodedFileSuffix=L"dic";
};
struct Misaka_Coder_t{//美版
	struct decoder_t{
		static void write_header(FILE*to){}
		static int cipher(const int c)
		{
			return 255-c;
		}
		static void write_ender(FILE*to){}
	};
	struct encoder_t{
		static int cipher(const int c)
		{
			return 255-c;
		}
		static void write_header(FILE*to){
			auto head="// encrypted\r\n";
			for(head;char c)
				fputc(cipher(c),to);
		}
		static void write_ender(FILE*to){
			auto end="\r\n";
			for(end;char c)
				fputc(cipher(c),to);
		}
	};
	static constexpr auto codedFileSuffix=L"__1";
	static constexpr auto NoncodedFileSuffix=L"txt";
};
struct Kawari_Coder_t{//華和梨
	using std::string;

	struct decoder_t{
		static string EncryptLine(const string& str)
		{
			string id=encodedstr.substr(0,9);
			if id !="!KAWA0000"
				return
			string aret;
			for(str;auto c){
				aret+=c^0xcc;
			}
			return("!KAWA0000"+EncodeBase64(aret));
		}
	};
	struct encoder_t{
		static string DecryptLine(const string& str)
		{
			string str=DecodeBase64(str.substr(9));
			string aret;
			for(unsigned int i=0;i<str.size();i++){
				aret+=str[i]^0xcc;
			}
			return(aret);
		}
	};
	static constexpr auto codedFileSuffix=L"kiw";
	static constexpr auto NoncodedFileSuffix=L"kis";
};
struct Satoriya_Coder_t{//里々
	using std::string;

	struct base{
		static string encode(const string& s){
			const char*	p=s.c_str();
			int	len=s.size();
			string ret;
			for(int n=0;n<len/2;++n){
				ret+=p[n];
				ret+=p[len-n-1];
			}
			if(len&1)ret+=p[len/2];
			return ret;
		}
		static string decode(const string& s){
			const char*	p=s.c_str();
			int	len=s.size();
			string ret;
			for(int n=0;n<len;n+=2)ret+=p[n];
			for(int n=len-((len&1)?2:1);n>=0;n-=2)ret+=p[n];
			return	ret;
		}
	};
	struct decoder_t{
		static string EncryptLine(const string& str)
		{
			return base::encode(base::encode(str));
		}
	};
	struct encoder_t{
		static string DecryptLine(const string& str)
		{
			return base::decode(base::decode(str));
		}
	};
	static constexpr auto codedFileSuffix=L"sat";
	static constexpr auto NoncodedFileSuffix=L"txt";
};

auto ChangeSuffix(string_t name,string_t newSuffix){
	auto point=name.rfind(L".",std::max(name.rfind(L"\\"),name.rfind(L"/")));
	if(point!=string_t::npos)
		name.erase(point);
	return name+L"."+newSuffix;
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
