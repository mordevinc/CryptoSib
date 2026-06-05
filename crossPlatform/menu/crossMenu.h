#pragma once
#ifndef CROSSMENU_H
#define CROSSMENU_H
// Платформозависимые заголовки
#include "../crypto/crossCrypto.h"
#include "../../src/menu/menu.h"


void crosspShowMenu();

void crosspChoiceFuncOfTextAffine();
void crosspChoiceFuncOfTextPleyfair();
void crosspChoiceFuncOfFileAffine();
void crosspChoiceFuncOfFilePleyfair();

void crosspChoiceFuncOfText(); 
void crosspChoiceFuncOfFile();


#endif