#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;

string BinToHex(string str);//������ת��Ϊʮ������
string HexToBin(string str);//ʮ������ת��Ϊ������
int BinToDec(string str);//������ת��Ϊʮ����
string DecToBin(int str);//ʮ����ת��Ϊ������
int HexToDec(string str);//ʮ������ת��Ϊʮ����
string DecToHex(int str);//ʮ����ת��Ϊʮ������
string padding(string str);//�������
string LeftShift(string str, int len);//ѭ������lenλ
string XOR(string str1, string str2);//���
string AND(string str1, string str2);//��
string OR(string str1, string str2);//��
string NOT(string str);//��
char binXor(char str1, char str2);//�����ص����
char binAnd(char str1, char str2);//�����ص���
string ModAdd(string str1, string str2);//mod 2^32����
string P1(string str);//ʵ���û�����P1��X��
string P0(string str);//ʵ���û�����P0��X��
string T(int j);//����Tj����
string FF(string str1, string str2, string str3, int j);//ʵ�ֲ�������FF
string GG(string str1, string str2, string str3, int j);//ʵ�ֲ�������GG
string extension(string str);//��Ϣ��չ����
string compress(string str1, string str2);//��Ϣѹ������
string iteration(string str);//����ѹ������ʵ��
void rho_attack();//pollard rho�㷨����
clock_t begin, end;
string BinToHex(string str) {
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0) {
		str = "0" + str;
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;
		if (temp < 10) {
			hex += to_string(temp);
		}
		else {
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

string HexToBin(string str) {
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			bin += table[str[i] - 'A' + 10];
		}
		else {
			bin += table[str[i] - '0'];
		}
	}
	return bin;
}

