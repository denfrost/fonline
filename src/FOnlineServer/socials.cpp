
#include "stdafx.h"

#include <string.h>
#include <stdio.h>

#include <FOnlineCommon/Common.hpp>

#include "socials.h"
#include "main.h"

soc_def* socials=NULL;

int SocLoaded=0;
int SocialsCount=0;

void LoadSocials(/*MYSQL* mysql*/)
{
  FONLINE_LOG("Loading socials...");

  /*if(mysql_query(mysql,"select * from socials"))
  {
    FONLINE_LOG("SQL error: %s",mysql_error(mysql));
    return;
  }

  MYSQL_RES* res=mysql_store_result(mysql);

  SocialsCount=(int)mysql_num_rows(res);

  if(SocialsCount)
  {
    socials=new soc_def[SocialsCount];

    MYSQL_ROW row;
    int i=0;
    while((row=mysql_fetch_row(res)))
    {
      strcpy(socials[i].cmd,row[1]);
      strcpy(socials[i].NoVictimSelf,row[2]);
      strcpy(socials[i].NoVictimAll,row[3]);
      strcpy(socials[i].VictimSelf,row[4]);
      strcpy(socials[i].VictimAll,row[5]);
      strcpy(socials[i].VictimVictim,row[6]);
      strcpy(socials[i].VictimErr,row[7]);
      strcpy(socials[i].SelfSelf,row[8]);
      strcpy(socials[i].SelfAll,row[9]);
      i++;
    }
  }

  mysql_free_result(res);*/

  //// HACK[22.9.2012 alex]: do not laod socials
  if(SocialsCount); SocLoaded=1;
}

void UnloadSocials()
{
  if(socials) delete[] socials;
}

#define GEN_MALE  0
#define GEN_FEM   1
#define GEN_IT    2
#define GEN_MANY  3

char str_m[][20]={"его", "ее", "его", "их"};
char str_s[][20]={"его", "ее", "его", "их"};
char str_e[][20]={"он", "она", "оно", "они"};
char str_q[][20]={"", "ла", "ло", "ли"};
char str_w[][20]={"ый", "ая", "ое", "ые"};
char str_y[][20]={"", "а", "о", "и"};
char str_u[][20]={"ся", "ась", "ось", "ись"};
char str_i[][20]={"ел", "ла", "ло", "ли"};
char str_g[][20]={"ым", "ой", "ым", "ыми"};
char str_h[][20]={"ему", "ей", "ему", "им"};
char str_j[][20]={"ним", "ней", "ним", "ними"};
char str_k[][20]={"нем", "ней", "нем", "них"};

char* MakeName(char* str, char* str2) {
  strcpy(str2,str);
  str2[0]-=0x20;
  return str2;
}


