#pragma once
#ifndef CROSSMENU_H
#define CROSSMENU_H
// Платформозависимые заголовки
#include "../crypto/crossCrypto.h"
#include "../../src/menu/menu.h"

class CrossPlatform {

public:
	void crosspShowMenu();

private:
	void choiceFuncOfTextAffine();
	void choiceFuncOfTextPleyfair();
	void choiceFuncOfFileAffine();
	void choiceFuncOfFilePleyfair();

	void choiceFuncOfText();
	void choiceFuncOfFile();

	void choiceKeyGen();

};

#endif