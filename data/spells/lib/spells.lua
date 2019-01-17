function healingFormula(level, maglevel, base, variation, value_min, value_max)
	local value = 3 * maglevel + (2 * level)
	
	if value_min ~= nil and value <= value_min then
		value = value_min
	end
	
	if value_max ~= nil and value >= value_max then
		value = value_max
	end
	
	local min = value * (base - variation) / 100
	local max = value * (base + variation) / 100
	return min, max
end

function damageFormula(level, maglevel, base, variation)
	local value = 3 * maglevel + (2 * level)

	local min = value * (base - variation) / 100
	local max = value * (base + variation) / 100
	return min, max
end

function computeFormula(level, maglevel, base, variation)
	local damage = base
	if variation > 0 then
		damage = math.random(-variation, variation) + damage
	end
	
	local level_formula = 2 * level
	local magic_formula = 3 * maglevel + level_formula 

	return magic_formula * damage / 100
end

---------------------------------------------------------------------------------------

AREA_WAVE3 = {
{1, 1, 1},
{1, 1, 1},
{0, 3, 0}
}

AREA_WAVE4 = {
{1, 1, 1, 1, 1},
{0, 1, 1, 1, 0},
{0, 1, 1, 1, 0},
{0, 0, 3, 0, 0}
}

AREA_WAVE6 = {
{0, 0, 0, 0, 0},
{0, 1, 3, 1, 0},
{0, 0, 0, 0, 0}
}

AREA_SQUAREWAVE5 = {
{1, 1, 1},
{1, 1, 1},
{1, 1, 1},
{0, 1, 0},
{0, 3, 0}
}

AREA_SQUAREWAVE6 = {
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0}
}

AREA_SQUAREWAVE7 = {
{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0}
}

--Diagonal waves
AREADIAGONAL_WAVE4 = {
{0, 0, 0, 0, 1, 0},
{0, 0, 0, 1, 1, 0},
{0, 0, 1, 1, 1, 0},
{0, 1, 1, 1, 1, 0},
{1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 0, 3}
}

AREADIAGONAL_SQUAREWAVE5 = {
{1, 1, 1, 0, 0},
{1, 1, 1, 0, 0},
{1, 1, 1, 0, 0},
{0, 0, 0, 1, 0},
{0, 0, 0, 0, 3}
}

AREADIAGONAL_WAVE6 = {
{0, 0, 1},
{0, 3, 0},
{1, 0, 0}
}

--Beams
AREA_BEAM1 = {
{3}
}

AREA_BEAM5 = {
{1},
{1},
{1},
{1},
{3}
}

AREA_BEAM7 = {
{1},
{1},
{1},
{1},
{1},
{1},
{3}
}

AREA_BEAM8 = {
{1},
{1},
{1},
{1},
{1},
{1},
{1},
{3}
}

--Diagonal Beams
AREADIAGONAL_BEAM5 = {
{1, 0, 0, 0, 0},
{0, 1, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 1, 0},
{0, 0, 0, 0, 3}
}

AREADIAGONAL_BEAM7 = {
{1, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 0, 3}
}

--Circles
AREA_CIRCLE2X2 = {
{0, 1, 1, 1, 0},
{1, 1, 1, 1, 1},
{1, 1, 3, 1, 1},
{1, 1, 1, 1, 1},
{0, 1, 1, 1, 0}
}

AREA_CIRCLE3X3 = {
{0, 0, 1, 1, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 3, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1},
{0, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 0, 0}
}

-- Crosses
AREA_CROSS1X1 = {
{0, 1, 0},
{1, 3, 1},
{0, 1, 0}
}

AREA_CIRCLE5X5 = {
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}
}

--Squares
AREA_SQUARE1X1 = {
{1, 1, 1},
{1, 3, 1},
{1, 1, 1}
}

-- Walls
AREA_WALLFIELD = {
{1, 1, 3, 1, 1}
}

AREADIAGONAL_WALLFIELD = {
{0, 0, 0, 0, 1},
{0, 0, 0, 1, 1},
{0, 1, 3, 1, 0},
{1, 1, 0, 0, 0},
{1, 0, 0, 0, 0},
}