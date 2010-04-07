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

class TestSettings {
public:
    int memory_limit; // in kB
    int time_limit; // in msec
};

class Testovac {
private:
    static void clean_sandbox();
    static void copy_wrapper();
    static void copy_test_data(const char* taskname);
    static void write_to_file(const char * filename, vector<string>& lines);
    static void read_from_file(const char * filename, vector<string> *lines);
    static int initialized;
    static string testdir;
    static string get_sandbox_dir();
    static string get_wrapper_dir();
    static string get_program_bin();
    static string get_program_source(string ext);
    static string inttostr(int i);
public:
    static void initialize(const char* testdir);

    static int compile(vector<string>& program,
            CompileSettings& settings,
            vector<string> *output);

    static int test_on_input(vector<string>& program,
            vector<string>& input,
            CompileSettings& compile_settings,
            TestSettings& test_setting,
            vector<string> *compile_output,
            vector<string> *test_output);

    static int full_test(const char* taskname,
            vector<string>& program,
            CompileSettings& compile_settings,
            TestSettings& test_settings,
            vector<string> *compile_output,
            vector<string> *test_output);
};
