/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.45 from the
 * contents of Syslog.xs. Do not edit this file, edit Syslog.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "Syslog.xs"
/*
 * Syslog.xs
 * 
 * XS wrapper for the syslog(3) facility.
 * 
 */

#if defined(_WIN32)
#  include <windows.h>
#endif

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#ifdef USE_PPPORT_H
#  include "ppport.h"
#endif

#ifndef HAVE_SYSLOG
#define HAVE_SYSLOG 1
#endif

#if defined(_WIN32) && !defined(__CYGWIN__)
#  undef HAVE_SYSLOG
#  include "fallback/syslog.h"
#else
#  if defined(I_SYSLOG) || PATCHLEVEL < 6
#    include <syslog.h>
#  else
#    undef HAVE_SYSLOG
#    include "fallback/syslog.h"
#  endif
#endif

static SV *ident_svptr;


#ifndef LOG_FAC
#define LOG_FACMASK     0x03f8
#define LOG_FAC(p)      (((p) & LOG_FACMASK) >> 3)
#endif

#ifndef LOG_PRIMASK
#define LOG_PRIMASK     0x07
#endif

#ifndef	LOG_PRI
#define	LOG_PRI(p)	((p) & LOG_PRIMASK)
#endif

#ifndef	LOG_MAKEPRI
#define	LOG_MAKEPRI(fac, pri)	(((fac) << 3) | (pri))
#endif

#ifndef LOG_MASK
#define	LOG_MASK(pri)	(1 << (pri))
#endif

#ifndef LOG_UPTO
#define	LOG_UPTO(pri)	((1 << ((pri)+1)) - 1)
#endif

#include "const-c.inc"


#line 76 "Syslog.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef dVAR
#  define dVAR		dNOOP
#endif


/* This stuff is not part of the API! You have been warned. */
#ifndef PERL_VERSION_DECIMAL
#  define PERL_VERSION_DECIMAL(r,v,s) (r*1000000 + v*1000 + s)
#endif
#ifndef PERL_DECIMAL_VERSION
#  define PERL_DECIMAL_VERSION \
	  PERL_VERSION_DECIMAL(PERL_REVISION,PERL_VERSION,PERL_SUBVERSION)
#endif
#ifndef PERL_VERSION_GE
#  define PERL_VERSION_GE(r,v,s) \
	  (PERL_DECIMAL_VERSION >= PERL_VERSION_DECIMAL(r,v,s))
#endif
#ifndef PERL_VERSION_LE
#  define PERL_VERSION_LE(r,v,s) \
	  (PERL_DECIMAL_VERSION <= PERL_VERSION_DECIMAL(r,v,s))
#endif

/* XS_INTERNAL is the explicit static-linkage variant of the default
 * XS macro.
 *
 * XS_EXTERNAL is the same as XS_INTERNAL except it does not include
 * "STATIC", ie. it exports XSUB symbols. You probably don't want that
 * for anything but the BOOT XSUB.
 *
 * See XSUB.h in core!
 */


/* TODO: This might be compatible further back than 5.10.0. */
#if PERL_VERSION_GE(5, 10, 0) && PERL_VERSION_LE(5, 15, 1)
#  undef XS_EXTERNAL
#  undef XS_INTERNAL
#  if defined(__CYGWIN__) && defined(USE_DYNAMIC_LOADING)
#    define XS_EXTERNAL(name) __declspec(dllexport) XSPROTO(name)
#    define XS_INTERNAL(name) STATIC XSPROTO(name)
#  endif
#  if defined(__SYMBIAN32__)
#    define XS_EXTERNAL(name) EXPORT_C XSPROTO(name)
#    define XS_INTERNAL(name) EXPORT_C STATIC XSPROTO(name)
#  endif
#  ifndef XS_EXTERNAL
#    if defined(HASATTRIBUTE_UNUSED) && !defined(__cplusplus)
#      define XS_EXTERNAL(name) void name(pTHX_ CV* cv __attribute__unused__)
#      define XS_INTERNAL(name) STATIC void name(pTHX_ CV* cv __attribute__unused__)
#    else
#      ifdef __cplusplus
#        define XS_EXTERNAL(name) extern "C" XSPROTO(name)
#        define XS_INTERNAL(name) static XSPROTO(name)
#      else
#        define XS_EXTERNAL(name) XSPROTO(name)
#        define XS_INTERNAL(name) STATIC XSPROTO(name)
#      endif
#    endif
#  endif
#endif

