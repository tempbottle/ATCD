// -*- C++ -*-

//=============================================================================
/**
 *  @file   OS_NS_sys_select.h
 *
 *  $Id$
 *
 *  @author Douglas C. Schmidt <schmidt@cs.wustl.edu>
 *  @author Jesper S. M|ller<stophph@diku.dk>
 *  @author and a cast of thousands...
 *
 *  Originally in OS.h.
 */
//=============================================================================

#ifndef ACE_OS_NS_SYS_SELECT_H
# define ACE_OS_NS_SYS_SELECT_H

# include /**/ "ace/pre.h"

# include "ace/config-all.h"

# if !defined (ACE_LACKS_PRAGMA_ONCE)
#  pragma once
# endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/os_include/sys/os_select.h"

class ACE_Time_Value;

namespace ACE_OS {

  // Should be moved to cpp or inl.
  int select (int width,
              fd_set *rfds,
              fd_set *wfds = 0,
              fd_set *efds = 0,
              const ACE_Time_Value *tv = 0);
  int select (int width,
              fd_set *rfds,
              fd_set *wfds,
              fd_set *efds,
              const ACE_Time_Value &tv);

} /* namespace ACE_OS */

# if defined (ACE_HAS_INLINED_OSCALLS)
#   if defined (ACE_INLINE)
#     undef ACE_INLINE
#   endif /* ACE_INLINE */
#   define ACE_INLINE inline
#   include "ace/OS_NS_sys_select.inl"
# endif /* ACE_HAS_INLINED_OSCALLS */

# include /**/ "ace/post.h"
#endif /* ACE_OS_NS_SYS_SELECT_H */
