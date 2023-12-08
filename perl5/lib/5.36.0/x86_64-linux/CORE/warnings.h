/* -*- buffer-read-only: t -*-
   !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
   This file is built by regen/warnings.pl.
   Any changes made here will be lost!
 */


#define Perl_Warn_Off_(x)           ((x) / 8)
#define Perl_Warn_Bit_(x)           (1 << ((x) % 8))
#define PerlWarnIsSet_(a, x)        ((a)[Perl_Warn_Off_(x)] & Perl_Warn_Bit_(x))


#define G_WARN_OFF		0 	/* $^W == 0 */
#define G_WARN_ON		1	/* -w flag and $^W != 0 */
#define G_WARN_ALL_ON		2	/* -W flag */
#define G_WARN_ALL_OFF		4	/* -X flag */
#define G_WARN_ONCE		8	/* set if 'once' ever enabled */
#define G_WARN_ALL_MASK		(G_WARN_ALL_ON|G_WARN_ALL_OFF)

#define pWARN_STD		NULL
#define pWARN_ALL		(STRLEN *) &PL_WARN_ALL    /* use warnings 'all' */
#define pWARN_NONE		(STRLEN *) &PL_WARN_NONE   /* no  warnings 'all' */

#define specialWARN(x)		((x) == pWARN_STD || (x) == pWARN_ALL ||	\
                                 (x) == pWARN_NONE)

/* if PL_warnhook is set to this value, then warnings die */
#define PERL_WARNHOOK_FATAL	(&PL_sv_placeholder)

/* Warnings Categories added in Perl 5.008 */

#define WARN_ALL			 0
#define WARN_CLOSURE			 1
#define WARN_DEPRECATED			 2
#define WARN_EXITING			 3
#define WARN_GLOB			 4
#define WARN_IO				 5
#define WARN_CLOSED			 6
#define WARN_EXEC			 7
#define WARN_LAYER			 8
#define WARN_NEWLINE			 9
#define WARN_PIPE			 10
#define WARN_UNOPENED			 11
#define WARN_MISC			 12
#define WARN_NUMERIC			 13
#define WARN_ONCE			 14
#define WARN_OVERFLOW			 15
#define WARN_PACK			 16
#define WARN_PORTABLE			 17
#define WARN_RECURSION			 18
#define WARN_REDEFINE			 19
#define WARN_REGEXP			 20
#define WARN_SEVERE			 21
#define WARN_DEBUGGING			 22
#define WARN_INPLACE			 23
#define WARN_INTERNAL			 24
#define WARN_MALLOC			 25
#define WARN_SIGNAL			 26
#define WARN_SUBSTR			 27
#define WARN_SYNTAX			 28
#define WARN_AMBIGUOUS			 29
#define WARN_BAREWORD			 30
#define WARN_DIGIT			 31
#define WARN_PARENTHESIS		 32
#define WARN_PRECEDENCE			 33
#define WARN_PRINTF			 34
#define WARN_PROTOTYPE			 35
#define WARN_QW				 36
#define WARN_RESERVED			 37
#define WARN_SEMICOLON			 38
#define WARN_TAINT			 39
#define WARN_THREADS			 40
#define WARN_UNINITIALIZED		 41
#define WARN_UNPACK			 42
#define WARN_UNTIE			 43
#define WARN_UTF8			 44
#define WARN_VOID			 45

/* Warnings Categories added in Perl 5.011 */

#define WARN_IMPRECISION		 46
#define WARN_ILLEGALPROTO		 47

/* Warnings Categories added in Perl 5.013 */

#define WARN_NON_UNICODE		 48
#define WARN_NONCHAR			 49
#define WARN_SURROGATE			 50

/* Warnings Categories added in Perl 5.017 */

#define WARN_EXPERIMENTAL		 51
#define WARN_EXPERIMENTAL__LEXICAL_SUBS	 52
#define WARN_EXPERIMENTAL__REGEX_SETS	 53
#define WARN_EXPERIMENTAL__SMARTMATCH	 54

/* Warnings Categories added in Perl 5.019 */

#define WARN_EXPERIMENTAL__POSTDEREF	 55
#define WARN_EXPERIMENTAL__SIGNATURES	 56
#define WARN_SYSCALLS			 57

