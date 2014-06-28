/* This Source Code Form is subject to the terms of the BSD 2-Clause
 * License. If a copy of the this license was not distributed with this
 * file, you can obtain one from http://opensource.org/licenses/BSD-2-Clause. */

// Copyright 2014, Schmidt


#include "SEXPtools.h"

// Internals
SEXP make_dataframe_default_colnames(int n)
{
  R_INIT;
  int i;
  SEXP basePackage;
  SEXP x;
  SEXP ret_names;
  
  PT( basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv ) );
  
  newRvec(x, n, "int");
  
  for (i=0; i<n; i++)
    INT(x,i) = i+1;
  
  PT( ret_names = eval( lang2( install("make.names"), x), basePackage) );
  
  R_END;
  return ret_names;
}



SEXP make_dataframe_default_rownames(int n)
{
  R_INIT;
  int i;
  SEXP ret_names;
  
  newRvec(ret_names, n, "int");
  
  for(i=0; i<n; i++)
    INT(ret_names,i) = i + 1;
  
  R_END;
  return ret_names;
}



// Actually useful things
SEXP make_dataframe(SEXP R_rownames, SEXP R_colnames, int n, ...)
{
  R_INIT;
  int i;
  SEXP R_df;
  SEXP R_default_rownames;
  SEXP R_default_colnames;
  SEXP tmp;
  va_list listPointer;
  
  // Construct list
  newRlist(R_df, n);
  
  va_start(listPointer, n);
  
  for(i=0; i<n; i++)
  {
    tmp = va_arg(listPointer, SEXP);
    
    SET_VECTOR_ELT(R_df, i, tmp);
  }
  
  va_end(listPointer);
  
  // Set names
  set_list_as_df(R_df);
  
  if (is_Rnull(R_rownames))
  {
    R_default_rownames = make_dataframe_default_rownames(n);
    set_df_rownames(R_df, R_default_rownames);
  }
  else
    set_df_rownames(R_df, R_rownames);
  
  if (is_Rnull(R_colnames))
  {
    R_default_colnames = make_dataframe_default_colnames(n);
    set_df_colnames(R_df, R_default_colnames);
  }
  else
    set_df_colnames(R_df, R_colnames);
  
  
  R_END;
  return R_df;
}

