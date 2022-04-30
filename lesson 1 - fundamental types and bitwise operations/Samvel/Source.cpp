#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
Задача 1.
С помощью битовых операций проверить число на четность
примеры 7 -> false, 4578 -> true
*/
bool is_even(int x)
{
	return !(x & 1);
}

/*
Задача 2.
Посчитать количество нулей в начале двоичного представления :
пример x = 784252715 (00101110101111101011111100101011)->функция должна возвращать 2
*/
int nulls_count(int x)
{
	for (int i = sizeof(int) * 8 - 2; i >= 0; i--) {
		if (x & (1 << i)) {
			return sizeof(int) * 8 - (i + 3);
		}
	}

	return 31;
}


/*
Задача 3.
Даны числа x и i, требуется обнулить все биты числа x от самого старшeго до i.
Пример x = 784252715 (00101110101111101011111100101011), i = 13->функция должна возвращать 442155 (00000000000000000001111100101011)
*/
int clear_bits_through_i(int x, int y)
{
	// again sizeof(int)*8 -2 is better than hard-coded 30
	// --y is more appropriate in this case than y--, or to not use one more line, you can remove y-- and use i >= y -1 in the for loop.
	//It's always better to compute something once and use it when needed instead of recomputing. So here `1 << i` can be computed only once
	// and use it in both places.
	// This solution is right, but you can also have a look at Hovhannes's solution as an alternative solution and also `x = x ^ (1 << i);` is 
	// equivalent to the `x = x & ~(1 << i);` in our case right (since there is no any leading zero at the i-th step).
	for (int i = sizeof(int) * 8 - 2; i >= (y - 1); i--) {
		if (x & (1 << i)) {
			x = x ^ (1 << i);
		}
	}

	return x;
}

// 2rd lucum

int clear_bits_through_i2(int x, int y)
{
	// This is a very nice solution, but why you convert it to long long and than convert it back to int ?
	// just return x & ((1 << y) - 1) is not the same ?

	// y = 31 i depqum 1 << 31 y int i sahmanneric durs kga dra hamar em long long sarqel heto int ov poxarinel
	int c = (1 << y);
	int cc = ((1 << y) - 1);
	long long ll = (long long)((1ll << y) - (long long)1);
	int llx = x & cc;
	long long llc = (long long)x & ll;
	int k = llc;

//	return x & ((1 << y) - 1);

	return (int)((long long)x & ((1ll << y) - 1));
}

/*
Задача 4.
Пусть дано целочисленное значение short x, требуется возвращать его бинарное представление в std::string(порядок - big endian).
Алгоритм должен использовать битовые операции.
Примеры
0   -> "0000000000000000"
1   -> "0000000000000001"
7   -> "0000000000000111"
777 -> "0000001100001001"
513 -> "0000001000000001"
- 7  -> "1111111111111001"
*/

string short_to_binary_string(short x)
{
	// Since Hovhannes's solution is similar, I'll just copy/paste my comment here for you too. https://github.com/DavidTsat/physmath_cpp_group/pull/1/files#r860872269
	string s;
	for (int i = sizeof(int) * 8 - 2; i >= 0; i--) {
		if (x & (1 << i)) {
			s += "1";
		}
		else {
			s += "0";
		}
	}

	return s;
}

/*
Задача 5.

Обратная задача.Дана строка, длиной 32 элемента - двоичное представление некоторого целого неотрицательного числа,
требуется возвращать это число с типом unsigned int.
Примеры
"0000000000000000" -> 0
"0000000000000001" -> 1
"0000000000000111" -> 7
"0000001100001001" -> 777
"0000001000000001" -> 513
*/
unsigned binary_string_to_int(string s)
{
	// again I will copy/paste my comment. It'll be useful for too https://github.com/DavidTsat/physmath_cpp_group/pull/1/files#r860871967
	unsigned answ = 0;

	for (int i = 0; i <= sizeof(int) * 8 - 1; i++) {
		if (s[i] == '1') {
			answ += (1 << (sizeof(int) * 8 - 1 - i));
		}
	}

	return answ;
}


/*
Задача 6.

В массиве каждое число встречается три раза, кроме одного числа, котороре встречается ровно один раз.
С помощью битовых операций найти элемент, который встречается один раз.
Примеры
{ 2,2,3,2 } -> 3
{0, 1, 0, 1, 0, 1, 99} -> 99
*/

int singleNumber(const vector<int>&nums)
{
	// Why you use long long as a key type for the map. Our input vector is vector of ints so converting int to long long is a waste of memory
	// but the solution is right
	// and a C++-ic note: If you are not modifying the input object (nums in our case), it is better to pass it as a const reference.
	map<int, int> mp;
	for (int i = 0; i < nums.size(); i++) {
		mp[nums[i]]++;
	}

	for (auto u : mp) {
		if (u.second == 1) {
			return u.first;
		}
	}

	// stex chi hasnelu
	return -1;
}