int BinToDec(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

string DecToBin(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

int HexToDec(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			dec += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else {
			dec += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return dec;
}

string DecToHex(int str) {
	string hex = "";
	int temp = 0;
	while (str >= 1) {
		temp = str % 16;
		if (temp < 10 && temp >= 0) {
			hex = to_string(temp) + hex;
		}
		else {
			hex += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return hex;
}
string padding(string str) {
	string res = "";
	for (int i = 0; i < str.size(); i++) {
		res += DecToHex((int)str[i]);
	}
    int res_length = res.size() * 4;
	//����sm3������,�ڻ�õ����ݺ�����1����16�������൱�������8
	res += "8";
	while (res.size() % 128 != 112) {
		res += "0";//��0���������
	}
	string res_len = DecToHex(res_length);//���ڼ�¼���ݳ��ȵ��ַ���
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LeftShift(string str, int len) {
	string res = HexToBin(str);
	res = res.substr(len) + res.substr(0, len);
	return BinToHex(res);
}

string XOR(string str1, string str2) {
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string AND(string str1, string str2) {
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

string OR(string str1, string str2) {
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BinToHex(res);
}

string NOT(string str) {
	string res1 = HexToBin(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BinToHex(res);
}

char binXor(char str1, char str2) {
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {
	string res1 = HexToBin(str1);
	string res2 = HexToBin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) {
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1') {
				temp = binAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return BinToHex(res);
}

string P1(string str) {
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) {
	//����
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) {
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}

string GG(string str1, string str2, string str3, int j) {
	if (0 <= j && j <= 15) {
		return XOR(XOR(str1, str2), str3);
	}
	else {
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
string extension(string str) {
	string res = str;//�ַ������ʹ洢ǰ68λ�洢��չ��Wֵ
	for (int i = 16; i < 68; i++) {//���ݹ�ʽ���ɵ�17λ����68λ��Wֵ
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	//���ݹ�ʽ����64λW'
	res += XOR(res.substr(0 * 8, 8), res.substr((0 + 4) * 8, 8));
	res += XOR(res.substr(1 * 8, 8), res.substr((1 + 4) * 8, 8));
	res += XOR(res.substr(2 * 8, 8), res.substr((2 + 4) * 8, 8));
	res += XOR(res.substr(3 * 8, 8), res.substr((3 + 4) * 8, 8));
	res += XOR(res.substr(4 * 8, 8), res.substr((4 + 4) * 8, 8));
	res += XOR(res.substr(5 * 8, 8), res.substr((5 + 4) * 8, 8));
	res += XOR(res.substr(6 * 8, 8), res.substr((6 + 4) * 8, 8));
	res += XOR(res.substr(7 * 8, 8), res.substr((7 + 4) * 8, 8));
	res += XOR(res.substr(8 * 8, 8), res.substr((8 + 4) * 8, 8));
	res += XOR(res.substr(9 * 8, 8), res.substr((9 + 4) * 8, 8));
	res += XOR(res.substr(10 * 8, 8), res.substr((10 + 4) * 8, 8));
	res += XOR(res.substr(11 * 8, 8), res.substr((11 + 4) * 8, 8));
	res += XOR(res.substr(12 * 8, 8), res.substr((12 + 4) * 8, 8));
	res += XOR(res.substr(13 * 8, 8), res.substr((13 + 4) * 8, 8));
	res += XOR(res.substr(14 * 8, 8), res.substr((14 + 4) * 8, 8));
	res += XOR(res.substr(15 * 8, 8), res.substr((15 + 4) * 8, 8));
	res += XOR(res.substr(16 * 8, 8), res.substr((16 + 4) * 8, 8));
	res += XOR(res.substr(17 * 8, 8), res.substr((17 + 4) * 8, 8));
	res += XOR(res.substr(18 * 8, 8), res.substr((18 + 4) * 8, 8));
	res += XOR(res.substr(19 * 8, 8), res.substr((19 + 4) * 8, 8));
	res += XOR(res.substr(20 * 8, 8), res.substr((20 + 4) * 8, 8));
	res += XOR(res.substr(21 * 8, 8), res.substr((21 + 4) * 8, 8));
	res += XOR(res.substr(22 * 8, 8), res.substr((22 + 4) * 8, 8));
	res += XOR(res.substr(23 * 8, 8), res.substr((23 + 4) * 8, 8));
	res += XOR(res.substr(24 * 8, 8), res.substr((24 + 4) * 8, 8));
	res += XOR(res.substr(25 * 8, 8), res.substr((25 + 4) * 8, 8));
	res += XOR(res.substr(26 * 8, 8), res.substr((26 + 4) * 8, 8));
	res += XOR(res.substr(27 * 8, 8), res.substr((27 + 4) * 8, 8));
	res += XOR(res.substr(28 * 8, 8), res.substr((28 + 4) * 8, 8));
	res += XOR(res.substr(29 * 8, 8), res.substr((29 + 4) * 8, 8));
	res += XOR(res.substr(30 * 8, 8), res.substr((30 + 4) * 8, 8));
	res += XOR(res.substr(31 * 8, 8), res.substr((31 + 4) * 8, 8));
	res += XOR(res.substr(32 * 8, 8), res.substr((32 + 4) * 8, 8));
	res += XOR(res.substr(33 * 8, 8), res.substr((33 + 4) * 8, 8));
	res += XOR(res.substr(34 * 8, 8), res.substr((34 + 4) * 8, 8));
	res += XOR(res.substr(35 * 8, 8), res.substr((35 + 4) * 8, 8));
	res += XOR(res.substr(36 * 8, 8), res.substr((36 + 4) * 8, 8));
	res += XOR(res.substr(37 * 8, 8), res.substr((37 + 4) * 8, 8));
	res += XOR(res.substr(38 * 8, 8), res.substr((38 + 4) * 8, 8));
	res += XOR(res.substr(39 * 8, 8), res.substr((39 + 4) * 8, 8));
	res += XOR(res.substr(40 * 8, 8), res.substr((40 + 4) * 8, 8));
	res += XOR(res.substr(41 * 8, 8), res.substr((41 + 4) * 8, 8));
	res += XOR(res.substr(42 * 8, 8), res.substr((42 + 4) * 8, 8));
	res += XOR(res.substr(43 * 8, 8), res.substr((43 + 4) * 8, 8));
	res += XOR(res.substr(44 * 8, 8), res.substr((44 + 4) * 8, 8));
	res += XOR(res.substr(45 * 8, 8), res.substr((45 + 4) * 8, 8));
	res += XOR(res.substr(46 * 8, 8), res.substr((46 + 4) * 8, 8));
	res += XOR(res.substr(47 * 8, 8), res.substr((47 + 4) * 8, 8));
	res += XOR(res.substr(48 * 8, 8), res.substr((48 + 4) * 8, 8));
	res += XOR(res.substr(49 * 8, 8), res.substr((49 + 4) * 8, 8));
	res += XOR(res.substr(50 * 8, 8), res.substr((50 + 4) * 8, 8));
	res += XOR(res.substr(51 * 8, 8), res.substr((51 + 4) * 8, 8));
	res += XOR(res.substr(52 * 8, 8), res.substr((52 + 4) * 8, 8));
	res += XOR(res.substr(53 * 8, 8), res.substr((53 + 4) * 8, 8));
	res += XOR(res.substr(54 * 8, 8), res.substr((54 + 4) * 8, 8));
	res += XOR(res.substr(55 * 8, 8), res.substr((55 + 4) * 8, 8));
	res += XOR(res.substr(56 * 8, 8), res.substr((56 + 4) * 8, 8));
	res += XOR(res.substr(57 * 8, 8), res.substr((57 + 4) * 8, 8));
	res += XOR(res.substr(58 * 8, 8), res.substr((58 + 4) * 8, 8));
	res += XOR(res.substr(59 * 8, 8), res.substr((59 + 4) * 8, 8));
	res += XOR(res.substr(60 * 8, 8), res.substr((60 + 4) * 8, 8));
	res += XOR(res.substr(61 * 8, 8), res.substr((61 + 4) * 8, 8));
	res += XOR(res.substr(62 * 8, 8), res.substr((62 + 4) * 8, 8));
	res += XOR(res.substr(63 * 8, 8), res.substr((63 + 4) * 8, 8));
	return res;
}

string compress(string str1, string str2) {
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
		//cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	}
	string res = (A + B + C + D + E + F + G + H);
	//cout << endl;
	return res;
}

string iteration(string str) {
	int num = str.size() / 128;
	//cout << "group num:" + to_string(num) << endl;
	//cout << endl;
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		//cout << "the " << to_string(i + 1) << " group:" << endl;
		//cout << endl;
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}
//������
#define max_num 65536//2^16
//���
string inlist[max_num];
string outlist[max_num];

void rho_attack() {
	string str;
	string result;
	string paddingValue;
	int start = 0;
	int rho = 0;
	for (int i = 0; i < max_num; outlist[i++] = result) {
		if (rho != -1) {
			rho = 2 * rho + 1;	//rho���Ʊ��ʽ	
		}
		else {
			//����int���ޣ���һ����ʼֵ���¿�ʼ
			rho = ++start;
		}
		//cout << "Ŀǰ���ȣ�" << i << endl;
		str = to_string(rho);
		inlist[i] = str;
		paddingValue = padding(str);
		result = iteration(paddingValue);
		//���Ѱ������ײ
		for (int j = 0; j < i; j++) {
			if (outlist[j].substr(0, 4) == result.substr(0, 4) && str != inlist[j]) {
				cout << endl;
				cout << "collision string input 1 :" + str << endl << endl;
				cout << "collision hash value 1:" << endl;
				cout << result.substr(0, 8) << "  ";
				cout << result.substr(8, 8) << "  ";
				cout << result.substr(16, 8) << "  ";
				cout << result.substr(24, 8) << "  ";
				cout << result.substr(32, 8) << "  ";
				cout << result.substr(40, 8) << "  ";
				cout << result.substr(48, 8) << "  ";
				cout << result.substr(56, 8) << "  ";
				cout << endl;
				cout << "collision string input 2 :" + inlist[j] << endl << endl;
				cout << "collision hash value 2:" << endl;
				cout << outlist[j].substr(0, 8) << "  ";
				cout << outlist[j].substr(8, 8) << "  ";
				cout << outlist[j].substr(16, 8) << "  ";
				cout << outlist[j].substr(24, 8) << "  ";
				cout << outlist[j].substr(32, 8) << "  ";
				cout << outlist[j].substr(40, 8) << "  ";
				cout << outlist[j].substr(48, 8) << "  ";
				cout << outlist[j].substr(56, 8) << "  ";
				cout << endl << "finding num in all:  " << i;
				return;
			}
		}
	}
	cout << "rho attack failed!";
}

int main() {
	clock_t begin;
	clock_t end;
	begin = clock();
	rho_attack();
	end = clock();
	cout << "������ϣֵǰ16bit������ײ����ʱ��Ϊ��" <<(double) (end - begin) / CLOCKS_PER_SEC<<"s"<<endl;
	return 0;
}
