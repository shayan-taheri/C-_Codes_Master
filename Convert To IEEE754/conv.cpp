 #include <iostream>
 #include <deque>
 #include <vector>
 using namespace std;

 deque<bool> UInt_to_Binary (unsigned long int number) {	// The function for converting unsigned integer of IEEE754 number to its binary format.

	 deque<bool> answer;

	 while (number > 0) {
		 answer.push_back (number % 2);
		 number = number / 2;}
	 return answer;
 }

 unsigned int float_to_IEEE754 (float float_num) {

	unsigned total_bits = 32;
	unsigned exp_bits = 8;
	float float_normal;
	int shift;
	long long sign, exp, mantissa;
	unsigned mantissa_bits = total_bits - exp_bits - 1;				// total_bits = sign_bit + exp_bits + mantissa_bits

	if (float_num == 0.0) return 0;					// if the float is equal to zero, its equivalent is zero in "Unsigned Integer".

	if (float_num < 0) { sign = 1; float_normal = -float_num; }			// if float number is negative, build representation based on that.
	else { sign = 0; float_normal = float_num; }						// otherwise, build representation based on the positive one.

	// Calculating the normalized form of float_num and update the exponent.

	shift = 0;
	while (float_normal >= 2.0) { float_normal /= 2.0; shift++; }
	while (float_normal < 1.0) { float_normal *= 2.0; shift--; }
	float_normal = float_normal - 1.0;									// We drop the "1" (before the '.') from representation in IEEE754.

	// Calculating the binary form of the mantissa and rounding it.

	mantissa = float_normal * ((1LL << mantissa_bits) + 0.5*float_num);

	exp = shift + 127;			// exponent (IEEE754) = exponent (real) + bias (127)

	return (sign << (total_bits - 1)) | (exp << (total_bits - exp_bits - 1)) | mantissa;		// Constructing the IEEE754 representation.
}



int main(void)
{
	float IN1 = 0.0;
	float IN2 = 0.0;
	float Res = 0.0;
	unsigned int f_to_i = 0;
	deque<bool> temp;
	bool sval = 0;
	vector<bool> val;

	cout << "Please Enter Input 1: ";
	cin >> IN1;
	cout << '\n' << "Please Enter Input 2: ";
	cin >> IN2;

	cout << '\n';

	Res = 0.0;
	f_to_i = 0;
	temp.clear();
	sval = 0;
	val.clear();

	Res = IN1 * IN2;

	f_to_i = float_to_IEEE754 (Res);

	temp = UInt_to_Binary (f_to_i);

	if (temp.size() < 32) {
		for (deque<bool>::size_type oo = 0; oo < (32 - temp.size()); oo++) {
			temp.push_back(0);
		}
	}

	while (!temp.empty()) {
		sval = temp.back();
		val.push_back(sval);
		temp.pop_back();}

	cout << "Multiplication Result:" << '\n';

	cout << "Sign: " << val[0] << '\n';

	cout << "Exponent: ";
	for (vector<bool>::size_type hh = 1; hh <= 8; hh++) {
		cout << val[hh] << ' ';
	}

	cout << '\n';

	cout << "Mantissa: ";
	for (vector<bool>::size_type xx = 9; xx <= 31; xx++) {
		cout << val[xx] << ' ';
	}

	cout << '\n' << '\n';

	Res = 0.0;
	f_to_i = 0;
	temp.clear();
	sval = 0;
	val.clear();

	Res = IN1 + IN2;

	f_to_i = float_to_IEEE754 (Res);

	temp = UInt_to_Binary (f_to_i);

	if (temp.size() < 32) {
		for (deque<bool>::size_type oo = 0; oo < (32 - temp.size()); oo++) {
			temp.push_back(0);
		}
	}

	while (!temp.empty()) {
		sval = temp.back();
		val.push_back(sval);
		temp.pop_back();}

	cout << "Addition Result:" << '\n';

	cout << "Sign: " << val[0] << '\n';

	cout << "Exponent: ";
	for (vector<bool>::size_type hh = 1; hh <= 8; hh++) {
		cout << val[hh] << ' ';
	}

	cout << '\n';

	cout << "Mantissa: ";
	for (vector<bool>::size_type xx = 9; xx <= 31; xx++) {
		cout << val[xx] << ' ';
	}


	cout << '\n' << '\n';

	Res = 0.0;
	f_to_i = 0;
	temp.clear();
	sval = 0;
	val.clear();

	Res = IN1 - IN2;

	f_to_i = float_to_IEEE754 (Res);

	temp = UInt_to_Binary (f_to_i);

	if (temp.size() < 32) {
		for (deque<bool>::size_type oo = 0; oo < (32 - temp.size()); oo++) {
			temp.push_back(0);
		}
	}

	while (!temp.empty()) {
		sval = temp.back();
		val.push_back(sval);
		temp.pop_back();}

	cout << "Subtraction Result:" << '\n';

	cout << "Sign: " << val[0] << '\n';

	cout << "Exponent: ";
	for (vector<bool>::size_type hh = 1; hh <= 8; hh++) {
		cout << val[hh] << ' ';
	}

	cout << '\n';

	cout << "Mantissa: ";
	for (vector<bool>::size_type xx = 9; xx <= 31; xx++) {
		cout << val[xx] << ' ';
	}

	return 0;
}
