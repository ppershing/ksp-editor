#include "testovac.cpp"

int main() {
    CompileSettings settings;
    vector<string> program;
    vector<string> output;

    settings.compiler = CompileSettings::COMPILER_PAS;
    settings.compile_with_warnings = 0;

/*    program.push_back("#include <stdio.h>");
    program.push_back("int main() {");
    program.push_back(" int nepouzivana;");
    program.push_back(" printf(\"Hello world\\n\");");
    program.push_back("}");*/
    program.push_back("var nepouzivana: integer;");
    program.push_back("begin");    
    program.push_back("writeln('Hello world!');");
    program.push_back("end.");

    int retval = Testovac::compile(program, settings, &output);

    printf("compiling returned value %d\n", retval);
    printf("errors encountered:\n");
    for (int i=0; i<output.size(); i++) {
        printf("%s\n", output[i].c_str());
    }
}
