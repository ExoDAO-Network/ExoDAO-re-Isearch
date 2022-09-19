#pragma ident  "@(#)soundex.cxx  1.6 11/04/98 09:54:19 BSN"

/************************************************************************

Copyright (c) 1995, Basis Systeme netzwerk/Munich
              All Rights Reserved.

************************************************************************/

/*- @@@
File:        soundex.cxx
Version:     2.01
Description: Soundex support for STRING class
Author:      Edward C. Zimmermann <edz@bsn.com>
@@@ -*/

/*-
// $Log: soundex.cxx,v $
// Revision 1.1  2007/05/15 15:47:23  edz
// Initial revision
//
// Revision 1.11  1996/05/02  19:52:37  edz
// Sync
//
// Revision 1.1  1995/11/19  02:19:09  edz
// Initial revision
//
// Revision 1.1  1995/11/19  02:19:09  edz
// Initial revision
//
// Revision 2.1  1995/10/22  23:22:07  edz
// Silly bug fix
//
// Revision 2.0  1995/10/05  21:59:48  edz
// Retro-fit to CNIDR's Isearch
//
// Revision 1.5  1995/07/20  22:45:45  edz
// Sync
//
// Revision 1.4  1995/06/12  08:53:10  edz
// Cosmetic changes.
//
// Revision 1.3  1995/06/08  15:08:33  edz
// Reworked to be FASTER and for ISO 8859-1 (Latin 1) platforms
// to support accented and ligature characters.
//
-*/

#include <ctype.h>
#include <memory.h>
#include "defs.hxx"
#include "soundex.hxx"

#define MODULO	7		/* 7 for Soundex, 10 otherwize */
#define _SP -1			/* Code for ' ', \r and \n: 0 or -1 */

// Question: - words? eg. anti-communist ?

/*
Character classification:
In Phonix: F and V are mapped to 7
In Soundex:F and V is mapped to 1, clumped with B and P
==> map to 8

In Phonix: S and Z are mapped to 8
In Soundex: S and Z is mapped to 2, clumped with C,G,J,K,Q
==> map to 9

So <Soundex code> is <Phonix code>%7
In phonix all vowels as first character are mapped together!
*/

#define ISO_8859_1 1

#if ISO_8859_1
// ISO 8859-1 (Latin-1) Soundex Character Codes
// with support for accented characters and ligatures.

// Soundex Code tables for other ISO 8859-x character
// sets can be designed. The utility of the soundex
// algorithm for non Anglo-Saxon languages is questionable.
// [even for English its utility is very specific]
static const signed char Soundex_code[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, _SP, -1, -1, _SP, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, _SP, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,
    7 /* A */, 1 /* B */, 2 /* C */, 3 /* D */,
    7 /* E */, 8 /* F */, 2 /* G */, 0 /* H */,
    7 /* I */, 2 /* J */, 2 /* K */, 4 /* L */,
    5 /* M */, 5 /* N */, 7 /* O */, 1 /* P */,
    2 /* Q */, 6 /* R */, 9 /* S */, 3 /* T */,
    7 /* U */, 8 /* V */, 0 /* W */, 2 /* X */,
    7 /* Y */, 9 /* Z */,
    -1, -1, -1, -1, -1, -1,
    7 /* a */, 1 /* b */, 2 /* c */, 3 /* d */,
    7 /* e */, 8 /* f */, 2 /* g */, 0 /* h */,
    7 /* i */, 2 /* j */, 2 /* k */, 4 /* l */,
    5 /* m */, 5 /* n */, 7 /* o */, 1 /* p */,
    2 /* q */, 6 /* r */, 9 /* s */, 3 /* t */,
    7 /* u */, 8 /* v */, 0 /* w */, 2 /* x */,
    7 /* y */, 9 /* z */ ,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, 2 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    3 /* � */, 5 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, -1,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 0 /* � */, 3 /* � */, 2 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, 2 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    3 /* � */, 5 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 7 /* � */, 7 /* � */, -1,
    7 /* � */, 7 /* � */, 7 /* � */, 7 /* � */,
    7 /* � */, 0 /* � */, 3 /* � */, 0 /* � */
};
#else
const CHSIZ = (1 << (8 * sizeof (char)));
static signed char Soundex_code[CHSIZ];

static int BuildSoundexTable ()
{
  static int i = 0; // Build table first time only
  while (i < CHSIZ)
    {
      char ch2 = toupper((unsigned char)i);
      switch (ch2)
	{
	case ' ': case '\r': case '\n':
	  ch2 = _SP;
	  break;
	case 'H': case 'W':
	  ch2 = 0;
	  break;
	case 'B': case 'P':
	  ch2 = 1;
	  break;
	case 'C': case 'G': case 'J': case 'K': case 'Q': case 'X':
	  ch2 = 2;
	  break;
	case 'D': case 'T':
	  ch2 = 3;
	  break;
	case 'L':
	  ch2 = 4;
	  break;
	case 'M': case 'N':
	  ch2 = 5;
	  break;
	case 'R':
	  ch2 = 6;
	  break;
	case 'A': case 'E': case 'I': case 'O': case 'U': case 'Y':
	  ch2 = 7;
	  break;
        case 'F': case 'V':
          ch2 = 8;
	case 'S': case 'Z':
	  ch2 = 9;
	  break;
	default:
	  if (!_ib_isalpha((UCHR)i)) ch2 = -1; 
	  break;
	}
      Soundex_code[i++] = ch2;
    };
  return i;
}
#endif

