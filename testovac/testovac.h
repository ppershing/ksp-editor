#include <vector>
#include <string>
using namespace std;

class CompileSettings {
public:
    static const int COMPILER_CPP=1;
    static const int COMPILER_PAS=2;
    int compiler;
    int compile_with_warnings;
};

class Testovac {
private:
    static void clean_sandbox();
    static void write_to_file(const char * filename, vector<string>& lines);
    static void read_from_file(const char * filename, vector<string> *lines);
public:
    static int compile(vector<string>& program,
            CompileSettings& settings,
            vector<string> *output);
};
