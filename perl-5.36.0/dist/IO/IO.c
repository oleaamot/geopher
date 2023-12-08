/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.45 from the
 * contents of IO.xs. Do not edit this file, edit IO.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "IO.xs"
/*
 * Copyright (c) 1997-8 Graham Barr <gbarr@pobox.com>. All rights reserved.
 * This program is free software; you can redistribute it and/or
 * modify it under the same terms as Perl itself.
 */

#define PERL_EXT_IO

#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#define PERLIO_NOT_STDIO 1
#include "perl.h"
#include "XSUB.h"
#define NEED_newCONSTSUB
#define NEED_newSVpvn_flags
#include "ppport.h"
#include "poll.h"
#ifdef I_UNISTD
#  include <unistd.h>
#endif
#if defined(I_FCNTL) || defined(HAS_FCNTL)
#  include <fcntl.h>
#endif

#ifndef SIOCATMARK
#   ifdef I_SYS_SOCKIO
#       include <sys/sockio.h>
#   endif
#endif

#ifdef PerlIO
#if defined(MACOS_TRADITIONAL) && defined(USE_SFIO)
#define PERLIO_IS_STDIO 1
#undef setbuf
#undef setvbuf
#define setvbuf		_stdsetvbuf
#define setbuf(f,b)	( __sf_setbuf(f,b) )
#endif
typedef int SysRet;
typedef PerlIO * InputStream;
typedef PerlIO * OutputStream;
#else
#define PERLIO_IS_STDIO 1
typedef int SysRet;
typedef FILE * InputStream;
typedef FILE * OutputStream;
#endif

#define MY_start_subparse(fmt,flags) start_subparse(fmt,flags)

#ifndef __attribute__noreturn__
#  define __attribute__noreturn__
#endif

#ifndef NORETURN_FUNCTION_END
# define NORETURN_FUNCTION_END /* NOT REACHED */ return 0
#endif

#ifndef OpSIBLING
#  define OpSIBLING(o) (o)->op_sibling
#endif

static int not_here(const char *s) __attribute__noreturn__;
static int
not_here(const char *s)
{
    croak("%s not implemented on this architecture", s);
    NORETURN_FUNCTION_END;
}

#ifndef PerlIO
#define PerlIO_fileno(f) fileno(f)
#endif

static int
io_blocking(pTHX_ InputStream f, int block)
{
    int fd = -1;
#if defined(HAS_FCNTL)
    int RETVAL;
    if (!f) {
	errno = EBADF;
	return -1;
    }
    fd = PerlIO_fileno(f);
    if (fd < 0) {
      errno = EBADF;
      return -1;
    }
    RETVAL = fcntl(fd, F_GETFL, 0);
    if (RETVAL >= 0) {
	int mode = RETVAL;
	int newmode = mode;
#ifdef O_NONBLOCK
	/* POSIX style */

# ifndef O_NDELAY
#  define O_NDELAY O_NONBLOCK
# endif
	/* Note: UNICOS and UNICOS/mk a F_GETFL returns an O_NDELAY
	 * after a successful F_SETFL of an O_NONBLOCK. */
	RETVAL = RETVAL & (O_NONBLOCK | O_NDELAY) ? 0 : 1;

	if (block == 0) {
	    newmode &= ~O_NDELAY;
	    newmode |= O_NONBLOCK;
	} else if (block > 0) {
	    newmode &= ~(O_NDELAY|O_NONBLOCK);
	}
#else
	/* Not POSIX - better have O_NDELAY or we can't cope.
	 * for BSD-ish machines this is an acceptable alternative
	 * for SysV we can't tell "would block" from EOF but that is
	 * the way SysV is...
	 */
	RETVAL = RETVAL & O_NDELAY ? 0 : 1;

	if (block == 0) {
	    newmode |= O_NDELAY;
	} else if (block > 0) {
	    newmode &= ~O_NDELAY;
	}
#endif
	if (newmode != mode) {
            const int ret = fcntl(fd, F_SETFL, newmode);
	    if (ret < 0)
		RETVAL = ret;
	}
    }
    return RETVAL;
#else
#   ifdef WIN32
    if (block >= 0) {
	unsigned long flags = !block;
	/* ioctl claims to take char* but really needs a u_long sized buffer */
	const int ret = ioctl(fd, FIONBIO, (char*)&flags);
	if (ret != 0)
	    return -1;
	/* Win32 has no way to get the current blocking status of a socket.
	 * However, we don't want to just return undef, because there's no way
	 * to tell that the ioctl succeeded.
	 */
	return flags;
    }
    /* TODO: Perhaps set $! to ENOTSUP? */
    return -1;
#   else
    return -1;
#   endif
#endif
}