UINT8 SoundexEncodeName(const STRING& Name, GDT_BOOLEAN FirstThenLast)
{
  STRING name (Name);

  size_t  pos = name.Search(",");
  if (pos == 0 && FirstThenLast == GDT_TRUE)
    pos = name.SearchReverse(" ");
  if (pos > 0)
    {
#if 0
      // TODO: Should check for Mr. Miss Mrs Frau Herr Dr Prof
      char ch = name.GetChr(1);
      const char *ptr = name.c_str();
      switch (ch) {
	case 'F':
	  if (strncmp(ptr, "Frau", 4) == 0)
	    {
	      if (isspace(ptr+4))
		skip = 4;
	      else if (strncmp(ptr, "Fraulein", 8) == 0 && isspace(ptr+8))
		skip = 5;
	    }
	  break;
	case 'M':
	  if (strncmp(ptr , "Mr", 2) == 0) {
	    if ((ch = name.GetChr(3)) == 's')
	      {
		// Mrs or Mrs.
	        if ((ch = name.GetChr(4)) == '.') skip = 4;
		else if (isspace(ch) skip = 3; 
	      }
	    else if (ch == '.') skip = 3;
	    else if (isspace(ch)) skip = 2;
	  }
	break;
      }
#endif
      STRING first (name);
      STRING last  (name);
      first.EraseBefore(pos+1);
      last.EraseAfter(pos-1);
      if (FirstThenLast)
	name = first + " " + last;
      else
	name = last + " " + first;
      name.Pack();
    }
  return SoundexEncode(name);
}


// Modified Soundex algorithm
UINT8 SoundexEncode (const STRING& Word, PSTRING StringBuffer, const int HashLen)
{
#ifndef ISO_8859_1
  static int i = 0; // Build table first time only
  if (!i) i = BuildSoundexTable ();
#endif
  int               slen = HashLen > 10 ? 10 : HashLen;
  CHR               Key[11];
  int               Index = 0;
  const STRINGINDEX WordLength = Word.GetLength ();

  // Do we have a word?
  if (WordLength)
    {
      int code, old_code = 0;
      CHR LastLetter;

      STRINGINDEX pos = 0;
      CHR         ch;

      // Get first non white letter
      do {
	ch = Word.GetChr(++pos);
      } while (!IsWordSep(ch) && pos < WordLength);

      // If its a vowel then map to common characer
      if (Soundex_code[(unsigned char)ch] == 7) ch = '7';
      // Keep first element
      Key[Index++] = (LastLetter = toupper((UCHR)ch));

      // scan rest of string
      while ((Index < slen) && ++pos <= WordLength)
	{
	  ch = Word.GetChr(pos);
	  // Soundex ignores repeated successive characters
	  // --- to support complex words we ignore '-' as well
	  if (LastLetter != ch && ch != '-')
	    {
	      /* new LastLetter */
	      LastLetter = ch;

	      /* ignore letters with code <=0 */
	      if ((code = Soundex_code[(unsigned char) LastLetter]) > 0)
		{
		  if (old_code != 7 || code != old_code)
		    {
		      Key[Index++] = (CHR) ('0' + code%(MODULO));
		      old_code =  (ch != 'e' ? code : 0);
		    }
		  else old_code = 0;
		}
	      else if (code == -1)
		{
		  break;	// Non-alpha character
		}
	    }
	}			// while
    }
  memset (&Key[Index], '0', sizeof(CHR)*(slen - Index));// Right pad with '0's
  Key[slen] = '\0';		// ASCIZ

  if (StringBuffer) *StringBuffer = Key;

  // Now generate the number
  UINT8 Number = 0;
  while (--slen >= 0)
    Number = (Number << 8) + (BYTE)Key[slen]; 

  return Number;
}

// Modified Soundex algorithm
GDT_BOOLEAN SoundexMatch (const STRING& Word, const STRING& Hash)
{
  return SoundexMatch ((const char *)Word, Hash);
}

GDT_BOOLEAN SoundexMatch (const CHR *Word, const STRING& Hash)
{

#ifndef ISO_8859_1
  static int i = 0; // Build table first time only
  if (!i) i = BuildSoundexTable ();
#endif
  int slen = Hash.GetLength();
  if (slen > 10) slen = 10;
  CHR Key[11];
  int Index = 0;

  // Do we have a word?
  if (*Word)
    {
      int code, old_code = 0;
      UCHR LastLetter;

      size_t pos = 0;
      UCHR ch= Word[pos]; // Get first letter
      // If its a vowel then map to common characer
      if (Soundex_code[(unsigned char)ch] == 7) ch = '7';
      // Keep first element
      Key[Index++] = (LastLetter = toupper((UCHR)ch));
      if (Hash.GetChr(Index) != LastLetter)
	return GDT_FALSE; // No match

      // scan rest of string
      while ((Index < slen) && (ch = Word[++pos]))
	{
	  // Soundex ignores repeated successive characters
	  // --- to support complex words we ignore '-' as well
	  if (LastLetter != ch && ch != '-')
	    {
	      /* new LastLetter */
	      LastLetter = ch;

	      /* ignore letters with code <=0 */
	      if ((code = Soundex_code[(unsigned char) LastLetter]) > 0)
		{
		  if (old_code != 7 || code != old_code)
                    {
		      ch = (UCHR) ('0' + code%(MODULO));
		      if (Hash.GetChr(Index+1) != ch)
			return GDT_FALSE;
		      Key[Index++] = ch;
		      old_code = (ch != 'e' ? code : 0);
		    }
		  else old_code = 0;
		}
	      else if (code == -1)
		{
		  break;	// Non-alpha character
		}
	    }
	}			// while
    }
  memset (&Key[Index], '0', sizeof(CHR)*(slen - Index));// Right pad with '0's
  Key[slen] = '\0';		// ASCIZ
  return (Hash.Equals(Key));
}
