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
	for(int i=0;i<tasklist.size();i++)
		taskDescriptions.push_back(toQStringList(Testovac::get_task_description(tasklist.at(i).toStdString().c_str())).join("\n"));

	tasklist.push_back("Už si spravil všetky ulohy.");
	taskDescriptions.push_back("Už si spravil všetky ulohy.");
	currentTask = s->getInt("tasks/done");
}

TestDialog::~TestDialog()
{
	delete ui;
}

void TestDialog::show(){
	ui->textBrowser->clear();
	ui->radioButtonCompileOnly->setEnabled(s->getBool("upgrades/compileOnly"));
	ui->radioButtonManualTest->setEnabled(s->getBool("upgrades/manualTest"));
	ui->pushButton->setEnabled(s->getInt("credits/count")>=s->getInt("prices/submitAction"));
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
		qs.push_back(QString::fromUtf8(s[i].c_str()));
	}
	return qs;
}

void TestDialog::on_pushButton_clicked()
{
	Logger::log("Submit start");
	ui->textBrowser->clear();
	compile_output.clear();
	output.clear();

	if(currentTask>=tasklist.size()-1)return;

	compile_settings.compiler = (ui->comboBox->currentText()=="cpp")?CompileSettings::COMPILER_CPP:CompileSettings::COMPILER_PAS;
	compile_settings.compile_with_warnings = s->getInt("upgrades/showCompilationWarnings");

	test_settings.memory_limit = s->getBool("upgrades/memoryLimit")?10000:1000;
	test_settings.time_limit = 1000;
	test_settings.full_test_log = s->getInt("upgrades/showFullLog");

	prog = fromQStringList(program.split("\n"));

	// teraz za to zaplatia

	// COMPILE ONLY

	if(ui->radioButtonCompileOnly->isChecked()){
	        s->decrement("credits/count",s->getInt("prices/compileAction"));
	        ui->pushButton->setEnabled(s->getInt("credits/count")>=s->getInt("prices/compileAction"));
		ui->textBrowser->append("COMPILING...");
		int retval = Testovac::compile(prog,compile_settings,&compile_output);
		ui->textBrowser->append((retval==0)?"OK":"FAILED");
		return;
	}

	// SUBMIT

	if(ui->radioButtonSubmit->isChecked()){
	        s->decrement("credits/count",s->getInt("prices/submitAction"));
	        ui->pushButton->setEnabled(s->getInt("credits/count")>=s->getInt("prices/submitAction"));
		ui->textBrowser->append("SUBMITTING...");
		emit submitting();
		int retval = Testovac::submit_solution(tasklist.at(currentTask).toAscii(),prog,compile_settings,test_settings,&compile_output,&output);
		Logger::log("Submit uloha "+QString::number(currentTask)+": "+((retval==0)?"PASSED":"FAILED"));
		ui->textBrowser->append(retval==0?"PASSED":"FAILED");
		if(s->getBool("upgrades/showCompilationStatus")){
			ui->textBrowser->append("");
			ui->textBrowser->append("<hr>COMPILATION OUTPUT: ");
			ui->textBrowser->append(toQStringList(compile_output).join("\n"));
		}
		if(s->getBool("upgrades/showLog")){
			ui->textBrowser->append("");
			ui->textBrowser->append("<hr>TEST LOG:");
			ui->textBrowser->append(toQStringList(output).join("\n"));
		}

		if(retval==0){
			qDebug() << currentTask << ": OK";
			currentTask++;
			s->setProp("tasks/done",currentTask);
			if(currentTask==tasklist.size()-1)
				qDebug() << "HOTOVO";

		}
		return;
	}

	// MANUAL TEST

	if(ui->radioButtonManualTest->isChecked()){
	        s->decrement("credits/count",s->getInt("prices/manualTestAction"));
	        ui->pushButton->setEnabled(s->getInt("credits/count")>=s->getInt("prices/manualTestAction"));
		ui->textBrowser->append("MANUAL TESTING...");
		std::vector<std::string> input = fromQStringList(ui->plainTextEdit->toPlainText().split("\n"));
		int retval = Testovac::test_on_input(prog,input,compile_settings,test_settings,&compile_output,&output);
		if(retval!=0)ui->textBrowser->append("FAILED TO RUN");
		if(s->getBool("upgrades/showCompilationStatus")){
			ui->textBrowser->append("");
			ui->textBrowser->append("<hr>COMPILATION OUTPUT: ");
			ui->textBrowser->append(toQStringList(compile_output).join("\n"));
		}
		if(s->getBool("upgrades/showLog")){
			ui->textBrowser->append("");
			ui->textBrowser->append("<hr>TEST LOG:");
			ui->textBrowser->append(toQStringList(output).join("\n"));
		}
		return;
	}
}

void TestDialog::on_radioButtonManualTest_toggled(bool checked)
{
	if(checked){
		this->resize(this->width()+300,this->height());
		ui->plainTextEdit->move(ui->textBrowser->x()+ui->textBrowser->width(),ui->textBrowser->y());
		ui->plainTextEdit->resize(300,ui->textBrowser->height());
		ui->label_2->move(ui->textBrowser->width()+20,5);
		ui->label_2->resize(71,16);
	}else{
		this->resize(this->width()-300,this->height());
		ui->plainTextEdit->resize(0,0);
		ui->label_2->resize(0,0);
	}
}
