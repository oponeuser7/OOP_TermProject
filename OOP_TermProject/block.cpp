#include <string>
using namespace std;

class block {
private:
	string word;
	size_t column;
public:
	block(string& input_word) : word(input_word), column(0) {}
	string return_word() { return word; }
	size_t return_word_size() { return word.size(); }
	void set_column(size_t column_) { column = column_; }
};