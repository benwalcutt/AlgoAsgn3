#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

string addarrays(string, string);

string negarray(string X, int digits) {
/*	Negarray Routine
	Take in a string and find the nines complement	
*/
	// variable declaration
	
	// bounds is used because sometimes using x.length() in for loops gave errant results
	int bounds = X.length();
	int itemp = 0;
	int difference = 0;
	string temp = "";
	string nines = "";
	
	// pad with zeros
	difference = digits - bounds;
	for (int i = 1; i <= difference; i++) {
		X = "0" + X;
	}
	
	bounds = X.length();
	for (int i = 0; i < bounds; i++) {
		// find int of char, subtract 48 to get actually int, subtract from 9
		itemp = 9 - (int(X[i]) - 48);
		
		// add 48 to result and then convert back to int and place back in string
		X[i] = char(itemp+48);
		
		// pad with zeros
		if (!(i == bounds - 1)) {
			temp = "0" + temp;
		}
	}
	
	// add one since we are using nines complements
	temp = temp + "1";
	return addarrays(X, temp);
	
}

string addarrays(string X, string Y) {
/*	Addarrays routine
	Take in two strings of numbers and add them one at a time
*/
	// variable declaration
	bool carry = 0;
	int bounds = 0;
	int result = 0;
	string addition = "";

	// pad to make sure same length
	if (X.length() > Y.length()) {
		int bounds = X.length() - Y.length();
		for (int i = 1; i <= bounds; i++) {
			Y = "0" + Y;
		}
	}
	if (X.length() < Y.length()) {
		int bounds = Y.length() - X.length();
		for (int i = 1; i <= bounds; i++) {
			X = "0" + X;
		}
	}
	
	// setting up length of addition to be the same length as the inputs (plus one for carry)
	bounds = X.length() - 1;
	for (int k = 0; k < X.length(); k++) {
		addition.push_back('0');
	}
	
	// do the actual addition one index at at time, checking to see if the carry flag is up
	for (int k = bounds; k >= 0; k--) {
		if (carry == 1) {
			result = 1 + (int(X[k]) - 48) + (int(Y[k]) - 48);
			// there is a carry, raise the flag
			if (result / 10) {
				carry = 1;
			}
			else
				carry = 0;
			addition[k] = char(result % 10 + 48);
		}
		else {
			result = (int(X[k]) - 48) + (int(Y[k]) - 48);
			// there is a carry, raise the flag
			if (result / 10) {
				carry = 1;
			}
			else
				carry = 0;
			addition[k] = char(result % 10 + 48);
		}
	}
	// carry remains to be raised, so add a one to end of the output
	if (carry == 1) {
		addition = "1" + addition;
	}
	return addition;
}

string myitoa(long long param) {
    long long modresult;
    string first = "";
    string second = "";
    bool negative = 0;
	
	if (param < 0) {
		negative = 1;
		param *= -1;
	}
	
    do {
        // save the ones digit
        modresult = param % 10;
        // lose the ones digit
        param = param / 10;
        
        switch (modresult) {
            case 0: {
                first = "0";
                break;
            }
            case 1: {
                first = "1";
                break;
            }
            case 2: {
                first = "2";
                break;
            }
            case 3: {
                first = "3";
                break;
            }
            case 4: {
                first = "4";
                break;
            }
            case 5: {
                first = "5";
                break;
            }
            case 6: {
                first = "6";
                break;
            }
            case 7: {
                first = "7";
                break;
            }
            case 8: {
                first = "8";
                break;
            }
            case 9: {
                first = "9";
                break;
            } 
        }
        second = first + second;
    } while(param / 1 != 0);
	if (negative) {second = "-" + second;}
    return second;
}
	