/* Warnings Categories added in Perl 5.021 */

#define WARN_EXPERIMENTAL__BITWISE	 58
#define WARN_EXPERIMENTAL__CONST_ATTR	 59
#define WARN_EXPERIMENTAL__RE_STRICT	 60
#define WARN_EXPERIMENTAL__REFALIASING	 61
#define WARN_LOCALE			 62
#define WARN_MISSING			 63
#define WARN_REDUNDANT			 64

/* Warnings Categories added in Perl 5.025 */

#define WARN_EXPERIMENTAL__DECLARED_REFS 65

/* Warnings Categories added in Perl 5.027 */

#define WARN_EXPERIMENTAL__ALPHA_ASSERTIONS 66
#define WARN_EXPERIMENTAL__SCRIPT_RUN	 67
#define WARN_SHADOW			 68

/* Warnings Categories added in Perl 5.029 */

#define WARN_EXPERIMENTAL__PRIVATE_USE	 69
#define WARN_EXPERIMENTAL__UNIPROP_WILDCARDS 70
#define WARN_EXPERIMENTAL__VLB		 71

/* Warnings Categories added in Perl 5.031 */

#define WARN_EXPERIMENTAL__ISA		 72

/* Warnings Categories added in Perl 5.033 */

#define WARN_EXPERIMENTAL__TRY		 73

/* Warnings Categories added in Perl 5.035 */

#define WARN_EXPERIMENTAL__ARGS_ARRAY_WITH_SIGNATURES 74
#define WARN_EXPERIMENTAL__BUILTIN	 75
#define WARN_EXPERIMENTAL__DEFER	 76
#define WARN_EXPERIMENTAL__EXTRA_PAIRED_DELIMITERS 77
#define WARN_EXPERIMENTAL__FOR_LIST	 78
#define WARN_SCALAR			 79
#define WARNsize			 20
#define WARN_ALLstring			 "\125\125\125\125\125\125\125\125\125\125\125\125\125\125\125\125\125\125\125\125"
#define WARN_NONEstring			 "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"

#define isLEXWARN_on \
        cBOOL(PL_curcop && PL_curcop->cop_warnings != pWARN_STD)
#define isLEXWARN_off \
        cBOOL(!PL_curcop || PL_curcop->cop_warnings == pWARN_STD)
#define isWARN_ONCE	(PL_dowarn & (G_WARN_ON|G_WARN_ONCE))
#define isWARN_on(c,x)	(PerlWarnIsSet_((U8 *)(c + 1), 2*(x)))
#define isWARNf_on(c,x)	(PerlWarnIsSet_((U8 *)(c + 1), 2*(x)+1))

#define DUP_WARNINGS(p) Perl_dup_warnings(aTHX_ p)

#define free_and_set_cop_warnings(cmp,w) STMT_START { \
  if (!specialWARN((cmp)->cop_warnings)) PerlMemShared_free((cmp)->cop_warnings); \
  (cmp)->cop_warnings = w; \
} STMT_END

/*

=head1 Warning and Dieing

In all these calls, the C<U32 wI<n>> parameters are warning category
constants.  You can see the ones currently available in
L<warnings/Category Hierarchy>, just capitalize all letters in the names
and prefix them by C<WARN_>.  So, for example, the category C<void> used in a
perl program becomes C<WARN_VOID> when used in XS code and passed to one of
the calls below.

=for apidoc Am|bool|ckWARN|U32 w
=for apidoc_item ||ckWARN2|U32 w1|U32 w2
=for apidoc_item ||ckWARN3|U32 w1|U32 w2|U32 w3
=for apidoc_item ||ckWARN4|U32 w1|U32 w2|U32 w3|U32 w4
These return a boolean as to whether or not warnings are enabled for any of
the warning category(ies) parameters:  C<w>, C<w1>, ....

Should any of the categories by default be enabled even if not within the
scope of S<C<use warnings>>, instead use the C<L</ckWARN_d>> macros.

The categories must be completely independent, one may not be subclassed from
the other.

=for apidoc Am|bool|ckWARN_d|U32 w
=for apidoc_item ||ckWARN2_d|U32 w1|U32 w2
=for apidoc_item ||ckWARN3_d|U32 w1|U32 w2|U32 w3
=for apidoc_item ||ckWARN4_d|U32 w1|U32 w2|U32 w3|U32 w4

Like C<L</ckWARN>>, but for use if and only if the warning category(ies) is by
default enabled even if not within the scope of S<C<use warnings>>.

=for apidoc Am|U32|packWARN|U32 w1
=for apidoc_item ||packWARN2|U32 w1|U32 w2
=for apidoc_item ||packWARN3|U32 w1|U32 w2|U32 w3
=for apidoc_item ||packWARN4|U32 w1|U32 w2|U32 w3|U32 w4

These macros are used to pack warning categories into a single U32 to pass to
macros and functions that take a warning category parameter.  The number of
categories to pack is given by the name, with a corresponding number of
category parameters passed.

=cut

*/

