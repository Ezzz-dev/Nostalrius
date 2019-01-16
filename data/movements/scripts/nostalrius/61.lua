function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 32566, y = 31959, z = 01})
		Game.sendMagicEffect({x = 32487, y = 31928, z = 07}, 3)
	end
end
