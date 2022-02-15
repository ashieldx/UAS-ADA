#include <iostream>

using namespace std;

bool searchString(string a, string b){
	int i = 0, j = 0, pos = 0;
	int len_a = a.length(), len_b = b.length();
	bool flag = false;
		
	while(j < len_b){ 
		if(a[i] == b[j]){
			i++, j++;
			if(i == len_a){ 
				i = 0;
				flag = true;
			}
		}else{
			if(++pos == len_a) return false;
			i = pos; 
			j = 0; 
			flag = false;
		}
	}
	if(i) return true;
	return flag;	
}

int main(){
	
	string a, b;
	cin >> a >> b;
	cout << (searchString(a, b) ? "YA" : "TIDAK") << endl;
	
	return 0;
}
