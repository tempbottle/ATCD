/* $Id$

 * ============================================================================
 *
 * = LIBRARY
 *    pace
 *
 * = FILENAME
 *    pace/unistd.h
 *
 * = AUTHOR
 *    Luther Baker
 *
 * ============================================================================ */

#ifndef PACE_UNISTD_H_INDIRECT
#define PACE_UNISTD_H_INDIRECT

#if defined (PACE_HAS_POSIX)
# include "pace/posix/unistd.h"
#elif defined (PACE_VXWORKS)
# include "pace/vxworks/unistd.h"
#elif defined (PACE_WIN32)
# include "pace/win32/unistd.h"
#endif

#endif /* PACE_UNISTD_H_INDIRECT */
