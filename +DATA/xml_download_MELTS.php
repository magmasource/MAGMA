<?php
$hostname_connMELTS = "ofm-research.org";
$database_connMELTS = "MELTS";
$username_connMELTS = "webauthor";
$password_connMELTS = "Fo90Fa10";
$connMELTS = mysql_pconnect($hostname_connMELTS, $username_connMELTS, $password_connMELTS) or trigger_error(mysql_error(),E_USER_ERROR); 

set_time_limit(600);

$fname = tempnam(".", "melts_download.xml");
$outFile = fopen($fname, "w");

mysql_select_db($database_connMELTS, $connMELTS);

fwrite($outFile, "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n");
fwrite($outFile, "<LEPERdatabase>\n");

for ($nl=0; $nl<2494; $nl++) {

  $query_rsLiquid = sprintf("SELECT * FROM liquid WHERE liquid_id = %d", $nl+1);
  $rsLiquid = mysql_query($query_rsLiquid, $connMELTS) or die(mysql_error());
  $row_rsLiquid = mysql_fetch_array($rsLiquid, MYSQL_BOTH);
  $totalRows_rsLiquid = mysql_num_rows($rsLiquid);
 
  $query_rsExperiment = sprintf("SELECT * FROM experiment WHERE experiment_id = %s", $row_rsLiquid['experiment_id']);
  $rsExperiment = mysql_query($query_rsExperiment, $connMELTS) or die(mysql_error());
  $row_rsExperiment = mysql_fetch_array($rsExperiment);
  $totalRows_rsExperiment = mysql_num_rows($rsExperiment);
 
  $query_rsAuthor = sprintf("SELECT * FROM author WHERE author_id = %s", $row_rsLiquid['author_id']);
  $rsAuthor = mysql_query($query_rsAuthor, $connMELTS) or die(mysql_error());
  $row_rsAuthor = mysql_fetch_assoc($rsAuthor);
  $totalRows_rsAuthor = mysql_num_rows($rsAuthor);
 
  fwrite($outFile, "<experiment>\n");
  
  $LEPRnum = 100000 + $nl;
 
  fwrite($outFile, "<number>" . $LEPRnum                                                    . "</number>\n");
  fwrite($outFile, "<name>"   . "MELTS/pMELTS"                                              . "</name>\n");
  fwrite($outFile, "<author>" . $row_rsAuthor['first'] . " (" . $row_rsAuthor['date'] . ")" . "</author>\n");
  fwrite($outFile, "<lab>"    . "Unknown"                                                   . "</lab>\n");
  fwrite($outFile, "<t>"      . $row_rsExperiment['t']                                      . "</t>\n");
  fwrite($outFile, "<p>"      . $row_rsExperiment['p']/10000.0                              . "</p>\n");
  fwrite($outFile, "<fo2val>" . $row_rsExperiment['log_fo2']                                . "</fo2val>\n");
  		
  fwrite($outFile, "<liquid>\n");
  $nComp = count($row_rsLiquid)/2 - 1;
  for ($n=2; $n < $nComp; $n++) if (($row_rsLiquid[$n] != "") && ($row_rsLiquid[$n] != 0.0)) {
    fwrite($outFile, "<" . substr(mysql_field_name($rsLiquid, $n),3) . ">" . $row_rsLiquid[$n] . "</" . substr(mysql_field_name($rsLiquid, $n),3) . ">\n");
  }
  fwrite($outFile, "</liquid>\n");
 
  $rs1 = mysql_list_tables( $database_connMELTS );
  for ($num=0; $num < mysql_num_rows( $rs1 ); $num++) { 
    $nm1 = mysql_tablename( $rs1, $num);
	if (   !(strcmp($nm1, "experiment") == 0)
	    && !(strcmp($nm1, "liquid")     == 0)
	    && !(strcmp($nm1, "solid")      == 0)
	    && !(strcmp($nm1, "author")     == 0) ) {
      $query_rsPhase = sprintf("SELECT * FROM %s WHERE liquid_id = %d", $nm1, $nl+1);
      $rsPhase = mysql_query($query_rsPhase, $connMELTS) or die(mysql_error());
      $row_rsPhase = mysql_fetch_array($rsPhase, MYSQL_NUM);
      $totalRows_rsPhase = mysql_num_rows($rsPhase);

	  if ($totalRows_rsPhase != 0) {
        $nComp = count($row_rsPhase) - 1;
		
		for ($row=0; $row<$totalRows_rsPhase; $row++) {
		  fwrite($outFile, "<phase type=\"" . strtolower($nm1) . "\">\n");
		
		  for ($n=2; $n < $nComp; $n++) if (($row_rsPhase[$n] != "") && ($row_rsPhase[$n] != 0.0)) {
            fwrite($outFile, "<" . substr(mysql_field_name($rsPhase,  $n),3) . ">" . $row_rsPhase[$n] . "</" . substr(mysql_field_name($rsPhase,  $n),3) . ">\n");
          }
		 		  
          if (($row+1) < $totalRows_rsPhase) $row_rsPhase = mysql_fetch_array($rsPhase, MYSQL_NUM);
		  
		  fwrite($outFile, "</phase>\n");
		}
	  }
	  	  
	  mysql_free_result($rsPhase);
	} 
  }
  
  mysql_free_result($rsLiquid);
  mysql_free_result($rsExperiment);
  mysql_free_result($rsAuthor);
  
  fwrite($outFile, "</experiment>\n");
}

fwrite($outFile, "</LEPERdatabase>\n");
fclose($outFile);

exit;
?>
