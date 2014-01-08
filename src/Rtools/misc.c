/* This Source Code Form is subject to the terms of the BSD 2-Clause
 * License. If a copy of the this license was not distributed with this
 * file, you can obtain one from http://opensource.org/licenses/BSD-2-Clause. */

// Copyright 2014, Schmidt


#include "Rtools.h"

int is_Rnull(SEXP x)
{
  PTINIT;
  SEXP basePackage;
  SEXP tmp;
  int ret;
  
  PT(basePackage);
  basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv );
  
  tmp = eval( lang2( install("is.null"), x), basePackage);
  
  UNPT;
  return INT(tmp,0);
}



int is_Rnan(SEXP x)
{
  PTINIT;
  SEXP basePackage;
  SEXP tmp;
  int ret;
  
  PT(basePackage);
  basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv );
  
  tmp = eval( lang2( install("is.nan"), x), basePackage);
  
  UNPT;
  return INT(tmp,0);
}



int is_Rna(SEXP x)
{
  PTINIT;
  SEXP basePackage;
  SEXP tmp;
  int ret;
  
  PT(basePackage);
  basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv );
  
  tmp = eval( lang2( install("is.na"), x), basePackage);
  
  UNPT;
  return INT(tmp,0);
}