#define ckWARN(w)		Perl_ckwarn(aTHX_ packWARN(w))

/* The w1, w2 ... should be independent warnings categories; one shouldn't be
 * a subcategory of any other */

#define ckWARN2(w1,w2)		Perl_ckwarn(aTHX_ packWARN2(w1,w2))
#define ckWARN3(w1,w2,w3)	Perl_ckwarn(aTHX_ packWARN3(w1,w2,w3))
#define ckWARN4(w1,w2,w3,w4)	Perl_ckwarn(aTHX_ packWARN4(w1,w2,w3,w4))

#define ckWARN_d(w)		Perl_ckwarn_d(aTHX_ packWARN(w))
#define ckWARN2_d(w1,w2)	Perl_ckwarn_d(aTHX_ packWARN2(w1,w2))
#define ckWARN3_d(w1,w2,w3)	Perl_ckwarn_d(aTHX_ packWARN3(w1,w2,w3))
#define ckWARN4_d(w1,w2,w3,w4)	Perl_ckwarn_d(aTHX_ packWARN4(w1,w2,w3,w4))

#define WARNshift		8

#define packWARN(a)		(a                                      )

/* The a, b, ... should be independent warnings categories; one shouldn't be
 * a subcategory of any other */

#define packWARN2(a,b)		((a) | ((b)<<8)                         )
#define packWARN3(a,b,c)	((a) | ((b)<<8) | ((c)<<16)             )
#define packWARN4(a,b,c,d)	((a) | ((b)<<8) | ((c)<<16) | ((d) <<24))

#define unpackWARN1(x)		((U8)  (x)       )
#define unpackWARN2(x)		((U8) ((x) >>  8))
#define unpackWARN3(x)		((U8) ((x) >> 16))
#define unpackWARN4(x)		((U8) ((x) >> 24))

#define ckDEAD(x)							\
   (PL_curcop &&                                                        \
    !specialWARN(PL_curcop->cop_warnings) &&			        \
    (isWARNf_on(PL_curcop->cop_warnings, unpackWARN1(x)) ||	        \
      (unpackWARN2(x) &&                                                \
        (isWARNf_on(PL_curcop->cop_warnings, unpackWARN2(x)) ||	        \
          (unpackWARN3(x) &&                                            \
            (isWARNf_on(PL_curcop->cop_warnings, unpackWARN3(x)) ||	\
              (unpackWARN4(x) &&                                        \
                isWARNf_on(PL_curcop->cop_warnings, unpackWARN4(x)))))))))



