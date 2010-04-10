#include "testdialog.h"
#include "ui_testdialog.h"

TestDialog::TestDialog(Settings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);
	s = settings;
	Testovac::initialize("testovac/");
}

TestDialog::~TestDialog()
{
	delete ui;
}

void TestDialog::show(){
	ui->textBrowser->clear();
	QDialog::show();
}

void TestDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
std::vector<std::string> TestDialog::fromQStringList(QStringList s){
	std::vector<QString> vqs = s.toVector().toStdVector();
	std::vector<std::string> vs;
	for(int i=0;i<vqs.size();i++){
		vs.push_back(vqs[i].toStdString());
	}
	return vs;
}

void TestDialog::on_pushButton_clicked()
{
	ui->textBrowser->append(" testing...");

	compile_settings.compiler = CompileSettings::COMPILER_CPP;
	compile_settings.compile_with_warnings = 0;

	test_settings.memory_limit = 1000;
	test_settings.time_limit = 1000;


	std::vector<std::string> prog = fromQStringList(program.split("\n"));
	std::vector<std::string> output;
	std::vector<std::string> compile_output;
	std::vector<std::string> input;
	std::vector<std::string> task_list;




	int retval = Testovac::submit_solution("sucet",prog,compile_settings,test_settings,&compile_output,&output);
}
