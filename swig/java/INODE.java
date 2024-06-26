/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.36
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class INODE {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected INODE(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(INODE obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      IBJNI.delete_INODE(swigCPtr);
    }
    swigCPtr = 0;
  }

  public INODE() {
    this(IBJNI.new_INODE__SWIG_0(), true);
  }

  public INODE(String Path) {
    this(IBJNI.new_INODE__SWIG_1(Path), true);
  }

  public void Clear() {
    IBJNI.INODE_Clear(swigCPtr, this);
  }

  public SWIGTYPE_p_GDT_BOOLEAN Set(String Path) {
    return new SWIGTYPE_p_GDT_BOOLEAN(IBJNI.INODE_Set__SWIG_0(swigCPtr, this, Path), true);
  }

  public SWIGTYPE_p_GDT_BOOLEAN Set(SWIGTYPE_p_FILE fp) {
    return new SWIGTYPE_p_GDT_BOOLEAN(IBJNI.INODE_Set__SWIG_1(swigCPtr, this, SWIGTYPE_p_FILE.getCPtr(fp)), true);
  }

  public SWIGTYPE_p_GDT_BOOLEAN Set(int fd) {
    return new SWIGTYPE_p_GDT_BOOLEAN(IBJNI.INODE_Set__SWIG_2(swigCPtr, this, fd), true);
  }

  public String Key() {
    return IBJNI.INODE_Key(swigCPtr, this);
  }

  public boolean isLinked() {
    return IBJNI.INODE_isLinked(swigCPtr, this);
  }

  public boolean isDangling() {
    return IBJNI.INODE_isDangling(swigCPtr, this);
  }

  public int inode() {
    return IBJNI.INODE_inode(swigCPtr, this);
  }

  public int device() {
    return IBJNI.INODE_device(swigCPtr, this);
  }

}
