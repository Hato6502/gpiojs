/* Gpiojs Config
 * Set gpio No. and allocating key to the array.
 * format: {gpio No., key}
 * Regarding the keys, refer the Linux Input Subsystem.
 * At the end of array, insert the following NULL node: {BUTTONGPIO_NULL,0}. */

ButtonNode buttonList[] = {
	/* Example */
	/*{19,BTN_START},
	{26,BTN_A},
	{16,BTN_B},
	{20,BTN_X},
	{21,BTN_Y},*/
	{BUTTONGPIO_NULL,0},	/*End of list*/
};
