/*@@@
File:		Ipresent.cxx
Version:	1.00
$Revision$
Description:	Command-line search utility w/ XML results
@@@*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

//#include "isearch.hxx"

#include "common.hxx"
#include "string.hxx"
#include "vidb.hxx"
#include "registry.hxx"
#include "result.hxx"
#include "dtreg.hxx"
//#include "HTMLEntities.hxx"


void
XmlBail(const STRING& DBName, const STRING& error_message) {
  STRING XmlBuffer;
  
  XmlBuffer = DBName;
//  XmlBuffer.XmlCleanup();
  cout << "\t<isearch:present status=\"Error\" dbname=\"" << XmlBuffer
       << "\">" << endl;

  XmlBuffer = error_message;
//  XmlBuffer.XmlCleanup();
  cout << "\t\t<isearch:error_block>" << endl;
  cout << XmlBuffer;
  cout << "\t\t</isearch:error_block>" << endl;
  cout << "\t</isearch:present>" << endl;
  cout << "</zpresent>" << endl;
  exit(0);
}

int 
main(int argc, char** argv) {
  if (argc < 2) {
    cerr << argv[0] <<  ": zpresent v" <<  __IB_Version << endl << "\
Copyright (c) 2020-2022 Project re-Isearch, 2000-2003 MCNC/CNIDR and A/WWW Enterprises\n\
Usage is: "  << argv[0] << " [-d db] [options]\n\
-d (X)   # Search database with root name (X).\n\
-id (X)  # Request document(s) with docid (X).\n\
-l (X)   # Request document(s) with docids listed in file (X).\n\
-p (X)   # Present element set (X) with results.\n\
-f (X)   # Present results in format (X)." << endl;
 
//    PrintDoctypeList(cerr);

#if 0
    cerr << "\n\
zpresent is currently experimental and should be used cautiously.  Suggestions\n\
and improvements are welcomed." << endl << endl;
#endif
    exit (-1);
  }

  STRING charset;

  GetGlobalCharset(&charset);
  if (charset.IsEmpty()) charset = "iso-8859-1";

  cout << "<?xml version=\"1.0\" encoding=\"" << charset << "\"?>\n\
<!-- Generated by zpresent v" << __IB_Version << ", part of the re-Isearch engine -->\n\
<!DOCTYPE zpresent SYSTEM \"zpresent-v3.dtd\">\n\
<zpresent xmlns:isearch=\"https://raw.githubusercontent.com/re-Isearch/re-Isearch/master/dtd\">" << endl;

  STRING Flag;
  STRING DBName="";
  STRING RecordKey="";
  STRING ESet;
  RecordSyntax Encoding;
  INT x = 0;
  INT LastUsed = 0;
  STRING DBPathName, DBFileName;
  STRING PathName, FileName;
  RESULT RsRecord;
  STRING Record;
  GDT_BOOLEAN Error=GDT_FALSE;
  STRING error_message="";
  STRLIST RecordKeyList;
  INT n_keys;
  STRING ListFile;
  STRING XmlBuffer;

  // HTMLEntities Entities;

  SetGlobalCharset();

  ESet = "B";
  while (x < argc) {
    if (argv[x][0] == '-') {
      Flag = argv[x];
      if (Flag.Equals("-d")) {
	if (++x >= argc) {
	  error_message.Cat("\t\t\t<isearch:error_text>ERROR: No database name specified after -d.</isearch:error_text>\n");
	  XmlBail(DBName,error_message);
	}
	DBName = argv[x];
	LastUsed = x;
      }
      if (Flag.Equals("-id") || Flag.Equals("-key")) {
	if (++x >= argc) {
	  error_message.Cat("\t\t\t<isearch:error_text>ERROR: No document key specified after -id.</isearch:error_text>\n");
	  XmlBail(DBName,error_message);
	}
	RecordKey = argv[x];
	LastUsed = x;
      }
      if (Flag.Equals("-p")) {
	if (++x >= argc) {
	  error_message.Cat("\t\t\t<isearch:error_text>ERROR: No element set specified after -p.</isearch:error_text>\n");
	  XmlBail(DBName,error_message);
	}
	ESet = argv[x];
	LastUsed = x;
      }
      if (Flag.Equals("-f")) {
	if (++x >= argc) {
	  error_message.Cat("\t\t\t<isearch:error_text>ERROR: No format specified after -f.</isearch:error_text>\n");
	  XmlBail(DBName,error_message);
	}
	Encoding = argv[x];
	LastUsed = x;
      }
      if (Flag.Equals("-l")) {
	if (++x >= argc) {
	  error_message.Cat("\t\t\t<isearch:error_text>ERROR: No list file specified after -l.</isearch:error_text>\n");
	  XmlBail(DBName,error_message);
	}
	ListFile = argv[x];
	LastUsed = x;
      }
    }
    x++;
  }
	
  if (DBName.GetLength() == 0) {
    error_message.Cat("\t\t\t<isearch:error_text>No database name given.</isearch:error_text>\n");
    XmlBail(DBName,error_message);
  }
  /*
#ifdef REMOTE_INDEXING
  // Store the cache file with the index, and any retrieved (remote)
  // files in the CachePath
  STRING CacheName;
  STRING CachePath = "";
  CacheName = DBName;
  CacheName.Cat(DbExtCache);
  ExpandFileSpec(&CacheName);
  Cache = new RLDCACHE(CachePath, CacheName, GDT_FALSE);
#endif
  */
  if ((RecordKey.GetLength() > 0) && (ListFile.GetLength() > 0)) {
    error_message.Cat("\t\t\t<isearch:error_text>Cannot specify both -id and -l.</isearch:error_text>\n");
    XmlBail(DBName,error_message);
  }

  if (ListFile.GetLength() > 0) {
    RecordKey.ReadFile(ListFile);
    RecordKey.Replace("\n","");
  }

  if (RecordKey.GetLength() == 0) {
    error_message.Cat("\t\t\t<isearch:error_text>No record keys given.</isearch:error_text>\n");
    XmlBail(DBName,error_message);
  }

  RecordKeyList.Split(',',RecordKey);
  n_keys = RecordKeyList.GetTotalEntries();
  if (n_keys <= 0) {
    error_message.Cat("\t\t\t<isearch:error_text>No record ids given.</isearch:error_text>\n");
    XmlBail(DBName,error_message);
  }
  
  /*	
  if (!setlocale(LC_CTYPE,"")) {
    fprintf(stderr,"Warning: Failed to set the locale!\n");
  }
  */

  x = LastUsed + 1;
  if (x > argc) {
    error_message.Cat("\t\t\t<isearch:error_text>Unrecognized arguments</isearch:error_text>\n");
    XmlBail(DBName,error_message);
  }
  
  DBPathName = DBName;
  DBFileName = DBName;
  RemovePath(&DBFileName);
  RemoveFileName(&DBPathName);

  // See if we have a legitimate file
  if (!DBExists(DBName)) {
    // The file does not exist
    error_message.Cat("\t\t\t<isearch:error_text>The specified database was not found: ");
    error_message.Cat(DBName);
    error_message.Cat("</isearch:error_text>\n");
    XmlBail(DBName,error_message);
  }

  VIDB *pdb;
  pdb = new VIDB(DBPathName, DBFileName, true);
  /*
  if (DebugFlag) {
    pdb->DebugModeOn();
  }
  */
  if (!pdb->IsDbCompatible()) {
    Error=GDT_TRUE;
    error_message.Cat("\t\t\t<isearch:error_text>The specified database is not compatible with this version of zpresent.</isearch:error_text>\n");
    delete pdb;
    XmlBail(DBName,error_message);
  }

  if (!Encoding.Ok())
    Encoding = Syntax::XmlRecordSyntax;

  STRING OID_encoding = Encoding.OID();

  XmlBuffer = DBName;
