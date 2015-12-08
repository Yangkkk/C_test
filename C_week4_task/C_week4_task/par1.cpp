Complex & operator=(string s){
	int pos = s.find("+", 0);
	string s0 = s.substr(0, pos);
	string s1 = s.substr(pos + 1, s.length() - pos - 2);
	r = atof(s0.c_str());
	i = atof(s1.c_str());
	return *this;
}