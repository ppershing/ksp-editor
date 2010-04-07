#include "testovac.h"
#include <cstdlib>
#include <fstream>
#include <cassert>

string Testovac::testdir;
int Testovac::initialized;

void Testovac::initialize(const char* testdir){
    Testovac::testdir = testdir;
    Testovac::initialized = 1;
}

string Testovac::get_sandbox_dir(){
    return testdir+"/sandbox";
}

string Testovac::get_wrapper_dir(){
    return testdir;
}

string Testovac::get_program_bin(){
    return get_sandbox_dir()+"/program";
}

string Testovac::get_program_source(string ext){
    return get_program_bin()+"."+ext;
}

void Testovac::clean_sandbox() {
    assert(initialized);
    string s="rm -rf \""+get_sandbox_dir()+"/*\"";
    system(s.c_str());
}

void Testovac::copy_wrapper() {
    assert(initialized);
    string wrapper = get_wrapper_dir()+"/wrapper";
    string sandbox = get_sandbox_dir()+"/wrapper";
    string s="cp \""+wrapper+"\" \""+sandbox+"\"";
    system(s.c_str());
}

void Testovac::copy_test_data(const char* taskname) {
    system((string("cp ") + taskname + "/* sandbox/").c_str());
}

int Testovac::compile(vector<string>& program,
            CompileSettings& settings,
            vector<string> *output) {
    string programName;
    string compileLine;
    int retval;

    assert(initialized);
    assert (settings.compiler == CompileSettings::COMPILER_CPP ||
            settings.compiler == CompileSettings::COMPILER_PAS);

    if (settings.compiler == CompileSettings::COMPILER_CPP) {
        programName = get_program_source("cpp");
        compileLine = "g++ " + programName +
                      " -static -static-libc" + 
                      " -o " + get_program_bin();
        if (settings.compile_with_warnings) {
            compileLine+=" -W -Wall";
        }
    } else 
    if (settings.compiler == CompileSettings::COMPILER_PAS) {
        programName = get_program_source("pas");
        compileLine = "fpc " + programName;
        if (settings.compile_with_warnings) {
            compileLine+=" -veiwn";
        } else {
            compileLine+=" -ve";
        }
    }

    Testovac::clean_sandbox();
    write_to_file(programName.c_str(), program);

    string error_file=get_sandbox_dir()+"/compile_err";
    string s=compileLine + " &>"+error_file;
    retval = system(s.c_str());

    read_from_file(error_file.c_str(), output);
    return retval;
}

void Testovac::write_to_file(const char * filename, vector<string>& lines) {
    ofstream s(filename);
    for (int i=0; i<(int) lines.size(); i++) {
        s << lines[i] << endl;
    }
    s.close();
}

void Testovac::read_from_file(const char * filename, vector<string> *lines) {
    ifstream s(filename);
    char buf[1000];
    assert(lines != NULL);
    lines->clear();
    while (!s.eof()) {
        s.getline(buf, 999);
        lines->push_back(string(buf));
    }
}

string Testovac::inttostr(int i){
    char tmp[100];
    sprintf(tmp,"%d",i);
    return string(tmp);
}

int Testovac::test_on_input(vector<string> &program,
        vector<string>& input,
        CompileSettings& compile_settings,
        TestSettings& test_settings,
        vector<string> *compile_output,
        vector<string> *test_output) {
    int compile_ret;
    compile_ret = Testovac::compile(program, compile_settings, compile_output);
    if (compile_ret) return compile_ret;
    Testovac::copy_wrapper();
    string test_in = get_sandbox_dir()+"/test.in";
    write_to_file(test_in.c_str(), input);
    string test_out = get_sandbox_dir()+"/test.out";

    string testcmd = "cd "+get_sandbox_dir()+" && ./wrapper -a0 -ff";
    testcmd += " -m"+inttostr(test_settings.memory_limit);
    testcmd += " -t"+inttostr(test_settings.time_limit);
    testcmd += " -itest.in -otest.out";
    testcmd += " ./program &>test.log";
    int retval;
    retval = system(testcmd.c_str());
    read_from_file(test_out.c_str(), test_output);
    return retval;

}

int Testovac::full_test(const char* taskname,
        vector<string> &program,
        CompileSettings& compile_settings,
        TestSettings& test_settings,
        vector<string> *compile_output,
        vector<string> *test_output) {
    int compile_ret;
    compile_ret = Testovac::compile(program, compile_settings, compile_output);
    if (compile_ret) return compile_ret;
    Testovac::copy_wrapper();
    Testovac::copy_test_data(taskname);

    int retval;
    retval = system("cd sandbox && ./testuj.sh 1>test_out 2>test_err");
    read_from_file("sandbox/test_out", test_output);
    return retval;

}