/*
=for apidoc Amnh||WARN_ALL
=for apidoc Amnh||WARN_CLOSURE
=for apidoc Amnh||WARN_DEPRECATED
=for apidoc Amnh||WARN_EXITING
=for apidoc Amnh||WARN_GLOB
=for apidoc Amnh||WARN_IO
=for apidoc Amnh||WARN_CLOSED
=for apidoc Amnh||WARN_EXEC
=for apidoc Amnh||WARN_LAYER
=for apidoc Amnh||WARN_NEWLINE
=for apidoc Amnh||WARN_PIPE
=for apidoc Amnh||WARN_UNOPENED
=for apidoc Amnh||WARN_MISC
=for apidoc Amnh||WARN_NUMERIC
=for apidoc Amnh||WARN_ONCE
=for apidoc Amnh||WARN_OVERFLOW
=for apidoc Amnh||WARN_PACK
=for apidoc Amnh||WARN_PORTABLE
=for apidoc Amnh||WARN_RECURSION
=for apidoc Amnh||WARN_REDEFINE
=for apidoc Amnh||WARN_REGEXP
=for apidoc Amnh||WARN_SEVERE
=for apidoc Amnh||WARN_DEBUGGING
=for apidoc Amnh||WARN_INPLACE
=for apidoc Amnh||WARN_INTERNAL
=for apidoc Amnh||WARN_MALLOC
=for apidoc Amnh||WARN_SIGNAL
=for apidoc Amnh||WARN_SUBSTR
=for apidoc Amnh||WARN_SYNTAX
=for apidoc Amnh||WARN_AMBIGUOUS
=for apidoc Amnh||WARN_BAREWORD
=for apidoc Amnh||WARN_DIGIT
=for apidoc Amnh||WARN_PARENTHESIS
=for apidoc Amnh||WARN_PRECEDENCE
=for apidoc Amnh||WARN_PRINTF
=for apidoc Amnh||WARN_PROTOTYPE
=for apidoc Amnh||WARN_QW
=for apidoc Amnh||WARN_RESERVED
=for apidoc Amnh||WARN_SEMICOLON
=for apidoc Amnh||WARN_TAINT
=for apidoc Amnh||WARN_THREADS
=for apidoc Amnh||WARN_UNINITIALIZED
=for apidoc Amnh||WARN_UNPACK
=for apidoc Amnh||WARN_UNTIE
=for apidoc Amnh||WARN_UTF8
=for apidoc Amnh||WARN_VOID
=for apidoc Amnh||WARN_IMPRECISION
=for apidoc Amnh||WARN_ILLEGALPROTO
=for apidoc Amnh||WARN_NON_UNICODE
=for apidoc Amnh||WARN_NONCHAR
=for apidoc Amnh||WARN_SURROGATE
=for apidoc Amnh||WARN_EXPERIMENTAL
=for apidoc Amnh||WARN_EXPERIMENTAL__LEXICAL_SUBS
=for apidoc Amnh||WARN_EXPERIMENTAL__REGEX_SETS
=for apidoc Amnh||WARN_EXPERIMENTAL__SMARTMATCH
=for apidoc Amnh||WARN_EXPERIMENTAL__POSTDEREF
=for apidoc Amnh||WARN_EXPERIMENTAL__SIGNATURES
=for apidoc Amnh||WARN_SYSCALLS
=for apidoc Amnh||WARN_EXPERIMENTAL__BITWISE
=for apidoc Amnh||WARN_EXPERIMENTAL__CONST_ATTR
=for apidoc Amnh||WARN_EXPERIMENTAL__RE_STRICT
=for apidoc Amnh||WARN_EXPERIMENTAL__REFALIASING
=for apidoc Amnh||WARN_LOCALE
=for apidoc Amnh||WARN_MISSING
=for apidoc Amnh||WARN_REDUNDANT
=for apidoc Amnh||WARN_EXPERIMENTAL__DECLARED_REFS
=for apidoc Amnh||WARN_EXPERIMENTAL__ALPHA_ASSERTIONS
=for apidoc Amnh||WARN_EXPERIMENTAL__SCRIPT_RUN
=for apidoc Amnh||WARN_SHADOW
=for apidoc Amnh||WARN_EXPERIMENTAL__PRIVATE_USE
=for apidoc Amnh||WARN_EXPERIMENTAL__UNIPROP_WILDCARDS
=for apidoc Amnh||WARN_EXPERIMENTAL__VLB
=for apidoc Amnh||WARN_EXPERIMENTAL__ISA
=for apidoc Amnh||WARN_EXPERIMENTAL__TRY
=for apidoc Amnh||WARN_EXPERIMENTAL__ARGS_ARRAY_WITH_SIGNATURES
=for apidoc Amnh||WARN_EXPERIMENTAL__BUILTIN
=for apidoc Amnh||WARN_EXPERIMENTAL__DEFER
=for apidoc Amnh||WARN_EXPERIMENTAL__EXTRA_PAIRED_DELIMITERS
=for apidoc Amnh||WARN_EXPERIMENTAL__FOR_LIST
=for apidoc Amnh||WARN_SCALAR

=cut
*/

/* end of file warnings.h */

/* ex: set ro: */