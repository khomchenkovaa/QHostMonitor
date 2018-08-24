#!/bin/sh
#[Name] USER: # of sessions
#[Hint] Params: <UserName>  <MinLimit>  <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.0
#[Date] 04.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
#Purpose:    Checks the number of processes started by specified user
#
#Parameters:
#- UserName: user's login name
#- MaxLimit: script sets "Bad" status when the user has more running
#            processes then specified limit
#
#Tested on :
# - AIX 5.3                 - NetBSD 3.0.1
# - Linux Mandrake 9.1      - FreeBSD 4.5
# - Solaris 9               - OpenBSD 3.9
#--------------------------------------------------------------------
#[History]
# Feb 01, 2004	v 1.0	KS-Soft: Just released

if [ $# -ge 3 ]
then
  w -h | awk '\
    BEGIN { count=0 } $1=="'$1'"{count++} \
    END {\
      if ((count<'$2')||(count>'$3')) {printf("ScriptRes:Bad:%d\n",count)}\
                    else {printf("ScriptRes:Ok:%d\n",count)} }'
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
