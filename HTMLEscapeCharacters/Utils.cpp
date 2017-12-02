﻿#include "stdafx.h"
#include "Utils.h"

#include <map> 
#include <set>
#include <regex>
#include <iostream> 
#include <cctype>
#include <string>
#include <algorithm>

#include "EncodeHTML.h"
#include "ParseParameters.h"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

// for testing purpose repeate main 
int Execute(int argc, char *argv[])
{
	int nRet(0);
	CParseParameters p(argc, argv);

	nRet = p.Validate();
	if (0 == nRet)
	{
		CEncodeHTML encode(p.GetEncode(), p.GetSubdirectories());
		nRet = encode.EncodePath(p.GetSource(), p.GetDestination(),p.GetExtensions());
	}
	return nRet;
}

std::wstring EncodeHTML(std::wstring &strSource)
{
	static std::map<wchar_t, std::wstring> mapCache =
	{
		{ L'™',L"&#8482;" },
		//{ L'€',L"" },
		{ L' ',L"&#32;" },
		{ L'!',L"&#33;" },
		{ L'"',L"&#34;" },
		{ L'#',L"&#35;" },
		{ L'$',L"&#36;" },
		{ L'%',L"&#37;" },
		{ L'&',L"&#38;" },
		{ L'\'',L"&#39;"},
		{ L'(',L"&#40;" },
		{ L')',L"&#41;" },
		{ L'*',L"&#42;" },
		{ L'+',L"&#43;" },
		{ L',',L"&#44;" },
		{ L'-',L"&#45;" },
		{ L'.',L"&#46;" },
		{ L'/',L"&#47;" },
		{ L'0',L"&#48;" },
		{ L'1',L"&#49;" },
		{ L'2',L"&#50;" },
		{ L'3',L"&#51;" },
		{ L'4',L"&#52;" },
		{ L'5',L"&#53;" },
		{ L'6',L"&#54;" },
		{ L'7',L"&#55;" },
		{ L'8',L"&#56;" },
		{ L'9',L"&#57;" },
		{ L':',L"&#58;" },
		{ L';',L"&#59;" },
		{ L'<',L"&#60;" },
		{ L'=',L"&#61;" },
		{ L'>',L"&#62;" },
		{ L'?',L"&#63;" },
		{ L'@',L"&#64;" },
		{ L'A',L"&#65;" },
		{ L'B',L"&#66;" },
		{ L'C',L"&#67;" },
		{ L'D',L"&#68;" },
		{ L'E',L"&#69;" },
		{ L'F',L"&#70;" },
		{ L'G',L"&#71;" },
		{ L'H',L"&#72;" },
		{ L'I',L"&#73;" },
		{ L'J',L"&#74;" },
		{ L'K',L"&#75;" },
		{ L'L',L"&#76;" },
		{ L'M',L"&#77;" },
		{ L'N',L"&#78;" },
		{ L'O',L"&#79;" },
		{ L'P',L"&#80;" },
		{ L'Q',L"&#81;" },
		{ L'R',L"&#82;" },
		{ L'S',L"&#83;" },
		{ L'T',L"&#84;" },
		{ L'U',L"&#85;" },
		{ L'V',L"&#86;" },
		{ L'W',L"&#87;" },
		{ L'X',L"&#88;" },
		{ L'Y',L"&#89;" },
		{ L'Z',L"&#90;" },
		{ L'[',L"&#91;" },
		{ L'\\',L"&#92;"},
		{ L']',L"&#93;"},
		{ L'^',L"&#94;" },
		{ L'_',L"&#95;" },
		{ L'`',L"&#96;" },
		{ L'a',L"&#97;" },
		{ L'b',L"&#98;" },
		{ L'c',L"&#99;" },
		{ L'd',L"&#100;" },
		{ L'e',L"&#101;" },
		{ L'f',L"&#102;" },
		{ L'g',L"&#103;" },
		{ L'h',L"&#104;" },
		{ L'i',L"&#105;" },
		{ L'j',L"&#106;" },
		{ L'k',L"&#107;" },
		{ L'l',L"&#108;" },
		{ L'm',L"&#109;" },
		{ L'n',L"&#110;" },
		{ L'o',L"&#111;" },
		{ L'p',L"&#112;" },
		{ L'q',L"&#113;" },
		{ L'r',L"&#114;" },
		{ L's',L"&#115;" },
		{ L't',L"&#116;" },
		{ L'u',L"&#117;" },
		{ L'v',L"&#118;" },
		{ L'w',L"&#119;" },
		{ L'x',L"&#120;" },
		{ L'y',L"&#121;" },
		{ L'z',L"&#122;" },
		{ L'{',L"&#123;" },
		{ L'|',L"&#124;" },
		{ L'}',L"&#125;" },
		{ L'~',L"&#126;" },
		//{ L'Non-breaking space',L"&#160;" },
		{ L'¡',L"&#161;" },
		{ L'¢',L"&#162;" },
		{ L'£',L"&#163;" },
		{ L'¤',L"&#164;" },
		{ L'¥',L"&#165;" },
		{ L'¦',L"&#166;" },
		{ L'§',L"&#167;" },
		{ L'¨',L"&#168;" },
		{ L'©',L"&#169;" },
		{ L'ª',L"&#170;" },
		{ L'«',L"&#171;" },
		{ L'¬',L"&#172;" },
		{ L'­' ,L"&#173;" },
		{ L'®',L"&#174;" },
		{ L'¯',L"&#175;" },
		{ L'°',L"&#176;" },
		{ L'±',L"&#177;" },
		{ L'²',L"&#178;" },
		{ L'³',L"&#179;" },
		{ L'´',L"&#180;" },
		{ L'µ',L"&#181;" },
		{ L'¶',L"&#182;" },
		{ L'·',L"&#183;" },
		{ L'¸',L"&#184;" },
		{ L'¹',L"&#185;" },
		{ L'º',L"&#186;" },
		{ L'»',L"&#187;" },
		{ L'¼',L"&#188;" },
		{ L'½',L"&#189;" },
		{ L'¾',L"&#190;" },
		{ L'¿',L"&#191;" },
		{ L'À',L"&#192;" },
		{ L'Á',L"&#193;" },
		{ L'Â',L"&#194;" },
		{ L'Ã',L"&#195;" },
		{ L'Ä',L"&#196;" },
		{ L'Å',L"&#197;" },
		{ L'Æ',L"&#198;" },
		{ L'Ç',L"&#199;" },
		{ L'È',L"&#200;" },
		{ L'É',L"&#201;" },
		{ L'Ê',L"&#202;" },
		{ L'Ë',L"&#203;" },
		{ L'Ì',L"&#204;" },
		{ L'Í',L"&#205;" },
		{ L'Î',L"&#206;" },
		{ L'Ï',L"&#207;" },
		{ L'Ð',L"&#208;" },
		{ L'Ñ',L"&#209;" },
		{ L'Ò',L"&#210;" },
		{ L'Ó',L"&#211;" },
		{ L'Ô',L"&#212;" },
		{ L'Õ',L"&#213;" },
		{ L'Ö',L"&#214;" },
		{ L'×',L"&#215;" },
		{ L'Ø',L"&#216;" },
		{ L'Ù',L"&#217;" },
		{ L'Ú',L"&#218;" },
		{ L'Û',L"&#219;" },
		{ L'Ü',L"&#220;" },
		{ L'Ý',L"&#221;" },
		{ L'Þ',L"&#222;" },
		{ L'ß',L"&#223;" },
		{ L'à',L"&#224;" },
		{ L'á',L"&#225;" },
		{ L'â',L"&#226;" },
		{ L'ã',L"&#227;" },
		{ L'ä',L"&#228;" },
		{ L'å',L"&#229;" },
		{ L'æ',L"&#230;" },
		{ L'ç',L"&#231;" },
		{ L'è',L"&#232;" },
		{ L'é',L"&#233;" },
		{ L'ê',L"&#234;" },
		{ L'ë',L"&#235;" },
		{ L'ì',L"&#236;" },
		{ L'í',L"&#237;" },
		{ L'î',L"&#238;" },
		{ L'ï',L"&#239;" },
		{ L'ð',L"&#240;" },
		{ L'ñ',L"&#241;" },
		{ L'ò',L"&#242;" },
		{ L'ó',L"&#243;" },
		{ L'ô',L"&#244;" },
		{ L'õ',L"&#245;" },
		{ L'ö',L"&#246;" },
		{ L'÷',L"&#247;" },
		{ L'ø',L"&#248;" },
		{ L'ù',L"&#249;" },
		{ L'ú',L"&#250;" },
		{ L'û',L"&#251;" },
		{ L'ü',L"&#252;" },
		{ L'ý',L"&#253;" },
		{ L'þ',L"&#254;" },
		{ L'ÿ',L"&#255;" },
		{ L'Ā',L"&#256;" },
		{ L'ā',L"&#257;" },
		{ L'Ă',L"&#258;" },
		{ L'ă',L"&#259;" },
		{ L'Ą',L"&#260;" },
		{ L'ą',L"&#261;" },
		{ L'Ć',L"&#262;" },
		{ L'ć',L"&#263;" },
		{ L'Ĉ',L"&#264;" },
		{ L'ĉ',L"&#265;" },
		{ L'Ċ',L"&#266;" },
		{ L'ċ',L"&#267;" },
		{ L'Č',L"&#268;" },
		{ L'č',L"&#269;" },
		{ L'Ď',L"&#270;" },
		{ L'ď',L"&#271;" },
		{ L'Đ',L"&#272;" },
		{ L'đ',L"&#273;" },
		{ L'Ē',L"&#274;" },
		{ L'ē',L"&#275;" },
		{ L'Ĕ',L"&#276;" },
		{ L'ĕ',L"&#277;" },
		{ L'Ė',L"&#278;" },
		{ L'ė',L"&#279;" },
		{ L'Ę',L"&#280;" },
		{ L'ę',L"&#281;" },
		{ L'Ě',L"&#282;" },
		{ L'ě',L"&#283;" },
		{ L'Ĝ',L"&#284;" },
		{ L'ĝ',L"&#285;" },
		{ L'Ğ',L"&#286;" },
		{ L'ğ',L"&#287;" },
		{ L'Ġ',L"&#288;" },
		{ L'ġ',L"&#289;" },
		{ L'Ģ',L"&#290;" },
		{ L'ģ',L"&#291;" },
		{ L'Ĥ',L"&#292;" },
		{ L'ĥ',L"&#293;" },
		{ L'Ħ',L"&#294;" },
		{ L'ħ',L"&#295;" },
		{ L'Ĩ',L"&#296;" },
		{ L'ĩ',L"&#297;" },
		{ L'Ī',L"&#298;" },
		{ L'ī',L"&#299;" },
		{ L'Ĭ',L"&#300;" },
		{ L'ĭ',L"&#301;" },
		{ L'Į',L"&#302;" },
		{ L'į',L"&#303;" },
		{ L'İ',L"&#304;" },
		{ L'ı',L"&#305;" },
		{ L'Ĳ',L"&#306;" },
		{ L'ĳ',L"&#307;" },
		{ L'Ĵ',L"&#308;" },
		{ L'ĵ',L"&#309;" },
		{ L'Ķ',L"&#310;" },
		{ L'ķ',L"&#311;" },
		{ L'ĸ',L"&#312;" },
		{ L'Ĺ',L"&#313;" },
		{ L'ĺ',L"&#314;" },
		{ L'Ļ',L"&#315;" },
		{ L'ļ',L"&#316;" },
		{ L'Ľ',L"&#317;" },
		{ L'ľ',L"&#318;" },
		{ L'Ŀ',L"&#319;" },
		{ L'ŀ',L"&#320;" },
		{ L'Ł',L"&#321;" },
		{ L'ł',L"&#322;" },
		{ L'Ń',L"&#323;" },
		{ L'ń',L"&#324;" },
		{ L'Ņ',L"&#325;" },
		{ L'ņ',L"&#326;" },
		{ L'Ň',L"&#327;" },
		{ L'ň',L"&#328;" },
		{ L'ŉ',L"&#329;" },
		{ L'Ŋ',L"&#330;" },
		{ L'ŋ',L"&#331;" },
		{ L'Ō',L"&#332;" },
		{ L'ō',L"&#333;" },
		{ L'Ŏ',L"&#334;" },
		{ L'ŏ',L"&#335;" },
		{ L'Ő',L"&#336;" },
		{ L'ő',L"&#337;" },
		{ L'Œ',L"&#338;" },
		{ L'œ',L"&#339;" },
		{ L'Ŕ',L"&#340;" },
		{ L'ŕ',L"&#341;" },
		{ L'Ŗ',L"&#342;" },
		{ L'ŗ',L"&#343;" },
		{ L'Ř',L"&#344;" },
		{ L'ř',L"&#345;" },
		{ L'Ś',L"&#346;" },
		{ L'ś',L"&#347;" },
		{ L'Ŝ',L"&#348;" },
		{ L'ŝ',L"&#349;" },
		{ L'Ş',L"&#350;" },
		{ L'ş',L"&#351;" },
		{ L'Š',L"&#352;" },
		{ L'š',L"&#353;" },
		{ L'Ţ',L"&#354;" },
		{ L'ţ',L"&#355;" },
		{ L'Ť',L"&#356;" },
		{ L'ť',L"&#357;" },
		{ L'Ŧ',L"&#358;" },
		{ L'ŧ',L"&#359;" },
		{ L'Ũ',L"&#360;" },
		{ L'ũ',L"&#361;" },
		{ L'Ū',L"&#362;" },
		{ L'ū',L"&#363;" },
		{ L'Ŭ',L"&#364;" },
		{ L'ŭ',L"&#365;" },
		{ L'Ů',L"&#366;" },
		{ L'ů',L"&#367;" },
		{ L'Ű',L"&#368;" },
		{ L'ű',L"&#369;" },
		{ L'Ų',L"&#370;" },
		{ L'ų',L"&#371;" },
		{ L'Ŵ',L"&#372;" },
		{ L'ŵ',L"&#373;" },
		{ L'Ŷ',L"&#374;" },
		{ L'ŷ',L"&#375;" },
		{ L'Ÿ',L"&#376;" },
		{ L'Ź',L"&#377;" },
		{ L'ź',L"&#378;" },
		{ L'Ż',L"&#379;" },
		{ L'ż',L"&#380;" },
		{ L'Ž',L"&#381;" },
		{ L'ž',L"&#382;" },
		{ L'ſ',L"&#383;" },
		{ L'Ŕ',L"&#340;" },
		{ L'ŕ',L"&#341;" },
		{ L'Ŗ',L"&#342;" },
		{ L'ŗ',L"&#343;" },
		{ L'Ř',L"&#344;" },
		{ L'ř',L"&#345;" },
		{ L'Ś',L"&#346;" },
		{ L'ś',L"&#347;" },
		{ L'Ŝ',L"&#348;" },
		{ L'ŝ',L"&#349;" },
		{ L'Ş',L"&#350;" },
		{ L'ş',L"&#351;" },
		{ L'Š',L"&#352;" },
		{ L'š',L"&#353;" },
		{ L'Ţ',L"&#354;" },
		{ L'ţ',L"&#355;" },
		{ L'Ť',L"&#356;" },
		{ L'ť',L"&#577;" },
		{ L'Ŧ',L"&#358;" },
		{ L'ŧ',L"&#359;" },
		{ L'Ũ',L"&#360;" },
		{ L'ũ',L"&#361;" },
		{ L'Ū',L"&#362;" },
		{ L'ū',L"&#363;" },
		{ L'Ŭ',L"&#364;" },
		{ L'ŭ',L"&#365;" },
		{ L'Ů',L"&#366;" },
		{ L'ů',L"&#367;" },
		{ L'Ű',L"&#368;" },
		{ L'ű',L"&#369;" },
		{ L'Ų',L"&#370;" },
		{ L'ų',L"&#371;" },
		{ L'Ŵ',L"&#372;" },
		{ L'ŵ',L"&#373;" },
		{ L'Ŷ',L"&#374;" },
		{ L'ŷ',L"&#375;" },
		{ L'Ÿ',L"&#376;" },
		{ L'Ź',L"&#377;" },
		{ L'ź',L"&#378;" },
		{ L'Ż',L"&#379;" },
		{ L'ż',L"&#380;" },
		{ L'Ž',L"&#381;" },
		{ L'ž',L"&#382;" },
		{ L'ſ',L"&#383;" }
	};

	std::wstring strRet;

	for (auto c : strSource)
	{
		auto f = mapCache.find(c);
		if (f != mapCache.end())
		{
			strRet += f->second;
		}
		else
		{
			strRet += c;
		}

	}

	return strRet;
}

