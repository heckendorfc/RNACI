RNACI_FUNTYPE SEXP make_list_names(int n, ...)
{
  R_INIT;
  int i;
  char *tmp;
  SEXP R_list_names;
  va_list listPointer;
  
  newRvec(R_list_names, n, "str");
  
  va_start(listPointer, n);
  
  for(i=0; i<n; i++)
  {
    tmp = va_arg(listPointer, char *);
  
    SET_STRING_ELT(R_list_names, i, mkChar(tmp));
  }
  
  va_end(listPointer);
  
  R_END;
  return R_list_names;
}

RNACI_FUNTYPE SEXP make_list(SEXP R_list_names, const int n, ...)
{
  R_INIT;
  int i;
/*  const int n = LENGTH(R_list_names);*/
  SEXP tmp, R_list;
  va_list listPointer;
  
  newRlist(R_list, n);
  
  va_start(listPointer, n);
  
  for(i=0; i<n; i++)
  {
    tmp = va_arg(listPointer, SEXP);
  
    SET_VECTOR_ELT(R_list, i, tmp);
  }
  
  va_end(listPointer);
  
/*  setAttrib(R_list, R_NamesSymbol, R_list_names);*/
  if (!is_Rnull(R_list_names))
    set_list_names(R_list, R_list_names);
  
  R_END;
  return R_list;
}
