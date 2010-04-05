#include "testovac.h"
#include <cstdlib>
#include <fstream>
#include <cassert>

void Testovac::clean_sandbox() {
    system("rm -rf sandbox/*");
}


int Testovac::compile(vector<string>& program,
            CompileSettings& settings,
            vector<string> *output) {
    string programName;
    string compileLine;
    int retval;

    assert (settings.compiler == CompileSettings::COMPILER_CPP ||
            settings.compiler == CompileSettings::COMPILER_PAS);

    if (settings.compiler == CompileSettings::COMPILER_CPP) {
        programName = "sandbox/program.cpp";
        compileLine = "g++ " + programName +
                      " -o sandbox/program";
        if (settings.compile_with_warnings) {
            compileLine+=" -W -Wall";
        }
    } else 
    if (settings.compiler == CompileSettings::COMPILER_PAS) {
        programName = "sandbox/program.pas";
        compileLine = "fpc " + programName;
        if (settings.compile_with_warnings) {
            compileLine+=" -veiwn";
        } else {
            compileLine+=" -ve";
        }
    }

    Testovac::clean_sandbox();
    write_to_file(programName.c_str(), program);

    retval = system((compileLine + " &>sandbox/compile_err").c_str());

    read_from_file("sandbox/compile_err", output);
    return retval;
}

void Testovac::write_to_file(const char * filename, vector<string>& lines) {
    ofstream s(filename);
    for (int i=0; i<lines.size(); i++) {
        s << lines[i] << endl;
    }
    s.close();
    assert(s.fail() == 0);
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

