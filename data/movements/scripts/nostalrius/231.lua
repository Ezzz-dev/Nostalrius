function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
		doRelocate(item:getPosition(),{x = 32918, y = 32072, z = 12})
		Game.sendMagicEffect({x = 32918, y = 32072, z = 11}, 13)
	end
end
