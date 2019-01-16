local ropeSpots = {
	386, 421
}

function onCastSpell(creature, variant)
	local position = creature:getPosition()
	position:sendMagicEffect(CONST_ME_POFF)

	local tile = Tile(position)
	if table.contains(ropeSpots, tile:getGround():getId()) then
		tile = Tile(position:moveUpstairs())
		if tile then
			creature:teleportTo(position)
			position:sendMagicEffect(CONST_ME_TELEPORT)
		else
			creature:sendCancelMessage(RETURNVALUE_NOTENOUGHROOM)
		end
	else
		creature:sendCancelMessage(RETURNVALUE_NOTPOSSIBLE)
		return false
	end
	return true
end