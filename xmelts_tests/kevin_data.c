#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <my_global.h>
#include <mysql.h>

int data (const char *phase, const char *component, double *params) {
  int i;
  MYSQL *conn;
  MYSQL_RES *mysqlResult;
  MYSQL_ROW mysqlRow;
  char select[100];
  
  conn = mysql_init(NULL);
  if (conn == NULL) return FALSE;
  if(mysql_real_connect(conn, "public.ofm-research.org", "webauthor", "Fo90Fa10", "stixrude", 0, NULL, 0) == NULL) return FALSE;
  
  sprintf(select, "SELECT * FROM endmembers WHERE phase = '%s' AND component = '%s'", phase, component);
  if(mysql_query(conn, select)) return FALSE;
  mysqlResult = mysql_store_result(conn);
  if(mysqlResult == NULL) return FALSE;
  if(mysql_num_rows(mysqlResult) == 0) return FALSE;
  while ((mysqlRow = mysql_fetch_row(mysqlResult))) {
  
    params[0] = atof(mysqlRow[ 4])*1000.0;  /* a0     */
    params[1] = atof(mysqlRow[ 5]);         /* n      */
    params[2] = atof(mysqlRow[ 6])/10.0;    /* v0     */
    params[3] = atof(mysqlRow[ 7])*10000.0; /* k00    */
    params[4] = atof(mysqlRow[ 8]);         /* k0p    */
    params[5] = atof(mysqlRow[ 9]);         /* theta0 */
    params[6] = atof(mysqlRow[10]);         /* gamma0 */
    params[7] = atof(mysqlRow[11]);         /* q      */
    params[8] = atof(mysqlRow[12]);         /* refS   */
  
  }
  
  mysql_free_result(mysqlResult);
  mysql_close(conn);
  
  return TRUE;

}
