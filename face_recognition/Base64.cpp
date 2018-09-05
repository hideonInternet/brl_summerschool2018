#include "Base64.h"

string ZBase64::Encode(const unsigned char* Data, int DataByte)
{
	//�����
	const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//����ֵ
	string strEncode;
	unsigned char Tmp[4] = { 0 };
	int LineLength = 0;
	for (int i = 0; i<(int)(DataByte / 3); i++)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode += EncodeTable[Tmp[1] >> 2];
		strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode += EncodeTable[Tmp[3] & 0x3F];
		if (LineLength += 4, LineLength == 76) { strEncode += "\r\n"; LineLength = 0; }
	}
	//��ʣ�����ݽ��б���
	int Mod = DataByte % 3;
	if (Mod == 1)
	{
		Tmp[1] = *Data++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode += "==";
	}
	else if (Mod == 2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode += "=";
	}
	ofstream file;
	file.open("test.txt", 'w');
	file << urlencode(strEncode);
	return strEncode;
}

string ZBase64::Decode(const char* Data, int DataByte, int& OutByte)
{
	//�����
	const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62, // '+'
		0, 0, 0,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};
	//����ֵ
	string strDecode;
	int nValue;
	int i = 0;
	while (i < DataByte)
	{
		if (*Data != '\r' && *Data != '\n')
		{
			nValue = DecodeTable[*Data++] << 18;
			nValue += DecodeTable[*Data++] << 12;
			strDecode += (nValue & 0x00FF0000) >> 16;
			OutByte++;
			if (*Data != '=')
			{
				nValue += DecodeTable[*Data++] << 6;
				strDecode += (nValue & 0x0000FF00) >> 8;
				OutByte++;
				if (*Data != '=')
				{
					nValue += DecodeTable[*Data++];
					strDecode += nValue & 0x000000FF;
					OutByte++;
				}
			}
			i += 4;
		}
		else// �س�����,����
		{
			Data++;
			i++;
		}
	}
	return strDecode;
}
void hexchar(unsigned char c, unsigned char &hex1, unsigned char &hex2)
{
	hex1 = c / 16;
	hex2 = c % 16;
	hex1 += hex1 <= 9 ? '0' : 'a' - 10;
	hex2 += hex2 <= 9 ? '0' : 'a' - 10;
}

string ZBase64::urlencode(string s)
{
	const char *str = s.c_str();
	vector<char> v(s.size());
	v.clear();
	for (size_t i = 0, l = s.size(); i < l; i++)
	{
		char c = str[i];
		if ((c >= '0' && c <= '9') ||
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			c == '-' || c == '_' || c == '.' || c == '!' || c == '~' ||
			c == '*' || c == '\'' || c == '(' || c == ')')
		{
			v.push_back(c);
		}
		else if (c == ' ')
		{
			v.push_back('+');
		}
		else
		{
			v.push_back('%');
			unsigned char d1, d2;
			hexchar(c, d1, d2);
			v.push_back(d1);
			v.push_back(d2);
		}
	}

	return string(v.cbegin(), v.cend());
}
