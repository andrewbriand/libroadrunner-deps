using System;
using System.Runtime.InteropServices;
 
//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.12
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace libsbmlcs {

 using System;
 using System.Runtime.InteropServices;

/** 
 * @sbmlpackage{core}
 *
@htmlinclude pkg-marker-core.html 
 * @internal
 */

public class MathFilter : ElementFilter {
	private HandleRef swigCPtr;
	
	internal MathFilter(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.MathFilter_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.MathFilterUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(MathFilter obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (MathFilter obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~MathFilter() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_MathFilter(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public MathFilter() : this(libsbmlPINVOKE.new_MathFilter(), true) {
    SwigDirectorConnect();
  }

  
/**
   * Predicate to test elements.
   *
   * This is the central predicate of the ElementFilter class.  In subclasses
   * of ElementFilter, callers should implement this method such that it
   * returns @c true for @p element arguments that are 'desirable' and
   * @c false for those that are 'undesirable' in whatever filtering context the
   * ElementFilter subclass is designed to be used.
   *
   * @param element the element to be tested.
   *
   * @return @c true if the @p element is desirable or should be kept,
   * @c false otherwise.
   */ public virtual
 bool filter(SBase element) {
    bool ret = (SwigDerivedClassHasMethod("filter", swigMethodTypes0) ? libsbmlPINVOKE.MathFilter_filterSwigExplicitMathFilter(swigCPtr, SBase.getCPtr(element)) : libsbmlPINVOKE.MathFilter_filter(swigCPtr, SBase.getCPtr(element)));
    return ret;
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("filter", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateMathFilter_0(SwigDirectorfilter);
    libsbmlPINVOKE.MathFilter_director_connect(swigCPtr, swigDelegate0);
  }

  private bool SwigDerivedClassHasMethod(string methodName, global::System.Type[] methodTypes) {
    global::System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, global::System.Reflection.BindingFlags.Public | global::System.Reflection.BindingFlags.NonPublic | global::System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(MathFilter));
    return hasDerivedMethod;
  }

  private bool SwigDirectorfilter(global::System.IntPtr element) {
    return filter((element == global::System.IntPtr.Zero) ? null : new SBase(element, false));
  }

  public delegate bool SwigDelegateMathFilter_0(global::System.IntPtr element);

  private SwigDelegateMathFilter_0 swigDelegate0;

  private static global::System.Type[] swigMethodTypes0 = new global::System.Type[] { typeof(SBase) };
}

}
