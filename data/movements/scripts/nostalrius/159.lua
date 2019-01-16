function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
		doRelocate(item:getPosition(),{x = 32615, y = 32483, z = 09})
		Game.sendMagicEffect({x = 32615, y = 32483, z = 09}, 13)
	end
end
