/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.36
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class ArraySTRING {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ArraySTRING(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ArraySTRING obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      IBJNI.delete_ArraySTRING(swigCPtr);
    }
    swigCPtr = 0;
  }

  public ArraySTRING() {
    this(IBJNI.new_ArraySTRING__SWIG_0(), true);
  }

  public ArraySTRING(int size) {
    this(IBJNI.new_ArraySTRING__SWIG_1(size), true);
  }

  public ArraySTRING(ArraySTRING OtherArraySTRING) {
    this(IBJNI.new_ArraySTRING__SWIG_2(ArraySTRING.getCPtr(OtherArraySTRING), OtherArraySTRING), true);
  }

  public ArraySTRING(STRLIST list) {
    this(IBJNI.new_ArraySTRING__SWIG_3(STRLIST.getCPtr(list), list), true);
  }

  public void Empty() {
    IBJNI.ArraySTRING_Empty(swigCPtr, this);
  }

  public void Clear() {
    IBJNI.ArraySTRING_Clear(swigCPtr, this);
  }

  public long Count() {
    return IBJNI.ArraySTRING_Count(swigCPtr, this);
  }

  public boolean IsEmpty() {
    return IBJNI.ArraySTRING_IsEmpty(swigCPtr, this);
  }

  public String Item(long nIndex) {
    return IBJNI.ArraySTRING_Item(swigCPtr, this, nIndex);
  }

  public String GetEntry(long Index) {
    return IBJNI.ArraySTRING_GetEntry(swigCPtr, this, Index);
  }

  public String __getitem__(int i) {
    return IBJNI.ArraySTRING___getitem__(swigCPtr, this, i);
  }

  public void SetEntry(long Index, String src) {
    IBJNI.ArraySTRING_SetEntry(swigCPtr, this, Index, src);
  }

  public void Add(String str) {
    IBJNI.ArraySTRING_Add(swigCPtr, this, str);
  }

  public void Insert(String str, long uiIndex) {
    IBJNI.ArraySTRING_Insert(swigCPtr, this, str, uiIndex);
  }

  public void Replace(String src, long nIndex) {
    IBJNI.ArraySTRING_Replace(swigCPtr, this, src, nIndex);
  }

  public void Remove(long nIndex) {
    IBJNI.ArraySTRING_Remove(swigCPtr, this, nIndex);
  }

  public ArraySTRING getself() {
    return new ArraySTRING(IBJNI.ArraySTRING_getself(swigCPtr, this), false);
  }

  public String Join(String seperator) {
    return IBJNI.ArraySTRING_Join(swigCPtr, this, seperator);
  }

}