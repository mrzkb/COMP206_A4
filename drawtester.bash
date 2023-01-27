#!/bin/bash
#Mira Kandlikar-Bloch mira.kandlikar-bloch@mail.mcgill.ca, 261035244

if [[ ! -f asciidraw.c ]]
then
	echo "Error cannot locate asciidraw.c"
	exit 1
fi

gcc -o asciidraw asciidraw.c -lm
rc=$?

if [[ $rc -ne 0 ]]
then
	echo "There were errors/warnings from gcc. rc = $rc"
	exit $rc
fi

echo " --- test case to draw simple lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,20 25,30
CHAR +
LINE 5,10 10,15
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,20 25,30
CHAR +
LINE 5,10 10,15
DISPLAY
END
ENDOFCMDS


echo " --- test case to draw multiple shapes, switching characters, etc --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 20,20 25,30
CHAR +
CIRCLE 25,25 10
DISPLAY
LINE 10,10 15,20
CHAR %
RECTANGLE 30,45 35,35
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 20,20 25,30
CHAR +
CIRCLE 25,25 10
DISPLAY
LINE 10,10 15,20
CHAR %
RECTANGLE 30,45 35,35
DISPLAY
END
ENDOFCMDS

echo " --- test case to draw vertical lines--"
echo '
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 10,5 10,50
CHAR $
LINE 20,10 20,30
DISPLAY 
END 
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS 
GRID 50 50
LINE 10,5 10,50
CHAR $
LINE 20,10 20,30
DISPLAY
END
ENDOFCMDS

echo "--test case to draw horizontal lines--"
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 5,20 25,20
LINE 9,8 16,8
CHAR !
LINE 13,33 33,33
CHAR $
LINE 20,2 39,2
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 40
LINE 5,20 25,20
LINE 9,8 16,8
CHAR !
LINE 13,33 33,33
CHAR $
LINE 20,2 39,2
DISPLAY
END
ENDOFCMDS

echo "--test case for command errors--"
echo '
./asciidraw <<ENDOFCMDS
RECTANGLE 4,15 20,1
CIRCLE 10,20 6
CHAR &
GRID 45 45
LINW 30,10 4,5
CIRCA 10,20 
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
RECTANGLE 4,15 20,1
CIRCLE 10,20 6
CHAR &
GRID 45 45
LINW 30,10 4,5
CIRCA 10,20
END
ENDOFCMDS

echo "--test case for symmetry of lines --"
echo '
./asciidraw <<ENDOFCMDS 
GRID 50 50
CHAR ^
LINE 5,3 7,33
CHAR "
LINE 45,2 48,48
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 50 50
LINE 45,12 5,10 
CHAR ^
LINE 5,3 6,33
CHAR "
LINE 45,2 48,48
DISPLAY
END
ENDOFCMDS

echo "--test case rectangle, line as a point (given points are the same)--"
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 30,24 30,24
CHAR $
LINE 8,10 8,10 
DISPLAY 
END 
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 30,24 30,24
CHAR $
LINE 8,10 8,10
DISPLAY
END
ENDOFCMDS

echo "--test case truncating figures--"
echo '
./asciidraw <<ENDOFCMDS 
GRID 45 45 
LINE 5,100 16,2
CHAR $
CIRCLE 50,17 20
CHAR (
CIRCLE 12,47 13
CHAR @
RECTANGLE 33,18 50,5
RECTANGLE 4000,1600 4300,800
DISPLAY 
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS 
GRID 45 45 
LINE 5,100 16,2
CHAR $
CIRCLE 50,17 20
CHAR (
CIRCLE 12,47 13
CHAR @
RECTANGLE 33,18 50,5
RECTANGLE 4000,1600 4300,800
DISPLAY 
END
ENDOFCMDS

echo "--test case rectangle as a line (both y coordinates are the same)--"
echo '
./asciidraw <<ENDOFCMDS 
GRID 70 42
RECTANGLE 3,40 19,40
CHAR %
RECTANGLE 18,17 52,17
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 70 42
RECTANGLE 3,40 19,40
CHAR %
RECTANGLE 18,17 52,17
DISPLAY
END
ENDOFCMDS

echo"--test case for overwriting figures--"
echo '
./asciidraw <<ENDOFCMDS
GRID 100 100
LINE 15,15 80,15
CHAR $
RECTANGLE 15,15 5,70
CHAR )
LINE 30,18 20,5
CHAR &
CIRCLE 20,5 12
DISPLAY 
END 
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 100 100
LINE 1,15 80,15
DISPLAY
CHAR $
RECTANGLE  5,70 15,15
DISPLAY
CHAR )
LINE 30,18 20,5
DISPLAY
CHAR &
CIRCLE 20,5 12
DISPLAY
END
ENDOFCMDS

