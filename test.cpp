#include <iostream>
#include <cstdlib>

using namespace std;
string addarrays(string, string);

string negarray(string X) {
	int bounds = X.length();
	int itemp = 0;
	string temp = "";
	string nines = "";
	
	for (int i = 0; i < bounds; i++) {
		itemp = 9 - (int(X[i]) - 48);
		X[i] = char(itemp+48);
		if (!(i == bounds - 1)) {
			temp = "0" + temp;
		}
	}
	temp = temp + "1";
	cout << X << endl;
	cout << temp << endl;
	return addarrays(X, temp);
	
}
string addarrays(string X, string Y) {
	bool carry = 0;
	int bounds = 0;
	int result = 0;
	string addition = "";

	if (X.length() > Y.length()) {Y = "0" + Y;}
	if (X.length() < Y.length()) {X = "0" + X;}
	bounds = X.length() - 1;
	for (int k = 0; k < X.length(); k++) {
		addition.push_back('0');
	}
	for (int k = bounds; k >= 0; k--) {
		if (carry == 1) {
			result = 1 + (int(X[k]) - 48) + (int(Y[k]) - 48);
			if (result / 10) {
				carry = 1;
			}
			else
				carry = 0;
			addition[k] = char(result % 10 + 48);
		}
		else {
			result = (int(X[k]) - 48) + (int(Y[k]) - 48);
			if (result / 10) {
				carry = 1;
			}
			else
				carry = 0;
			addition[k] = char(result % 10 + 48);
		}
	}
	if (carry == 1) {
		addition = "1" + addition;
	}
	cout << "Inside add: " << addition << endl;
	return addition;
}

int main() {
	string a = "1542";
	string b = "10000";
	cout << addarrays(a, b);
	return 0;
}