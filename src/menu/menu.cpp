#include "menu.h"

// ��������� ��������� �������
void setConsoleEncoding() {
#ifdef _WIN32
	// Windows: ������������� ��������� 1251
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
#else
	setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
}

int Windows::showTextOperations() {
	cout << "\n����� ��������:" << endl;
	cout << "1) ���������� ������" << endl;
	cout << "2) ������������� ������" << endl;
	cout << "������� ��� ����� (1 ��� 2): ";
	return Windows::getChoice(1, 2, "������� ��� ����� (1 ��� 2): ");
}

int Windows::showFileOperations() {
	cout << "\n����� ��������:" << endl;
	cout << "1) ���������� �����" << endl;
	cout << "2) ������������� �����" << endl;
	cout << "������� ��� ����� (1 ��� 2): ";

	return Windows::getChoice(1, 2, "������� ��� ����� (1 ��� 2): ");
}

void Windows::showMenu(){
	while (true) {

		cout << "�������� ����� ������ ����������" << endl;
		cout << "1) ����������/������������ ������" << endl;
		cout << "2) ����������/������������ �����" << endl;
		cout << "3) ��������� ������" << endl;
		cout << "��� �����: ";

		int choice = getChoice(1, 4, " ");

		cout << endl;

		switch (FunctionsOfProgram(choice)) {
		case FunctionsOfProgram::TEXT:
			Windows::choiceFuncOfText();
			break;
		case FunctionsOfProgram::FILE:
			Windows::choiceFuncOfFile();
			break;
		case FunctionsOfProgram::KEY:
			Windows::choiceKeyGen();
			break;
		case FunctionsOfProgram::OFF:
			std::cout << "����� �� ����������...\n";
			return;
			break;
		default: cout << "������\n";
		}
	}
}

void Windows::choiceFuncOfText() {
    cout << "\n�������� �������� ��� ����������/������������ ������:" << endl;
    cout << "1) ������� ����" << endl;
    cout << "2) ���� ��������" << endl;
    cout << "3) ���� ������" << endl;
    cout << "4) RSA" << endl;
    cout << "5) ����� �� ASCII" << endl;
    cout << "6) XOR" << endl;
    cout << "7) RC4" << endl;
    cout << "8) ���������� ������������" << endl;

    int choice = getChoice(1, 8, "������� ��� ����� (1-8): ");

    switch (Algorithms(choice)) {
    case Algorithms::AFFINE:      choiceFuncOfTextAffine(); break;
    case Algorithms::PLAYFAIR:    choiceFuncOfTextPleyfair(); break;
    case Algorithms::CAESAR:      choiceFuncOfTextCaesar(); break;
    case Algorithms::RSA:         choiceFuncOfTextRsa(); break;
    case Algorithms::ASCII:       choiceFuncOfTextAscii(); break;
    case Algorithms::XOR:        choiceFuncOfTextXOR(); break;
    case Algorithms::RC4:         choiceFuncOfTextRc4(); break;
    case Algorithms::PERMUTATION: choiceFuncOfTextPermutation(); break;
    default: cout << "������\n";
    }
}

void Windows::choiceFuncOfFile() {
    cout << "\n�������� �������� ��� ����������/������������ �����:" << endl;
    cout << "1) ������� ����" << endl;
    cout << "2) ���� ��������" << endl;
    cout << "3) ���� ������" << endl;
    cout << "4) RSA" << endl;
    cout << "5) ����� �� ASCII" << endl;
    cout << "6) XOR" << endl;
    cout << "7) RC4" << endl;
    cout << "8) ���������� ������������" << endl;

    int choice = getChoice(1, 8, "������� ��� ����� (1-8): ");

    switch (Algorithms(choice)) {
    case Algorithms::AFFINE:      choiceFuncOfFileAffine(); break;
    case Algorithms::PLAYFAIR:    choiceFuncOfFilePleyfair(); break;
    case Algorithms::CAESAR:      choiceFuncOfFileCaesar(); break;
    case Algorithms::RSA:         choiceFuncOfFileRsa(); break;
    case Algorithms::ASCII:       choiceFuncOfFileAscii(); break;
    case Algorithms::XOR:        choiceFuncOfFileXOR(); break;
    case Algorithms::RC4:         choiceFuncOfFileRc4(); break;
    case Algorithms::PERMUTATION: choiceFuncOfFilePermutation(); break;
    default: cout << "������\n";
    }
}