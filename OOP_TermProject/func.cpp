#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
using namespace std;

void input(vector<string>& v, vector<unsigned> line_header, string arguments) {
	int column, row;
	int count = 0;
	string temp;
	vector<string> arguments_parsed;
	stringstream stream;
	stream.str(arguments);
	while (getline(stream, temp, ',')) {
		arguments_parsed.push_back(temp);
		count++;
	}
	//인자 수 맞추기
	if (count < 3)
		throw invalid_argument("exception");

	column = stoi(arguments_parsed[0]);
	row = stoi(arguments_parsed[1]);
	arguments_parsed[2] += ' ';

	//예외 탐색
	for (int i = 0; i < row; i++) 
		if (v[line_header[column - 1] + i] == v[line_header[column]])
			throw out_of_range("exception");
	
	if (arguments_parsed[2].size() >= 75)
		throw out_of_range("exception");
	else if (column > 20)
		throw out_of_range("exception");
	
	//단어 넣기
	v.emplace((v.begin() + (line_header[column - 1] + row)), arguments_parsed[2]);
}

void delete_(vector<string>& v, vector<unsigned> line_header, string arguments) {
	int column, row;
	int count = 0;
	string temp;
	vector<string> arguments_parsed;
	stringstream stream;
	stream.str(arguments);
	while (getline(stream, temp, ',')) {
		arguments_parsed.push_back(temp);
		count++;
	}
	//인자 수 맞추기
	if (count < 2)
		throw invalid_argument("exception");

	column = stoi(arguments_parsed[0]);
	row = stoi(arguments_parsed[1]);

	//예외 탐색
	for (int i = 0; i < row; i++) 
		if (v[line_header[column - 1] + i] == v[line_header[column]])
			throw out_of_range("exception");

	if (column > 20)
		throw out_of_range("exception");

	//단어 지우기
	v.erase((v.begin() + (line_header[column - 1] + row - 1)));
}

void search(vector<string>& v, vector<unsigned> page_header, string argument, string& message) {
	unsigned index = 0;
	argument += ' ';

	//첫번째로 일치하는 단어를 검색
	for (unsigned i = 0; i < v.size(); i++) {
		if (v[i] == argument) {
			index = i;
			break;
		}
	}
	if (index) {
		int page = 0;
		int line = 0;
		int word = 0;
		int i = 0;
		int count_row = 76;

		//몇 페이지에 있는가
		while (page_header[i] <= index) { 
			page++;
			i++;
		}

		//몇 라인 몇 번째 단어인가
		for (unsigned i = page_header[page - 1]; i < v.size(); i++) {
			count_row += v[i].size();
			if (count_row > (size_t)76) {
				count_row = v[i].size();
				word = 1;
				line += 1;
			}
			else {
				word += 1;
			}
			if (i == index)
				break;
		}
		//정수를 문자열로 변환
		string page_ = to_string(page);
		string line_ = to_string(line);
		string word_ = to_string(word);

		//콘솔메세지 입력
		message = "찾는 단어 : " + argument + ", 위치: " + page_ + "페이지 " + line_ + "라인 " + word_ + "번째 단어";
	}
	else
		message = "There is no match";
}

void change(vector<string>& v, string arguments, string& message) {

	vector<unsigned> matches;
	int count = 0;
	int parse_count = 0;
	string temp;
	vector<string> arguments_parsed;
	stringstream stream;
	stream.str(arguments);
	while (getline(stream, temp, ',')) {
		arguments_parsed.push_back(temp);
		parse_count++;
	}

	//인자 수 맞추기
	if (parse_count < 2)
		throw invalid_argument("exception");

	if (arguments_parsed[1].size() >= 75)
		throw out_of_range("exception");

	arguments_parsed[0] += ' ';
	arguments_parsed[1] += ' ';

	//일치하는 단어 검색
	for (unsigned i = 0; i < v.size(); i++) 
		if (v[i] == arguments_parsed[0]) {
			matches.push_back(i);
			count++;
		}

	if (count) {
		//단어 일괄 교체
		for (unsigned i = 0; i < matches.size(); i++) {
			v.erase(v.begin() + matches[i]);
			v.emplace(v.begin() + matches[i], arguments_parsed[1]);
		}
	}
	else
		message = "There is no match";
}