std::wstring DecodeHTML(std::wstring &strSource)
{
	static std::map<std::wstring, std::wstring> mapCache =
	{
		{ L"&#8482;",L"™" },
		{ L"",L"€" },
		{ L"&#32;",L" " },
		{ L"&#33;",L"!" },
		{ L"&#34;",L"\"" },
		{ L"&#35;",L"#" },
		{ L"&#36;",L"$" },
		{ L"&#37;",L"%" },
		{ L"&#38;",L"&" },
		{ L"&#39;",L"'" },
		{ L"&#40;",L"(" },
		{ L"&#41;",L")" },
		{ L"&#42;",L"*" },
		{ L"&#43;",L"+" },
		{ L"&#44;",L"," },
		{ L"&#45;",L"-" },
		{ L"&#46;",L"." },
		{ L"&#47;",L"/" },
		{ L"&#48;",L"0" },
		{ L"&#49;",L"1" },
		{ L"&#50;",L"2" },
		{ L"&#51;",L"3" },
		{ L"&#52;",L"4" },
		{ L"&#53;",L"5" },
		{ L"&#54;",L"6" },
		{ L"&#55;",L"7" },
		{ L"&#56;",L"8" },
		{ L"&#57;",L"9" },
		{ L"&#58;",L":" },
		{ L"&#59;",L";" },
		{ L"&#60;",L"<" },
		{ L"&#61;",L"=" },
		{ L"&#62;",L">" },
		{ L"&#63;",L"?" },
		{ L"&#64;",L"@" },
		{ L"&#65;",L"A" },
		{ L"&#66;",L"B" },
		{ L"&#67;",L"C" },
		{ L"&#68;",L"D" },
		{ L"&#69;",L"E" },
		{ L"&#70;",L"F" },
		{ L"&#71;",L"G" },
		{ L"&#72;",L"H" },
		{ L"&#73;",L"I" },
		{ L"&#74;",L"J" },
		{ L"&#75;",L"K" },
		{ L"&#76;",L"L" },
		{ L"&#77;",L"M" },
		{ L"&#78;",L"N" },
		{ L"&#79;",L"O" },
		{ L"&#80;",L"P" },
		{ L"&#81;",L"Q" },
		{ L"&#82;",L"R" },
		{ L"&#83;",L"S" },
		{ L"&#84;",L"T" },
		{ L"&#85;",L"U" },
		{ L"&#86;",L"V" },
		{ L"&#87;",L"W" },
		{ L"&#88;",L"X" },
		{ L"&#89;",L"Y" },
		{ L"&#90;",L"Z" },
		{ L"&#91;",L"[" },
		{ L"&#92;",L"\\" },
		{ L"&#93;",L"]" },
		{ L"&#94;",L"^" },
		{ L"&#95;",L"_" },
		{ L"&#96;",L"`" },
		{ L"&#97;",L"a" },
		{ L"&#98;",L"b" },
		{ L"&#99;",L"c" },
		{ L"&#100;",L"d" },
		{ L"&#101;",L"e" },
		{ L"&#102;",L"f" },
		{ L"&#103;",L"g" },
		{ L"&#104;",L"h" },
		{ L"&#105;",L"i" },
		{ L"&#106;",L"j" },
		{ L"&#107;",L"k" },
		{ L"&#108;",L"l" },
		{ L"&#109;",L"m" },
		{ L"&#110;",L"n" },
		{ L"&#111;",L"o" },
		{ L"&#112;",L"p" },
		{ L"&#113;",L"q" },
		{ L"&#114;",L"r" },
		{ L"&#115;",L"s" },
		{ L"&#116;",L"t" },
		{ L"&#117;",L"u" },
		{ L"&#118;",L"v" },
		{ L"&#119;",L"w" },
		{ L"&#120;",L"x" },
		{ L"&#121;",L"y" },
		{ L"&#122;",L"z" },
		{ L"&#123;",L"{" },
		{ L"&#124;",L"|" },
		{ L"&#125;",L"}" },
		{ L"&#126;",L"~" },
		//{ L"&#160;",L"Non-breaking space" },
		{ L"&#161;",L"¡" },
		{ L"&#162;",L"¢" },
		{ L"&#163;",L"£" },
		{ L"&#164;",L"¤" },
		{ L"&#165;",L"¥" },
		{ L"&#166;",L"¦" },
		{ L"&#167;",L"§" },
		{ L"&#168;",L"¨" },
		{ L"&#169;",L"©" },
		{ L"&#170;",L"ª" },
		{ L"&#171;",L"«" },
		{ L"&#172;",L"¬" },
		{ L"&#173;",L"­" },
		{ L"&#174;",L"®" },
		{ L"&#175;",L"¯" },
		{ L"&#176;",L"°" },
		{ L"&#177;",L"±" },
		{ L"&#178;",L"²" },
		{ L"&#179;",L"³" },
		{ L"&#180;",L"´" },
		{ L"&#181;",L"µ" },
		{ L"&#182;",L"¶" },
		{ L"&#183;",L"·" },
		{ L"&#184;",L"¸" },
		{ L"&#185;",L"¹" },
		{ L"&#186;",L"º" },
		{ L"&#187;",L"»" },
		{ L"&#188;",L"¼" },
		{ L"&#189;",L"½" },
		{ L"&#190;",L"¾" },
		{ L"&#191;",L"¿" },
		{ L"&#192;",L"À" },
		{ L"&#193;",L"Á" },
		{ L"&#194;",L"Â" },
		{ L"&#195;",L"Ã" },
		{ L"&#196;",L"Ä" },
		{ L"&#197;",L"Å" },
		{ L"&#198;",L"Æ" },
		{ L"&#199;",L"Ç" },
		{ L"&#200;",L"È" },
		{ L"&#201;",L"É" },
		{ L"&#202;",L"Ê" },
		{ L"&#203;",L"Ë" },
		{ L"&#204;",L"Ì" },
		{ L"&#205;",L"Í" },
		{ L"&#206;",L"Î" },
		{ L"&#207;",L"Ï" },
		{ L"&#208;",L"Ð" },
		{ L"&#209;",L"Ñ" },
		{ L"&#210;",L"Ò" },
		{ L"&#211;",L"Ó" },
		{ L"&#212;",L"Ô" },
		{ L"&#213;",L"Õ" },
		{ L"&#214;",L"Ö" },
		{ L"&#215;",L"×" },
		{ L"&#216;",L"Ø" },
		{ L"&#217;",L"Ù" },
		{ L"&#218;",L"Ú" },
		{ L"&#219;",L"Û" },
		{ L"&#220;",L"Ü" },
		{ L"&#221;",L"Ý" },
		{ L"&#222;",L"Þ" },
		{ L"&#223;",L"ß" },
		{ L"&#224;",L"à" },
		{ L"&#225;",L"á" },
		{ L"&#226;",L"â" },
		{ L"&#227;",L"ã" },
		{ L"&#228;",L"ä" },
		{ L"&#229;",L"å" },
		{ L"&#230;",L"æ" },
		{ L"&#231;",L"ç" },
		{ L"&#232;",L"è" },
		{ L"&#233;",L"é" },
		{ L"&#234;",L"ê" },
		{ L"&#235;",L"ë" },
		{ L"&#236;",L"ì" },
		{ L"&#237;",L"í" },
		{ L"&#238;",L"î" },
		{ L"&#239;",L"ï" },
		{ L"&#240;",L"ð" },
		{ L"&#241;",L"ñ" },
		{ L"&#242;",L"ò" },
		{ L"&#243;",L"ó" },
		{ L"&#244;",L"ô" },
		{ L"&#245;",L"õ" },
		{ L"&#246;",L"ö" },
		{ L"&#247;",L"÷" },
		{ L"&#248;",L"ø" },
		{ L"&#249;",L"ù" },
		{ L"&#250;",L"ú" },
		{ L"&#251;",L"û" },
		{ L"&#252;",L"ü" },
		{ L"&#253;",L"ý" },
		{ L"&#254;",L"þ" },
		{ L"&#255;",L"ÿ" },
		{ L"&#256;",L"Ā" },
		{ L"&#257;",L"ā" },
		{ L"&#258;",L"Ă" },
		{ L"&#259;",L"ă" },
		{ L"&#260;",L"Ą" },
		{ L"&#261;",L"ą" },
		{ L"&#262;",L"Ć" },
		{ L"&#263;",L"ć" },
		{ L"&#264;",L"Ĉ" },
		{ L"&#265;",L"ĉ" },
		{ L"&#266;",L"Ċ" },
		{ L"&#267;",L"ċ" },
		{ L"&#268;",L"Č" },
		{ L"&#269;",L"č" },
		{ L"&#270;",L"Ď" },
		{ L"&#271;",L"ď" },
		{ L"&#272;",L"Đ" },
		{ L"&#273;",L"đ" },
		{ L"&#274;",L"Ē" },
		{ L"&#275;",L"ē" },
		{ L"&#276;",L"Ĕ" },
		{ L"&#277;",L"ĕ" },
		{ L"&#278;",L"Ė" },
		{ L"&#279;",L"ė" },
		{ L"&#280;",L"Ę" },
		{ L"&#281;",L"ę" },
		{ L"&#282;",L"Ě" },
		{ L"&#283;",L"ě" },
		{ L"&#284;",L"Ĝ" },
		{ L"&#285;",L"ĝ" },
		{ L"&#286;",L"Ğ" },
		{ L"&#287;",L"ğ" },
		{ L"&#288;",L"Ġ" },
		{ L"&#289;",L"ġ" },
		{ L"&#290;",L"Ģ" },
		{ L"&#291;",L"ģ" },
		{ L"&#292;",L"Ĥ" },
		{ L"&#293;",L"ĥ" },
		{ L"&#294;",L"Ħ" },
		{ L"&#295;",L"ħ" },
		{ L"&#296;",L"Ĩ" },
		{ L"&#297;",L"ĩ" },
		{ L"&#298;",L"Ī" },
		{ L"&#299;",L"ī" },
		{ L"&#300;",L"Ĭ" },
		{ L"&#301;",L"ĭ" },
		{ L"&#302;",L"Į" },
		{ L"&#303;",L"į" },
		{ L"&#304;",L"İ" },
		{ L"&#305;",L"ı" },
		{ L"&#306;",L"Ĳ" },
		{ L"&#307;",L"ĳ" },
		{ L"&#308;",L"Ĵ" },
		{ L"&#309;",L"ĵ" },
		{ L"&#310;",L"Ķ" },
		{ L"&#311;",L"ķ" },
		{ L"&#312;",L"ĸ" },
		{ L"&#313;",L"Ĺ" },
		{ L"&#314;",L"ĺ" },
		{ L"&#315;",L"Ļ" },
		{ L"&#316;",L"ļ" },
		{ L"&#317;",L"Ľ" },
		{ L"&#318;",L"ľ" },
		{ L"&#319;",L"Ŀ" },
		{ L"&#320;",L"ŀ" },
		{ L"&#321;",L"Ł" },
		{ L"&#322;",L"ł" },
		{ L"&#323;",L"Ń" },
		{ L"&#324;",L"ń" },
		{ L"&#325;",L"Ņ" },
		{ L"&#326;",L"ņ" },
		{ L"&#327;",L"Ň" },
		{ L"&#328;",L"ň" },
		{ L"&#329;",L"ŉ" },
		{ L"&#330;",L"Ŋ" },
		{ L"&#331;",L"ŋ" },
		{ L"&#332;",L"Ō" },
		{ L"&#333;",L"ō" },
		{ L"&#334;",L"Ŏ" },
		{ L"&#335;",L"ŏ" },
		{ L"&#336;",L"Ő" },
		{ L"&#337;",L"ő" },
		{ L"&#338;",L"Œ" },
		{ L"&#339;",L"œ" },
		{ L"&#340;",L"Ŕ" },
		{ L"&#341;",L"ŕ" },
		{ L"&#342;",L"Ŗ" },
		{ L"&#343;",L"ŗ" },
		{ L"&#344;",L"Ř" },
		{ L"&#345;",L"ř" },
		{ L"&#346;",L"Ś" },
		{ L"&#347;",L"ś" },
		{ L"&#348;",L"Ŝ" },
		{ L"&#349;",L"ŝ" },
		{ L"&#350;",L"Ş" },
		{ L"&#351;",L"ş" },
		{ L"&#352;",L"Š" },
		{ L"&#353;",L"š" },
		{ L"&#354;",L"Ţ" },
		{ L"&#355;",L"ţ" },
		{ L"&#356;",L"Ť" },
		{ L"&#357;",L"ť" },
		{ L"&#358;",L"Ŧ" },
		{ L"&#359;",L"ŧ" },
		{ L"&#360;",L"Ũ" },
		{ L"&#361;",L"ũ" },
		{ L"&#362;",L"Ū" },
		{ L"&#363;",L"ū" },
		{ L"&#364;",L"Ŭ" },
		{ L"&#365;",L"ŭ" },
		{ L"&#366;",L"Ů" },
		{ L"&#367;",L"ů" },
		{ L"&#368;",L"Ű" },
		{ L"&#369;",L"ű" },
		{ L"&#370;",L"Ų" },
		{ L"&#371;",L"ų" },
		{ L"&#372;",L"Ŵ" },
		{ L"&#373;",L"ŵ" },
		{ L"&#374;",L"Ŷ" },
		{ L"&#375;",L"ŷ" },
		{ L"&#376;",L"Ÿ" },
		{ L"&#377;",L"Ź" },
		{ L"&#378;",L"ź" },
		{ L"&#379;",L"Ż" },
		{ L"&#380;",L"ż" },
		{ L"&#381;",L"Ž" },
		{ L"&#382;",L"ž" },
		{ L"&#383;",L"ſ" },
		{ L"&#340;",L"Ŕ" },
		{ L"&#341;",L"ŕ" },
		{ L"&#342;",L"Ŗ" },
		{ L"&#343;",L"ŗ" },
		{ L"&#344;",L"Ř" },
		{ L"&#345;",L"ř" },
		{ L"&#346;",L"Ś" },
		{ L"&#347;",L"ś" },
		{ L"&#348;",L"Ŝ" },
		{ L"&#349;",L"ŝ" },
		{ L"&#350;",L"Ş" },
		{ L"&#351;",L"ş" },
		{ L"&#352;",L"Š" },
		{ L"&#353;",L"š" },
		{ L"&#354;",L"Ţ" },
		{ L"&#355;",L"ţ" },
		{ L"&#356;",L"Ť" },
		{ L"&#577;",L"ť" },
		{ L"&#358;",L"Ŧ" },
		{ L"&#359;",L"ŧ" },
		{ L"&#360;",L"Ũ" },
		{ L"&#361;",L"ũ" },
		{ L"&#362;",L"Ū" },
		{ L"&#363;",L"ū" },
		{ L"&#364;",L"Ŭ" },
		{ L"&#365;",L"ŭ" },
		{ L"&#366;",L"Ů" },
		{ L"&#367;",L"ů" },
		{ L"&#368;",L"Ű" },
		{ L"&#369;",L"ű" },
		{ L"&#370;",L"Ų" },
		{ L"&#371;",L"ų" },
		{ L"&#372;",L"Ŵ" },
		{ L"&#373;",L"ŵ" },
		{ L"&#374;",L"Ŷ" },
		{ L"&#375;",L"ŷ" },
		{ L"&#376;",L"Ÿ" },
		{ L"&#377;",L"Ź" },
		{ L"&#378;",L"ź" },
		{ L"&#379;",L"Ż" },
		{ L"&#380;",L"ż" },
		{ L"&#381;",L"Ž" },
		{ L"&#382;",L"ž" },
		{ L"&#383;",L"ſ" },

	};


	std::wstring strRet(strSource);
	std::wregex r(L"&#\\d+;"); // &#32; "&#8482;

	int shift(0);
	for (std::wsregex_iterator i = std::wsregex_iterator(strSource.begin(), strSource.end(), r); i != std::wsregex_iterator(); ++i)
	{
		std::wsmatch m = *i;
		//std::cout << m.str() << " at position " << m.position() << '\n';
		auto f = mapCache.find(m.str());
		if (f != mapCache.end())
		{
			strRet.replace(m.position() - shift, m.str().size(), f->second);
			shift += m.str().size() - f->second.size();
		}
	}

	return strRet;
}



