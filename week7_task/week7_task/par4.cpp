#include<iostream>
#include<string>
using namespace std;
string ss[21];
int total;
bool it = true;
enum{ copy_, add, find, rfind, insert, reset, print, printall, over };
string dealstring();
int dealint();
void deal();
int transit(string & a)
{
	if (a == "copy")return copy_;
	if (a == "add")return add;
	if (a == "find")return find;
	if (a == "rfind")return rfind;
	if (a == "insert")return insert;
	if (a == "reset")return reset;
	if (a == "print")return print;
	if (a == "printall")return printall;
	if (a == "over")return over;
	return -1;
}
bool IsInt(const string & ss)
{
	int len = ss.length(), i;
	if (len > 5)return false;
	for (i = 0; i < len; i++)
	if (isdigit(ss[i]) == 0)return false;
	return true;
}
int dealint()
{
	int N;
	string a, S;
	cin >> a;
	switch (transit(a)){
	case "find":
		S = dealstring(); N = dealint();
		if (strstr(ss[N].c_str(), S.c_str()) != NULL)return ss[N].find(S);
		else return S.length();
	case "rfind"
		:S = dealstring(); N = dealint();
		if (strstr(ss[N].c_str(), S.c_str()) != NULL)return ss[N].rfind(S);
		else return S.length();
	default: return atoi(a.c_str());
	}
}
string dealstring()
{
	int N, X, L;
	static string temp;
	string a, S1, S2;
	static char b[10];
	cin >> a;
	switch (transit(a)){
	case copy_:N = dealint(); X = dealint(); L = dealint(); return ss[N].substr(X, L);
	case add:S1 = dealstring(); S2 = dealstring();
		if (IsInt(S1) && IsInt(S2)){ _itoa_s((atoi(S1.c_str()) + atoi(S2.c_str())), b, 10); temp = b; return temp; }
		else return S1 + S2;
	default: return a;
	}
}
void deal()
{
	int N, X;
	string S;
	string a;
	cin >> a;
	switch (transit(a)){
	case insert:S = dealstring(); N = dealint(); X = dealint(); ss[N].insert(X, S); break;
	case reset:S = dealstring(); N = dealint(); ss[N] = S; break;
	case print:N = dealint(); cout << ss[N] << endl; break;
	case printall:for (int i = 1; i <= total; i++)cout << ss[i] << endl; break;
	case over:it = false; break;
	default:;
	}
}
int main()
{
	cin >> total;
	for (int i = 1; i <= total; i++)cin >> ss[i];
	while (it)deal();
	return 0;
}
