/* This Source Code Form is subject to the terms of the BSD 2-Clause
 * License. If a copy of the this license was not distributed with this
 * file, you can obtain one from http://opensource.org/licenses/BSD-2-Clause. */

// Copyright 2014, Schmidt


#include "Rtools.h"

// Internals
SEXP make_dataframe_default_colnames(int n)
{
  PTINIT;
  int i;
  SEXP basePackage;
  SEXP x;
  SEXP ret_names;
  
  PT(basePackage);
  basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv );
  
  PT(x = Rvecalloc(n, "int"));
  
  for (i=0; i<n; i++)
    INT(x,i) = i+1;
  
  PT(ret_names);
  
  ret_names = eval( lang2( install("make.names"), x), basePackage);
  
  UNPT;
  return ret_names;
}



SEXP make_dataframe_default_rownames(int n)
{
  PTINIT;
  int i;
  SEXP ret_names;
  
  PT(ret_names = Rvecalloc(n, "int"));
  for(i=0; i<n; i++)
    INT(ret_names,i) = i + 1;
  
  UNPT;
  return ret_names;
}



// Actually useful things
SEXP make_dataframe_nonames(int n, ...)
{
  PTINIT;
  int i, nrows;
  SEXP R_list;
  SEXP R_rownames;
  SEXP R_colnames;
  SEXP tmp;
  va_list listPointer;
  
  // Construct list
  PT(R_list = Rvecalloc(n, "vec"));
  
  va_start(listPointer, n);
  
  for(i=0; i<n; i++)
  {
    tmp = va_arg(listPointer, SEXP);
    
    SET_VECTOR_ELT(R_list, i, tmp);
  }
  
  va_end(listPointer);
  
  // Set rownames
  R_rownames = make_dataframe_default_rownames(n);
  
  // Set colnames
  R_colnames = make_dataframe_default_colnames(n);
  
  setAttrib(R_list, R_ClassSymbol, mkString("data.frame"));
  setAttrib(R_list, R_RowNamesSymbol, R_rownames);
  setAttrib(R_list, R_NamesSymbol, R_colnames);
  
  UNPT;
  return R_list;
}