/* perl >= 5.10.0 && perl <= 5.15.1 */


/* The XS_EXTERNAL macro is used for functions that must not be static
 * like the boot XSUB of a module. If perl didn't have an XS_EXTERNAL
 * macro defined, the best we can do is assume XS is the same.
 * Dito for XS_INTERNAL.
 */
#ifndef XS_EXTERNAL
#  define XS_EXTERNAL(name) XS(name)
#endif
#ifndef XS_INTERNAL
#  define XS_INTERNAL(name) XS(name)
#endif

/* Now, finally, after all this mess, we want an ExtUtils::ParseXS
 * internal macro that we're free to redefine for varying linkage due
 * to the EXPORT_XSUB_SYMBOLS XS keyword. This is internal, use
 * XS_EXTERNAL(name) or XS_INTERNAL(name) in your code if you need to!
 */

#undef XS_EUPXS
#if defined(PERL_EUPXS_ALWAYS_EXPORT)
#  define XS_EUPXS(name) XS_EXTERNAL(name)
#else
   /* default to internal */
#  define XS_EUPXS(name) XS_INTERNAL(name)
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
	    Perl_croak_nocontext("Usage: %s::%s(%s)", hvname, gvname, params);
        else
	    Perl_croak_nocontext("Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
	Perl_croak_nocontext("Usage: CODE(0x%" UVxf ")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#define croak_xs_usage        S_croak_xs_usage

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#if PERL_VERSION_LE(5, 21, 5)
#  define newXS_deffile(a,b) Perl_newXS(aTHX_ a,b,file)
#else
#  define newXS_deffile(a,b) Perl_newXS_deffile(aTHX_ a,b)
#endif

#line 220 "Syslog.c"

/* INCLUDE:  Including 'const-xs.inc' from 'Syslog.xs' */


XS_EUPXS(XS_Sys__Syslog_constant); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_constant)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "sv");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	sv = ST(0)
;
#line 284 "./const-xs.inc"
#ifndef SYMBIAN
	/* It's not obvious how to calculate this at C pre-processor time.
	   However, any compiler optimiser worth its salt should be able to
	   remove the dead code, and hopefully the now-obviously-unused static
	   function too.  */
	HV *constant_missing = (C_ARRAY_LENGTH(values_for_notfound) > 1)
	    ? get_missing_hash(aTHX) : NULL;
	if ((C_ARRAY_LENGTH(values_for_notfound) > 1)
	    ? hv_exists_ent(constant_missing, sv, 0) : 0) {
	    sv = newSVpvf("Your vendor has not defined Sys::Syslog macro %" SVf
			  ", used", sv);
	} else
#endif
	{
	    sv = newSVpvf("%" SVf " is not a valid Sys::Syslog macro",
			  sv);
	}
	PUSHs(sv_2mortal(sv));
#line 255 "Syslog.c"
	PUTBACK;
	return;
    }
}


/* INCLUDE: Returning to 'Syslog.xs' from 'const-xs.inc' */


XS_EUPXS(XS_Sys__Syslog_LOG_FAC); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_LOG_FAC)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "p");
    {
	int	p = (int)SvIV(ST(0))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = LOG_FAC(p);
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sys__Syslog_LOG_PRI); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_LOG_PRI)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "p");
    {
	int	p = (int)SvIV(ST(0))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = LOG_PRI(p);
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sys__Syslog_LOG_MAKEPRI); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_LOG_MAKEPRI)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "fac, pri");
    {
	int	fac = (int)SvIV(ST(0))
;
	int	pri = (int)SvIV(ST(1))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = LOG_MAKEPRI(fac, pri);
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sys__Syslog_LOG_MASK); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_LOG_MASK)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "pri");
    {
	int	pri = (int)SvIV(ST(0))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = LOG_MASK(pri);
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sys__Syslog_LOG_UPTO); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_LOG_UPTO)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "pri");
    {
	int	pri = (int)SvIV(ST(0))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = LOG_UPTO(pri);
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}