#line 164 "IO.c"
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

#line 308 "IO.c"

XS_EUPXS(XS_IO__Seekable_getpos); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Seekable_getpos)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)))
;
#line 160 "IO.xs"
	if (handle) {
#ifdef PerlIO
#if PERL_VERSION_LT(5,8,0)
	    Fpos_t pos;
	    ST(0) = sv_newmortal();
	    if (PerlIO_getpos(handle, &pos) != 0) {
		ST(0) = &PL_sv_undef;
	    }
	    else {
		sv_setpvn(ST(0), (char *)&pos, sizeof(Fpos_t));
	    }
#else
	    ST(0) = sv_newmortal();
	    if (PerlIO_getpos(handle, ST(0)) != 0) {
		ST(0) = &PL_sv_undef;
	    }
#endif
#else
	    Fpos_t pos;
	    if (fgetpos(handle, &pos)) {
		ST(0) = &PL_sv_undef;
	    } else {
#  if PERL_VERSION_GE(5,11,0)
		ST(0) = newSVpvn_flags((char*)&pos, sizeof(Fpos_t), SVs_TEMP);
#  else
		ST(0) = sv_2mortal(newSVpvn((char*)&pos, sizeof(Fpos_t)));
#  endif
	    }
#endif
	}
	else {
	    errno = EINVAL;
	    ST(0) = &PL_sv_undef;
	}
#line 354 "IO.c"
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Seekable_setpos); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Seekable_setpos)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "handle, pos");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)))
;
	SV *	pos = ST(1)
;
	SysRet	RETVAL;
#line 200 "IO.xs"
	if (handle) {
#ifdef PerlIO
#if PERL_VERSION_LT(5,8,0)
	    char *p;
	    STRLEN len;
	    if (SvOK(pos) && (p = SvPV(pos,len)) && len == sizeof(Fpos_t)) {
		RETVAL = PerlIO_setpos(handle, (Fpos_t*)p);
	    }
	    else {
		RETVAL = -1;
		errno = EINVAL;
	    }
#else
	    RETVAL = PerlIO_setpos(handle, pos);
#endif
#else
	    char *p;
	    STRLEN len;
	    if ((p = SvPV(pos,len)) && len == sizeof(Fpos_t)) {
		RETVAL = fsetpos(handle, (Fpos_t*)p);
	    }
	    else {
		RETVAL = -1;
		errno = EINVAL;
	    }
#endif
	}
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 404 "IO.c"
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    if (RETVAL != -1) {
		if (RETVAL == 0)
		    sv_setpvn(RETVALSV, "0 but true", 10);
		else
		    sv_setiv(RETVALSV, (IV)RETVAL);
	    }
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__File_new_tmpfile); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__File_new_tmpfile)
{
    dVAR; dXSARGS;
    if (items < 0 || items > 1)
       croak_xs_usage(cv,  "packname = \"IO::File\"");
    {
	const char *	packname;
#line 240 "IO.xs"
	OutputStream fp;
	GV *gv;
#line 432 "IO.c"

	if (items < 1)
	    packname = "IO::File";
	else {
	    packname = (const char *)SvPV_nolen(ST(0))
;
	}
#line 243 "IO.xs"
#ifdef PerlIO
	fp = PerlIO_tmpfile();
#else
	fp = tmpfile();
#endif
	gv = (GV*)SvREFCNT_inc(newGVgen(packname));
	if (gv)
	    (void) hv_delete(GvSTASH(gv), GvNAME(gv), GvNAMELEN(gv), G_DISCARD);
	if (gv && do_open(gv, "+>&", 3, FALSE, 0, 0, fp)) {
	    ST(0) = sv_2mortal(newRV_inc((SV*)gv));
	    sv_bless(ST(0), gv_stashpv(packname, TRUE));
	    SvREFCNT_dec(gv);   /* undo increment in newRV() */
	}
	else {
	    ST(0) = &PL_sv_undef;
	    SvREFCNT_dec(gv);
	}
#line 458 "IO.c"
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Poll__poll); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Poll__poll)
{
    dVAR; dXSARGS;
    if (items < 1)
       croak_xs_usage(cv,  "timeout, ...");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	int	timeout = (int)SvIV(ST(0))
;
#line 267 "IO.xs"
{
#ifdef HAS_POLL
    const int nfd = (items - 1) / 2;
    SV *tmpsv = sv_2mortal(NEWSV(999,nfd * sizeof(struct pollfd)));
    /* We should pass _some_ valid pointer even if nfd is zero, but it
     * doesn't matter what it is, since we're telling it to not check any fds.
     */
    struct pollfd *fds = nfd ? (struct pollfd *)SvPVX(tmpsv) : (struct pollfd *)tmpsv;
    int i,j,ret;
    for(i=1, j=0  ; j < nfd ; j++) {
	fds[j].fd = SvIV(ST(i));
	i++;
	fds[j].events = (short)SvIV(ST(i));
	i++;
	fds[j].revents = 0;
    }
    if((ret = poll(fds,nfd,timeout)) >= 0) {
	for(i=1, j=0 ; j < nfd ; j++) {
	    sv_setiv(ST(i), fds[j].fd); i++;
	    sv_setiv(ST(i), fds[j].revents); i++;
	}
    }
    XSRETURN_IV(ret);
#else
	not_here("IO::Poll::poll");
#endif
}
#line 503 "IO.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IO__Handle_blocking); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_blocking)
{
    dVAR; dXSARGS;
    if (items < 1 || items > 2)
       croak_xs_usage(cv,  "handle, blk=-1");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)))
