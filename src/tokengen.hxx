/*
Copyright (c) 2020-21 Project re-Isearch and its contributors: See CONTRIBUTORS.
It is made available and licensed under the Apache 2.0 license: see LICENSE
*/
#ifndef TOKENGEN_HXX
#define TOKENGEN_HXX

class TOKENGEN
{
  friend class INFIX2RPN;
public:
  TOKENGEN (const STRING& InString);
  ~TOKENGEN ();
  bool GetEntry (const size_t Index, STRING *StringEntry);
  void        SetQuoteStripping (bool);
  size_t      GetTotalEntries ();

private:
  CHR * nexttoken (CHR *input, STRING *token);
  STRLIST TokenList;
  bool DoStripQuotes, HaveParsed;
  void DoParse (void);
  CHR *InCharP;
};

#endif
