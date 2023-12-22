// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);


TBitField::TBitField(int len)
{
    /*if (len < 0)
        throw "oshibka";
    else if (len == 0) 
    {
        BitLen = 0;
        MemLen = 0;
        pMem = nullptr;
    }
    else{
    BitLen = len;
    if (len % 8 == 0)
        MemLen = BitLen / sizeof(TELEM);
    else
        MemLen = BitLen / sizeof(TELEM) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 1;
}*/}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n<0 || n>BitLen)
        throw "neverno";
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n<0 || n>BitLen)
        throw "neverno";
    return 1 << ((n - 1) % (8 * sizeof(TELEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n<0 || n>BitLen)
        throw "neverno";
    pMem[GetMemIndex(n)] |= GetMemMask(n);

        
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n<0 || n>BitLen)
        throw "oshibka";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n<0 || n>BitLen) 
        throw "oshibka";
    return pMem[GetMemIndex(n)] &= GetMemMask(n) ; 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this != &bf) 
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        this->~TBitField();
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen && MemLen == bf.MemLen) {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != pMem[i])
                return false;
        return true;
    }
    return false;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen || MemLen != bf.MemLen) {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] == pMem[i])
                return false;
        return true;
    }
    return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int Max = max(BitLen, bf.BitLen); 
    int Min = min(BitLen, bf.BitLen); 
    TBitField tmp(Max);  

    for (int i = 0; i <Min; i++) {
        tmp.pMem[i] = bf.pMem[i] | pMem[i];   
    }

    for (int i=Min; i < MemLen; i++) {
        tmp.pMem[i] = pMem[i];
    }

    for (int i=Min; i < bf.MemLen; i++) {
        tmp.pMem[i] = bf.pMem[i];
    }

    return tmp; 
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
   
    int Max = max(BitLen,bf.BitLen);  
    int Min = min(BitLen,bf.BitLen);  
    TBitField tmp(Max); 

 
    for (int i = 0; i <Min; i++) { 
        tmp.pMem[i] = bf.pMem[i] & pMem[i];
    }

    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen); 
    int i; 
    for (i = 0; i < MemLen; i++) { 
        tmp.pMem[i] = ~pMem[i]; 
    }

        return tmp; 
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string tmp;
    istr >> tmp;

    if (tmp.size() != bf.GetLength())
        throw - 1;
        else{
        for (int i = 0; i < bf.GetLength(); i++)
                {
                if (tmp[i] == '0')
                    bf.ClrBit(i);
                else if (tmp[i] == '1')
                    bf.SetBit(i);
                else
                    throw -1;
                }

    }
    return istr; 
     
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++)
    {
        if (bf.GetBit(i))
            ostr << 1;
        else
            ostr << 0;
    }
    return ostr;
}