int singleNumber(vector<int>& nums)
{
	vector<int> bits(sizeof(int) * 8 - 1, 0);
	// Great solution (but again using hard-coded 30, 31 is not a good thing)
	for (int i = 0; i < nums.size(); i++) {
		for (int j = 0; j <= sizeof(int) * 8 - 2; j++) {
			if (nums[i] & (1 << j)) {
				bits[j]++;
			}
		}
	}

	int answ = 0;
	for (int i = 0; i <= sizeof(int) * 8 - 2; i++) {
		if (bits[i] % 3 != 0) {
			answ |= (1 << i);
		}
	}

	return answ;
}

/*
Задача 7.

Даны два целых числа left и right, которые представляют диапазон[left, left].
Требуется написать оптимальный алгоритм, который возвращает побитовый and (&) всех чисел в этом диапазоне.

Примеры
1. left = 5, right = 7
вывод: 4
2. left = 0, right = 0
вывод : 0
3. left = 1, right = 2147483647
вывод : 0
*/

void solve() {
	int left, right;
	cin >> left >> right;
	// This solution seemed very interesting to me, but this is not working correctly for some cases (since they're the cases when a power of two
	// is in the range and the answer should be zero. 
	// So for example your solution work in cases left == 9 and right == 13, left == 5 and right == 7, but in cases left == 3 and right == 4, left == 7 and right == 9 your solution is not returning zero.

	int answ = 0;
	for (int i = sizeof(int) * 8 - 2; i >= 0; i--) {
		if (left & (1 << i) && right & (1 << i) && (right - left) < (1 << i)) {
			answ |= (1 << i);
		}
	}

	cout << answ << endl;
}

/*
Задача 8.
Дано некоторое множество целых чисел(длина множества не превышает 32).Требуется выводить все его подмножества.

Пример
{ 0, 2, 3 }
вывод: {}, { 0 }, { 2 }, { 3 }, { 0,2 }, { 0,3 }, { 2,3 }, { 0,2,3 }
*/

vector<vector<int>> power_set(vector<int> v)
{
	// Great solution.
	// Can you try to solve this problem without bitwise operations, but with recursion ? 
	int n = v.size();
	vector<vector<int>> answ;
	for (int mask = 0; mask < (1 << n); mask++) {
		vector<int> currSubset;
		for (int i = 0; i < n; i++) {
			if (mask & (1 << i)) {
				currSubset.push_back(v[i]);
			}
		}
		answ.push_back(currSubset);
	}
	return answ;
}


// recursion

vector<vector<int>> answ;

void rec(int currIndex, vector<int> currSubset, vector<int> fullArray) {
	if (currIndex == fullArray.size()) {
		answ.push_back(currSubset);
		return;
	}

	rec(currIndex + 1, currSubset, fullArray);
	currSubset.push_back(fullArray[currIndex]);
	rec(currIndex + 1, currSubset, fullArray);
}

void solve_subsets() {
	rec(0, {}, { 1, 2, 3 });
}

/*
Задача 9.
Дан массив положительных целых чисел arr.Дан еще массив от массивов от двух элементов xor_indices, в котором каждый
элемент xor_indices[i][0] и xor_indices[i][1] представляют собой индексы.Требуется посчитатьxor всех элементов, входящих
в диапазон[xor_indices[i][0], xor_indices[i][1]]. (если xor_indices[i][0] == xor_indices[i][1], то возвращается только значение
arr[xor_indices[i][0]], а не 0).
Важно найти оптимальное, линейное решение, а не просто писать цикл от xor_indices[i][0] до xor_indices[i][1] и считатьxor всех элементов)

Пример 1.
Вход: arr = [1, 3, 4, 8], xor_indices = [[0, 1], [1, 2], [0, 3], [3, 3]]
Выход : [2, 7, 14, 8]
Объяснение :
Двоичное представление элементов :
1 = 0001
3 = 0011
4 = 0100
8 = 1000
результат :
[0, 1] = 1 xor 3 = 2
[1, 2] = 3 xor 4 = 7
[0, 3] = 1 xor 3 xor 4 xor 8 = 14
[3, 3] = 8

Пример 2.
Вход: arr = [4, 8, 2, 10], xor_indices = [[2, 3], [1, 3], [0, 0], [0, 3]]
Выход : [8, 0, 4, 4]
*/

// 1 lucumy karelia segment tree ov anel
// amen harcumy log(N) um kanenq

// 2rd lucumy prefix array ov

vector<int> xor_subarrays(vector<int>&arr, vector<vector<int>>&xor_indices)
{
	int n = (int)arr.size();
	vector<int> prefix(n + 1);

	for (int i = 1; i <= n; i++) {
		prefix[i] = prefix[i - 1] ^ arr[i - 1];
	}

	vector<int> answ;
	for (int i = 0; i < xor_indices.size(); i++) {
		int l = xor_indices[i].front(), r = xor_indices[i].back() + 1;
		answ.push_back(prefix[r] ^ prefix[l]);
	}
	return answ;
}


int main()
{
	cout << (1 << 31) << endl;
	cout << INT_MIN << endl;
	cout << clear_bits_through_i2(1<<31, 3) << endl;

	return 0;
}