std::vector<std::string> Split(std::string str, const std::string &strDelimiter)
{
	size_t pos_start = 0, pos_end, delim_len = strDelimiter.length();
	std::string token;
	std::vector<std::string> res;
	while ((pos_end = str.find(strDelimiter, pos_start)) != std::string::npos)
	{
		token = str.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}
	res.push_back(str.substr(pos_start));
	return res;
}

std::string Trim(const std::string &s)
{
	auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
	auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

static bool FilterFilesByExtensions(const std::string &strDir, const std::vector<std::string> &strExtensions, std::vector<std::string> &files)
{
	bool bRet(false);

	if (fs::is_regular_file(strDir))
	{
		auto ext = fs::path(strDir).extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
		if (strExtensions.empty() || find(strExtensions.begin(), strExtensions.end(), ext) != strExtensions.end())
		{
			files.push_back(strDir);
			bRet = true;
		}
	}
	return bRet;
}
// version v1
// doesn't work with wildcards :(
std::vector<std::string> GetDirectoryFiles(const std::string &strDir, const std::vector<std::string> &strExtensions, bool bSub)
{
	std::vector<std::string> files;
	if (fs::is_regular_file(strDir))
	{
		FilterFilesByExtensions(strDir, strExtensions, files);
	}
	else
	{
		if (bSub)
		{
			for (auto & p : fs::recursive_directory_iterator(strDir))
			{
				FilterFilesByExtensions(p.path().generic_string().c_str(), strExtensions, files);
			}
		}
		else
		{
			for (auto & p : fs::directory_iterator(strDir))
			{
				FilterFilesByExtensions(p.path().generic_string().c_str(), strExtensions, files);
			}
		}

	}
	return files;
}

