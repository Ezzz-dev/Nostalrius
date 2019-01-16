local food = {
	3577, 3582, 3585, 3592, 3602
}

function onCastSpell(creature, variant)
	creature:addItem(food[math.random(#food)])
	creature:getPosition():sendMagicEffect(CONST_ME_MAGIC_GREEN)
	return true
end