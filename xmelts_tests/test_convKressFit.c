#define REC 134

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  char line[REC];
  const char *infile  = "kress-FeFit.dat"; FILE *input;
  const char *outfile = "kress-FeFit.xml"; FILE *output;

  double t, p, logfo2, wt[24];
  int i, id, len;

  int nl = 0;
  int np = 0;

  printf("Attempting to open input file %s for analysis.\n", infile);
  if ((input = fopen (infile, "r")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  printf("Attempting to open output file %s for analysis.\n", outfile);
  if ((output = fopen (outfile, "w")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  fprintf(output, "<LEPRdatabase>\n");
  id = 90000;

  for (;;) {
    if (fgets(line, REC, input) == NULL) break;
    id++;
    
    len = strlen(line); line[len-2] = '\0'; 
    
    fprintf(output, "<experiment>\n");
    fprintf(output, "<number>%d</number>\n", id);
    fprintf(output, "<name>%s</name>\n", line);
    fprintf(output, "<author>%s</author>\n", "Kress and Carmichael (1991)");
    fprintf(output, "<lab>%d</lab>\n", 0);
    
    fgets(line, REC, input);
    fprintf(output, "<t>");      for (i=0; i<10; i++) fprintf(output,"%c", line[   i]); fprintf(output, "</t>\n");
    fprintf(output, "<p>");                           fprintf(output,"0.0001"        ); fprintf(output, "</p>\n");
    fprintf(output, "<fo2val>"); for (i=0; i<10; i++) fprintf(output,"%c", line[20+i]); fprintf(output, "</fo2val>\n");
    
    fprintf(output, "<liquid>\n");

    fgets(line, REC, input);
    fprintf(output, "<sio2>");  for (i=0; i<10; i++) fprintf(output,"%c", line[   i]); fprintf(output, "</sio2>\n");
    fprintf(output, "<tio2>");  for (i=0; i<10; i++) fprintf(output,"%c", line[10+i]); fprintf(output, "</tio2>\n");
    fprintf(output, "<al2o3>"); for (i=0; i<10; i++) fprintf(output,"%c", line[20+i]); fprintf(output, "</al2o3>\n");
    fprintf(output, "<fe2o3>"); for (i=0; i<10; i++) fprintf(output,"%c", line[30+i]); fprintf(output, "</fe2o3>\n");
    fprintf(output, "<cr2o3>"); for (i=0; i<10; i++) fprintf(output,"%c", line[40+i]); fprintf(output, "</cr2o3>\n");
    fprintf(output, "<feo>");   for (i=0; i<10; i++) fprintf(output,"%c", line[50+i]); fprintf(output, "</feo>\n");
    fprintf(output, "<mno>");   for (i=0; i<10; i++) fprintf(output,"%c", line[60+i]); fprintf(output, "</mno>\n");
    fprintf(output, "<mgo>");   for (i=0; i<10; i++) fprintf(output,"%c", line[70+i]); fprintf(output, "</mgo>\n");
    
    fgets(line, REC, input);
    fprintf(output, "<nio>");   for (i=0; i<10; i++) fprintf(output,"%c", line[   i]); fprintf(output, "</nio>\n");
    fprintf(output, "<coo>");   for (i=0; i<10; i++) fprintf(output,"%c", line[10+i]); fprintf(output, "</coo>\n");
    fprintf(output, "<cao>");   for (i=0; i<10; i++) fprintf(output,"%c", line[20+i]); fprintf(output, "</cao>\n");
    fprintf(output, "<na2o>");  for (i=0; i<10; i++) fprintf(output,"%c", line[30+i]); fprintf(output, "</na2o>\n");
    fprintf(output, "<k2o>");   for (i=0; i<10; i++) fprintf(output,"%c", line[40+i]); fprintf(output, "</k2o>\n");
    fprintf(output, "<p2o5>");  for (i=0; i<10; i++) fprintf(output,"%c", line[50+i]); fprintf(output, "</p2o5>\n");

    fprintf(output, "</liquid>\n");
    
    fprintf(output, "<phase type=\"O2\"></phase>\n");
    
    fprintf(output, "</experiment>\n");
  }
  
  fprintf(output, "</LEPRdatabase>\n");
  exit(0);   
}
