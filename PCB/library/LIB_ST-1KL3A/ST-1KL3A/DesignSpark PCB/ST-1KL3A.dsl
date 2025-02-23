SamacSys ECAD Model
876211/1372192/2.50/2/3/Phototransistor

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c119.2_h65"
		(holeDiam 0.65)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.192) (shapeHeight 1.192))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.192) (shapeHeight 1.192))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "ST1KL3A" (originalName "ST1KL3A")
		(multiLayer
			(pad (padNum 1) (padStyleRef c119.2_h65) (pt 0.000, 0.000) (rotation 90))
			(pad (padNum 2) (padStyleRef c119.2_h65) (pt 2.540, 0.000) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 1.270, 0.000) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1.43 0) (pt -1.43 0) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(arc (pt 1.27, 0) (radius 2.7) (startAngle 180) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 3.97 0) (pt 3.97 0) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(arc (pt 1.27, 0) (radius 2.7) (startAngle .0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt -2.43 0) (pt -2.43 0) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(arc (pt 1.27, 0) (radius 3.7) (startAngle 180) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 4.97 0) (pt 4.97 0) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(arc (pt 1.27, 0) (radius 3.7) (startAngle .0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.43 0) (pt -1.43 0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 1.27, 0) (radius 2.7) (startAngle 180) (sweepAngle 180.0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 3.97 0) (pt 3.97 0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 1.27, 0) (radius 2.7) (startAngle .0) (sweepAngle 180.0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -2.1 0) (pt -2.1 0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -2.05, 0) (radius 0.05) (startAngle 180) (sweepAngle 180.0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -2 0) (pt -2 0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -2.05, 0) (radius 0.05) (startAngle .0) (sweepAngle 180.0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -2.1 0) (pt -2.1 0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -2.05, 0) (radius 0.05) (startAngle 180) (sweepAngle 180.0) (width 0.2))
		)
	)
	(symbolDef "ST-1KL3A" (originalName "ST-1KL3A")

		(pin (pinNum 1) (pt 0 mils -600 mils) (rotation 90) (pinLength 100 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 5 mils -600 mils) (rotation 90]) (justify "LowerLeft") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils 0 mils) (rotation 270) (pinLength 100 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 5 mils 0 mils) (rotation 90]) (justify "UpperLeft") (textStyleRef "Default"))
		))
		(line (pt -100 mils -200 mils) (pt -100 mils -400 mils) (width 20 mils))
		(line (pt -100 mils -250 mils) (pt 0 mils -150 mils) (width 6 mils))
		(line (pt 0 mils -450 mils) (pt 0 mils -500 mils) (width 6 mils))
		(line (pt 0 mils -150 mils) (pt 0 mils -100 mils) (width 6 mils))
		(line (pt -100 mils -350 mils) (pt 0 mils -450 mils) (width 6 mils))
		(line (pt -300 mils -80 mils) (pt -200 mils -180 mils) (width 6 mils))
		(line (pt -360 mils -140 mils) (pt -260 mils -240 mils) (width 6 mils))
		(arc (pt -50 mils -300 mils) (radius 158.114 mils) (startAngle 0) (sweepAngle 360) (width 10  mils))
		(poly (pt -70 mils -400 mils) (pt -50 mils -380 mils) (pt -30 mils -420 mils) (pt -70 mils -400 mils) (width 10  mils))
		(poly (pt -320 mils -210 mils) (pt -290 mils -180 mils) (pt -260 mils -240 mils) (pt -320 mils -210 mils) (width 10  mils))
		(poly (pt -260 mils -150 mils) (pt -230 mils -120 mils) (pt -200 mils -180 mils) (pt -260 mils -150 mils) (width 10  mils))
		(attr "RefDes" "RefDes" (pt 150 mils -250 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "ST-1KL3A" (originalName "ST-1KL3A") (compHeader (numPins 2) (numParts 1) (refDesPrefix Q)
		)
		(compPin "1" (pinName "E") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "C") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "ST-1KL3A"))
		(attachedPattern (patternNum 1) (patternName "ST1KL3A")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "RS Part Number" "6051442")
		(attr "RS Price/Stock" "https://uk.rs-online.com/web/p/products/6051442")
		(attr "Manufacturer_Name" "KODENSHI")
		(attr "Manufacturer_Part_Number" "ST-1KL3A")
		(attr "Description" "high-sensitivity NPN silicon phototransistor VCEO 40v VECO 6v IC 50mA TO-18 can ")
		(attr "Datasheet Link" "https://www.kodenshi.co.jp/files/product/ST-1KL3A.pdf")
		(attr "Height" "6.7 mm")
	)

)
