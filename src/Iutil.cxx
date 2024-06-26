/* Copyright (c) 2020-21 Project re-Isearch and its contributors: See CONTRIBUTORS.
It is made available and licensed under the Apache 2.0 license: see LICENSE */
/*@@@
File:    Iutil.cxx
Description:   Command-line utility for re-Isearch databases
@@@*/
static const char RCS_Id[] = "$Id: Iutil.cxx,v 1.2 2007/05/21 07:13:49 edz Exp $";

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <iostream.h>
#include <iomanip.h>
#include "common.hxx"
#include "vidb.hxx"
#include "record.hxx"
#include "strlist.hxx"
#include "dtreg.hxx"
#include "thesaurus.hxx"
#if defined(_MSDOS) || defined(_WIN32)
# include <direct.h>
#endif
#include "registry.hxx"

int 
main(int argc, char **argv)
{
#ifdef __GNUG__
  // cout is a performance disaster in libg++ unless we do this.
  ios::sync_with_stdio (0);
#endif
/*
  if (argc < 2) return -1;
  cerr << "Path=" << argv[1] << endl;
  cerr << "Dir=" << argv[2] << endl;
  cerr << "Relative Path = " << RelativizePathname(argv[1], argv[2]) << endl;
  return 0;
*/

  if (argc < 2) {
    cout << endl << "Iutil, Version " << __IB_Version
    << " " << __DATE__ << " (" << __HostPlatform << ")" << endl
    <<"Copyright \251 1995-2007 Basis Systeme netzwerk/Munich. All Rights Reserved." << endl << endl;
    cout << "Usage is: " << argv[0] << " [-d db] [options]" << endl
      << "Options:" << endl
      << " -d (X)         // Use (X) as the root name for database files." << endl
      << " -id (X)        // Select document with docid (X)." << endl
      << " -thes (X)      // File (X) contains Thesaurus." << endl
      << " -centroid      // Create centroid." << endl
      << " -vi            // View summary information about the database/record." << endl
      << " -vf            // View list of fields defined in the database." << endl
      << " -v             // View list of documents in the database." << endl
      << " -mdt           // Dump MDT (debug option)." << endl
      << " -inx           // Dump INX (debug option)." << endl
      << " -level NN      // Set message level to NN (0-255)." << endl
      << " -newpaths      // Prompt for new pathnames for files." << endl 
      << " -relative (Dir)// Relativize all paths with respect to (Dir)." << endl
      << "                // \".\" is current directory, \"\" is db path." << endl
      << " -mvdir old=new // Change all paths old to new." << endl
      << "                // Example: /opt=/var will change /opt/main.html to /var/main.html but" << endl
      << "                // not change /opt/html/main.html (see -dirmv below to change base of tree)" << endl
      << " -dirmv old=new // Move the base of tree from old to new." << endl
      << "                // Example: /opt=/var will change /opt/html/main.html to /var/html/main.html etc." << endl
      << " -del           // Mark individual documents (by key) to be deleted from database." << endl
      << "                // Note: to remove records by file use the Idelete command instead." << endl
      << " -del_expired   // Mark expired documents as deleted." << endl
      << " -undel         // Unmark documents (by key) that were marked for deletion." << endl
      << " -c             // Cleanup database by removing unused data (useful after -del)." << endl
      << " -erase         // Erase the entire database." << endl
      << " -g (X)         // Use (X) as Stopwords list (language)." << endl
      << " -gl0]          // Clear external stopwords list and use default." << endl
      << " -gt (X)        // Set (X) as the global document type for the database." << endl
      << "                // Specify X as * to get a list of available doctypes." << endl
      << " -gt0           // Clear the global document type for the database." << endl
      << " -server host   // Set the server hostname or IP address." << endl
      << " -web URL=base  // map base/XXX -> URL/XXX (e.g. http://www.nonmonotonic.com/=/var/html-data/BSN/)." << endl
      << " -mirror ROOT   // Set Mirror root." << endl
      << " -collapse      // Collapse last two database indexes." << endl
      << " -optimize      // Optimize database indexes." << endl
      << " -pcache (X)    // Set presentation cache base directory to (X)." << endl
      << "                // Uses X/<DATABASE> for files. (X) must exist and be writable." << endl
      << " -fill (X)[,..] // Fill the headline cache (not CacheDir must be set beforehand!) for the" << endl
      << "                // different record syntaxes (,-list), where (X) is the Record Syntax OID" << endl
      << "                // or any of the \"shorthand names\" HTML, SUTRS, USMARC, XML." << endl
      << " -clip (NN)     // Set Db Search cut-off default." << endl
      << " -priority (N.N)// Set priority factor." << endl
      << " -title (X)     // Set database title to (X)." << endl
      << " -copyright (X) // Set database copyright statement." << endl
      << " -comments (X)  // Set database comments statement." << endl
      << " -o (X)         // Document type specific option." << endl << endl
      << "Example:  Iutil -d POETRY -del key1 key2 key3" << endl << endl;
    return 0;
  } 
  STRLIST         DocTypeOptions;
  DOCTYPE_ID      GlobalDoctype;
  STRING          Title, Comments, Copyright;
  STRING          Server, URL, Pages, Mirror;
  STRING          RecordID;
  STRING          CacheDir;
  STRING          StoplistFilename;
  STRING          FillCacheSyntax;
  INT             SetGlobalDoctype = 0;
  INT             SetStoplist = 0;
  INT             Clip = 0;
  DOUBLE          PriorityFactor =  1.192092896E-07F;
  STRING          Flag;
  STRING          DBName;
  STRING          OldDir, NewDir;
  STRING          OldDirBase, NewDirBase;
  STRING          RootDir;
  STRLIST         WordList;
  INT             DebugFlag = 0;
  INT             Skip = 0;
  INT             EraseAll = 0;
  INT             PathChange = 0;
  INT             DeleteByKey = 0;
  INT		  DeleteExpired = 0;
  INT             UndeleteByKey = 0;
  INT             Cleanup = 0;
  INT             View = 0;
  INT             ViewInfo = 0;
  INT             ViewFields = 0;
  INT             DumpMdt = 0;
  INT             DumpInx = 0;
  INT             Scan = 0;
  INT             mvDirs = 0;
  INT             relPaths = 0;
  INT             dirsMv = 0;
  STRING          ScanField;

  INT             Optimize = 0;
  INT             Collapse = 0;

  STRING          SynonymFileName;
  INT             Synonyms = 0;
  INT             DoCentroid = 0;

  // INT Recursive = 0;
  // INT AppendDb = 0;
  // UINT4 MemoryUsage = 0;
  INT             x = 0;
  INT             LastUsed = 0;
  char           *argv0 = argv[0];

  if (argv0 == NULL) argv0 = "Iutil";

   __Register_IB_Application(argv0,  stderr, false);
#define DEF_LOG (LOG_PANIC|LOG_FATAL|LOG_ERROR|LOG_ERRNO|LOG_WARN|LOG_NOTICE|LOG_INFO)
  log_init(DEF_LOG, argv[0], stderr);
  while (x < argc) {
    if (argv[x][0] == '-') {
      Flag = argv[x];

      if (Flag.Equals("-m")) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No option specified after %s", Flag.c_str());
	  return 0;
	}
	LastUsed = x;
      } else if (Flag.Equals("-o")) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No option specified after %s", Flag.c_str());
	  return 0;
	}
	STRING          S;
	S = argv[x];
	DocTypeOptions.AddEntry(S);
	LastUsed = x;
      } else if (Flag.Equals("-S")) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No field specified after %s", Flag.c_str());
	  return 0;
	}
	ScanField = argv[x];
	Scan = 1;
	LastUsed = x;
      } else if (Flag.Equals("-d")) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No database name specified after %s", Flag.c_str());
	  return 0;
	}
	DBName = argv[x];
	LastUsed = x;
      } else if (Flag.Equals("-id")) {
        if (++x >= argc) {
          message_log (LOG_FATAL, "Option error: No key specified after %s", Flag.c_str());
          return 0;
        }
        RecordID = argv[x];
        LastUsed = x;
      } else if (Flag.Equals("-pcache")) {
        if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No directory specified after %s", Flag.c_str());
          return 0;
        }
        CacheDir = argv[x];
        LastUsed = x;
      } else if (Flag.Equals("-fill")) {
        if (++x >= argc) {
          message_log (LOG_FATAL, "Option error: No OID specified after %s", Flag.c_str());
          return 0;
        }
	FillCacheSyntax = argv[x];
	if (FillCacheSyntax ^= "html")
	  FillCacheSyntax = HtmlRecordSyntax;
	else if (FillCacheSyntax ^= "sutrs")
	  FillCacheSyntax = SutrsRecordSyntax;
	LastUsed = x;
      } else if (Flag.Equals("-title")) {
        if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No title string specified after %s", Flag.c_str());
          return 0;
        }
        Title = argv[x];
        LastUsed = x;
     } else if (Flag.Equals("-copyright")) {
        if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No copyright string specified after %s", Flag.c_str());
          return 0;
        }
        Copyright = argv[x];
        LastUsed = x;
     } else if (Flag.Equals("-comments")) {
        if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No comments string specified after %s", Flag.c_str());
          return 0;
        }
        Comments = argv[x];
        LastUsed = x;
     } else if (Flag.Equals("-server")) {
        if (++x >= argc) {
          message_log (LOG_FATAL, "Option error: No hostname specified after %s", Flag.c_str());
          return 0;
        }
        Server = argv[x];
        LastUsed = x;
     } else if (Flag.Equals("-clip")) {
        if (++x >= argc) {
          message_log (LOG_FATAL, "Option error: No number specified after %s", Flag.c_str());
          return 0;
        }
        Clip = atoi(argv[x]);
        LastUsed = x;
     } else if (Flag.Equals("-priority")) {
        if (++x >= argc) {
          message_log (LOG_FATAL, "Option error: No number specified after %s", Flag.c_str());
          return 0;
        }
        PriorityFactor = atof(argv[x]);
        LastUsed = x;
      } else if (Flag.Equals("-web")) {
        if (++x >= argc) {
          message_log (LOG_FATAL, "Option error: No arg specified after %s", Flag.c_str());
          return 0;
        }
        URL = argv[x];
        Pages = argv[x];
        STRINGINDEX pos = URL.Search("=");
        if (pos == 0)
          {
            message_log (LOG_FATAL, "Option error: Usage for %s is URL=Base", Flag.c_str());
            return -1;
          }
        URL.EraseAfter(pos-1);
        AddTrailingSlash(&URL);
        Pages.EraseBefore(pos+1);
        AddTrailingSlash(&Pages);
        LastUsed = x;
	LastUsed = x;
     } else if (Flag.Equals("-mirror")) {
        if (++x >= argc) {
          message_log (LOG_FATAL, "Option error: No directory specified after %s", Flag.c_str());
          return 0;
        }
        Mirror = argv[x];
        LastUsed = x;
      } else if (Flag.Equals("-gt")) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No document type specified after %s (use -gt0 for no type)", Flag.c_str());
	  return 0;
	}
	if (*(argv[x]) == '*') {
	  PrintDoctypeList();
	} else {
	  GlobalDoctype = argv[x];
	  SetGlobalDoctype = 1;
	}
	LastUsed = x;
      } else if (Flag.Equals("-gl")) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No Stopwords id specified after %s (use -gl0 for default)", Flag.c_str());
	  return 0;
	}
	StoplistFilename = argv[x];
	SetStoplist = 1;
	LastUsed = x;
      } else if (Flag.Equals("-gt0")) {
	GlobalDoctype = "";
	SetGlobalDoctype = 1;
	LastUsed = x;
      } else if (Flag.Equals("-gl0")) {
	StoplistFilename = "";
	SetStoplist = 1;
	LastUsed = x;

      } else if (Flag.Equals("-centroid")) {
        DoCentroid = 1;
        LastUsed = x;
      } else if (Flag.Equals("-syn") || (Flag.Equals("-thes"))) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No synonym file name specified after %s", Flag.c_str());
          return -1;
        }
        SynonymFileName = argv[x];
        Synonyms = 1;
        LastUsed = x;
      } else if (Flag.Equals("-debug")) {
	DebugFlag = 1;
	if (x + 1 < argc) {
	  if (isdigit(*argv[x + 1])) {
	    Skip = atoi(argv[x + 1]);
	    x++;
	  }
	}
        __Register_IB_Application(argv0, stderr, DebugFlag);
	log_init (LOG_ALL);
	LastUsed = x;
      } else if (Flag.Equals("-erase")) {
	EraseAll = 1;
	LastUsed = x;
      } else if (Flag.Equals("-dirmv")) {
        if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No directories specified after %s", Flag.c_str());
          return -1;
        }
        OldDirBase = argv[x];
        NewDirBase = argv[x];
        STRINGINDEX pos = OldDirBase.Search("=");
        if (pos == 0)
          {
	    message_log (LOG_FATAL, "Option error: Usage for %s is OldDir=NewDir", Flag.c_str()); 
            return -1;
          }
        OldDirBase.EraseAfter(pos-1);
	AddTrailingSlash(&OldDirBase);
        NewDirBase.EraseBefore(pos+1);
	AddTrailingSlash(&NewDirBase);
        dirsMv = 1;
        LastUsed = x;
     } else if (Flag.Equals("-mvdir")) {
	if (++x >= argc) {
	  message_log (LOG_FATAL, "Option error: No directories specified after %s", Flag.c_str()); 
          return -1;
        }
	OldDir = argv[x];
        NewDir = argv[x];
  	STRINGINDEX pos = OldDir.Search("=");
	if (pos == 0)
	  {
	    message_log (LOG_FATAL, "Option error: Usage for %s is OldDir=NewDir", Flag.c_str()); 
	    return -1;
	  }
	OldDir.EraseAfter(pos-1);
	AddTrailingSlash(&OldDir);
	NewDir.EraseBefore(pos+1);
	AddTrailingSlash(&NewDir);
	mvDirs = 1;
        LastUsed = x;
     } else if (Flag.Equals("-relative")) {
        if (++x >= argc)
	  RootDir = NulString;
	else
	  RootDir = argv[x];
	if (RootDir == ".")
	  RootDir = GetCwd();
	if (RootDir.GetLength() && isspace(RootDir.GetChr(1)))
	  RootDir = NulString;
        relPaths = 1;
        LastUsed = x;
      } else if (Flag.Equals("-newpaths")) {
	PathChange = 1;
	LastUsed = x;
      } else if (Flag.Equals("-v")) {
	View = 1;
	LastUsed = x;
      } else if (Flag.Equals("-mdt")) {
        DumpMdt = 1;
        LastUsed = x;
      } else if (Flag.Equals("-inx")) {
	DumpInx = 1;
	LastUsed = x;
      } else if (Flag.Equals("-vf")) {
	ViewFields = 1;
	LastUsed = x;
      } else if (Flag.Equals("-vi")) {
	ViewInfo = 1;
	LastUsed = x;
      } else if (Flag.Equals("-del")) {
	DeleteByKey = 1;
	LastUsed = x;
      } else if (Flag.Equals("-del_expired")) {
	DeleteExpired = 1;
	LastUsed = x;
      } else if (Flag.Equals("-undel")) {
	UndeleteByKey = 1;
	LastUsed = x;
      } else if (Flag.Equals("-c")) {
	Cleanup = 1;
	LastUsed = x;
      } else if (Flag.Equals("-optimize") || Flag.Equals("-optimise")) {
	Optimize = 1;
	LastUsed = x;
      } else if (Flag.Equals("-collapse")) {
	Collapse = 1;
	LastUsed = x;
      } else if (Flag.Equals ("-level")) {
        if (++x >= argc) {
	  message_log (LOG_FATAL, "Usage: No level specified after -level.");
	  return 2;
	}
	log_init((int)(strtol (argv[x], NULL, 10) & 0xFF));
	LastUsed = x;
     }

    }
    x++;
  }
  message_log (LOG_INFO, "Iutil %s (%s)", __IB_Version, __HostPlatform);
  if (DBName.IsEmpty()) {
    DBName = __IB_DefaultDbName;
    message_log (LOG_WARN, "No database name specified! Using default \"%s\"", DBName.c_str() );
  }
  x = LastUsed + 1;

  // RECLIST reclist;
  // RECORD record;
  // STRING PathName, FileName;

  STRING          S;
  INT             NumWords = argc - x;
  INT             z = x;
  for (z = 0; z < NumWords; z++) {
    S = argv[z + x];
    WordList.AddEntry(S);
  }

  // we need to prevent bad combinations of options, such as -erase and -del together

  VIDB           *vdb;
  IDB            *pdb;

  if ((vdb = new VIDB(DBName, DocTypeOptions)) == NULL)
    {
      message_log (LOG_PANIC, "Could not create VIDB!");
      return -1;
    }
  if (vdb->GetTotalDatabases() > 1)
    {
      int n = vdb->GetTotalDatabases();
      message_log (LOG_ERROR, "Usage ERROR: Virtual Collection contains %d indexes.", n);
      delete vdb;
      if (n > 1) message_log (LOG_PANIC, "Sorry, this program is designed ONLY FOR SINGLE REAL INDEXES!");
      return -1;
    }

  pdb = (IDB *)vdb->GetIDB (1); // Get the IDB
  if (pdb == NULL)
    return -1;

  if (DebugFlag) {
    pdb->SetDebugSkip(Skip);
    pdb->DebugModeOn();
  }

  if (!CacheDir.IsEmpty())
    pdb->SetCacheDir(CacheDir);
  if (!FillCacheSyntax.IsEmpty())
    {
      STRLIST list (FillCacheSyntax, ',');
      message_log (LOG_INFO, "Filling HeadlineCache for: %s", FillCacheSyntax.c_str());
      for (const STRLIST *p = list.Next(); p != &list; p = p->Next())
	{
	  STRING Syntax = p->Value();
	  if (Syntax.IsEmpty())
	    continue;
	  if (Syntax ^= "html")
	    Syntax = HtmlRecordSyntax;
	  else if (Syntax ^= "sutrs")
	    Syntax = SutrsRecordSyntax;
	  else if (Syntax ^= "usmarc")
	    Syntax = UsmarcRecordSyntax;
	  else if (Syntax ^= "xml")
	    Syntax = XmlRecordSyntax;
	  else if (Syntax ^= "sgml")
	    Syntax = SgmlRecordSyntax;
	  pdb->FillHeadlineCache(Syntax);
	}
    }
  if (Clip >= 0)
    pdb->SetDefaultDbSearchCutoff(Clip);
  if (PriorityFactor != 1.192092896E-07F)
    pdb->SetDefaultPriorityFactor(PriorityFactor);
  if (!Title.IsEmpty())
    pdb->SetTitle(Title);
  if (!Comments.IsEmpty())
    pdb->SetComments(Comments);
  if (!Copyright.IsEmpty())
    pdb->SetCopyright(Copyright);
  if (!Server.IsEmpty())
    pdb->SetServerName(Server);
  if (!Mirror.IsEmpty())
    pdb->SetMirrorBaseDirectory(Mirror);
  if (!URL.IsEmpty())
    pdb->SetHTTPServer(URL);
  if (!Pages.IsEmpty())
    pdb->SetHTTPPages(Pages);

  if (!pdb->IsDbCompatible()) {
    cout << "The specified database is not compatible with this version of Iutil." << endl;
    cout << "Please use matching versions of Iindex, Isearch, and Iutil." << endl;
    delete          vdb;
    return 0;
  }

  if (Optimize) {
    pdb->MergeIndexFiles();
  }
  if (Collapse) {
    pdb->CollapseIndexFiles();
  }
  if (DoCentroid)
    pdb->CreateCentroid();
  if (Scan) {
    STRLIST         Words;
    STRING          s;
    pdb->Scan(&Words, ScanField);
    size_t          Total = Words.GetTotalEntries();
    for (size_t i = 1; i <= Total; i++)
      printf("%s\n", Words.GetEntry(i).c_str());
  }

  if (DeleteExpired) {
      size_t    expired = pdb->DeleteExpired();
      if (expired)
	cout << expired << " records were expired and marked as deleted." << endl;
  }

  if (ViewInfo) {
    if (RecordID.IsEmpty()) {
      STRING          S;
      INT             x, y, z;
      pdb->GetDbFileStem(&S);
      cout << "Database name: " << S << endl;
      DOCTYPE_ID GlobalDoc = pdb->GetGlobalDoctype();
      if (!GlobalDoc) {
        S = "(none)";
      } else S = GlobalDoc.DocumentType();
      cout << "Global document type: " << S << endl;

      cout << "Total Number of Words: " 
	<< pdb->GetTotalWords() << " (" << pdb->GetTotalUniqueWords() << " unique to " 
	<< pdb->GetDbSisLimit() << " characters)" << endl;
      y = pdb->GetTotalRecords();
      cout << "Total number of documents: " << y << endl;
      z = 0;
      for (x = 1; x <= y; x++) {
        if (pdb->GetDocumentDeleted(x)) {
  	z++;
        }
      }
      cout << "Documents marked as deleted: " << z << endl;

    } else {
      // Show the Info for the Record
      RECORD Record;
      RESULT Result;

      if (pdb->KeyLookup(RecordID, &Result))
        {
	  pdb->GetDocumentInfo(Result.GetMdtIndex(), &Record);
	  SRCH_DATE date;
	  cout << 
	      "  Headline: " <<  pdb->Headline(Result) << endl <<
	      "  Key: " << Record.GetKey() << endl << 
              "  Path: " << Record.GetFullFileName() <<
	      "  [" << Record.GetRecordStart() << "-" << Record.GetRecordEnd() << "]" << endl <<
	      "  Type: " << Record.GetDocumentType().DocumentType() <<endl <<
	      "  Locale: " << Record.GetLocale().LocaleName() << endl;
	   if ((date = Record.GetDate()).Ok())
	      cout << " Date: " << date.RFCdate() << endl;
          if ((date = Record.GetDateCreated()).Ok())
              cout << " Created: " << date.RFCdate() << endl;
          if ((date = Record.GetDateModified()).Ok())
              cout << " Modified: " << date.RFCdate() << endl;
          if ((date = Record.GetDateExpires()).Ok())
              cout << " Expires: " << date.RFCdate() << endl;

	}
      else
	message_log (LOG_ERROR, "No such record defined by '%s'", RecordID.c_str());
    }
  }
  if (SetGlobalDoctype) {
    pdb->SetGlobalDoctype(GlobalDoctype);
    if (GlobalDoctype.DocumentType().IsEmpty()) {
      message_log(LOG_INFO, "Global document type cleared.");
    } else {
      message_log(LOG_INFO, "Global document type set to %s.", GlobalDoctype.c_str());
    }
  }
  if (SetStoplist) {
    pdb->SetGlobalStoplist(StoplistFilename);
    if (StoplistFilename == "") {
      message_log(LOG_INFO, "Global Stopwords list cleared.");
    } else {
      message_log(LOG_INFO, "Global Stopwords list set to %s.", (const char *) StoplistFilename);
    }
  }
  if (Synonyms) {
    THESAURUS MyThesaurus;
    if (MyThesaurus.Compile(SynonymFileName, DBName, true))
      message_log (LOG_INFO, "Thesaurus '%s' compiled.", SynonymFileName.c_str());
    else
      message_log (LOG_ERROR, "Compile of thesaurus '%s' failed.", SynonymFileName.c_str());
  }
  if (EraseAll) {
    cout << "Erasing database files ..." << endl;
    pdb->KillAll();
    delete          vdb;
    cout << "Database files erased." << endl;
    return 0;
  }
  if (dirsMv) {
    INT             y = pdb->GetTotalRecords();
    RECORD          Record;
    STRING          OldPath;
    int             count = 0;
    size_t          len = OldDirBase.GetLength();

    message_log (LOG_INFO, "Moving %s -> %s", OldDirBase.c_str(), NewDirBase.c_str());
    for (INT x = 1; x <= y; x++) {
        pdb->GetDocumentInfo(x, &Record);
        OldPath = Record.GetPathName();
        if (strncmp(OldPath.c_str(), OldDirBase, len) == 0)
          {
	    OldPath.EraseBefore(len+1);
            Record.SetPath(  NewDirBase+OldPath );
            pdb->SetDocumentInfo(x, Record);
            count++;
          }
    }
   message_log (LOG_INFO, "Done. Changed %d paths (%u).", count, y);
  }
  if (mvDirs) {
    INT             y = pdb->GetTotalRecords();
    RECORD          Record;
    STRING          OldPath;
    int             count = 0;


    message_log (LOG_INFO, "Moving %s -> %s", OldDir.c_str(), NewDir.c_str());
    for (INT x = 1; x <= y; x++) {
        pdb->GetDocumentInfo(x, &Record);
        Record.GetPathName(&OldPath);
	if (OldPath == OldDir)
	  {
	    Record.SetPath(NewDir);
	    pdb->SetDocumentInfo(x, Record);
	    count++;
	  }
    }
   message_log (LOG_INFO, "Done. Changed %d paths (%u).", count, y);
  }
  if (PathChange) {
    message_log(LOG_INFO, "Scanning database for file paths ...");
    INT             y = pdb->GetTotalRecords();
    if (y) {
      cerr << "Enter new path or <Return> to leave unchanged:" << endl;
      RECORD          Record;
      PCHR            p;
      STRING          OldPath, NewPath;
      STRLIST         PathList;
      CHR             s[512];
      for (INT x = 1; x <= y; x++) {
	pdb->GetDocumentInfo(x, &Record);
	Record.GetPathName(&OldPath);
	p = OldPath.NewCString();
	PathList.GetValue(p, &NewPath);
	delete[] p;
	if (NewPath == "") {
	  cerr << "Path=[" << OldPath << "]" << endl;
	  cerr << "    > ";
	  // cin.getline(s, 512, '\n');
	  char *tp = fgets(s, sizeof(s), stdin);
	  if (tp == NULL)
	    s[0] = '\0';

	  if (s[0] == '\0') {
	    NewPath = OldPath;
	  } else {
	    NewPath = s;
	  }
	  Record.SetPath(NewPath.Trim(true));
	  OldPath += "=";
	  OldPath += NewPath;
	  PathList.AddEntry(OldPath);
	} else {
	  Record.SetPath(NewPath);
	}
	pdb->SetDocumentInfo(x, Record);
      }
      cerr  << "Done." << endl;
    }
  }
  if (relPaths) {
    INT             y = pdb->GetTotalRecords();
    RECORD          Record;
    PATHNAME        Pathname;
    STRING          path;

    if (!RootDir.IsEmpty())
      pdb->SetWorkingDirectory(RootDir);
    else
      RootDir = pdb->GetWorkingDirectory();

    if (!IsRootDirectory(RootDir)) {
      pdb->setUseRelativePaths(true);
      message_log (LOG_INFO, "Relativizing around '%s' (%d records)", RootDir.c_str(), y);
      for (INT x = 1; x <= y; x++) {
        pdb->GetDocumentInfo(x, &Record);
        pdb->SetDocumentInfo(x, Record);
      }
      message_log (LOG_INFO, "Done.");
    }
  }

  if (DeleteByKey) {
    message_log(LOG_INFO, "Marking documents as deleted ...");
    INT             x, z;
    INT             y = 0;
    STRING          S;
    z = WordList.GetTotalEntries();
    for (x = 1; x <= z; x++) {
      WordList.GetEntry(x, &S);
      y += pdb->DeleteByKey(S);
    }
    message_log(LOG_INFO, "%d document(s) marked as deleted.", y);
  }
  if (UndeleteByKey) {
    message_log(LOG_INFO, "Removing deletion mark from documents ...");
    INT             x, z;
    INT             y = 0;
    STRING          S;
    z = WordList.GetTotalEntries();
    for (x = 1; x <= z; x++) {
      WordList.GetEntry(x, &S);
      y += pdb->UndeleteByKey(S);
    }
    message_log(LOG_INFO, "Deletion mark removed for %d document(s).", y);
  }
  if (Cleanup) {
    message_log(LOG_INFO, "Cleaning up database (removing deleted documents) ...");
    INT             x = pdb->CleanupDb();
    message_log(LOG_INFO, "%d document(s) were removed.", x);
  }

  if (ViewFields) {
    DFDT            Dfdt;
    DFD             Dfd;
    FIELDTYPE       fieldtype;
    STRING          S;

    pdb->GetDfdt(&Dfdt);
    INT             y = Dfdt.GetTotalEntries();
    STRING          message;

    if (y >= 1)
      message = "The following fields are defined in this database:";
    else
      message = "No fields in this database";
    for (INT x = 1; x <= y; x++) {
      Dfdt.GetEntry(x, &Dfd);
      Dfd.GetFieldName(&S);
      message << " '" << S << "'";
      fieldtype = Dfd.GetFieldType();

      if (!fieldtype.IsText())
	message << "::" << fieldtype.c_str();
    }
    cout << message << endl;
  }
  if (View) {
    RECORD          Record;
    const size_t    y = pdb->GetTotalRecords();
    DOCTYPE_ID      id;
    if (y < 1)
      cout << y << " Total Records (!!!)" << endl;
    for (size_t x = 1; x <= y; x++) {
      if (x == 1)
	cout << "     \tLocale\tDocType: [Key] (Start - End) TTL File (* indicates deleted record)" << endl;
      pdb->GetDocumentInfo(x, &Record);
      if (!Record.IsBadRecord())
	{
	  int ttl;
	  cout << "[" << x << "]\t" 
		<< Record.GetLocale().LocaleName() << "\t"
		<< ((id = Record.GetDocumentType()).IsDefined() ? id.c_str() : "(none)" ) 
		<< ": [" << Record.GetKey() << "] ("
		<< Record.GetRecordStart() << " - " << Record.GetRecordEnd() << ") ";
	  if (ttl = Record.TTL() >= 0)
	    cout << ttl << " ";
	  else 
	    cout << "INF ";
	  cout << Record.GetFullFileName();
	  if (pdb->GetDocumentDeleted(x)) cout << " *";
	  cout << endl;
	}
    }
  }
  if (DumpMdt)
    {
      MDT *MainMdtPtr = pdb->GetMainMdt();
      if (MainMdtPtr)
	MainMdtPtr->Dump(0, cout);
    }
  if (DumpInx)
    {
      INDEX *MainIndexPtr = pdb->GetMainIndex();
      if (MainIndexPtr)
	MainIndexPtr->Dump (Skip);
    }
  message_log (LOG_INFO, "Done.");
  delete          vdb; // TO FIX A TEMP BUG...!!!!!!
  return 0;
}
