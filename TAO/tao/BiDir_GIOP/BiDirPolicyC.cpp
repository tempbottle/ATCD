// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be\be_codegen.cpp:323


#include "BiDirGIOP.h"
#include "tao/CDR.h"
#include "ace/OS_NS_string.h"

#if defined (__BORLANDC__)
#pragma option -w-rvl -w-rch -w-ccc -w-aus -w-sig
#endif /* __BORLANDC__ */

#if !defined (__ACE_INLINE__)
#include "BiDirPolicyC.i"
#endif /* !defined INLINE */

// TAO_IDL - Generated from
// be\be_visitor_arg_traits.cpp:64

// Arg traits specializations.
namespace TAO
{
}


// TAO_IDL - Generated from
// be\be_visitor_interface/interface_cs.cpp:60

// Traits specializations for BiDirPolicy::BidirectionalPolicy.

ACE_TEMPLATE_CLASS_MEMBER_SPECIALIZATION
BiDirPolicy::BidirectionalPolicy_ptr
TAO::Objref_Traits<BiDirPolicy::BidirectionalPolicy>::tao_duplicate (
    BiDirPolicy::BidirectionalPolicy_ptr p
  )
{
  return BiDirPolicy::BidirectionalPolicy::_duplicate (p);
}

ACE_TEMPLATE_CLASS_MEMBER_SPECIALIZATION
void
TAO::Objref_Traits<BiDirPolicy::BidirectionalPolicy>::tao_release (
    BiDirPolicy::BidirectionalPolicy_ptr p
  )
{
  CORBA::release (p);
}

ACE_TEMPLATE_CLASS_MEMBER_SPECIALIZATION
BiDirPolicy::BidirectionalPolicy_ptr
TAO::Objref_Traits<BiDirPolicy::BidirectionalPolicy>::tao_nil (void)
{
  return BiDirPolicy::BidirectionalPolicy::_nil ();
}

ACE_TEMPLATE_CLASS_MEMBER_SPECIALIZATION
CORBA::Boolean
TAO::Objref_Traits<BiDirPolicy::BidirectionalPolicy>::tao_marshal (
    BiDirPolicy::BidirectionalPolicy_ptr p,
    TAO_OutputCDR & cdr
  )
{
  return CORBA::Object::marshal (p, cdr);
}

// Function pointer for collocation factory initialization.
TAO::Collocation_Proxy_Broker * 
(*BiDirPolicy__TAO_BidirectionalPolicy_Proxy_Broker_Factory_function_pointer) (
    CORBA::Object_ptr obj
  ) = 0;

BiDirPolicy::BidirectionalPolicy::BidirectionalPolicy (void)
{}

BiDirPolicy::BidirectionalPolicy::~BidirectionalPolicy (void)
{}

BiDirPolicy::BidirectionalPolicy_ptr
BiDirPolicy::BidirectionalPolicy::_narrow (
    CORBA::Object_ptr _tao_objref
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  if (CORBA::is_nil (_tao_objref))
    {
      return BidirectionalPolicy::_nil ();
    }
  
  BidirectionalPolicy_ptr proxy =
    dynamic_cast<BidirectionalPolicy_ptr> (_tao_objref);
  
  return BidirectionalPolicy::_duplicate (proxy);
}

BiDirPolicy::BidirectionalPolicy_ptr
BiDirPolicy::BidirectionalPolicy::_unchecked_narrow (
    CORBA::Object_ptr _tao_objref
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  if (CORBA::is_nil (_tao_objref))
    {
      return BidirectionalPolicy::_nil ();
    }
  
  BidirectionalPolicy_ptr proxy =
    dynamic_cast<BidirectionalPolicy_ptr> (_tao_objref);
  
  return BidirectionalPolicy::_duplicate (proxy);
}

BiDirPolicy::BidirectionalPolicy_ptr
BiDirPolicy::BidirectionalPolicy::_duplicate (BidirectionalPolicy_ptr obj)
{
  if (! CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

CORBA::Boolean
BiDirPolicy::BidirectionalPolicy::_is_a (
    const char *value
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  if (
      !ACE_OS::strcmp (
          (char *)value,
          "IDL:omg.org/CORBA/Policy:1.0"
        ) ||
      !ACE_OS::strcmp (
          (char *)value,
          "IDL:omg.org/BiDirPolicy/BidirectionalPolicy:1.0"
        ) ||
      !ACE_OS::strcmp (
          (char *)value,
          "IDL:omg.org/CORBA/LocalObject:1.0"
        ) ||
      !ACE_OS::strcmp (
          (char *)value,
          "IDL:omg.org/CORBA/Object:1.0"
        )
     )
    {
      return 1; // success using local knowledge
    }
  else
    {
      return 0;
    }
}

const char* BiDirPolicy::BidirectionalPolicy::_interface_repository_id (void) const
{
  return "IDL:omg.org/BiDirPolicy/BidirectionalPolicy:1.0";
}

CORBA::Boolean
BiDirPolicy::BidirectionalPolicy::marshal (TAO_OutputCDR &)
{
  return 0;
}

// TAO_IDL - Generated from
// be\be_visitor_root/root.cpp:1628

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

  template class
    TAO::Objref_Traits<
        BiDirPolicy::BidirectionalPolicy
      >;

  template class
    TAO_Objref_Var_T<
        BiDirPolicy::BidirectionalPolicy
      >;
  
  template class
    TAO_Objref_Out_T<
        BiDirPolicy::BidirectionalPolicy
      >;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

# pragma instantiate \
    TAO::Objref_Traits< \
        BiDirPolicy::BidirectionalPolicy \
      >

# pragma instantiate \
    TAO_Objref_Var_T< \
        BiDirPolicy::BidirectionalPolicy
      >
  
# pragma instantiate \
    TAO_Objref_Out_T< \
        BiDirPolicy::BidirectionalPolicy
      >

#endif /* !ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */ 

