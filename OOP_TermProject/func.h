#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
using namespace std;

void input(vector<string>& v, vector<unsigned>line_header, string arguments);
void delete_(vector<string>& v, vector<unsigned> line_header, string arguments);
void search(vector<string>& v, vector<unsigned> page_header, string argument, string& message);
void change(vector<string>& v, string argument, string& message);