;
	int	blk;

	if (items < 2)
	    blk = -1;
	else {
	    blk = (int)SvIV(ST(1))
;
	}
#line 303 "IO.xs"
{
    const int ret = io_blocking(aTHX_ handle, items == 1 ? -1 : blk ? 1 : 0);
    if(ret >= 0)
	XSRETURN_IV(ret);
    else
	XSRETURN_UNDEF;
}
#line 535 "IO.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_IO__Handle_ungetc); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_ungetc)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "handle, c");
    {
	InputStream	handle = IoIFP(sv_2io(ST(0)))
;
	SV *	c = ST(1)
;
	int	RETVAL;
	dXSTARG;
#line 318 "IO.xs"
	if (handle) {
#ifdef PerlIO
            UV v;

            if ((SvIOK_notUV(c) && SvIV(c) < 0) || (SvNOK(c) && SvNV(c) < 0.0))
                croak("Negative character number in ungetc()");

            v = SvUV(c);
            if (UVCHR_IS_INVARIANT(v) || (v <= 0xFF && !PerlIO_isutf8(handle)))
                RETVAL = PerlIO_ungetc(handle, (int)v);
            else {
                U8 buf[UTF8_MAXBYTES + 1], *end;
                Size_t len;

                if (!PerlIO_isutf8(handle))
                    croak("Wide character number in ungetc()");

                /* This doesn't warn for non-chars, surrogate, and
                 * above-Unicodes */
                end = uvchr_to_utf8_flags(buf, v, 0);
                len = end - buf;
                if ((Size_t)PerlIO_unread(handle, &buf, len) == len)
                    XSRETURN_UV(v);
                else
                    RETVAL = EOF;
            }
#else
            RETVAL = ungetc((int)SvIV(c), handle);
#endif
        }
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 589 "IO.c"
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Handle_error); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_error)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	SV *	handle = ST(0)
;
#line 359 "IO.xs"
        IO *io = sv_2io(handle);
        InputStream in = IoIFP(io);
        OutputStream out = IoOFP(io);
#line 610 "IO.c"
	int	RETVAL;
	dXSTARG;
#line 363 "IO.xs"
	if (in)
#ifdef PerlIO
	    RETVAL = PerlIO_error(in) || (out && in != out && PerlIO_error(out));
#else
	    RETVAL = ferror(in) || (out && in != out && ferror(out));
