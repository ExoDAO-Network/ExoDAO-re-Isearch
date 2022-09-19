/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.36
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class RECORD {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected RECORD(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(RECORD obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      IBJNI.delete_RECORD(swigCPtr);
    }
    swigCPtr = 0;
  }

  public RECORD() {
    this(IBJNI.new_RECORD__SWIG_0(), true);
  }

  public RECORD(String Fullpath) {
    this(IBJNI.new_RECORD__SWIG_1(Fullpath), true);
  }

  public RECORD(RECORD OtherRecord) {
    this(IBJNI.new_RECORD__SWIG_2(RECORD.getCPtr(OtherRecord), OtherRecord), true);
  }

  public void SetKey(String NewKey) {
    IBJNI.RECORD_SetKey(swigCPtr, this, NewKey);
  }

  public String GetKey() {
    return IBJNI.RECORD_GetKey(swigCPtr, this);
  }

  public void SetPath(String NewPathName) {
    IBJNI.RECORD_SetPath(swigCPtr, this, NewPathName);
  }

  public String GetPath() {
    return IBJNI.RECORD_GetPath(swigCPtr, this);
  }

  public void SetFileName(String NewName) {
    IBJNI.RECORD_SetFileName(swigCPtr, this, NewName);
  }

  public String GetFileName() {
    return IBJNI.RECORD_GetFileName(swigCPtr, this);
  }

  public void SetFullFileName(String FullName) {
    IBJNI.RECORD_SetFullFileName(swigCPtr, this, FullName);
  }

  public String GetFullFileName() {
    return IBJNI.RECORD_GetFullFileName(swigCPtr, this);
  }

  public void SetRecordStart(long NewStart) {
    IBJNI.RECORD_SetRecordStart(swigCPtr, this, NewStart);
  }

  public long GetRecordStart() {
    return IBJNI.RECORD_GetRecordStart(swigCPtr, this);
  }

  public void SetRecordEnd(long NewEnd) {
    IBJNI.RECORD_SetRecordEnd(swigCPtr, this, NewEnd);
  }

  public long GetRecordEnd() {
    return IBJNI.RECORD_GetRecordEnd(swigCPtr, this);
  }

  public void SetDocumentType(DOCTYPE_ID NewType) {
    IBJNI.RECORD_SetDocumentType(swigCPtr, this, DOCTYPE_ID.getCPtr(NewType), NewType);
  }

  public DOCTYPE_ID GetDocumentType() {
    return new DOCTYPE_ID(IBJNI.RECORD_GetDocumentType(swigCPtr, this), true);
  }

  public LOCALE GetLocale() {
    return new LOCALE(IBJNI.RECORD_GetLocale(swigCPtr, this), true);
  }

  public void SetLocale(LOCALE NewLocale) {
    IBJNI.RECORD_SetLocale(swigCPtr, this, LOCALE.getCPtr(NewLocale), NewLocale);
  }

  public void SetLanguage(String Language) {
    IBJNI.RECORD_SetLanguage(swigCPtr, this, Language);
  }

  public void SetCharset(String Charset) {
    IBJNI.RECORD_SetCharset(swigCPtr, this, Charset);
  }

  public SRCH_DATE GetDate() {
    return new SRCH_DATE(IBJNI.RECORD_GetDate(swigCPtr, this), true);
  }

  public void SetDate(SRCH_DATE NewDate) {
    IBJNI.RECORD_SetDate(swigCPtr, this, SRCH_DATE.getCPtr(NewDate), NewDate);
  }

  public void SetDateModified(SRCH_DATE NewDate) {
    IBJNI.RECORD_SetDateModified(swigCPtr, this, SRCH_DATE.getCPtr(NewDate), NewDate);
  }

  public SRCH_DATE GetDateModified() {
    return new SRCH_DATE(IBJNI.RECORD_GetDateModified(swigCPtr, this), true);
  }

  public void SetDateCreated(SRCH_DATE NewDate) {
    IBJNI.RECORD_SetDateCreated(swigCPtr, this, SRCH_DATE.getCPtr(NewDate), NewDate);
  }

  public SRCH_DATE GetDateCreated() {
    return new SRCH_DATE(IBJNI.RECORD_GetDateCreated(swigCPtr, this), true);
  }

  public int GetPriority() {
    return IBJNI.RECORD_GetPriority(swigCPtr, this);
  }

  public void SetPriority(int arg0) {
    IBJNI.RECORD_SetPriority(swigCPtr, this, arg0);
  }

  public int GetCategory() {
    return IBJNI.RECORD_GetCategory(swigCPtr, this);
  }

  public void SetCategory(int newCategory) {
    IBJNI.RECORD_SetCategory(swigCPtr, this, newCategory);
  }

  public int __len__() {
    return IBJNI.RECORD___len__(swigCPtr, this);
  }

  public void SetDateExpires(SRCH_DATE NewDate) {
    IBJNI.RECORD_SetDateExpires(swigCPtr, this, SRCH_DATE.getCPtr(NewDate), NewDate);
  }

  public SRCH_DATE GetDateExpires() {
    return new SRCH_DATE(IBJNI.RECORD_GetDateExpires(swigCPtr, this), true);
  }

  public int TTL() {
    return IBJNI.RECORD_TTL__SWIG_0(swigCPtr, this);
  }

  public int TTL(SRCH_DATE Now) {
    return IBJNI.RECORD_TTL__SWIG_1(swigCPtr, this, SRCH_DATE.getCPtr(Now), Now);
  }

}
