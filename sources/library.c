/* ================================================================================== */
/* ================================================================================== */
/* Public interface for libMelts                                                      */
/* ================================================================================== */
/* ================================================================================== */

/* ================================================================================== */
/* Returns oxide names and order for bulk composition vector                          */
/* Output:                                                                            */
/*   oxideNames - array of oxide names, ordered as in MELTS                           */
/* ================================================================================== */

void meltsGetOxideNames(char **oxideNames);        

/* ================================================================================== */
/* Returns phase names and order for output properties vector                         */
/* Output:                                                                            */
/*   phaseNames - array of phase names, ordered as in MELTS                           */
/*              - first name is always "system"                                       */
/* ================================================================================== */

void meltsGetPhaseNames(char **phaseNames);        

/* ================================================================================== */
/* MELTS processing call       							      */
/* Input:           								      */
/*   nodeIndex       - Index number of node (must be unique)                          */
/*   mode            - = 0, continuing run, pickup from last successful call          */
/*                     = 1, initial or reset run.  System is reset to input           */
/*                          conditions, temperature is input in place of enthalpy     */
/*   enthalpy        - Total enthalpy in J of the node, if mode =0                    */
/*                     Temperature of the node (K), if mode = 1                       */
/*   pressure        - Pressure in bars of the node                                   */
/*   bulkComposition - Bulk composition in grams of oxides                            */ 
/* Output:                                                                            */
/*   outMask         - Bit mask; 0 = phase absent, 1 = phase present                  */
/*                   - first bit is always on, as system properties fill the first    */
/*                     column of phase Properties                                     */
/*   iterations      - Number of quadratic iterations                                 */
/*   status          - 0 = success,                                                   */
/*                   - 1 - 100 non fatal error condition                              */
/*                   - > 100 fatal error condition                                    */
/*   phaseProperties - 2-d array, one column per phase, row length is fixed as        */
/*                     G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2,    */
/*                     oxide compositions in order of meltsGetOxideNames in grams     */
/*                     The first column is always the properties of the system        */ 
/* ================================================================================== */

void meltsProcess(int *nodeIndex, int *mode, double *enthalpy, double *pressure, 
         double *bulkComposition, int *outMask, int *iterations, int *status, 
	 double *phaseProperties);
		  
/* ================================================================================== */
/* Returns explanatory string associated with input status                            */
/* Input:                                                                             */
/*   status      - status integer returned from meltsProcess                          */
/* Output:                                                                            */
/*   errorString - character string describing status                                 */
/* ================================================================================== */

void meltsGetErrorString(int *status, char *errorString);

/* ================================================================================== */
/* Retrieves properties of solid and liquid phases                                    */
/* Input:           								      */
/*   nodeIndex       - Index number of node (must be unique)                          */
/*   phaseIndex      - string as returned from meltsGetPhaseNames                     */
/*   temperature     - Temperature in Kelvins of the node                             */
/*   pressure        - Pressure in bars of the node                                   */
/*   bulkComposition - Bulk composition in grams of oxides                            */ 
/* Output:                                                                            */
/*   phaseProperties - 1-d array, properties in the order                             */
/*                     G, H, S, V, Cp, dCpdT, dVdT, dVdP, d2VdT2, d2VdTdP, d2VdP2     */
/* ================================================================================== */

void meltsGetPhaseProperties(int *nodeIndex, char *phaseName, double *temperature, 
         double *pressure, double *bulkComposition, double *phaseProperties);
