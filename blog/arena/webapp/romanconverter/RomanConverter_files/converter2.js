 /*************************************************************
 *         Thesh Ooter's Roman Numeral Converter V2.0         *
 *                                                            *
 * For converting between integers and Roman Numerals as well *
 * as checking the validity of Roman Numerals. By convering   *
 * a roman numeral into an integer with strict set to false   *
 * and then convering that back into a roman, you can attempt *
 * to correct any mistakes in the roman numeral. However, I   *
 * can't guarantee that it will fix your specific mistake.    *
 *                                                            *
 * This script should work with any web browser that supports *
 * ECMAScript V3 (specifically try and catch) and the DOM2    *
 * method 'getElementById()'; this has been tested to work    *
 * in IE5.5+ and Mozilla 1.7 (although it should work with    *
 * earlier versions, it is untesed) as well as Opera 7.5. I   *
 * do not have access to a KHTML based browser like Safari or *
 * Konqueror, but I expect this to work in recent versions.   *
 *                                                            *
 * This script was written by Scott Hulberg (AKA Thesh Ooter) *
 * scott_hulberg@yahoo.com                                    *
 *************************************************************/

// Stores the values of the roman numerals
var romans = new Object();
romans["I"] = 1;
romans["V"] = 5;
romans["X"] = 10;
romans["L"] = 50;
romans["C"] = 100;
romans["D"] = 500;
romans["M"] = 1000;

// Used for converting an integer to a roman numeral
var getChar = new Array("I", "V", "X", "L", "C", "D", "M");

 /***********************************
 * These next two functions are     *
 * used to test for errors in the   *
 * input                            *
 ***********************************/

function testRom(rString) {
	var check = rString.match(/[IVXLCDM]+/);
	if ((check == null) || (check[0] != rString))
		throw new TypeError("Not a Roman Numeral");
}

function checkRom(roman) { // Invoked only when strict is set to true in the next function
	var romregex = /M*(?:(?:CM|CD)|(?:D?C{0,3}))?(?:(?:XC|XL)|(?:L?X{0,3}))?(?:(?:IX|IV)|(?:V?I{0,3}))?/;
	if (roman != roman.match(romregex)[0])
		throw new TypeError("Not a Properly Formed Numeral");
}
// This function converts a roman numeral to an integer
function parseRomanToInt(rNumb, strict) {
	var intNumb = 0;
	rNumb = rNumb.toString().toUpperCase();
	void testRom(rNumb);
	if (strict) void checkRom(rNumb);
	for (var i=0; i<rNumb.length; i++) {
		var currentR = rNumb.charAt(i);
		var nextR = rNumb.charAt(i + 1);
		if (romans[currentR] < romans[nextR]) {
			intNumb += (romans[nextR] - romans[currentR]);
			i++;
		}
		else 
			intNumb += romans[currentR];
	}
	return Number(intNumb);
}

 /***********************************
 * The next two functions are used  *
 * for converting an integer into a *
 * roman numeral.                   *
 ***********************************/

function ints(pos, iValue) {
	var charValue = "";
	var s = 2*pos;
	if (pos > 2) {
		for (var i=0; i<iValue*Math.pow(10,(pos-3)); i++)
			charValue += "M";
	}
	else if (iValue < 4) {
		for (var i=0; i<iValue; i++)
			charValue += getChar[s];
	}
	else if (iValue == 4) charValue = getChar[s] + getChar[s+1];
	else if (iValue < 9) {
		charValue = getChar[s+1];
		for (var i=0; i<iValue-5; i++)
			charValue += getChar[s];
	}
	else if (iValue == 9) charValue = getChar[s] + getChar[s+2];
	
	return String(charValue);
}

function parseIntToRoman(intNumb) {
	var romNumb;
	var romNumbFinal = "";
	
	if (parseInt(intNumb, 10) != intNumb) throw new TypeError("Not an Integer");
	else intNumb = parseInt(intNumb, 10); // Make sure there are no extra characters

	if (intNumb < 1) throw new RangeError("Not a Positive Integer");
	
	intNumb = intNumb.toString();
	for (var k=0; k<intNumb.length; k++) {
		var currentI = parseInt(intNumb.charAt(intNumb.length - (k + 1)));
		romNumb = romNumbFinal;
		romNumbFinal = ints(k, currentI) + romNumb;
	}
	return String(romNumbFinal);
}
