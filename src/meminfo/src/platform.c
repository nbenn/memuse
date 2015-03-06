/* Copyright (c) 2014-2015, Schmidt.  All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE file. */


#include "meminfo.h"
#include "platform.h"


#if OS_LINUX

int read_proc_file(const char *file, memsize_t *val, char *field, int fieldlen)
{
  size_t len = 0;
  char *tmp;
  memsize_t value = FAILURE;
  
  *val = 0L;
  
  FILE* fp = fopen(file, "r");
  
  if (fp != NULL)
  {
    while (getline(&tmp, &len, fp) >= 0)
    {
      if (strncmp(tmp, field, fieldlen) == 0)
      {
        sscanf(tmp, "%*s%ld", &value);
        break;
      }
    }
    
    fclose(fp);
    free(tmp);
    
    if (value != FAILURE)
    {
      *val = value;
      return MEMINFO_OK;
    }
  }
  
  return FAILURE;
}

int read_proc_self_stat(runtime_t *val, const int n)
{
  int i;
  int spaces = 0, last_space = 0;
  char *line = NULL;
  size_t linelen = 0;
  memsize_t value = FAILURE;
  char *end;
  
  uint64_t tmp = 0L;
  *val = 0.;
  
  FILE* fp = fopen("/proc/self/stat", "r");
  if (fp == NULL)
    return FAILURE;
  
  linelen = getline(&line, &linelen, fp);
  
  for (i=0; i<linelen; i++)
  {
    if (line[i] == ' ')
    {
      spaces++;
      
      if (spaces == n)
        tmp = strtoull(line+last_space, &end, 10);
      else
        last_space = i;
    }
  }
  
  *val = (runtime_t) tmp;
  
  free(line);
  fclose(fp);
  
  return MEMINFO_OK;
}



#elif OS_MAC || OS_FREEBSD

int sysctl_mib(char *name, int *mib, size_t *mibsize){
  return sysctlnametomib(name,mib,mibsize);
}

int sysctlmib_val(int *mib, size_t mibsize, void *data, size_t *datasize){
  return sysctl(mib, mibsize+1, data, datasize, NULL, 0);
}

int sysctl_val(char *name, memsize_t *val)
{
  int ret;
  size_t vallen;
  vallen = sizeof(*val);
  
  ret = sysctlbyname(name, val, &vallen, NULL, 0);
  
  return ret;
}




#elif OS_WINDOWS

void FILETIMEtoULI(FILETIME *ft, ULARGE_INTEGER *uli)
{
  uli->LowPart   = ft->dwLowDateTime;
  uli->HighPart  = ft->dwHighDateTime;
}

// ft1 - ft2
runtime_t FILETIMEdiff(FILETIME *ft1, FILETIME *ft2)
{
  runtime_t ut;
  
  ULARGE_INTEGER uli1, uli2;
  
  FILETIMEtoULI(ft1, &uli1);
  FILETIMEtoULI(ft2, &uli2);
  
  ut = (runtime_t) (uli1.QuadPart - uli2.QuadPart) * 1e-7;
  
  return ut;
}

#endif

