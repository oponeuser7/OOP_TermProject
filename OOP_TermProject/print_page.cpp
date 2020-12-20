#include <string>
#include <vector>
#include <iostream>
using namespace std;

void print_page(unsigned i, vector<string> v, vector<unsigned> &line_header) {
	size_t count_row = 76;
	int count_column = 0;
	for (i; i < v.size(); i++) {
		count_row += v[i].size();
		if (count_row > (size_t)76) {
			if (count_column < 20) {
				line_header.push_back(i);
				count_row = v[i].size();
				count_column += 1;
				if(count_column < 10) // 십의 자리 수와 줄맞춤
					cout << '\n' << ' ' <<count_column << "| " << v[i];
				else
					cout << '\n' << count_column << "| " << v[i];
			}
			else {
				break;
			}
		}
		else
			cout << v[i];
	}
}

void count_page(vector<string> v, vector<unsigned> &page_header) {
	size_t count_row = 76;
	int count_column = 20;
	for ( unsigned i = 0; i < v.size(); i++) {
		count_row += v[i].size();
		if (count_row > (size_t)76) {
			if (count_column < 20) {
				count_row = v[i].size();
				count_column += 1;
			}
			else {
				count_row = v[i].size();
				count_column = 1;
				page_header.push_back(i); //페이지 헤더 저장
			}
		}
	}
}