void ParseSymbolStr(char* symstr,char* resstr, crit_info* self, crit_info* victim)
{
  char selfname[MAX_NAME+1];
  char vicname[MAX_NAME+1];

  char selfcase[MAX_NAME+1];
  char viccase[MAX_NAME+1];

  uint8_t selfgen;
  uint8_t vicgen;

  if(self)
  {
    switch(self->st[ST_GENDER])
    {
    case 0:
      selfgen=GEN_MALE;
      break;
    case 1:
      selfgen=GEN_FEM;
      break;
    case 2:
      selfgen=GEN_IT;
      break;
    default:
      selfgen=GEN_MANY;
    }
  }
  else selfgen=GEN_MANY;

  if(victim)
  {
    switch(victim->st[ST_GENDER])
    {
    case 0:
      vicgen=GEN_MALE;
      break;
    case 1:
      vicgen=GEN_FEM;
      break;
    case 2:
      vicgen=GEN_IT;
      break;
    default:
      vicgen=GEN_MANY;
    }
  }
  else vicgen=GEN_MANY;

  int wpos=0;
  for(int i=0;symstr[i];i++)
  {
    if(symstr[i]!='$') resstr[wpos++]=symstr[i];
    else
      {
        switch(symstr[++i])
        {
        case 'n':
          strcpy(selfname,self->name);
          if(i==1) MakeName(selfname,selfname);
          int j;
          for(j=0;selfname[j];j++)
            resstr[wpos++]=selfname[j];
          break;
        case 'N':
          strcpy(vicname,victim->name);
          if(i==1) MakeName(vicname,vicname);
          for(j=0;vicname[j];j++)
            resstr[wpos++]=vicname[j];
          break;
        case 'r':
          strcpy(selfcase,self->cases[0]);
          if(i==1) MakeName(selfcase,selfcase);
          for(j=0;selfcase[j];j++)
            resstr[wpos++]=selfcase[j];
          break;
        case 'R':
          strcpy(viccase,victim->cases[0]);
          if(i==1) MakeName(viccase,viccase);
          for(j=0;viccase[j];j++)
            resstr[wpos++]=viccase[j];
          break;
        case 'd':
          strcpy(selfcase,self->cases[1]);
          if(i==1) MakeName(selfcase,selfcase);
          for(j=0;selfcase[j];j++)
            resstr[wpos++]=selfcase[j];
          break;
        case 'D':
          strcpy(viccase,victim->cases[1]);
          if(i==1) MakeName(viccase,viccase);
          for(j=0;viccase[j];j++)
            resstr[wpos++]=viccase[j];
          break;
        case 'v':
          strcpy(selfcase,self->cases[2]);
          if(i==1) MakeName(selfcase,selfcase);
          for(j=0;selfcase[j];j++)
            resstr[wpos++]=selfcase[j];
          break;
        case 'V':
          strcpy(viccase,victim->cases[2]);
          if(i==1) MakeName(viccase,viccase);
          for(j=0;viccase[j];j++)
            resstr[wpos++]=viccase[j];
          break;
        case 't':
          strcpy(selfcase,self->cases[3]);
          if(i==1) MakeName(selfcase,selfcase);
          for(j=0;selfcase[j];j++)
            resstr[wpos++]=selfcase[j];
          break;
        case 'T':
          strcpy(viccase,victim->cases[3]);
          if(i==1) MakeName(viccase,viccase);
          for(j=0;viccase[j];j++)
            resstr[wpos++]=viccase[j];
          break;
        case 'p':
          strcpy(selfcase,self->cases[4]);
          if(i==1) MakeName(selfcase,selfcase);
          for(j=0;selfcase[j];j++)
            resstr[wpos++]=selfcase[j];
          break;
        case 'P':
          strcpy(viccase,victim->cases[4]);
          if(i==1) MakeName(viccase,viccase);
          for(j=0;viccase[j];j++)
            resstr[wpos++]=viccase[j];
          break;
        case 'M':
        case 'S':
          for(j=0;str_m[vicgen][j];j++)
            resstr[wpos++]=str_m[vicgen][j];
          break;
        case 'E':
          for(j=0;str_e[vicgen][j];j++)
            resstr[wpos++]=str_e[vicgen][j];
          break;
        case 'Q':
          for(j=0;str_q[vicgen][j];j++)
            resstr[wpos++]=str_q[vicgen][j];
          break;
        case 'W':
          for(j=0;str_w[vicgen][j];j++)
            resstr[wpos++]=str_w[vicgen][j];
          break;
        case 'Y':
          for(j=0;str_y[vicgen][j];j++)
            resstr[wpos++]=str_y[vicgen][j];
          break;
        case 'U':
          for(j=0;str_u[vicgen][j];j++)
            resstr[wpos++]=str_u[vicgen][j];
          break;
        case 'I':
          for(j=0;str_i[vicgen][j];j++)
            resstr[wpos++]=str_i[vicgen][j];
          break;
        case 'G':
          for(j=0;str_g[vicgen][j];j++)
            resstr[wpos++]=str_g[vicgen][j];
          break;
        case 'H':
          for(j=0;str_h[vicgen][j];j++)
            resstr[wpos++]=str_h[vicgen][j];
          break;
        case 'J':
          for(j=0;str_j[vicgen][j];j++)
            resstr[wpos++]=str_j[vicgen][j];
          break;
        case 'K':
          for(j=0;str_k[vicgen][j];j++)
            resstr[wpos++]=str_k[vicgen][j];
          break;
        case 'm':
        case 's':
          for(j=0;str_m[selfgen][j];j++)
            resstr[wpos++]=str_m[selfgen][j];
          break;
        case 'e':
          for(j=0;str_e[selfgen][j];j++)
            resstr[wpos++]=str_e[selfgen][j];
          break;
        case 'q':
          for(j=0;str_q[selfgen][j];j++)
            resstr[wpos++]=str_q[selfgen][j];
          break;
        case 'w':
          for(j=0;str_w[selfgen][j];j++)
            resstr[wpos++]=str_w[selfgen][j];
          break;
        case 'y':
          for(j=0;str_y[selfgen][j];j++)
            resstr[wpos++]=str_y[selfgen][j];
          break;
        case 'u':
          for(j=0;str_u[selfgen][j];j++)
            resstr[wpos++]=str_u[selfgen][j];
          break;
        case 'i':
          for(j=0;str_i[selfgen][j];j++)
            resstr[wpos++]=str_i[selfgen][j];
          break;
        case 'g':
          for(j=0;str_g[selfgen][j];j++)
            resstr[wpos++]=str_g[selfgen][j];
          break;
        case 'h':
          for(j=0;str_h[selfgen][j];j++)
            resstr[wpos++]=str_h[selfgen][j];
          break;
        case 'j':
          for(j=0;str_j[selfgen][j];j++)
            resstr[wpos++]=str_j[selfgen][j];
          break;
        case 'k':
          for(j=0;str_k[selfgen][j];j++)
            resstr[wpos++]=str_k[selfgen][j];
          break;
        default:
          resstr[wpos++]=symstr[i];
        }//switch
      }// if ! $
  }//for
  resstr[wpos]=0;
}