#endif
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 624 "IO.c"
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Handle_clearerr); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_clearerr)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	SV *	handle = ST(0)
;
#line 380 "IO.xs"
        IO *io = sv_2io(handle);
        InputStream in = IoIFP(io);
        OutputStream out = IoOFP(io);
#line 645 "IO.c"
	int	RETVAL;
	dXSTARG;
#line 384 "IO.xs"
	if (handle) {
#ifdef PerlIO
	    PerlIO_clearerr(in);
            if (in != out)
                PerlIO_clearerr(out);
#else
	    clearerr(in);
            if (in != out)
                clearerr(out);
#endif
	    RETVAL = 0;
	}
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 665 "IO.c"
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Handle_untaint); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_untaint)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	SV *	handle = ST(0)
;
	int	RETVAL;
	dXSTARG;
#line 407 "IO.xs"
#ifdef IOf_UNTAINT
	IO * io;
	io = sv_2io(handle);
	if (io) {
	    IoFLAGS(io) |= IOf_UNTAINT;
	    RETVAL = 0;
	}
        else {
#endif
	    RETVAL = -1;
	    errno = EINVAL;
#ifdef IOf_UNTAINT
	}
#endif
#line 699 "IO.c"
	XSprePUSH;
	PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Handle_flush); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_flush)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "handle");
    {
	OutputStream	handle = IoOFP(sv_2io(ST(0)))
;
	SysRet	RETVAL;
#line 428 "IO.xs"
	if (handle)
#ifdef PerlIO
	    RETVAL = PerlIO_flush(handle);
#else
	    RETVAL = Fflush(handle);
#endif
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#line 728 "IO.c"
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    if (RETVAL != -1) {
		if (RETVAL == 0)
		    sv_setpvn(RETVALSV, "0 but true", 10);
		else
		    sv_setiv(RETVALSV, (IV)RETVAL);
	    }
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Handle_setbuf); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_setbuf)
{
    dVAR; dXSARGS;
    if (items < 1)
       croak_xs_usage(cv,  "handle, ...");
    {
	OutputStream	handle = IoOFP(sv_2io(ST(0)))
;
#line 445 "IO.xs"
	if (handle)
#ifdef PERLIO_IS_STDIO
        {
	    char *buf = items == 2 && SvPOK(ST(1)) ?
	      sv_grow(ST(1), BUFSIZ) : 0;
	    setbuf(handle, buf);
	}
#else
	    not_here("IO::Handle::setbuf");
#endif
#line 765 "IO.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_IO__Handle_setvbuf); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_setvbuf)
{
    dVAR; dXSARGS;
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    {
	SysRet	RETVAL;
#line 459 "IO.xs"
	if (items != 4)
            Perl_croak(aTHX_ "Usage: IO::Handle::setvbuf(handle, buf, type, size)");
#if defined(PERLIO_IS_STDIO) && defined(_IOFBF) && defined(HAS_SETVBUF)
    {
        OutputStream	handle = 0;
	char *		buf = SvPOK(ST(1)) ? sv_grow(ST(1), SvIV(ST(3))) : 0;
	int		type;
	int		size;

	if (items == 4) {
	    handle = IoOFP(sv_2io(ST(0)));
	    buf    = SvPOK(ST(1)) ? sv_grow(ST(1), SvIV(ST(3))) : 0;
	    type   = (int)SvIV(ST(2));
	    size   = (int)SvIV(ST(3));
	}
	if (!handle)			/* Try input stream. */
	    handle = IoIFP(sv_2io(ST(0)));
	if (items == 4 && handle)
	    RETVAL = setvbuf(handle, buf, type, size);
	else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
    }
#else
	RETVAL = (SysRet) not_here("IO::Handle::setvbuf");
#endif
#line 807 "IO.c"
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    if (RETVAL != -1) {
		if (RETVAL == 0)
		    sv_setpvn(RETVALSV, "0 but true", 10);
		else
		    sv_setiv(RETVALSV, (IV)RETVAL);
	    }
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Handle_sync); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_sync)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "arg");
    {
	SV *	arg = ST(0)
;
#line 494 "IO.xs"
	OutputStream handle = NULL;
#line 835 "IO.c"
	SysRet	RETVAL;
#line 496 "IO.xs"
#if defined(HAS_FSYNC) || defined(_WIN32)
	handle = IoOFP(sv_2io(arg));
	if (!handle)
	    handle = IoIFP(sv_2io(arg));
	if (handle) {
	    int fd = PerlIO_fileno(handle);
	    if (fd >= 0) {
#  ifdef _WIN32
                RETVAL = _commit(fd);
#  else
		RETVAL = fsync(fd);
#  endif
	    } else {
		RETVAL = -1;
		errno = EBADF;
	    }
	} else {
	    RETVAL = -1;
	    errno = EINVAL;
	}
#else
	RETVAL = (SysRet) not_here("IO::Handle::sync");
#endif
#line 861 "IO.c"
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    if (RETVAL != -1) {
		if (RETVAL == 0)
		    sv_setpvn(RETVALSV, "0 but true", 10);
		else
		    sv_setiv(RETVALSV, (IV)RETVAL);
	    }
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IO__Handle_getlines); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Handle_getlines)
{
    dVAR; dXSARGS;
    dXSI32;
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 554 "IO.xs"
    UNOP myop;
    SV *io;
    OP *was = PL_op;
#line 892 "IO.c"
#line 558 "IO.xs"
    if (items != 1)
        Perl_croak(aTHX_ "usage: $io->%s()", ix ? "getline" : "getlines");
    if (!ix && GIMME_V != G_LIST)
        Perl_croak(aTHX_ "Can't call $io->getlines in a scalar context, use $io->getline");
    Zero(&myop, 1, UNOP);
    myop.op_flags = (ix ? OPf_WANT_SCALAR : OPf_WANT_LIST ) | OPf_STACKED;
    myop.op_ppaddr = PL_ppaddr[OP_READLINE];
    myop.op_type = OP_READLINE;
    /* I don't know if we need this, but it's correct as far as the control flow
       goes. However, if we *do* need it, do we need to set anything else up? */
    myop.op_next = PL_op->op_next;
    /* Sigh, because pp_readline calls pp_rv2gv, and *it* has this wonderful
       state check for PL_op->op_type == OP_READLINE */
    PL_op = (OP *) &myop;
    io = ST(0);
    /* Our target (which we need to provide, as we don't have a pad entry.
       I think that this is only needed for G_SCALAR - maybe we can get away
       with NULL for list context? */
    PUSHs(sv_newmortal());
    XPUSHs(io);
    PUTBACK;
    /* And effectively we get away with tail calling pp_readline, as it stacks
       exactly the return value(s) we need to return. */
    PL_ppaddr[OP_READLINE](aTHX);
    PL_op = was;
    /* And we don't want to reach the line
       PL_stack_sp = sp;
       that xsubpp adds after our body becase PL_stack_sp is correct, not sp */
    return;
#line 923 "IO.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IO__Socket_sockatmark); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IO__Socket_sockatmark)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "sock");
    {
	InputStream	sock = IoIFP(sv_2io(ST(0)))
;
#line 595 "IO.xs"
     int fd;
#line 941 "IO.c"
	SysRet	RETVAL;
#line 597 "IO.xs"
     fd = PerlIO_fileno(sock);
     if (fd < 0) {
       errno = EBADF;
       RETVAL = -1;
     }
#ifdef HAS_SOCKATMARK
     else {
       RETVAL = sockatmark(fd);
     }
#else
     else {
       int flag = 0;
#   ifdef SIOCATMARK
#     if defined(NETWARE) || defined(WIN32)
       if (ioctl(fd, SIOCATMARK, (char*)&flag) != 0)
#     else
       if (ioctl(fd, SIOCATMARK, &flag) != 0)
#     endif
	 XSRETURN_UNDEF;
#   else
       not_here("IO::Socket::atmark");
#   endif
       RETVAL = flag;
     }
#endif
#line 969 "IO.c"
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    if (RETVAL != -1) {
		if (RETVAL == 0)
		    sv_setpvn(RETVALSV, "0 but true", 10);
		else
		    sv_setiv(RETVALSV, (IV)RETVAL);
	    }
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_IO); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_IO)
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

        newXS_deffile("IO::Seekable::getpos", XS_IO__Seekable_getpos);
        newXS_deffile("IO::Seekable::setpos", XS_IO__Seekable_setpos);
        newXS_deffile("IO::File::new_tmpfile", XS_IO__File_new_tmpfile);
        newXS_deffile("IO::Poll::_poll", XS_IO__Poll__poll);
        (void)newXSproto_portable("IO::Handle::blocking", XS_IO__Handle_blocking, file, "$;$");
        newXS_deffile("IO::Handle::ungetc", XS_IO__Handle_ungetc);
        newXS_deffile("IO::Handle::error", XS_IO__Handle_error);
        newXS_deffile("IO::Handle::clearerr", XS_IO__Handle_clearerr);
        newXS_deffile("IO::Handle::untaint", XS_IO__Handle_untaint);
        newXS_deffile("IO::Handle::flush", XS_IO__Handle_flush);
        newXS_deffile("IO::Handle::setbuf", XS_IO__Handle_setbuf);
        newXS_deffile("IO::Handle::setvbuf", XS_IO__Handle_setvbuf);
        newXS_deffile("IO::Handle::sync", XS_IO__Handle_sync);
        cv = newXS_deffile("IO::Handle::getline", XS_IO__Handle_getlines);
        XSANY.any_i32 = 1;
        cv = newXS_deffile("IO::Handle::getlines", XS_IO__Handle_getlines);
        XSANY.any_i32 = 0;
        cv = newXS_deffile("IO::Handle::gets", XS_IO__Handle_getlines);
        XSANY.any_i32 = 2;
        (void)newXSproto_portable("IO::Socket::sockatmark", XS_IO__Socket_sockatmark, file, "$");

    /* Initialisation Section */

