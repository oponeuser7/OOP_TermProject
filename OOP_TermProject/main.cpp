#include <fstream>
#include "print_page.h"
#include "func.h"
#define border "--------------------------------------------------------------------------------"

//factory method 패턴을 위한 클래스들
class page_turner {
public:
	static page_turner* maketurner(char choice);
	virtual void turn_page(unsigned& index) = 0;
};

class next_by_one : public page_turner {
	void turn_page(unsigned& index) {
		index += 1;
	}
};

class prev_by_one : public page_turner {
	void turn_page(unsigned& index) {
		index -= 1;
	}
};

page_turner* page_turner::maketurner(char choice) {
	switch (choice) {
	case 'n':
		return new next_by_one;
	case 'p':
		return new prev_by_one;
	default:
		return NULL;
	}
}

int main() {

	string user_input; 
	vector<string> user_input_parsed;
	vector<string> v; //파일 저장용 벡터
	vector<unsigned> line_header; // 각 line의 첫 단어들
	vector<unsigned> page_header;// 각 page의 첫 단어들
	page_turner* product; //factory method 패턴을 위한 객체
	v.reserve(1100); line_header.reserve(20); page_header.reserve(10); //초기 할당

	fstream myfile("test.txt");
	
	if (myfile.is_open()) {
		string temp;
		string message = "This is page 1"; //콘솔 메세지 저장
		unsigned index = 0; //page들을 traversing 하기 위한 index
		char exit_flag = 0; //t 입력 시 올라가는 플래그
		char page_flag = 0; //n, p 입력 시 올라가는 플래그

	    //벡터로 파일 내용 이동
		while (getline(myfile, temp, ' ')) { 
			temp += ' ';
			v.emplace_back(temp);
		}

		while (1) {
			//파일 출력
			page_header.clear();
			count_page(v, page_header);
			print_page(page_header[index], v, line_header);
			cout << '\n' << border << endl;
			cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장 후 종료" << endl;
			cout << border << endl;
			if (page_flag) { // n, p 입력 처리
				cout << "(콘솔메세지) This is page " << index + 1 << endl;
				page_flag = 0;
			}
			else
				cout << "(콘솔메세지) " << message << endl;
			cout << border << endl;
			message.clear();
			// t 입력 처리
			if (exit_flag) {
				myfile.close();
				return 0;
			}

			//입력 받고 파싱
			cout << "입력: ";
			cin >> user_input;
			stringstream stream;
			stream.str(user_input);
			(getline(stream, temp, '('));
		    user_input_parsed.emplace_back(temp);
			(getline(stream, temp, ')'));
			user_input_parsed.emplace_back(temp);
			
			//입력 해석 후 명령어 실행
			try {
				switch (*(user_input_parsed[0]).c_str()) {

				case 'i':
					input(v, line_header, user_input_parsed[1]); 
					break;

				case 'd':
					delete_(v, line_header, user_input_parsed[1]); 
					break;

				case 's':
					search(v, page_header, user_input_parsed[1], message); 
					break;

				case 'c':
					change(v, user_input_parsed[1], message); 
					break;

				case 't':
					for (unsigned i = 0; i < v.size(); i++) { myfile << v[i]; }
					message = "File saved.";
					exit_flag = 1;
					break;

				case 'n':
					if (index + 1 == page_header.size()) 
						message = "This is the last page.";
					else {
						product = page_turner::maketurner('n');
						product->turn_page(index);
						page_flag = 1;
					}
					break;

				case 'p':
					if (index == 0) 
						message = "This is the first page.";
					else {
						product = page_turner::maketurner('p');
						product->turn_page(index);
						page_flag = 1;
					}
					break;

				default:
					message = "Invalid input.";
				}
				//유저 입력 저장용 벡터를 비워주어야 한다.
				user_input_parsed.clear(); 
			}
			//예외 처리
			catch (invalid_argument& e) { 
				message = "Invalid input.";
				user_input_parsed.clear();
			}
			catch (out_of_range& e) { 
				message = "Invalid input."; 
				user_input_parsed.clear();
			}
		}
	}
	else { //파일이 존재하지 않는 경우
		cout << "failed to open file.\n";
		return 0;
	}
	myfile.close();
	return 0;
}