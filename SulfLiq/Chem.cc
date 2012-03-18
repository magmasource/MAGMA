/* 
   Chem implementation
   Victor Kress
   Seattle 7/4/04
   $Id: Chem.cc,v 1.10 2007/07/23 19:55:50 ghiorso Exp $
*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Chem.h"
#include "PhaseExceptions.h"

Chem::Chem() {
  return;
}

Chem::~Chem() {
  return;
}

// Data ///////////////////////////////////////////
const EleProp Chem::ele[] = {{"",0.,""},
			     {"H" ,   1.0079  ,"hydrogen"   },
			     {"He",   4.00260 ,"helium"     },
			     {"Li",   6.94    ,"lithium"    },
			     {"Be",   9.01218 ,"beryllium"  },
			     {"B" ,  10.81    ,"boron"      },
			     {"C" ,  12.011   ,"carbon"     },
			     {"N" ,  14.0067  ,"nitrogen"   },
			     {"O" ,  15.9994  ,"oxygen"     },
			     {"F" ,  18.998403,"fluorine"   },
			     {"Ne",  20.179   ,"neon"       },
			     {"Na",  22.98977 ,"sodium"     },
			     {"Mg",  24.305   ,"magnesium"  },
			     {"Al",  26.98154 ,"aluminum"   },
			     {"Si",  28.0855  ,"silicon"    },
			     {"P" ,  30.97376 ,"phosphorous"},
			     {"S" ,  32.06    ,"sulfur"     },
			     {"Cl",  35.453   ,"chlorine"   },
			     {"Ar",  39.948   ,"argon"      },
			     {"K" ,  39.102   ,"potassium"  },
			     {"Ca",  40.08    ,"calcium"    },
			     {"Sc",  44.9559  ,"scandium"   },
			     {"Ti",  47.90    ,"titanium"   },
			     {"V" ,  50.9415  ,"vanadium"   },
			     {"Cr",  51.996   ,"chromium"   },
			     {"Mn",  54.9380  ,"manganese"  },
			     {"Fe",  55.847   ,"iron"       },
			     {"Co",  58.9332  ,"cobalt"     },
			     {"Ni",  58.71    ,"nickel"     },
			     {"Cu",  63.546   ,"copper"     },
			     {"Zn",  65.38    ,"zinc"       },
			     {"Ga",  69.735   ,"gallium"    },
			     {"Ge",  72.59    ,"germanium"  },
			     {"As",  74.9216  ,"arsenic"    },
			     {"Se",  78.96    ,"selenium"   },
			     {"Br",  79.904   ,"bromine"    },
			     {"Kr",  83.80    ,"krypton"    },
			     {"Rb",  85.4678  ,"rubidium"   },
			     {"Sr",  87.62    ,"strontium"  },
			     {"Y" ,  88.9059  ,"yttrium"    },
			     {"Zr",  91.22    ,"zirconium"  },
			     {"Nb",  92.9064  ,"niobium"    },
			     {"Mo",  95.94    ,"molybdenum" },
			     {"Tc",  98.9062  ,"technetium" },
			     {"Ru", 101.07    ,"ruthenium"  },
			     {"Rh", 102.9055  ,"rhodium"    },
			     {"Pd", 106.4     ,"palladium"  },
			     {"Ag", 107.868   ,"silver"     },
			     {"Cd", 112.41    ,"cadmium"    },
			     {"In", 114.82    ,"indium"     },
			     {"Sn", 118.69    ,"tin"        },
			     {"Sb", 121.75    ,"antimony"   },
			     {"Te", 127.60    ,"tellurium"  },
			     {"I" , 126.9045  ,"iodine"     },
			     {"Xe", 131.30    ,"xenon"      },
			     {"Cs", 132.9054  ,"cesium"     },
			     {"Ba", 137.33    ,"barium"     },
			     {"La", 138.9055  ,"lantahnum"  },
			     {"Ce", 140.12    ,"cerium"     },
			     {"Pr", 140.9077  ,"praseodymium"},
			     {"Nd", 144.24    ,"neodymium"  },
			     {"Pm", 145.      ,"promethium" },
			     {"Sm", 150.4     ,"samarium"   },
			     {"Eu", 151.96    ,"europium"   },
			     {"Gd", 157.25    ,"gadolinium" },
			     {"Tb", 158.9254  ,"terbium"    },
			     {"Dy", 162.50    ,"dysprosium" },
			     {"Ho", 164.9304  ,"holmium"    },
			     {"Er", 167.26    ,"erbium"     },
			     {"Tm", 168.9342  ,"thulium"    },
			     {"Yb", 173.04    ,"ytterbium"  },
			     {"Lu", 174.967   ,"lutetium"   },
			     {"Hf", 178.49    ,"hafnium"    },
			     {"Ta", 180.9479  ,"tantalum"   },
			     {"W" , 183.85    ,"tungsten"   },
			     {"Re", 186.207   ,"rhenium"    },
			     {"Os", 190.2     ,"osmium"     },
			     {"Ir", 192.22    ,"iridium"    },
			     {"Pt", 195.09    ,"platinum"   },
			     {"Au", 196.9665  ,"gold"       },
			     {"Hg", 200.59    ,"mercury"    },
			     {"Tl", 204.37    ,"thallium"   },
			     {"Pb", 207.2     ,"lead"       },
			     {"Bi", 208.9804  ,"bismuth"    },
			     {"Po", 209.      ,"polonium"   },
			     {"At", 210.      ,"astatine"   },
			     {"Rn", 222.      ,"radon"      },
			     {"Fr", 223.      ,"francium"   },
			     {"Ra", 226.0254  ,"radium"     },
			     {"Ac", 227.      ,"actinium"   },
			     {"Th", 232.0381  ,"thorium"    },
			     {"Pa", 231.0359  ,"protactinium"},
			     {"U" , 238.029   ,"uranium"    },
			     {"Np", 237.0482  ,"neptunium"  },
			     {"Pu", 244.      ,"plutonium"  },
			     {"Am", 243.      ,"americium"  },
			     {"Cm", 247.      ,"curium"     },
			     {"Bk", 247.      ,"berkelium"  },
			     {"Cf", 251.      ,"californium"},
			     {"Es", 254.      ,"einsteinium"},
			     {"Fm", 257.      ,"fermium"    },
			     {"Md", 258.      ,"mendelevium"},
			     {"No", 259.      ,"nobelium"   },
			     {"Lw", 260.      ,"lawrencium" },
			     {"Rf", 260.      ,"ruferfordium"},
			     {"Ha", 260.      ,"hahnium"    }
};

const OxProp Chem::ox[] = {
  {"SiO2", 14,1.000000,2.000000, 60.084300},
  {"TiO2", 22,1.000000,2.000000, 79.898800},
  {"Al2O3", 13,2.000000,3.000000, 101.961280},
  {"Cr2O3", 24,2.000000,3.000000, 151.990200},
  {"FeO", 26,1.000000,1.000000, 71.846400},
  {"FeO1.5", 26,1.000000,1.500000, 79.846100},
  {"MnO", 25,1.000000,1.000000, 70.937400},
  {"MgO", 12,1.000000,1.000000, 40.304400},
  {"NiO", 28,1.000000,1.000000, 74.709400},
  {"CoO", 27,1.000000,1.000000, 74.932600},
  {"CaO", 20,1.000000,1.000000, 56.079400},
  {"Na2O", 11,2.000000,1.000000, 61.978940},
  {"K2O", 19,2.000000,1.000000, 94.203400},
  {"P2O5", 15,2.000000,5.000000, 141.944520},
  {"H2O", 1,2.000000,1.000000, 18.015200},
  {"CO2", 6,1.000000,2.000000, 44.009800},
  {"SO3", 16,1.000000,3.000000, 80.058200},
  {"Cl2O", 17,2.000000,1.000000, 86.905400},
  {"F2O", 9,2.000000,1.000000, 53.996206}
};

// methods ///////////////////////////////////////////

void Chem::parseFormula(char *formula,double *elarray) {
  int i;
  //first make sure array is zeroed
  for (i=0;i<nele;i++) elarray[i]=0.;
  i=strlen(formula);
  parseFormulaToken(formula,i,1.,elarray);
  return;
}
double Chem::mwt(double *elarray) {
  int i;
  double m;
  for (i=0,m=0.;i<nele;i++) {
    m+=elarray[i]*ele[i].aw;
  }
  return m;
}
double Chem::mwt(Stoich *st) {
  int i;
  double m;
  for (i=0,m=0.;i<st->nele;i++) {
    m+=st->stoich[i]*ele[st->ele[i]].aw;
  }
  return m;
}
void Chem::elToOx(double *elarray,double *oxarray){
  int i;
  double moles,temp;
  for (i=0;i<nox;i++) {
    // first find limiting 
    moles = elarray[8]/ox[i].nO;
    temp = elarray[ox[i].cation]/ox[i].ncat;
    if (temp<moles) moles=temp;
    // now subtract from array
    elarray[8] -= ox[i].nO*moles;
    elarray[ox[i].cation] -= ox[i].ncat*moles;
    oxarray[i] = moles;
  }
  return;
}
void Chem::oxToEl(double *oxarray,double *elarray) throw(PhaseError *) {
  int i;
  for (i=0;i<nele;i++) elarray[i]=0.;
  for (i=0;i<nox;i++) {
    if (oxarray[i]<0.) {
      PhaseError *e = 
	new PhaseError(INVALID,WARNING,"Chem",
		       "Negative oxide abundance in Chem::oxToEl()"
		       );
      throw e;
    }
      
    if (oxarray[i]>0.) {
      elarray[8] += ox[i].nO*oxarray[i];
      elarray[ox[i].cation] += ox[i].ncat*oxarray[i];
    }
  }
  return;
}
void Chem::oxMolToWt(double *oxarray) {
  int i;
  for (i=0;i<nox;i++) {
    oxarray[i]*=ox[i].mw;
  }
  return;
}
void Chem::oxWtToMol(double *oxarray) {
  int i;
  for (i=0;i<nox;i++) {
    oxarray[i]/=ox[i].mw;
  }
  return;
}
void Chem::parseFormulaToken(char *token,int len,double mult,
			     double *elarray) throw(PhaseError *){
  char *t2,*t3,*op,*cl,*mstr;
  // token2, token3, open, close, multiplier string
  int i,j,l1,l2,l3,dl,iele;
  double tmult;
  l1=l2=l3=0;
  t2=strchr(token,'('); //this ends first token
  if (t2!=NULL&&(t2-token)<len) {  //bracketted expression in range
    l1=t2-token;                   //first token ends at opening bracket
    op = t2;
    cl=strchr(op+1,')');
    do {
      op=strchr(op+1,'(');
      if (op!=NULL&&op<cl) {
	cl=strchr(op+1,')');
	if (cl==NULL||(cl-token)>len) {
	  char *errbuf = new char[100];
	  sprintf(errbuf,"Unbalanced brackets in %d char token %s",
		  len,token);
	  PhaseError *e = 
	    new PhaseError(INVALID,FATAL,"Chem",errbuf);
	  delete []errbuf;
	  throw e;
	}
      }
    } while (op!=NULL&&op<cl);
    t2+=1;  // past opening bracket
    l2=cl-t2;
    // get local multiplier
    mstr=cl+1;
    dl=0;
    while (isdigit(mstr[dl])||mstr[dl]=='.') {  // get multiplier length
      dl++;
    }
    if (dl) {
      sscanf(mstr,"%lf%*s",&tmult);       
    }
    else {
      tmult = 1.;
    }
    // set remaining token
    t3 = mstr+dl;
    l3 = len-(t3-token);
    if (l1) {
      parseFormulaToken(token,l1,mult,elarray);
    }
    if (l2) { // only bracketted expression will have local multiplier
      parseFormulaToken(t2,l2,mult*tmult,elarray);
    }
    if (l3) {
      parseFormulaToken(t3,l3,mult,elarray);
    }
  }
  else {  // no subtokens. Parse this token. 
    for (i=0;i<len;i++) {
      // parse element
      unsigned sl;
      if (!isupper(token[i])) {
	char *errbuf = new char[100];
	sprintf(errbuf,
		"Confused by %1c in %s at position %d. Should be capital"
		,token[i],token,i);
	PhaseError *e = 
	  new PhaseError(INVALID,FATAL,"Chem",errbuf);
	delete []errbuf;
	throw e;
      }
      sl = (islower(token[i+1]))? 2:1;
      for (j=0,iele=0;j<nele;j++) {  // look for symbol in element table
	if (strlen(ele[j].symbol)==sl) {  //length must match
	  if (memcmp(&token[i],ele[j].symbol,sl)==0) { // zero on match
	    iele=j;
	    break;
	  }
	}
      }
      if (!iele) {
	char *errbuf = new char[100];
	sprintf(errbuf,
		"Cant parse %d char token %s at position %d.",sl,token,i);
	PhaseError *e = 
	  new PhaseError(INVALID,FATAL,"Chem",errbuf);
	delete []errbuf;
	throw e;
      }
      i+=sl-1;
      dl=0;   // now get local multiplier for this element
      while (isdigit(token[i+dl+1])||token[i+dl+1]=='.') { 
	dl++;
      }
      if (dl) {
	sscanf(&token[i+1],"%lf%*s",&tmult);
	i += dl;
      }
      else {
	tmult = 1.;
      }
      // finally, add to array
      elarray[iele] += mult*tmult;
    }
  }
  return;
}