int PartialRight(char* str,char* et)
{
  int res=1;

  for(int i=0;str[i];i++)
    if(!et[i] || str[i]!=et[i]) return 0;

  return res;
}

int GetSocialId(char* cmd)
{
  if(!SocLoaded) return -1;

  FONLINE_LOG("TrySocial: %s",cmd);

  for(int i=0;i<SocialsCount;i++)
    if(PartialRight(cmd,socials[i].cmd)) {FONLINE_LOG("TrySocial found: %s",socials[i].cmd);return i;}

  FONLINE_LOG("TrySocial: not found!");
  return -1;
}

void GetSocNoStr(int socid, char* SelfStr, char* AllStr, crit_info* self)
{
  if(!SocLoaded) return;
  strcpy(SelfStr,"**");
  strcpy(AllStr,"**");

  ParseSymbolStr(socials[socid].NoVictimSelf,SelfStr+2,self,NULL);
  ParseSymbolStr(socials[socid].NoVictimAll,AllStr+2,self,NULL);
  strcat(SelfStr,"**");
  strcat(AllStr,"**");
}

void GetSocSelfStr(int socid, char* SelfStr, char* AllStr, crit_info* self)
{
  strcpy(SelfStr,"**");
  strcpy(AllStr,"**");
  if(!SocLoaded) return;

  ParseSymbolStr(socials[socid].SelfSelf,SelfStr+2,self,NULL);
  ParseSymbolStr(socials[socid].SelfAll,AllStr+2,self,NULL);
  strcat(SelfStr,"**");
  strcat(AllStr,"**");
}

void GetSocVicStr(int socid, char* SelfStr, char* VicStr, char* AllStr, crit_info* self, crit_info* victim)
{
  strcpy(SelfStr,"**");
  strcpy(VicStr,"**");
  strcpy(AllStr,"**");
  if(!SocLoaded) return;

  ParseSymbolStr(socials[socid].VictimSelf,SelfStr+2,self,victim);
  ParseSymbolStr(socials[socid].VictimVictim,VicStr+2,self,victim);
  ParseSymbolStr(socials[socid].VictimAll,AllStr+2,self,victim);
  strcat(SelfStr,"**");
  strcat(VicStr,"**");
  strcat(AllStr,"**");
}

void GetSocVicErrStr(int socid, char* SelfStr, crit_info* self)
{
  strcpy(SelfStr,"**");
  if(!SocLoaded) return;

  ParseSymbolStr(socials[socid].VictimErr,SelfStr+2,self,NULL);
  strcat(SelfStr,"**");
}

int GetPossParams(int socid)
{
  if(!socials[socid].SelfSelf[0] && !socials[socid].VictimSelf[0]) return SOC_NOPARAMS;
  if(!socials[socid].SelfSelf[0]) return SOC_NOSELF;

  return SOC_PARAMSOK;
}
