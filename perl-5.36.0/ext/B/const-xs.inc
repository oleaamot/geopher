BOOT:
  {
#if defined(dTHX) && !defined(PERL_NO_GET_CONTEXT)
    dTHX;
#endif
    HV *symbol_table = get_hv("B::", GV_ADD);
    AV *push = get_av("B::EXPORT_OK", GV_ADD);
    HE *he;

    static const struct iv_s values_for_iv[] =
      {
        { "HEf_SVKEY", 9, HEf_SVKEY },
        { NULL, 0, 0 } };
	const struct iv_s *value_for_iv = values_for_iv;

    static const struct uv_s values_for_uv[] =
      {
        { "SVTYPEMASK", 10, SVTYPEMASK },
        { "SVt_PVGV", 8, SVt_PVGV },
        { "SVt_PVHV", 8, SVt_PVHV },
        { "PAD_FAKELEX_ANON", 16, PAD_FAKELEX_ANON },
        { "PAD_FAKELEX_MULTI", 17, PAD_FAKELEX_MULTI },
        { "SVpad_STATE", 11, SVpad_STATE },
        { "SVpad_TYPED", 11, SVpad_TYPED },
        { "SVpad_OUR", 9, SVpad_OUR },
        { "CXTYPEMASK", 10, CXTYPEMASK },
        { "CXt_NULL", 8, CXt_NULL },
        { "CXt_WHEN", 8, CXt_WHEN },
        { "CXt_BLOCK", 9, CXt_BLOCK },
        { "CXt_GIVEN", 9, CXt_GIVEN },
        { "CXt_LOOP_ARY", 12, CXt_LOOP_ARY },
        { "CXt_LOOP_LAZYSV", 15, CXt_LOOP_LAZYSV },
        { "CXt_LOOP_LAZYIV", 15, CXt_LOOP_LAZYIV },
        { "CXt_LOOP_LIST", 13, CXt_LOOP_LIST },
        { "CXt_LOOP_PLAIN", 14, CXt_LOOP_PLAIN },
        { "CXt_SUB", 7, CXt_SUB },
        { "CXt_FORMAT", 10, CXt_FORMAT },
        { "CXt_EVAL", 8, CXt_EVAL },
        { "CXt_SUBST", 9, CXt_SUBST },
        { "CXt_DEFER", 9, CXt_DEFER },
        { "CXp_MULTICALL", 13, CXp_MULTICALL },
        { "CXp_HASARGS", 11, CXp_HASARGS },
        { "CXp_SUB_RE", 10, CXp_SUB_RE },
        { "CXp_SUB_RE_FAKE", 15, CXp_SUB_RE_FAKE },
        { "CXp_REAL", 8, CXp_REAL },
        { "CXp_EVALBLOCK", 13, CXp_EVALBLOCK },
        { "CXp_TRY", 7, CXp_TRY },
        { "CXp_FOR_DEF", 11, CXp_FOR_DEF },
        { "CXp_FOR_LVREF", 13, CXp_FOR_LVREF },
        { "CXp_FOR_GV", 10, CXp_FOR_GV },
        { "CXp_FOR_PAD", 11, CXp_FOR_PAD },
        { "CXp_ONCE", 8, CXp_ONCE },
        { "CXp_FINALLY", 11, CXp_FINALLY },
        { "G_SCALAR", 8, G_SCALAR },
        { "G_LIST", 6, G_LIST },
        { "G_VOID", 6, G_VOID },
        { "G_WANT", 6, G_WANT },
        { "G_DISCARD", 9, G_DISCARD },
        { "G_EVAL", 6, G_EVAL },
        { "G_NOARGS", 8, G_NOARGS },
        { "G_KEEPERR", 9, G_KEEPERR },
        { "G_NODEBUG", 9, G_NODEBUG },
        { "G_METHOD", 8, G_METHOD },
        { "G_FAKINGEVAL", 12, G_FAKINGEVAL },
        { "G_UNDEF_FILL", 12, G_UNDEF_FILL },
        { "G_WRITING_TO_STDERR", 19, G_WRITING_TO_STDERR },
        { "G_RE_REPARSING", 14, G_RE_REPARSING },
        { "G_METHOD_NAMED", 14, G_METHOD_NAMED },
        { "G_RETHROW", 9, G_RETHROW },
        { "EVAL_NULL", 9, EVAL_NULL },
        { "EVAL_INEVAL", 11, EVAL_INEVAL },
        { "EVAL_WARNONLY", 13, EVAL_WARNONLY },
        { "EVAL_KEEPERR", 12, EVAL_KEEPERR },
        { "EVAL_INREQUIRE", 14, EVAL_INREQUIRE },
        { "EVAL_RE_REPARSING", 17, EVAL_RE_REPARSING },
        { "PERLSI_UNDEF", 12, PERLSI_UNDEF },
        { "PERLSI_MAIN", 11, PERLSI_MAIN },
        { "PERLSI_MAGIC", 12, PERLSI_MAGIC },
        { "PERLSI_SORT", 11, PERLSI_SORT },
        { "PERLSI_SIGNAL", 13, PERLSI_SIGNAL },
        { "PERLSI_OVERLOAD", 15, PERLSI_OVERLOAD },
        { "PERLSI_DESTROY", 14, PERLSI_DESTROY },
        { "PERLSI_WARNHOOK", 15, PERLSI_WARNHOOK },
        { "PERLSI_DIEHOOK", 14, PERLSI_DIEHOOK },
        { "PERLSI_REQUIRE", 14, PERLSI_REQUIRE },
        { "PERLSI_MULTICALL", 16, PERLSI_MULTICALL },
        { "PERLSI_REGCOMP", 14, PERLSI_REGCOMP },
        { "CVf_METHOD", 10, CVf_METHOD },
        { "CVf_LVALUE", 10, CVf_LVALUE },
        { "CVf_CONST", 9, CVf_CONST },
        { "CVf_ISXSUB", 10, CVf_ISXSUB },
        { "CVf_WEAKOUTSIDE", 15, CVf_WEAKOUTSIDE },
        { "CVf_CLONE", 9, CVf_CLONE },
        { "CVf_CLONED", 10, CVf_CLONED },
        { "CVf_ANON", 8, CVf_ANON },
        { "CVf_UNIQUE", 10, CVf_UNIQUE },
        { "CVf_NODEBUG", 11, CVf_NODEBUG },
        { "CVf_CVGV_RC", 11, CVf_CVGV_RC },
        { "CVf_SLABBED", 11, CVf_SLABBED },
        { "CVf_DYNFILE", 11, CVf_DYNFILE },
        { "CVf_AUTOLOAD", 12, CVf_AUTOLOAD },
        { "CVf_HASEVAL", 11, CVf_HASEVAL },
        { "CVf_NAMED", 9, CVf_NAMED },
        { "CVf_LEXICAL", 11, CVf_LEXICAL },
        { "CVf_ANONCONST", 13, CVf_ANONCONST },
        { "CVf_SIGNATURE", 13, CVf_SIGNATURE },
        { "GVf_INTRO", 9, GVf_INTRO },
        { "GVf_MULTI", 9, GVf_MULTI },
        { "GVf_ASSUMECV", 12, GVf_ASSUMECV },
        { "GVf_IMPORTED", 12, GVf_IMPORTED },
        { "GVf_IMPORTED_SV", 15, GVf_IMPORTED_SV },
        { "GVf_IMPORTED_AV", 15, GVf_IMPORTED_AV },
        { "GVf_IMPORTED_HV", 15, GVf_IMPORTED_HV },
        { "GVf_IMPORTED_CV", 15, GVf_IMPORTED_CV },
        { "OPf_WANT", 8, OPf_WANT },
        { "OPf_WANT_VOID", 13, OPf_WANT_VOID },
        { "OPf_WANT_SCALAR", 15, OPf_WANT_SCALAR },
        { "OPf_WANT_LIST", 13, OPf_WANT_LIST },
        { "OPf_KIDS", 8, OPf_KIDS },
        { "OPf_PARENS", 10, OPf_PARENS },
        { "OPf_REF", 7, OPf_REF },
        { "OPf_MOD", 7, OPf_MOD },
        { "OPf_STACKED", 11, OPf_STACKED },
        { "OPf_SPECIAL", 11, OPf_SPECIAL },
        { "OPf_FOLDED", 10, OPf_FOLDED },
        { "PMf_HAS_ERROR", 13, PMf_HAS_ERROR },
        { "PMf_RETAINT", 11, PMf_RETAINT },
        { "PMf_ONCE", 8, PMf_ONCE },
        { "PMf_USED", 8, PMf_USED },
        { "PMf_CONST", 9, PMf_CONST },
        { "PMf_KEEP", 8, PMf_KEEP },
        { "PMf_GLOBAL", 10, PMf_GLOBAL },
        { "PMf_CONTINUE", 12, PMf_CONTINUE },
        { "PMf_EVAL", 8, PMf_EVAL },
        { "PMf_NONDESTRUCT", 15, PMf_NONDESTRUCT },
        { "PMf_HAS_CV", 10, PMf_HAS_CV },
        { "PMf_CODELIST_PRIVATE", 20, PMf_CODELIST_PRIVATE },
        { "PMf_IS_QR", 9, PMf_IS_QR },
        { "PMf_USE_RE_EVAL", 15, PMf_USE_RE_EVAL },
        { "PMf_WILDCARD", 12, PMf_WILDCARD },
        { "OA_MARK", 7, OA_MARK },
        { "OA_FOLDCONST", 12, OA_FOLDCONST },
        { "OA_RETSCALAR", 12, OA_RETSCALAR },
        { "OA_TARGET", 9, OA_TARGET },
        { "OA_TARGLEX", 10, OA_TARGLEX },
        { "OA_OTHERINT", 11, OA_OTHERINT },
        { "OA_DANGEROUS", 12, OA_DANGEROUS },
        { "OA_DEFGV", 8, OA_DEFGV },
        { "OCSHIFT", 7, OCSHIFT },
        { "OA_CLASS_MASK", 13, OA_CLASS_MASK },
        { "OA_BASEOP", 9, OA_BASEOP },
        { "OA_UNOP", 7, OA_UNOP },
        { "OA_BINOP", 8, OA_BINOP },
        { "OA_LOGOP", 8, OA_LOGOP },
        { "OA_LISTOP", 9, OA_LISTOP },
        { "OA_PMOP", 7, OA_PMOP },
        { "OA_SVOP", 7, OA_SVOP },
        { "OA_PADOP", 8, OA_PADOP },
        { "OA_PVOP_OR_SVOP", 15, OA_PVOP_OR_SVOP },
        { "OA_LOOP", 7, OA_LOOP },
        { "OA_COP", 6, OA_COP },
        { "OA_BASEOP_OR_UNOP", 17, OA_BASEOP_OR_UNOP },
        { "OA_FILESTATOP", 13, OA_FILESTATOP },
        { "OA_LOOPEXOP", 11, OA_LOOPEXOP },
        { "OA_METHOP", 9, OA_METHOP },
        { "OA_UNOP_AUX", 11, OA_UNOP_AUX },
        { "OASHIFT", 7, OASHIFT },
        { "OA_SCALAR", 9, OA_SCALAR },
        { "OA_LIST", 7, OA_LIST },
        { "OA_AVREF", 8, OA_AVREF },
        { "OA_HVREF", 8, OA_HVREF },
        { "OA_CVREF", 8, OA_CVREF },
        { "OA_FILEREF", 10, OA_FILEREF },
        { "OA_SCALARREF", 12, OA_SCALARREF },
        { "OA_OPTIONAL", 11, OA_OPTIONAL },
        { "PERL_LOADMOD_DENY", 17, PERL_LOADMOD_DENY },
        { "PERL_LOADMOD_NOIMPORT", 21, PERL_LOADMOD_NOIMPORT },
        { "PERL_LOADMOD_IMPORT_OPS", 23, PERL_LOADMOD_IMPORT_OPS },
        { "BHKf_bhk_start", 14, BHKf_bhk_start },
        { "BHKf_bhk_pre_end", 16, BHKf_bhk_pre_end },
        { "BHKf_bhk_post_end", 17, BHKf_bhk_post_end },
        { "BHKf_bhk_eval", 13, BHKf_bhk_eval },
        { "RV2CVOPCV_MARK_EARLY", 20, RV2CVOPCV_MARK_EARLY },
        { "RV2CVOPCV_RETURN_NAME_GV", 24, RV2CVOPCV_RETURN_NAME_GV },
        { "RV2CVOPCV_RETURN_STUB", 21, RV2CVOPCV_RETURN_STUB },
        { "RV2CVOPCV_MAYBE_NAME_GV", 23, RV2CVOPCV_MAYBE_NAME_GV },
        { "RV2CVOPCV_FLAG_MASK", 19, RV2CVOPCV_FLAG_MASK },
        { "OP_LVALUE_NO_CROAK", 18, OP_LVALUE_NO_CROAK },
        { "XOPf_xop_name", 13, XOPf_xop_name },
        { "XOPf_xop_desc", 13, XOPf_xop_desc },
        { "XOPf_xop_class", 14, XOPf_xop_class },
        { "XOPf_xop_peep", 13, XOPf_xop_peep },
        { "MDEREF_reload", 13, MDEREF_reload },
        { "MDEREF_AV_pop_rv2av_aelem", 25, MDEREF_AV_pop_rv2av_aelem },
        { "MDEREF_AV_gvsv_vivify_rv2av_aelem", 33, MDEREF_AV_gvsv_vivify_rv2av_aelem },
        { "MDEREF_AV_padsv_vivify_rv2av_aelem", 34, MDEREF_AV_padsv_vivify_rv2av_aelem },
        { "MDEREF_AV_vivify_rv2av_aelem", 28, MDEREF_AV_vivify_rv2av_aelem },
        { "MDEREF_AV_padav_aelem", 21, MDEREF_AV_padav_aelem },
        { "MDEREF_AV_gvav_aelem", 20, MDEREF_AV_gvav_aelem },
        { "MDEREF_HV_pop_rv2hv_helem", 25, MDEREF_HV_pop_rv2hv_helem },
        { "MDEREF_HV_gvsv_vivify_rv2hv_helem", 33, MDEREF_HV_gvsv_vivify_rv2hv_helem },
        { "MDEREF_HV_padsv_vivify_rv2hv_helem", 34, MDEREF_HV_padsv_vivify_rv2hv_helem },
        { "MDEREF_HV_vivify_rv2hv_helem", 28, MDEREF_HV_vivify_rv2hv_helem },
        { "MDEREF_HV_padhv_helem", 21, MDEREF_HV_padhv_helem },
        { "MDEREF_HV_gvhv_helem", 20, MDEREF_HV_gvhv_helem },
        { "MDEREF_ACTION_MASK", 18, MDEREF_ACTION_MASK },
        { "MDEREF_INDEX_none", 17, MDEREF_INDEX_none },
        { "MDEREF_INDEX_const", 18, MDEREF_INDEX_const },
        { "MDEREF_INDEX_padsv", 18, MDEREF_INDEX_padsv },
        { "MDEREF_INDEX_gvsv", 17, MDEREF_INDEX_gvsv },
        { "MDEREF_INDEX_MASK", 17, MDEREF_INDEX_MASK },
        { "MDEREF_FLAG_last", 16, MDEREF_FLAG_last },
        { "MDEREF_MASK", 11, MDEREF_MASK },
        { "MDEREF_SHIFT", 12, MDEREF_SHIFT },
        { "OPpARGELEM_SV", 13, OPpARGELEM_SV },
        { "OPpLVREF_SV", 11, OPpLVREF_SV },
        { "OPpARG1_MASK", 12, OPpARG1_MASK },
        { "OPpCOREARGS_DEREF1", 18, OPpCOREARGS_DEREF1 },
        { "OPpENTERSUB_INARGS", 18, OPpENTERSUB_INARGS },
        { "OPpPADHV_ISKEYS", 15, OPpPADHV_ISKEYS },
        { "OPpRV2HV_ISKEYS", 15, OPpRV2HV_ISKEYS },
        { "OPpSORT_NUMERIC", 15, OPpSORT_NUMERIC },
        { "OPpTRANS_CAN_FORCE_UTF8", 23, OPpTRANS_CAN_FORCE_UTF8 },
        { "OPpARGELEM_AV", 13, OPpARGELEM_AV },
        { "OPpCONST_NOVER", 14, OPpCONST_NOVER },
        { "OPpCOREARGS_DEREF2", 18, OPpCOREARGS_DEREF2 },
        { "OPpEVAL_HAS_HH", 14, OPpEVAL_HAS_HH },
        { "OPpFT_ACCESS", 12, OPpFT_ACCESS },
        { "OPpHINT_STRICT_REFS", 19, OPpHINT_STRICT_REFS },
        { "OPpITER_REVERSED", 16, OPpITER_REVERSED },
        { "OPpSORT_INTEGER", 15, OPpSORT_INTEGER },
        { "OPpTRANS_USE_SVOP", 17, OPpTRANS_USE_SVOP },
        { "OPpARG2_MASK", 12, OPpARG2_MASK },
        { "OPpAVHVSWITCH_MASK", 18, OPpAVHVSWITCH_MASK },
        { "OPpARGELEM_HV", 13, OPpARGELEM_HV },
        { "OPpASSIGN_TRUEBOOL", 18, OPpASSIGN_TRUEBOOL },
        { "OPpCONST_SHORTCIRCUIT", 21, OPpCONST_SHORTCIRCUIT },
        { "OPpDONT_INIT_GV", 15, OPpDONT_INIT_GV },
        { "OPpENTERSUB_HASTARG", 19, OPpENTERSUB_HASTARG },
        { "OPpEVAL_UNICODE", 15, OPpEVAL_UNICODE },
        { "OPpFT_STACKED", 13, OPpFT_STACKED },
        { "OPpLVREF_ELEM", 13, OPpLVREF_ELEM },
        { "OPpSLICEWARNING", 15, OPpSLICEWARNING },
        { "OPpSORT_REVERSE", 15, OPpSORT_REVERSE },
        { "OPpSPLIT_IMPLIM", 15, OPpSPLIT_IMPLIM },
        { "OPpTRANS_IDENTICAL", 18, OPpTRANS_IDENTICAL },
        { "OPpUSEINT", 9, OPpUSEINT },
        { "OPpARGELEM_MASK", 15, OPpARGELEM_MASK },
        { "OPpARG3_MASK", 12, OPpARG3_MASK },
        { "OPpPADRANGE_COUNTSHIFT", 22, OPpPADRANGE_COUNTSHIFT },
        { "OPpCONST_STRICT", 15, OPpCONST_STRICT },
        { "OPpENTERSUB_AMPER", 17, OPpENTERSUB_AMPER },
        { "OPpEVAL_BYTES", 13, OPpEVAL_BYTES },
        { "OPpFT_STACKING", 14, OPpFT_STACKING },
        { "OPpITER_DEF", 11, OPpITER_DEF },
        { "OPpLVREF_ITER", 13, OPpLVREF_ITER },
        { "OPpMAYBE_LVSUB", 14, OPpMAYBE_LVSUB },
        { "OPpMULTICONCAT_STRINGIFY", 24, OPpMULTICONCAT_STRINGIFY },
        { "OPpREVERSE_INPLACE", 18, OPpREVERSE_INPLACE },
        { "OPpSORT_INPLACE", 15, OPpSORT_INPLACE },
        { "OPpSPLIT_LEX", 12, OPpSPLIT_LEX },
        { "OPpTRANS_SQUASH", 15, OPpTRANS_SQUASH },
        { "OPpARG4_MASK", 12, OPpARG4_MASK },
        { "OPpASSIGN_COMMON_AGG", 20, OPpASSIGN_COMMON_AGG },
        { "OPpCONST_ENTERED", 16, OPpCONST_ENTERED },
        { "OPpDEREF_AV", 11, OPpDEREF_AV },
        { "OPpEVAL_COPHH", 13, OPpEVAL_COPHH },
        { "OPpFT_AFTER_t", 13, OPpFT_AFTER_t },
        { "OPpLVREF_AV", 11, OPpLVREF_AV },
        { "OPpMAYBE_TRUEBOOL", 17, OPpMAYBE_TRUEBOOL },
        { "OPpMULTIDEREF_EXISTS", 20, OPpMULTIDEREF_EXISTS },
        { "OPpOPEN_IN_RAW", 14, OPpOPEN_IN_RAW },
        { "OPpSORT_DESCEND", 15, OPpSORT_DESCEND },
        { "OPpSPLIT_ASSIGN", 15, OPpSPLIT_ASSIGN },
        { "OPpSUBSTR_REPL_FIRST", 20, OPpSUBSTR_REPL_FIRST },
        { "OPpTARGET_MY", 12, OPpTARGET_MY },
        { "OPpASSIGN_COMMON_RC1", 20, OPpASSIGN_COMMON_RC1 },
        { "OPpDEREF_HV", 11, OPpDEREF_HV },
        { "OPpEARLY_CV", 11, OPpEARLY_CV },
        { "OPpEVAL_RE_REPARSING", 20, OPpEVAL_RE_REPARSING },
        { "OPpHUSH_VMSISH", 14, OPpHUSH_VMSISH },
        { "OPpKVSLICE", 10, OPpKVSLICE },
        { "OPpLVREF_HV", 11, OPpLVREF_HV },
        { "OPpMAY_RETURN_CONSTANT", 22, OPpMAY_RETURN_CONSTANT },
        { "OPpMULTICONCAT_FAKE", 19, OPpMULTICONCAT_FAKE },
        { "OPpMULTIDEREF_DELETE", 20, OPpMULTIDEREF_DELETE },
        { "OPpOPEN_IN_CRLF", 15, OPpOPEN_IN_CRLF },
        { "OPpTRANS_COMPLEMENT", 19, OPpTRANS_COMPLEMENT },
        { "OPpTRUEBOOL", 11, OPpTRUEBOOL },
        { "OPpDEREF", 8, OPpDEREF },
        { "OPpDEREF_SV", 11, OPpDEREF_SV },
        { "OPpLVREF_CV", 11, OPpLVREF_CV },
        { "OPpLVREF_TYPE", 13, OPpLVREF_TYPE },
        { "OPpALLOW_FAKE", 13, OPpALLOW_FAKE },
        { "OPpASSIGN_BACKWARDS", 19, OPpASSIGN_BACKWARDS },
        { "OPpASSIGN_COMMON_SCALAR", 23, OPpASSIGN_COMMON_SCALAR },
        { "OPpCONCAT_NESTED", 16, OPpCONCAT_NESTED },
        { "OPpCONST_BARE", 13, OPpCONST_BARE },
        { "OPpCOREARGS_SCALARMOD", 21, OPpCOREARGS_SCALARMOD },
        { "OPpENTERSUB_DB", 14, OPpENTERSUB_DB },
        { "OPpEXISTS_SUB", 13, OPpEXISTS_SUB },
        { "OPpFLIP_LINENUM", 15, OPpFLIP_LINENUM },
        { "OPpINDEX_BOOLNEG", 16, OPpINDEX_BOOLNEG },
        { "OPpLIST_GUESSED", 15, OPpLIST_GUESSED },
        { "OPpLVAL_DEFER", 13, OPpLVAL_DEFER },
        { "OPpMULTICONCAT_APPEND", 21, OPpMULTICONCAT_APPEND },
        { "OPpOPEN_OUT_RAW", 15, OPpOPEN_OUT_RAW },
        { "OPpOUR_INTRO", 12, OPpOUR_INTRO },
        { "OPpPAD_STATE", 12, OPpPAD_STATE },
        { "OPpREFCOUNTED", 13, OPpREFCOUNTED },
        { "OPpREPEAT_DOLIST", 16, OPpREPEAT_DOLIST },
        { "OPpSLICE", 8, OPpSLICE },
        { "OPpTRANS_GROWS", 14, OPpTRANS_GROWS },
        { "OPpPADRANGE_COUNTMASK", 21, OPpPADRANGE_COUNTMASK },
        { "OPpASSIGN_CV_TO_GV", 18, OPpASSIGN_CV_TO_GV },
        { "OPpCOREARGS_PUSHMARK", 20, OPpCOREARGS_PUSHMARK },
        { "OPpDEFER_FINALLY", 16, OPpDEFER_FINALLY },
        { "OPpENTERSUB_NOPAREN", 19, OPpENTERSUB_NOPAREN },
        { "OPpLVALUE", 9, OPpLVALUE },
        { "OPpLVAL_INTRO", 13, OPpLVAL_INTRO },
        { "OPpOFFBYONE", 11, OPpOFFBYONE },
        { "OPpOPEN_OUT_CRLF", 16, OPpOPEN_OUT_CRLF },
        { "OPpPV_IS_UTF8", 13, OPpPV_IS_UTF8 },
        { "OPpTRANS_DELETE", 15, OPpTRANS_DELETE },
        { "RXf_PMf_STD_PMMOD_SHIFT", 23, RXf_PMf_STD_PMMOD_SHIFT },
        { "RXf_PMf_MULTILINE", 17, RXf_PMf_MULTILINE },
        { "RXf_PMf_SINGLELINE", 18, RXf_PMf_SINGLELINE },
        { "RXf_PMf_FOLD", 12, RXf_PMf_FOLD },
        { "RXf_PMf_EXTENDED", 16, RXf_PMf_EXTENDED },
        { "RXf_PMf_EXTENDED_MORE", 21, RXf_PMf_EXTENDED_MORE },
        { "RXf_PMf_NOCAPTURE", 17, RXf_PMf_NOCAPTURE },
        { "RXf_PMf_KEEPCOPY", 16, RXf_PMf_KEEPCOPY },
        { "RXf_PMf_CHARSET", 15, RXf_PMf_CHARSET },
        { "RXf_PMf_STRICT", 14, RXf_PMf_STRICT },
        { "RXf_PMf_SPLIT", 13, RXf_PMf_SPLIT },
        { "PMf_MULTILINE", 13, PMf_MULTILINE },
        { "PMf_SINGLELINE", 14, PMf_SINGLELINE },
        { "PMf_FOLD", 8, PMf_FOLD },
        { "PMf_EXTENDED", 12, PMf_EXTENDED },
        { "PMf_EXTENDED_MORE", 17, PMf_EXTENDED_MORE },
        { "PMf_NOCAPTURE", 13, PMf_NOCAPTURE },
        { "PMf_KEEPCOPY", 12, PMf_KEEPCOPY },
        { "PMf_CHARSET", 11, PMf_CHARSET },
        { "PMf_STRICT", 10, PMf_STRICT },
        { "PMf_SPLIT", 9, PMf_SPLIT },
        { "PADNAMEt_OUTER", 14, PADNAMEt_OUTER },
        { "PADNAMEt_STATE", 14, PADNAMEt_STATE },
        { "PADNAMEt_LVALUE", 15, PADNAMEt_LVALUE },
        { "PADNAMEt_TYPED", 14, PADNAMEt_TYPED },
        { "PADNAMEt_OUR", 12, PADNAMEt_OUR },
        { "RXf_NO_INPLACE_SUBST", 20, RXf_NO_INPLACE_SUBST },
        { "RXf_EVAL_SEEN", 13, RXf_EVAL_SEEN },
        { "RXf_UNBOUNDED_QUANTIFIER_SEEN", 29, RXf_UNBOUNDED_QUANTIFIER_SEEN },
        { "RXf_CHECK_ALL", 13, RXf_CHECK_ALL },
        { "RXf_MATCH_UTF8", 14, RXf_MATCH_UTF8 },
        { "RXf_USE_INTUIT_NOML", 19, RXf_USE_INTUIT_NOML },
        { "RXf_USE_INTUIT_ML", 17, RXf_USE_INTUIT_ML },
        { "RXf_INTUIT_TAIL", 15, RXf_INTUIT_TAIL },
        { "RXf_IS_ANCHORED", 15, RXf_IS_ANCHORED },
        { "RXf_COPY_DONE", 13, RXf_COPY_DONE },
        { "RXf_TAINTED_SEEN", 16, RXf_TAINTED_SEEN },
        { "RXf_TAINTED", 11, RXf_TAINTED },
        { "RXf_START_ONLY", 14, RXf_START_ONLY },
        { "RXf_SKIPWHITE", 13, RXf_SKIPWHITE },
        { "RXf_WHITE", 9, RXf_WHITE },
        { "RXf_NULL", 8, RXf_NULL },
        { "SVf_IOK", 7, SVf_IOK },
        { "SVf_NOK", 7, SVf_NOK },
        { "SVf_POK", 7, SVf_POK },
        { "SVf_ROK", 7, SVf_ROK },
        { "SVp_IOK", 7, SVp_IOK },
        { "SVp_NOK", 7, SVp_NOK },
        { "SVp_POK", 7, SVp_POK },
        { "SVp_SCREAM", 10, SVp_SCREAM },
        { "SVf_PROTECT", 11, SVf_PROTECT },
        { "SVs_PADTMP", 10, SVs_PADTMP },
        { "SVs_PADSTALE", 12, SVs_PADSTALE },
        { "SVs_TEMP", 8, SVs_TEMP },
        { "SVs_OBJECT", 10, SVs_OBJECT },
        { "SVs_GMG", 7, SVs_GMG },
        { "SVs_SMG", 7, SVs_SMG },
        { "SVs_RMG", 7, SVs_RMG },
        { "SVf_FAKE", 8, SVf_FAKE },
        { "SVf_OOK", 7, SVf_OOK },
        { "SVf_BREAK", 9, SVf_BREAK },
        { "SVf_READONLY", 12, SVf_READONLY },
        { "SVf_AMAGIC", 10, SVf_AMAGIC },
        { "SVf_IsCOW", 9, SVf_IsCOW },
        { "SVf_UTF8", 8, SVf_UTF8 },
        { "SVf_IVisUV", 10, SVf_IVisUV },
        { "SVs_PADMY", 9, SVs_PADMY },
        { NULL, 0, 0 } };
	const struct uv_s *value_for_uv = values_for_uv;
        while (value_for_iv->name) {
	    he = _add_symbol(aTHX_  symbol_table, value_for_iv->name,
				     value_for_iv->namelen, newSViv(value_for_iv->value));
	    av_push(push, newSVhek(HeKEY_hek(he)));
            ++value_for_iv;
	}
        while (value_for_uv->name) {
	    he = _add_symbol(aTHX_  symbol_table, value_for_uv->name,
				     value_for_uv->namelen, newSVuv(value_for_uv->value));
	    av_push(push, newSVhek(HeKEY_hek(he)));
            ++value_for_uv;
	}
	if (C_ARRAY_LENGTH(values_for_notfound) > 1) {
#ifndef SYMBIAN
	    HV *const _missing = get_missing_hash(aTHX);
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
		    croak("Couldn't add key '%s' to %%B::",
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
		if (!hv_common(_missing, NULL, HEK_KEY(hek),
 			       HEK_LEN(hek), HEK_FLAGS(hek), HV_FETCH_ISSTORE,
			       &PL_sv_yes, HEK_HASH(hek)))
		    croak("Couldn't add key '%s' to missing_hash",
			  value_for_notfound->name);
#endif
		av_push(push, newSVhek(hek));
	    } while ((++value_for_notfound)->name);
	}
    /* As we've been creating subroutines, we better invalidate any cached
       methods  */
    mro_method_changed_in(symbol_table);
  }