string kara(string a, string b) {
/*  Karatsuba routine:
	Routine that takes in two strings of numbers and multiplies them
	recursively using the Karatsuba algorigthm.
*/

	// Variable declaration
	int n = 0;
	int m = 0;
	int cutamount = 0;
	
	// strings to hold the split strings
	string high1 = "";
	string high2 = "";
	string low1 = "";
	string low2 = "";
	
	// strings to hold results
	string r = "";
	string p = "";
	string q = "";
	
	// various strings used as intermediate placeholders
	string inter = "";
	string addition = "";
	string temp1 = "";
	string temp2 = "";
	string temp3 = "";
	
	// two intermediate result placeholders
	unsigned long long result = 0;
	unsigned long long result2 = 0;
	
	// check if the input strings are 0
	result = atoi(a.c_str());
	if (result == 0) {return "0";}
	result = atoi(b.c_str());	
	if (result == 0) {return "0";}
	
	// determine length which is used in the return part of the karatsuba algorithm
	n = max(a.length(), b.length());
	
	// if the numbers are under the threshold, do immediate multiplication
	if (n < 4) {
		result = atol(a.c_str()) * atol(b.c_str());
		return myitoa(result);
	}
	
	// pad the input strings with zeros to ensure they are the same length
	if (b.length() < n) {
		int padding = 0;
		padding = n - b.length();
		for (int j = 1; j <= padding; j++) {
			b = "0" + b;
		}
	}
	
	if (a.length() < n) {
		int padding = 0;
		padding = n - a.length();
		for (int j = 1; j <= padding; j++) {
			a = "0" + a;
		}
	}
	// determine the middle point and round up
	// easiest way I could think to do it and then realized there were other methods
	if (n % 2) {
		m = n / 2 + 1;
		high1 = a.substr(0, m - 1);
		low1 = a.substr(m - 1);
	
		high2 = b.substr(0, m - 1);
		low2 = b.substr(m - 1);
	}
	else {
		m = n / 2;
		high1 = a.substr(0, m);
		low1 = a.substr(m);
	
		high2 = b.substr(0, m);
		low2 = b.substr(m);
	}
	
	// start the karatsuba algorithm
	
	q = kara(low1, low2);
	
	//result = atol(low1.c_str()) + atol(high1.c_str());
	//result2 = atol(low2.c_str()) + atol(high2.c_str());
	
	temp1 = addarrays(low1, high1);
	temp2 = addarrays(low2, high2);
	
	r = kara(temp1, temp2);
	p = kara(high1, high2);
	
	// k is used to negate P and Q so that we don't need subtraction 
	int k = r.length();

	temp1 = negarray(p, k);
	temp2 = negarray(q, k);
	addition = addarrays(r, temp1);
	addition = addarrays(addition, temp2);

	// determine how much to remove from front of result since we used nines complements ish
	cutamount = addition.length() - r.length();
	
	// and then cut
	inter = addition.substr(cutamount);
	
	// trim off leading zeros
	int counter = 0;
	while (inter[0] == '0') {
		inter.erase(0, 1);	
	}
	// pad P and inter to resemble multiplying by 10^2m and 10^m respectively	
	for (int i = 1; i <= 2 * m; i++) {
		p.push_back('0');
	}
	for (int i = 1; i <= m; i++) {
		inter.push_back('0');
	}
	
	

	// once again, padding with zeros to ensure same length
	int lengthdiff = p.length() - inter.length();

	for (int k = 1; k <= lengthdiff; k++) {
		inter = "0" + inter;
	}
	lengthdiff = p.length() - q.length();
	for (int k = 1; k <= lengthdiff; k++) {
		q = "0" + q;
	}
	// finally, add everything
	addition = addarrays(p, inter);
	addition = addarrays(addition, q);
	
	
	// trim leading zeros
	while (addition[0] == '0') {
		addition.erase(0, 1);		
	}
	return addition;	
}

int main() {
	string first;
	string second;
	string input;
	string output;

	do {
		getline(cin, input);
		if (input == "0") {break;}
		
		first = new char[input.length()];
		first = input;
		
		getline(cin, input);

		second = new char[input.length()];
		second = input;

		output = kara(first, second);
		cout << output << endl;	

	} while(1);

	return 0;
}
