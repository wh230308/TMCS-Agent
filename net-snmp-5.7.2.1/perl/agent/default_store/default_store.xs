#if defined(_WIN32) && !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x501
#endif

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/agent/ds_agent.h>


/* autogenerated by "gen" from const-c.inc */

#define PERL_constant_NOTFOUND	1
#define PERL_constant_NOTDEF	2
#define PERL_constant_ISIV	3
#define PERL_constant_ISNO	4
#define PERL_constant_ISNV	5
#define PERL_constant_ISPV	6
#define PERL_constant_ISPVN	7
#define PERL_constant_ISSV	8
#define PERL_constant_ISUNDEF	9
#define PERL_constant_ISUV	10
#define PERL_constant_ISYES	11

#ifndef NVTYPE
typedef double NV; /* 5.6 and later define NVTYPE, and typedef NV to it.  */
#endif
#ifndef aTHX_
#define aTHX_ /* 5.6 or later define this for threading support.  */
#endif
#ifndef pTHX_
#define pTHX_ /* 5.6 or later define this for threading support.  */
#endif

static int
constant_22 (pTHX_ const char *name, IV *iv_return) {
  /* When generated this function returned values for the list of names given
     here.  However, subsequent manual editing may have added or removed some.
     NETSNMP_DS_AGENT_FLAGS NETSNMP_DS_AGENT_PORTS NETSNMP_DS_SMUX_SOCKET */
  /* Offset 17 gives the best switch position.  */
  switch (name[17]) {
  case 'F':
    if (memEQ(name, "NETSNMP_DS_AGENT_FLAGS", 22)) {
    /*                                ^           */
#ifdef NETSNMP_DS_AGENT_FLAGS
      *iv_return = NETSNMP_DS_AGENT_FLAGS;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'O':
    if (memEQ(name, "NETSNMP_DS_SMUX_SOCKET", 22)) {
    /*                                ^           */
#ifdef NETSNMP_DS_SMUX_SOCKET
      *iv_return = NETSNMP_DS_SMUX_SOCKET;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'P':
    if (memEQ(name, "NETSNMP_DS_AGENT_PORTS", 22)) {
    /*                                ^           */
#ifdef NETSNMP_DS_AGENT_PORTS
      *iv_return = NETSNMP_DS_AGENT_PORTS;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  }
  return PERL_constant_NOTFOUND;
}

static int
constant_24 (pTHX_ const char *name, IV *iv_return) {
  /* When generated this function returned values for the list of names given
     here.  However, subsequent manual editing may have added or removed some.
     NETSNMP_DS_AGENT_GROUPID NETSNMP_DS_AGENT_VERBOSE NETSNMP_DS_NOTIF_LOG_CTX
     */
  /* Offset 19 gives the best switch position.  */
  switch (name[19]) {
  case 'G':
    if (memEQ(name, "NETSNMP_DS_NOTIF_LOG_CTX", 24)) {
    /*                                  ^           */
#ifdef NETSNMP_DS_NOTIF_LOG_CTX
      *iv_return = NETSNMP_DS_NOTIF_LOG_CTX;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'O':
    if (memEQ(name, "NETSNMP_DS_AGENT_GROUPID", 24)) {
    /*                                  ^           */
#ifdef NETSNMP_DS_AGENT_GROUPID
      *iv_return = NETSNMP_DS_AGENT_GROUPID;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'R':
    if (memEQ(name, "NETSNMP_DS_AGENT_VERBOSE", 24)) {
    /*                                  ^           */
#ifdef NETSNMP_DS_AGENT_VERBOSE
      *iv_return = NETSNMP_DS_AGENT_VERBOSE;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  }
  return PERL_constant_NOTFOUND;
}

static int
constant_30 (pTHX_ const char *name, IV *iv_return) {
  /* When generated this function returned values for the list of names given
     here.  However, subsequent manual editing may have added or removed some.
     NETSNMP_DS_AGENT_AGENTX_MASTER NETSNMP_DS_AGENT_CACHE_TIMEOUT
     NETSNMP_DS_AGENT_LEAVE_PIDFILE NETSNMP_DS_AGENT_STRICT_DISMAN */
  /* Offset 27 gives the best switch position.  */
  switch (name[27]) {
  case 'I':
    if (memEQ(name, "NETSNMP_DS_AGENT_LEAVE_PIDFILE", 30)) {
    /*                                          ^         */
#ifdef NETSNMP_DS_AGENT_LEAVE_PIDFILE
      *iv_return = NETSNMP_DS_AGENT_LEAVE_PIDFILE;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'M':
    if (memEQ(name, "NETSNMP_DS_AGENT_STRICT_DISMAN", 30)) {
    /*                                          ^         */
#ifdef NETSNMP_DS_AGENT_STRICT_DISMAN
      *iv_return = NETSNMP_DS_AGENT_STRICT_DISMAN;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'O':
    if (memEQ(name, "NETSNMP_DS_AGENT_CACHE_TIMEOUT", 30)) {
    /*                                          ^         */
#ifdef NETSNMP_DS_AGENT_CACHE_TIMEOUT
      *iv_return = NETSNMP_DS_AGENT_CACHE_TIMEOUT;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'T':
    if (memEQ(name, "NETSNMP_DS_AGENT_AGENTX_MASTER", 30)) {
    /*                                          ^         */
#ifdef NETSNMP_DS_AGENT_AGENTX_MASTER
      *iv_return = NETSNMP_DS_AGENT_AGENTX_MASTER;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  }
  return PERL_constant_NOTFOUND;
}

static int
constant_31 (pTHX_ const char *name, IV *iv_return) {
  /* When generated this function returned values for the list of names given
     here.  However, subsequent manual editing may have added or removed some.
     NETSNMP_DS_AGENT_AGENTX_RETRIES NETSNMP_DS_AGENT_AGENTX_TIMEOUT
     NETSNMP_DS_AGENT_NO_ROOT_ACCESS NETSNMP_DS_AGENT_PERL_INIT_FILE */
  /* Offset 27 gives the best switch position.  */
  switch (name[27]) {
  case 'C':
    if (memEQ(name, "NETSNMP_DS_AGENT_NO_ROOT_ACCESS", 31)) {
    /*                                          ^          */
#ifdef NETSNMP_DS_AGENT_NO_ROOT_ACCESS
      *iv_return = NETSNMP_DS_AGENT_NO_ROOT_ACCESS;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'E':
    if (memEQ(name, "NETSNMP_DS_AGENT_AGENTX_TIMEOUT", 31)) {
    /*                                          ^          */
#ifdef NETSNMP_DS_AGENT_AGENTX_TIMEOUT
      *iv_return = NETSNMP_DS_AGENT_AGENTX_TIMEOUT;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'F':
    if (memEQ(name, "NETSNMP_DS_AGENT_PERL_INIT_FILE", 31)) {
    /*                                          ^          */
#ifdef NETSNMP_DS_AGENT_PERL_INIT_FILE
      *iv_return = NETSNMP_DS_AGENT_PERL_INIT_FILE;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'R':
    if (memEQ(name, "NETSNMP_DS_AGENT_AGENTX_RETRIES", 31)) {
    /*                                          ^          */
#ifdef NETSNMP_DS_AGENT_AGENTX_RETRIES
      *iv_return = NETSNMP_DS_AGENT_AGENTX_RETRIES;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  }
  return PERL_constant_NOTFOUND;
}

static int
constant_33 (pTHX_ const char *name, IV *iv_return) {
  /* When generated this function returned values for the list of names given
     here.  However, subsequent manual editing may have added or removed some.
     NETSNMP_DS_AGENT_INTERNAL_SECNAME NETSNMP_DS_AGENT_INTERNAL_VERSION
     NETSNMP_DS_AGENT_QUIT_IMMEDIATELY */
  /* Offset 31 gives the best switch position.  */
  switch (name[31]) {
  case 'L':
    if (memEQ(name, "NETSNMP_DS_AGENT_QUIT_IMMEDIATELY", 33)) {
    /*                                              ^        */
#ifdef NETSNMP_DS_AGENT_QUIT_IMMEDIATELY
      *iv_return = NETSNMP_DS_AGENT_QUIT_IMMEDIATELY;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'M':
    if (memEQ(name, "NETSNMP_DS_AGENT_INTERNAL_SECNAME", 33)) {
    /*                                              ^        */
#ifdef NETSNMP_DS_AGENT_INTERNAL_SECNAME
      *iv_return = NETSNMP_DS_AGENT_INTERNAL_SECNAME;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 'O':
    if (memEQ(name, "NETSNMP_DS_AGENT_INTERNAL_VERSION", 33)) {
    /*                                              ^        */
#ifdef NETSNMP_DS_AGENT_INTERNAL_VERSION
      *iv_return = NETSNMP_DS_AGENT_INTERNAL_VERSION;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  }
  return PERL_constant_NOTFOUND;
}

static int
constant (pTHX_ const char *name, STRLEN len, IV *iv_return) {
  /* Initially switch on the length of the name.  */
  /* When generated this function returned values for the list of names given
     in this section of perl code.  Rather than manually editing these functions
     to add or remove constants, which would result in this comment and section
     of code becoming inaccurate, we recommend that you edit this section of
     code, and use it to regenerate a new set of constant functions which you
     then use to replace the originals.

     Regenerate these constant functions by feeding this entire source file to
     perl -x

#!/usr/bin/perl -w
use ExtUtils::Constant qw (constant_types C_constant XS_constant);

my $types = {map {($_, 1)} qw(IV)};
my @names = (qw(NETSNMP_DS_AGENT_AGENTX_MASTER
	       NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL
	       NETSNMP_DS_AGENT_AGENTX_RETRIES NETSNMP_DS_AGENT_AGENTX_TIMEOUT
	       NETSNMP_DS_AGENT_CACHE_TIMEOUT NETSNMP_DS_AGENT_DISABLE_PERL
	       NETSNMP_DS_AGENT_DONT_LOG_TCPWRAPPERS_CONNECTS
	       NETSNMP_DS_AGENT_DONT_RETAIN_NOTIFICATIONS
	       NETSNMP_DS_AGENT_FLAGS NETSNMP_DS_AGENT_GROUPID
	       NETSNMP_DS_AGENT_INTERNAL_SECLEVEL
	       NETSNMP_DS_AGENT_INTERNAL_SECNAME
	       NETSNMP_DS_AGENT_INTERNAL_VERSION NETSNMP_DS_AGENT_LEAVE_PIDFILE
	       NETSNMP_DS_AGENT_MAX_GETBULKREPEATS
	       NETSNMP_DS_AGENT_MAX_GETBULKRESPONSES
	       NETSNMP_DS_AGENT_NO_CACHING
	       NETSNMP_DS_AGENT_NO_CONNECTION_WARNINGS
	       NETSNMP_DS_AGENT_NO_ROOT_ACCESS NETSNMP_DS_AGENT_PERL_INIT_FILE
	       NETSNMP_DS_AGENT_PORTS NETSNMP_DS_AGENT_PROGNAME
	       NETSNMP_DS_AGENT_QUIT_IMMEDIATELY NETSNMP_DS_AGENT_ROLE
	       NETSNMP_DS_AGENT_SKIPNFSINHOSTRESOURCES
	       NETSNMP_DS_AGENT_STRICT_DISMAN NETSNMP_DS_AGENT_USERID
	       NETSNMP_DS_AGENT_VERBOSE NETSNMP_DS_AGENT_X_DIR_PERM
	       NETSNMP_DS_AGENT_X_SOCKET NETSNMP_DS_AGENT_X_SOCK_GROUP
	       NETSNMP_DS_AGENT_X_SOCK_PERM NETSNMP_DS_AGENT_X_SOCK_USER
	       NETSNMP_DS_APP_DONT_LOG NETSNMP_DS_NOTIF_LOG_CTX
	       NETSNMP_DS_SMUX_SOCKET));

print constant_types(); # macro defs
foreach (C_constant ("NetSNMP::agent::default_store", 'constant', 'IV', $types, undef, 3, @names) ) {
    print $_, "\n"; # C constant subs
}
print "#### XS Section:\n";
print XS_constant ("NetSNMP::agent::default_store", $types);
__END__
   */

  switch (len) {
  case 21:
    if (memEQ(name, "NETSNMP_DS_AGENT_ROLE", 21)) {
#ifdef NETSNMP_DS_AGENT_ROLE
      *iv_return = NETSNMP_DS_AGENT_ROLE;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 22:
    return constant_22 (aTHX_ name, iv_return);
    break;
  case 23:
    /* Names all of length 23.  */
    /* NETSNMP_DS_AGENT_USERID NETSNMP_DS_APP_DONT_LOG */
    /* Offset 18 gives the best switch position.  */
    switch (name[18]) {
    case 'S':
      if (memEQ(name, "NETSNMP_DS_AGENT_USERID", 23)) {
      /*                                 ^           */
#ifdef NETSNMP_DS_AGENT_USERID
        *iv_return = NETSNMP_DS_AGENT_USERID;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'T':
      if (memEQ(name, "NETSNMP_DS_APP_DONT_LOG", 23)) {
      /*                                 ^           */
#ifdef NETSNMP_DS_APP_DONT_LOG
        *iv_return = NETSNMP_DS_APP_DONT_LOG;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 24:
    return constant_24 (aTHX_ name, iv_return);
    break;
  case 25:
    /* Names all of length 25.  */
    /* NETSNMP_DS_AGENT_PROGNAME NETSNMP_DS_AGENT_X_SOCKET */
    /* Offset 19 gives the best switch position.  */
    switch (name[19]) {
    case 'O':
      if (memEQ(name, "NETSNMP_DS_AGENT_PROGNAME", 25)) {
      /*                                  ^            */
#ifdef NETSNMP_DS_AGENT_PROGNAME
        *iv_return = NETSNMP_DS_AGENT_PROGNAME;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'S':
      if (memEQ(name, "NETSNMP_DS_AGENT_X_SOCKET", 25)) {
      /*                                  ^            */
#ifdef NETSNMP_DS_AGENT_X_SOCKET
        *iv_return = NETSNMP_DS_AGENT_X_SOCKET;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 27:
    /* Names all of length 27.  */
    /* NETSNMP_DS_AGENT_NO_CACHING NETSNMP_DS_AGENT_X_DIR_PERM */
    /* Offset 24 gives the best switch position.  */
    switch (name[24]) {
    case 'E':
      if (memEQ(name, "NETSNMP_DS_AGENT_X_DIR_PERM", 27)) {
      /*                                       ^         */
#ifdef NETSNMP_DS_AGENT_X_DIR_PERM
        *iv_return = NETSNMP_DS_AGENT_X_DIR_PERM;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'I':
      if (memEQ(name, "NETSNMP_DS_AGENT_NO_CACHING", 27)) {
      /*                                       ^         */
#ifdef NETSNMP_DS_AGENT_NO_CACHING
        *iv_return = NETSNMP_DS_AGENT_NO_CACHING;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 28:
    /* Names all of length 28.  */
    /* NETSNMP_DS_AGENT_X_SOCK_PERM NETSNMP_DS_AGENT_X_SOCK_USER */
    /* Offset 27 gives the best switch position.  */
    switch (name[27]) {
    case 'M':
      if (memEQ(name, "NETSNMP_DS_AGENT_X_SOCK_PER", 27)) {
      /*                                          M      */
#ifdef NETSNMP_DS_AGENT_X_SOCK_PERM
        *iv_return = NETSNMP_DS_AGENT_X_SOCK_PERM;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'R':
      if (memEQ(name, "NETSNMP_DS_AGENT_X_SOCK_USE", 27)) {
      /*                                          R      */
#ifdef NETSNMP_DS_AGENT_X_SOCK_USER
        *iv_return = NETSNMP_DS_AGENT_X_SOCK_USER;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 29:
    /* Names all of length 29.  */
    /* NETSNMP_DS_AGENT_DISABLE_PERL NETSNMP_DS_AGENT_X_SOCK_GROUP */
    /* Offset 21 gives the best switch position.  */
    switch (name[21]) {
    case 'B':
      if (memEQ(name, "NETSNMP_DS_AGENT_DISABLE_PERL", 29)) {
      /*                                    ^              */
#ifdef NETSNMP_DS_AGENT_DISABLE_PERL
        *iv_return = NETSNMP_DS_AGENT_DISABLE_PERL;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'C':
      if (memEQ(name, "NETSNMP_DS_AGENT_X_SOCK_GROUP", 29)) {
      /*                                    ^              */
#ifdef NETSNMP_DS_AGENT_X_SOCK_GROUP
        *iv_return = NETSNMP_DS_AGENT_X_SOCK_GROUP;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 30:
    return constant_30 (aTHX_ name, iv_return);
    break;
  case 31:
    return constant_31 (aTHX_ name, iv_return);
    break;
  case 33:
    return constant_33 (aTHX_ name, iv_return);
    break;
  case 34:
    if (memEQ(name, "NETSNMP_DS_AGENT_INTERNAL_SECLEVEL", 34)) {
#ifdef NETSNMP_DS_AGENT_INTERNAL_SECLEVEL
      *iv_return = NETSNMP_DS_AGENT_INTERNAL_SECLEVEL;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 35:
    if (memEQ(name, "NETSNMP_DS_AGENT_MAX_GETBULKREPEATS", 35)) {
#ifdef NETSNMP_DS_AGENT_MAX_GETBULKREPEATS
      *iv_return = NETSNMP_DS_AGENT_MAX_GETBULKREPEATS;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 37:
    /* Names all of length 37.  */
    /* NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL
       NETSNMP_DS_AGENT_MAX_GETBULKRESPONSES */
    /* Offset 26 gives the best switch position.  */
    switch (name[26]) {
    case 'L':
      if (memEQ(name, "NETSNMP_DS_AGENT_MAX_GETBULKRESPONSES", 37)) {
      /*                                         ^                 */
#ifdef NETSNMP_DS_AGENT_MAX_GETBULKRESPONSES
        *iv_return = NETSNMP_DS_AGENT_MAX_GETBULKRESPONSES;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'N':
      if (memEQ(name, "NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL", 37)) {
      /*                                         ^                 */
#ifdef NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL
        *iv_return = NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 39:
    /* Names all of length 39.  */
    /* NETSNMP_DS_AGENT_NO_CONNECTION_WARNINGS
       NETSNMP_DS_AGENT_SKIPNFSINHOSTRESOURCES */
    /* Offset 21 gives the best switch position.  */
    switch (name[21]) {
    case 'N':
      if (memEQ(name, "NETSNMP_DS_AGENT_SKIPNFSINHOSTRESOURCES", 39)) {
      /*                                    ^                        */
#ifdef NETSNMP_DS_AGENT_SKIPNFSINHOSTRESOURCES
        *iv_return = NETSNMP_DS_AGENT_SKIPNFSINHOSTRESOURCES;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    case 'O':
      if (memEQ(name, "NETSNMP_DS_AGENT_NO_CONNECTION_WARNINGS", 39)) {
      /*                                    ^                        */
#ifdef NETSNMP_DS_AGENT_NO_CONNECTION_WARNINGS
        *iv_return = NETSNMP_DS_AGENT_NO_CONNECTION_WARNINGS;
        return PERL_constant_ISIV;
#else
        return PERL_constant_NOTDEF;
#endif
      }
      break;
    }
    break;
  case 42:
    if (memEQ(name, "NETSNMP_DS_AGENT_DONT_RETAIN_NOTIFICATIONS", 42)) {
#ifdef NETSNMP_DS_AGENT_DONT_RETAIN_NOTIFICATIONS
      *iv_return = NETSNMP_DS_AGENT_DONT_RETAIN_NOTIFICATIONS;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  case 46:
    if (memEQ(name, "NETSNMP_DS_AGENT_DONT_LOG_TCPWRAPPERS_CONNECTS", 46)) {
#ifdef NETSNMP_DS_AGENT_DONT_LOG_TCPWRAPPERS_CONNECTS
      *iv_return = NETSNMP_DS_AGENT_DONT_LOG_TCPWRAPPERS_CONNECTS;
      return PERL_constant_ISIV;
#else
      return PERL_constant_NOTDEF;
#endif
    }
    break;
  }
  return PERL_constant_NOTFOUND;
}



/* autogenerated by "gen" from const-xs.inc */

MODULE = NetSNMP::agent::default_store         PACKAGE = NetSNMP::agent::default_store

void
constant(sv)
    PREINIT:
#ifdef dXSTARG
	dXSTARG; /* Faster if we have it.  */
#else
	dTARGET;
#endif
	STRLEN		len;
        int		type;
	IV		iv = 0;
	/* NV		nv;	Uncomment this if you need to return NVs */
	/* const char	*pv;	Uncomment this if you need to return PVs */
    INPUT:
	SV *		sv;
        const char *	s = SvPV(sv, len);
    PPCODE:
        /* Change this to constant(aTHX_ s, len, &iv, &nv);
           if you need to return both NVs and IVs */
	type = constant(aTHX_ s, len, &iv);
      /* Return 1 or 2 items. First is error message, or undef if no error.
           Second, if present, is found value */
        switch (type) {
        case PERL_constant_NOTFOUND:
          sv = sv_2mortal(newSVpvf("%s is not a valid NetSNMP::agent::default_store macro", s));
          PUSHs(sv);
          break;
        case PERL_constant_NOTDEF:
          sv = sv_2mortal(newSVpvf(
	    "Your vendor has not defined NetSNMP::agent::default_store macro %s, used", s));
          PUSHs(sv);
          break;
        case PERL_constant_ISIV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHi(iv);
          break;
	/* Uncomment this if you need to return NOs
        case PERL_constant_ISNO:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHs(&PL_sv_no);
          break; */
	/* Uncomment this if you need to return NVs
        case PERL_constant_ISNV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHn(nv);
          break; */
	/* Uncomment this if you need to return PVs
        case PERL_constant_ISPV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHp(pv, strlen(pv));
          break; */
	/* Uncomment this if you need to return PVNs
        case PERL_constant_ISPVN:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHp(pv, iv);
          break; */
	/* Uncomment this if you need to return SVs
        case PERL_constant_ISSV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHs(sv);
          break; */
	/* Uncomment this if you need to return UNDEFs
        case PERL_constant_ISUNDEF:
          break; */
	/* Uncomment this if you need to return UVs
        case PERL_constant_ISUV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHu((UV)iv);
          break; */
	/* Uncomment this if you need to return YESs
        case PERL_constant_ISYES:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHs(&PL_sv_yes);
          break; */
        default:
          sv = sv_2mortal(newSVpvf(
	    "Unexpected return type %d while processing NetSNMP::agent::default_store macro %s, used",
               type, s));
          PUSHs(sv);
        }