#ifdef HAVE_SYSLOG
#define XSubPPtmpAAAA 1


XS_EUPXS(XS_Sys__Syslog_openlog_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_openlog_xs)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "ident, option, facility");
    {
	SV*	ident = ST(0)
;
	int	option = (int)SvIV(ST(1))
;
	int	facility = (int)SvIV(ST(2))
;
#line 105 "Syslog.xs"
        STRLEN len;
        char*  ident_pv;
#line 386 "Syslog.c"
#line 108 "Syslog.xs"
        ident_svptr = newSVsv(ident);
        ident_pv    = SvPV(ident_svptr, len);
        openlog(ident_pv, option, facility);
#line 391 "Syslog.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_Sys__Syslog_syslog_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_syslog_xs)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "priority, message");
    {
	int	priority = (int)SvIV(ST(0))
;
	const char *	message = (const char *)SvPV_nolen(ST(1))
;
#line 118 "Syslog.xs"
        syslog(priority, "%s", message);
#line 410 "Syslog.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_Sys__Syslog_setlogmask_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_setlogmask_xs)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "mask");
    {
	int	mask = (int)SvIV(ST(0))
;
	int	RETVAL;
	dXSTARG;
#line 125 "Syslog.xs"
        RETVAL = setlogmask(mask);
#line 429 "Syslog.c"
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sys__Syslog_closelog_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_closelog_xs)
{
    dVAR; dXSARGS;
    if (items != 0)
       croak_xs_usage(cv,  "");
    {
#line 132 "Syslog.xs"
        U32 refcnt;
#line 446 "Syslog.c"
#line 134 "Syslog.xs"
        if (!ident_svptr)
            return;
        closelog();
        refcnt = SvREFCNT(ident_svptr);
        if (refcnt) {
            SvREFCNT_dec(ident_svptr);
            if (refcnt == 1)
                ident_svptr = NULL;
        }
#line 457 "Syslog.c"
    }
    XSRETURN_EMPTY;
}

#else  /* HAVE_SYSLOG */
#define XSubPPtmpAAAB 1


XS_EUPXS(XS_Sys__Syslog_openlog_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_openlog_xs)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "ident, option, facility");
    {
	SV*	ident = ST(0)
;
	int	option = (int)SvIV(ST(1))
;
	int	facility = (int)SvIV(ST(2))
;
#line 152 "Syslog.xs"
#line 480 "Syslog.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_Sys__Syslog_syslog_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_syslog_xs)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "priority, message");
    {
	int	priority = (int)SvIV(ST(0))
;
	const char *	message = (const char *)SvPV_nolen(ST(1))
;
#line 159 "Syslog.xs"
#line 498 "Syslog.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_Sys__Syslog_setlogmask_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_setlogmask_xs)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "mask");
    {
	int	mask = (int)SvIV(ST(0))
;
	int	RETVAL;
	dXSTARG;
#line 165 "Syslog.xs"
#line 516 "Syslog.c"
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Sys__Syslog_closelog_xs); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Sys__Syslog_closelog_xs)
{
    dVAR; dXSARGS;
    if (items != 0)
       croak_xs_usage(cv,  "");
    {
#line 169 "Syslog.xs"
#line 530 "Syslog.c"
    }
    XSRETURN_EMPTY;
}

#endif /* HAVE_SYSLOG */
#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_Sys__Syslog); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_Sys__Syslog)
{
#if PERL_VERSION_LE(5, 21, 5)
    dVAR; dXSARGS;
#else
    dVAR; dXSBOOTARGSXSAPIVERCHK;
#endif
#if PERL_VERSION_LE(5, 8, 999) /* PERL_VERSION_LT is 5.33+ */
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(file);

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
#if PERL_VERSION_LE(5, 21, 5)
    XS_VERSION_BOOTCHECK;
#  ifdef XS_APIVERSION_BOOTCHECK
    XS_APIVERSION_BOOTCHECK;
#  endif
#endif

        newXS_deffile("Sys::Syslog::constant", XS_Sys__Syslog_constant);
        newXS_deffile("Sys::Syslog::LOG_FAC", XS_Sys__Syslog_LOG_FAC);
        newXS_deffile("Sys::Syslog::LOG_PRI", XS_Sys__Syslog_LOG_PRI);
        newXS_deffile("Sys::Syslog::LOG_MAKEPRI", XS_Sys__Syslog_LOG_MAKEPRI);
        newXS_deffile("Sys::Syslog::LOG_MASK", XS_Sys__Syslog_LOG_MASK);
        newXS_deffile("Sys::Syslog::LOG_UPTO", XS_Sys__Syslog_LOG_UPTO);
#if XSubPPtmpAAAA
        newXS_deffile("Sys::Syslog::openlog_xs", XS_Sys__Syslog_openlog_xs);
        newXS_deffile("Sys::Syslog::syslog_xs", XS_Sys__Syslog_syslog_xs);
        newXS_deffile("Sys::Syslog::setlogmask_xs", XS_Sys__Syslog_setlogmask_xs);
        newXS_deffile("Sys::Syslog::closelog_xs", XS_Sys__Syslog_closelog_xs);
#endif
#if XSubPPtmpAAAB
        newXS_deffile("Sys::Syslog::openlog_xs", XS_Sys__Syslog_openlog_xs);
        newXS_deffile("Sys::Syslog::syslog_xs", XS_Sys__Syslog_syslog_xs);
        newXS_deffile("Sys::Syslog::setlogmask_xs", XS_Sys__Syslog_setlogmask_xs);
        newXS_deffile("Sys::Syslog::closelog_xs", XS_Sys__Syslog_closelog_xs);
#endif

    /* Initialisation Section */

#line 2 "./const-xs.inc"
  {
#if defined(dTHX) && !defined(PERL_NO_GET_CONTEXT)
    dTHX;
#endif
    HV *symbol_table = get_hv("Sys::Syslog::", GV_ADD);

    static const struct iv_s values_for_iv[] =
      {
#ifdef LOG_ALERT
        { "LOG_ALERT", 9, LOG_ALERT },
#endif
#ifdef LOG_CRIT
        { "LOG_CRIT", 8, LOG_CRIT },
#endif
#ifdef LOG_DEBUG
        { "LOG_DEBUG", 9, LOG_DEBUG },
#endif
#ifdef LOG_EMERG
        { "LOG_EMERG", 9, LOG_EMERG },
#endif
#ifdef LOG_ERR
        { "LOG_ERR", 7, LOG_ERR },
#endif
#ifdef LOG_INFO
        { "LOG_INFO", 8, LOG_INFO },
#endif
#ifdef LOG_NOTICE
        { "LOG_NOTICE", 10, LOG_NOTICE },
#endif
#ifdef LOG_WARNING
        { "LOG_WARNING", 11, LOG_WARNING },
#endif
#ifdef LOG_AUTH
        { "LOG_AUTH", 8, LOG_AUTH },
#endif
#ifdef LOG_AUTHPRIV
        { "LOG_AUTHPRIV", 12, LOG_AUTHPRIV },
#endif
#ifdef LOG_CRON
        { "LOG_CRON", 8, LOG_CRON },
#endif
#ifdef LOG_DAEMON
        { "LOG_DAEMON", 10, LOG_DAEMON },
#endif
#ifdef LOG_FTP
        { "LOG_FTP", 7, LOG_FTP },
#endif
#ifdef LOG_KERN
        { "LOG_KERN", 8, LOG_KERN },
#endif
#ifdef LOG_LOCAL0
        { "LOG_LOCAL0", 10, LOG_LOCAL0 },
#endif
#ifdef LOG_LOCAL1
        { "LOG_LOCAL1", 10, LOG_LOCAL1 },
#endif
#ifdef LOG_LOCAL2
        { "LOG_LOCAL2", 10, LOG_LOCAL2 },
#endif
#ifdef LOG_LOCAL3
        { "LOG_LOCAL3", 10, LOG_LOCAL3 },
#endif
#ifdef LOG_LOCAL4
        { "LOG_LOCAL4", 10, LOG_LOCAL4 },
#endif
#ifdef LOG_LOCAL5
        { "LOG_LOCAL5", 10, LOG_LOCAL5 },
#endif
#ifdef LOG_LOCAL6
        { "LOG_LOCAL6", 10, LOG_LOCAL6 },
#endif
#ifdef LOG_LOCAL7
        { "LOG_LOCAL7", 10, LOG_LOCAL7 },
#endif
#ifdef LOG_LPR
        { "LOG_LPR", 7, LOG_LPR },
#endif
#ifdef LOG_MAIL
        { "LOG_MAIL", 8, LOG_MAIL },
#endif
#ifdef LOG_NEWS
        { "LOG_NEWS", 8, LOG_NEWS },
#endif
#ifdef LOG_SYSLOG
        { "LOG_SYSLOG", 10, LOG_SYSLOG },
#endif
#ifdef LOG_USER
        { "LOG_USER", 8, LOG_USER },
#endif
#ifdef LOG_UUCP
        { "LOG_UUCP", 8, LOG_UUCP },
#endif
#ifdef LOG_INSTALL
        { "LOG_INSTALL", 11, LOG_INSTALL },
#endif
#ifdef LOG_LAUNCHD
        { "LOG_LAUNCHD", 11, LOG_LAUNCHD },
#endif
#ifdef LOG_NETINFO
        { "LOG_NETINFO", 11, LOG_NETINFO },
#endif
#ifdef LOG_RAS
        { "LOG_RAS", 7, LOG_RAS },
#endif
#ifdef LOG_REMOTEAUTH
        { "LOG_REMOTEAUTH", 14, LOG_REMOTEAUTH },
#endif
#ifdef LOG_CONSOLE
        { "LOG_CONSOLE", 11, LOG_CONSOLE },
#endif
#ifdef LOG_NTP
        { "LOG_NTP", 7, LOG_NTP },
#endif
#ifdef LOG_SECURITY
        { "LOG_SECURITY", 12, LOG_SECURITY },
#endif
#ifdef LOG_AUDIT
        { "LOG_AUDIT", 9, LOG_AUDIT },
#endif
#ifdef LOG_LFMT
        { "LOG_LFMT", 8, LOG_LFMT },
#endif
#ifdef LOG_CONS
        { "LOG_CONS", 8, LOG_CONS },
#endif
#ifdef LOG_PID
        { "LOG_PID", 7, LOG_PID },
#endif
#ifdef LOG_NDELAY
        { "LOG_NDELAY", 10, LOG_NDELAY },
#endif
#ifdef LOG_NOWAIT
        { "LOG_NOWAIT", 10, LOG_NOWAIT },
#endif
#ifdef LOG_ODELAY
        { "LOG_ODELAY", 10, LOG_ODELAY },
#endif
#ifdef LOG_PERROR
        { "LOG_PERROR", 10, LOG_PERROR },
#endif
#ifdef LOG_FACMASK
        { "LOG_FACMASK", 11, LOG_FACMASK },
#endif
#ifdef LOG_PRIMASK
        { "LOG_PRIMASK", 11, LOG_PRIMASK },
#endif
#ifdef LOG_NFACILITIES
        { "LOG_NFACILITIES", 15, LOG_NFACILITIES },
#endif
#ifndef LOG_INSTALL
        /* This is the default value: */
        { "LOG_INSTALL", 11, LOG_USER },
#endif
#ifndef LOG_LAUNCHD
        /* This is the default value: */
        { "LOG_LAUNCHD", 11, LOG_DAEMON },
#endif
#ifndef LOG_NETINFO
        /* This is the default value: */
        { "LOG_NETINFO", 11, LOG_DAEMON },
#endif
#ifndef LOG_RAS
        /* This is the default value: */
        { "LOG_RAS", 7, LOG_AUTH },
#endif
#ifndef LOG_REMOTEAUTH
        /* This is the default value: */
        { "LOG_REMOTEAUTH", 14, LOG_AUTH },
#endif
#ifndef LOG_CONSOLE
        /* This is the default value: */
        { "LOG_CONSOLE", 11, LOG_USER },
#endif
#ifndef LOG_NTP
        /* This is the default value: */
        { "LOG_NTP", 7, LOG_DAEMON },
#endif
#ifndef LOG_SECURITY
        /* This is the default value: */
        { "LOG_SECURITY", 12, LOG_AUTH },
#endif
#ifndef LOG_AUDIT
        /* This is the default value: */
        { "LOG_AUDIT", 9, LOG_AUTH },
#endif
#ifndef LOG_LFMT
        /* This is the default value: */
        { "LOG_LFMT", 8, LOG_USER },
#endif
#ifndef LOG_PRIMASK
        /* This is the default value: */
        { "LOG_PRIMASK", 11, 7 },
#endif
#ifndef LOG_NFACILITIES
        /* This is the default value: */
        { "LOG_NFACILITIES", 15, 30 },
#endif
        { NULL, 0, 0 } };
	const struct iv_s *value_for_iv = values_for_iv;

    static const struct pv_s values_for_pv[] =
      {
#ifdef _PATH_LOG
        { "_PATH_LOG", 9, _PATH_LOG },
#endif
#ifndef _PATH_LOG
        /* This is the default value: */
        { "_PATH_LOG", 9, "/dev/log" },
#endif
        { NULL, 0, 0 } };
	const struct pv_s *value_for_pv = values_for_pv;
        while (value_for_iv->name) {
	    constant_add_symbol(aTHX_  symbol_table, value_for_iv->name,
				value_for_iv->namelen, newSViv(value_for_iv->value));
            ++value_for_iv;
	}
        while (value_for_pv->name) {
	    constant_add_symbol(aTHX_  symbol_table, value_for_pv->name,
				value_for_pv->namelen, newSVpv(value_for_pv->value, 0));
            ++value_for_pv;
	}
	if (C_ARRAY_LENGTH(values_for_notfound) > 1) {
#ifndef SYMBIAN
	    HV *const constant_missing = get_missing_hash(aTHX);
#endif
	    const struct notfound_s *value_for_notfound = values_for_notfound;
	    do {

		/* Need to add prototypes, else parsing will vary by platform.  */
		HE *he = (HE*) hv_common_key_len(symbol_table,
						 value_for_notfound->name,
						 value_for_notfound->namelen,
						 HV_FETCH_LVALUE, NULL, 0);
		SV *sv;
#ifndef SYMBIAN
		HEK *hek;
#endif
		if (!he) {
		    croak("Couldn't add key '%s' to %%Sys::Syslog::",
			  value_for_notfound->name);
		}
		sv = HeVAL(he);
		if (!SvOK(sv) && SvTYPE(sv) != SVt_PVGV) {
		    /* Nothing was here before, so mark a prototype of ""  */
		    sv_setpvn(sv, "", 0);
		} else if (SvPOK(sv) && SvCUR(sv) == 0) {
		    /* There is already a prototype of "" - do nothing  */
		} else {
		    /* Someone has been here before us - have to make a real
		       typeglob.  */
		    /* It turns out to be incredibly hard to deal with all the
		       corner cases of sub foo (); and reporting errors correctly,
		       so lets cheat a bit.  Start with a constant subroutine  */
		    CV *cv = newCONSTSUB(symbol_table,
					 value_for_notfound->name,
					 &PL_sv_yes);
		    /* and then turn it into a non constant declaration only.  */
		    SvREFCNT_dec(CvXSUBANY(cv).any_ptr);
		    CvCONST_off(cv);
		    CvXSUB(cv) = NULL;
		    CvXSUBANY(cv).any_ptr = NULL;
		}
#ifndef SYMBIAN
		hek = HeKEY_hek(he);
		if (!hv_common(constant_missing, NULL, HEK_KEY(hek),
 			       HEK_LEN(hek), HEK_FLAGS(hek), HV_FETCH_ISSTORE,
			       &PL_sv_yes, HEK_HASH(hek)))
		    croak("Couldn't add key '%s' to missing_hash",
			  value_for_notfound->name);
#endif
	    } while ((++value_for_notfound)->name);
	}
    /* As we've been creating subroutines, we better invalidate any cached
       methods  */
    mro_method_changed_in(symbol_table);
  }

#if XSubPPtmpAAAA
#endif
#if XSubPPtmpAAAB
#endif
#line 867 "Syslog.c"

    /* End of Initialisation Section */

#if PERL_VERSION_LE(5, 21, 5)
#  if PERL_VERSION_GE(5, 9, 0)
    if (PL_unitcheckav)
        call_list(PL_scopestack_ix, PL_unitcheckav);
#  endif
    XSRETURN_YES;
#else
    Perl_xs_boot_epilog(aTHX_ ax);
#endif
}

