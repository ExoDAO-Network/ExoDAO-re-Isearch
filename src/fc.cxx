/*
Copyright (c) 2020-21 Project re-Isearch and its contributors: See CONTRIBUTORS.
It is made available and licensed under the Apache 2.0 license: see LICENSE
*/
/*-@@@
File:		fc.cxx
Version:	1.00
Description:	Class FC - Field Coordinates
@@@*/

#include "fc.hxx"
#include "string.hxx"
#include "common.hxx"

#pragma ident  "@(#)fc.cxx  1.11 09/03/99 05:59:11 BSN"


FC::FC ()
{
  FieldStart = FieldEnd = 0;
}

FC::FC (const GPTYPE Gp)
{
  *this = Gp;
}


FC::FC (const FC& Fc)
{
  *this = Fc;
}

FC::FC(const GPTYPE GpPair[2])
{
  *this = GpPair;
}

FC::FC(const GPTYPE Start, const GPTYPE End)
{
  FieldStart = Start;
  FieldEnd = End;
}

void FC::FlipBytes()
{
  GpSwab(&FieldStart);
  GpSwab(&FieldEnd);
}


FC::operator STRING() const
{
  STRING res;

  res << "(" << FieldStart << "," << FieldEnd << ")";
  return res;
}


ostream& operator <<(ostream& Os, const FC& Fc)
{
  Os << "(" << Fc.FieldStart << ',' << Fc.FieldEnd << ")"; // << "[" << (Fc.FieldEnd-Fc.FieldStart) << "]";
  return Os;
}


FC& FC::operator =(const FC& Fc)
{
  FieldStart = Fc.FieldStart;
  FieldEnd = Fc.FieldEnd;
  return *this;
}

FC& FC::operator =(const GPTYPE Gp)
{
  FieldStart = Gp;
  FieldEnd = Gp;
  return *this;
}

FC& FC::operator =(const GPTYPE Pair[2])
{
  if (Pair)
    {
      FieldStart = Pair[0];
      FieldEnd = Pair[1];
    }
  else FieldStart = FieldEnd = 0;
  return *this;
}


FC operator+(int offset, const FC& Fc)
{
  return FC(Fc.FieldStart+offset, Fc.FieldEnd+offset);
}

FC operator-(int offset, const FC& Fc)
{
  return FC(offset - Fc.FieldStart, offset - Fc.FieldEnd);
}

FC operator+(const FC& Fc, int offset)
{
  return FC(Fc.FieldStart+offset, Fc.FieldEnd+offset);
}

FC operator-(const FC& Fc, int offset)
{
  return FC(Fc.FieldStart-offset, Fc.FieldEnd-offset);
}


FC& FC::operator+=(const GPTYPE Offset)
{
  FieldStart += Offset;
  FieldEnd   += Offset;
  return *this;
}

FC& FC::operator+=(const FC& Fc)
{
  FieldStart += Fc.FieldStart;
  FieldEnd   += Fc.FieldEnd;
  return *this;
}

FC& FC::operator-=(const GPTYPE Offset)
{
  FieldStart -= Offset;
  FieldEnd -= Offset;
  return *this;
}

FC& FC::operator-=(const FC& Fc)
{ 
  FieldStart -= Fc.FieldStart;
  FieldEnd -= Fc.FieldEnd; 
  return *this; 
}

#if 0

bool FC::Contains (const FC& Fc) const
{
  return (Fc.FieldStart >= FieldStart && Fc.FieldEnd <= FieldEnd);
}

bool FC::Contains (const GPTYPE Gp) const
{
  return (Gp >= FieldStart && Gp <= FieldEnd);
}

bool FC::operator ==(const FC& Fc) const
{
  return (FieldStart == Fc.FieldStart && FieldEnd == Fc.FieldEnd);
}

bool FC::operator <=(const FC& Fc) const
{
  return (FieldStart <= Fc.FieldStart && FieldEnd <= Fc.FieldEnd);
}

bool FC::operator >=(const FC& Fc) const
{
  return (FieldStart >= Fc.FieldStart && FieldEnd >= Fc.FieldEnd);
}

bool FC::operator <(const FC& Fc) const
{ 
  return (Fc.FieldStart < FieldStart && Fc.FieldEnd < FieldEnd);
}

bool FC::operator <(const GPTYPE Gp) const
{
  return (Gp < FieldStart);
}

bool FC::operator >(const FC& Fc) const
{ 
  return (Fc.FieldStart > FieldStart && Fc.FieldEnd > FieldEnd);
}

bool FC::operator >(const GPTYPE Gp) const 
{ 
  return (Gp > FieldEnd); 
}

#endif

INT FC::Compare (const FC& Fc) const
{
  if ( (FieldStart <= Fc.FieldStart) && (FieldEnd >= Fc.FieldEnd) )
    return 0; 
  else if ( FieldStart < Fc.FieldStart ) 
    return -1; 
  else 
    return 1;
}

#if 0

bool operator >(const GPTYPE Gp, const FC& Fc)
{
  return Gp > Fc.FieldEnd;
}

bool operator <(const GPTYPE Gp, const FC& Fc)
{
  return Gp < Fc.FieldStart;
}

INT Compare(const FC& Fc1, const FC& Fc2)
{
  return Fc1.Compare(Fc2);
}

void FC::SetFieldStart (const GPTYPE NewFieldStart)
{
  FieldStart = NewFieldStart;
}

GPTYPE FC::GetFieldStart () const
{
  return FieldStart;
}

void FC::SetFieldEnd (const GPTYPE NewFieldEnd)
{
  FieldEnd = NewFieldEnd;
}

GPTYPE FC::GetFieldEnd () const
{
  return FieldEnd;
}

GPTYPE FC::GetLength () const
{
  return FieldEnd - FieldStart;
}

#endif

void FC::Write (PFILE fp, const GPTYPE Offset) const
{
//cerr << "FC writing " << *this << endl;
  ::Write (FieldStart + Offset, fp);
  ::Write (FieldEnd + Offset, fp);
}

void FC::Write (PFILE fp) const
{
  ::Write (FieldStart, fp);
  ::Write (FieldEnd, fp);
}


bool FC::Read (PFILE fp)
{
  bool result = false;
  FieldStart = FieldEnd = 0;
  if (!feof(fp))
    {
      ::Read(&FieldStart, fp);
      ::Read(&FieldEnd, fp);
      result = true;
//cerr << "XXXXXXX Value = " << *this << " fd=" << fileno(fp) << "  ftell=" << ftell(fp) << endl;
    }
  return result;
}

FC::~FC ()
{
}


void Write(const FC& Fc, PFILE Fp)
{
  Fc.Write(Fp);
}

bool Read(PFC FcPtr, PFILE Fp)
{
  return FcPtr->Read(Fp);
}