#line 626 "IO.xs"
{
    HV *stash;
    /*
     * constant subs for IO::Poll
     */
    stash = gv_stashpvn("IO::Poll", 8, TRUE);
#ifdef	POLLIN
	newCONSTSUB(stash,"POLLIN",newSViv(POLLIN));
#endif
#ifdef	POLLPRI
        newCONSTSUB(stash,"POLLPRI", newSViv(POLLPRI));
#endif
#ifdef	POLLOUT
        newCONSTSUB(stash,"POLLOUT", newSViv(POLLOUT));
#endif
#ifdef	POLLRDNORM
        newCONSTSUB(stash,"POLLRDNORM", newSViv(POLLRDNORM));
#endif
#ifdef	POLLWRNORM
        newCONSTSUB(stash,"POLLWRNORM", newSViv(POLLWRNORM));
#endif
#ifdef	POLLRDBAND
        newCONSTSUB(stash,"POLLRDBAND", newSViv(POLLRDBAND));
#endif
#ifdef	POLLWRBAND
        newCONSTSUB(stash,"POLLWRBAND", newSViv(POLLWRBAND));
#endif
#ifdef	POLLNORM
        newCONSTSUB(stash,"POLLNORM", newSViv(POLLNORM));
#endif
#ifdef	POLLERR
        newCONSTSUB(stash,"POLLERR", newSViv(POLLERR));
#endif
#ifdef	POLLHUP
        newCONSTSUB(stash,"POLLHUP", newSViv(POLLHUP));
#endif
#ifdef	POLLNVAL
        newCONSTSUB(stash,"POLLNVAL", newSViv(POLLNVAL));
#endif
    /*
     * constant subs for IO::Handle
     */
    stash = gv_stashpvn("IO::Handle", 10, TRUE);
#ifdef _IOFBF
        newCONSTSUB(stash,"_IOFBF", newSViv(_IOFBF));
#endif
#ifdef _IOLBF
        newCONSTSUB(stash,"_IOLBF", newSViv(_IOLBF));
#endif
#ifdef _IONBF
        newCONSTSUB(stash,"_IONBF", newSViv(_IONBF));
#endif
#ifdef SEEK_SET
        newCONSTSUB(stash,"SEEK_SET", newSViv(SEEK_SET));
#endif
#ifdef SEEK_CUR
        newCONSTSUB(stash,"SEEK_CUR", newSViv(SEEK_CUR));
#endif
#ifdef SEEK_END
        newCONSTSUB(stash,"SEEK_END", newSViv(SEEK_END));
#endif
}

#line 1100 "IO.c"

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

