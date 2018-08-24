#!/bin/sh
#[Name] Process: VM usage
#[Hint] Params: <ProcName>  <MaxLimit (Kb)>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 04.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
# Purpose:    Checks virtual memory usage for the specified process. 
# Comment:    If there are several processes with the same name, script 
#            chooses process with max amount of memory usage
# Parameters:  
# - ProcName: name of the process that has to be checked. On Solaris you 
#            should specify first 8 characters of the base name of the 
#            process's executable file name 
# - MaxLimit: script sets "Bad" status when virtual memory usage by the 
#            process is over specified limit (Kb) 
# Tested on:  
# - AIX 5.3                 - NetBSD 3.0.1    - OpenBSD 3.9
# - Linux Mandrake 9.1      - FreeBSD 4.5     - Solaris 9 
#--------------------------------------------------------------------
#[History]
# Aug 04, 2017	v 1.3	KS-Soft: macOS support
# Nov 07, 2006	v 1.2	KS-Soft: NetBSD, OpenBSD support
# Oct 07, 2006	v 1.1	KS-Soft: AIX support
# Feb 01, 2004	v 1.0	KS-Soft: Just released

if [ $# -ge 2 ]
then
  OS=`uname`
  case $OS in
    AIX) PSLIST='ps -Ao comm,vsz';;
    Linux) PSLIST='ps -eo ucmd,vsize O-v';;
    Darwin)  PSLIST='ps -axco command,vsz';;
    FreeBSD) PSLIST='ps -axco command,vsz';;
    NetBSD)  PSLIST='ps -axco command,vsz';;
    OpenBSD) PSLIST='ps -axco command,vsz';;
    SunOS) PSLIST='ps -eo fname,vsz';;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  $PSLIST|awk 'BEGIN {size=0} $1=="'$1'"{if ($2>size) {size=$2}} \
    END {\
      if (size<='$2') {printf("ScriptRes:Ok:%d Kb\n",size)} else {printf("ScriptRes:Bad:%d Kb\n",size)} }'
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