//  XmlBuffer.XmlCleanup();
  cout << "\t<isearch:present status=\"OK\" dbname=\"" << XmlBuffer << "\">" << endl <<
	"\t\t<isearch:results count=\"" << n_keys << "\" eset=\"" << ESet << "\" prs=\"" <<
	OID_encoding << "\">";
  //  printf("\">\n");

  RecordKey = "";
  pdb->BeginRsetPresent(OID_encoding);

  for (INT i=1;i<=n_keys;i++) {

    RecordKeyList.GetEntry(i,&RecordKey);
    pdb->KeyLookup(RecordKey, &RsRecord);
    pdb->Present(RsRecord, ESet, OID_encoding, &Record);
    if (Record.GetLength() > 0) {
      Record.Trim();
      // Record.TrimLeading();
      Record.Print();

    } else {
      error_message.Cat("\t\t\t\t<isearch:error_text>Record ");
      error_message.Cat("not found.</isearch:error_text>\n");
      cout << "\t\t\t<isearch:result docid=\"" << RecordKey <<
	"\" status=\"Error\">\n";
      cout << error_message;
      cout << "\t\t\t</isearch:result>" << endl;
    }
  }


  pdb->EndRsetPresent(OID_encoding);

  cout << "</isearch:results>\n\t</isearch:present>\n</zpresent>" << endl;

  //#ifdef REMOTE_INDEXING
  //  delete Cache;
  //#endif

  if (pdb)
    delete pdb;
  exit (0);
}