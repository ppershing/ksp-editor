#include "testovac.cpp"

int main() {
    Testovac::initialize(".");
    CompileSettings compile_settings;
    TestSettings test_settings;
    vector<string> program;
    vector<string> output;
    vector<string> compile_output;
    vector<string> input;

    compile_settings.compiler = CompileSettings::COMPILER_CPP;
    compile_settings.compile_with_warnings = 0;

    test_settings.memory_limit = 100000;
    test_settings.time_limit = 1000;

    program.push_back("#include <stdio.h>");
    program.push_back("int main() {");
    program.push_back(" int nepouzivana;");
    program.push_back(" int cislo;");
    program.push_back(" printf(\"Zadaj cislo:\");");
    program.push_back(" scanf(\"%d\", &cislo);");
    program.push_back(" printf(\"Hello world %d\\n\",cislo);");
    program.push_back("}");
/*    program.push_back("var nepouzivana,cislo: integer;");
    program.push_back("begin");    
    program.push_back("writeln('zadaj cislo:');");
    program.push_back("readln(cislo);");
    program.push_back("writeln('Hello world!', cislo);");
    program.push_back("end.");*/

    input.push_back("5");

    int retval = Testovac::test_on_input(program, input,
            compile_settings,test_settings, &compile_output, &output);

    printf("compiling returned value %d\n", retval);
    printf("errors encountered:\n");
    for (int i=0; i<(int)output.size(); i++) {
        printf("%s\n", output[i].c_str());
    }
}
