#!/bin/sh
#[Name] SYSTEM: # of user sessions
#[Hint] Params: <MinLimit>  <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.0
#[Date] 24.01.2004
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
#Purpose:    Checks how many user sessions are opened on the system.
#
#Parameters:
#- MinLimit: script sets "Bad" status when number of sessions is less 
#            than specified limit. 
#- MaxLimit: script sets "Bad" status when number of sessions is greater 
#            than specified limit. 
#
#Tested on :
# - AIX 5.3                 - NetBSD 3.0.1
# - Linux Mandrake 9.1      - FreeBSD 4.5
# - Solaris 9               - OpenBSD 3.9
#--------------------------------------------------------------------#
[History]
# Feb 01, 2004	v 1.0	KS-Soft: Just released

if [ $# -ge 2 ]
then
  w -h | awk '\
    BEGIN { count=0 } {count++} \
    END {\
      if ((count<'$1')||(count>'$2')) {printf("ScriptRes:Bad:%d\n",count)}\
                    else {printf("ScriptRes:Ok:%d\n",count)} }'
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
