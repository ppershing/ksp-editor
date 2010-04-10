#include "testdialog.h"
#include "ui_testdialog.h"

TestDialog::TestDialog(Settings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);
	s = settings;
	Testovac::initialize("testovac");
	tasklist = toQStringList(Testovac::get_task_list());
	tasklist.push_back("Uz si spravil vsetky ulohy.");
	currentTask = 0;
}

TestDialog::~TestDialog()
{
	delete ui;
}

void TestDialog::show(){
	ui->textBrowser->clear();
	ui->radioButtonSubmit->setChecked(true);
	ui->radioButtonCompileOnly->setEnabled(s->getBool("upgrades/compileOnly"));
	ui->radioButtonManualTest->setEnabled(s->getBool("upgrades/manualTest"));
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
	for(int i=0;i<(int)vqs.size();i++){
		vs.push_back(vqs[i].toStdString());
	}
	return vs;
}

QStringList TestDialog::toQStringList(std::vector<std::string> s){
	QStringList qs;
	for(int i=0;i<(int)s.size();i++){
		qs.push_back(QString::fromStdString(s[i]));
	}
	return qs;
}

void TestDialog::on_pushButton_clicked()
{
	ui->textBrowser->clear();
	compile_output.clear();
	output.clear();

	if(currentTask>=tasklist.size()-1)return;

	compile_settings.compiler = CompileSettings::COMPILER_CPP;
	compile_settings.compile_with_warnings = s->getInt("upgrades/showCompilationWarnings");

	test_settings.memory_limit = 1000;
	test_settings.time_limit = 1000;
	test_settings.full_test_log = s->getInt("upgrades/fullLog");

	prog = fromQStringList(program.split("\n"));

	if(ui->radioButtonCompileOnly->isChecked()){
		ui->textBrowser->append("COMPILING...");
		int retval = Testovac::compile(prog,compile_settings,&compile_output);
		ui->textBrowser->append((retval==0)?"OK":"FAILED");
		return;
	}
	ui->textBrowser->append("SUBMITTING...");
	emit submitting();
	int retval = Testovac::submit_solution(tasklist.at(currentTask).toAscii(),prog,compile_settings,test_settings,&compile_output,&output);
	ui->textBrowser->append(retval==0?"PASSED":"FAILED");
	if(s->getBool("upgrades/showCompilationStatus")){
		ui->textBrowser->append("compile: "+toQStringList(compile_output).join("\n"));
	}
	if(ui->radioButtonCompileOnly->isChecked())return;
	//ui->textBrowser->append("output: "+toQStringList(output).join("\n"));

	if(retval==0){
		qDebug() << currentTask << ": OK";
		currentTask++;
		if(currentTask==tasklist.size()-1)
			qDebug() << "HOTOVO";

	}
}

void TestDialog::on_radioButtonManualTest_toggled(bool checked)
{
	if(checked){
		this->resize(this->width()+300,this->height());
	}else{
		this->resize(this->width()-300,this->height());
	}
}
